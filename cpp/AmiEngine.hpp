/**
 * @file AmiEngine.hpp
 * @brief Attention Mesh Index Transmission (AMI) 核心変速エンジン
 * @copyright Copyright (c) 2026 Kenji Igarashi
 * LinkedIn https://www.linkedin.com/in/kenjiigarashi
 * Licensed under the MIT License.
 * 
 * CUI（ターミナル）の標準入力から流れてくる「質問」の塊ごとに、
 * 同じモデルの量子化違い（2bit / 4bit / 16bit）のギアを順番に試していき、
 * 各ギアに設定された【鉄壁の合格スコア（テーブル保持）】を超えた瞬間に、
 * AIがその階層で弾き出した「回答文字列（一言から長文まで）」を、
 * 「出力 ➡️ クリア ➡️ 次のトークン」のストリーミング循環で安全に吐き出し、
 * 残りの重たい上位ギアの計算をすべてばっさりスキップする、世界最軽量の変速推論エンジン（PoC）です。
 * 
 * 【MITライセンス（日本語要約と権利表記）】
 * このソフトウェアはMITライセンスのもとで無償で公開されています。
 * 商用利用、改造、再配布、クローズドな世界での利用もすべて自由です！
 * ただし、この著作権表記とライセンスの全文をコードに残してください。
 * 
 * For each chunk of "questions" flowing from the CUI (terminal) standard input,
 * this engine sequentially tests different quantization gears (2-bit / 4-bit / 16-bit) of the same model.
 * The very moment it exceeds the [Ironclad Passing Score (held in a static table)] configured for each gear,
 * the AI safely flushes the generated "response string (from a single word to long text)" 
 * via a streaming loop of "Output ➡️ Clear ➡️ Next Token".
 * By completely skipping all subsequent heavy calculations of higher gears, 
 * this stands as the world's most lightweight multi-gear inference engine (PoC).
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 */

#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include "ggml.h" 
#include "llama.h"
// ========================================================
#define AMI_DEBUG_MODE 1  // 🌟 【本番切り替えスイッチ！】
                          // 1 にするとデバッグログ全開（ロマンモード）
                          // 0 にするとログを消して爆速化（製品モード）
// ========================================================

// 🛡️ スイッチが0（オフ）の時は、DEBUGログの出力を完全に「無効（消去）」にする魔法のマクロ
#if AMI_DEBUG_MODE
  #define AMI_LOG(x) x
#else
  #define AMI_LOG(x) // スイッチオフの時は、このログの計算ごと完全に消滅させる！
#endif


extern "C" const struct llama_vocab * llama_model_get_vocab(const struct llama_model * model);

/**
 * @struct LLMGear
 * @brief 各部屋（変速ギア）のモデルと計算部屋をひとまとめにする構造体
 */
struct LLMGear {
    int id;                          ///< ギア番号（0=Q2の部屋, 1=Q4の部屋, 2=高ビットの部屋）
    std::string model_path;          ///< 量子化されたモデルファイルがある場所（パス）
    float threshold;                 ///< この部屋を合格（大正解）にするための類似度の閾値
    struct llama_model* model = nullptr;    ///< AIの脳みそ本体（確定行列が詰まっている）
    struct llama_context* ctx = nullptr;    ///< 記憶や計算をリアルタイムに処理するお部屋（コンテキスト）
};
/**
 * @class AmiEngine
 * @brief クラウドコードを涙目にする、完全クローズド・極限最適化LLMトランスミッションエンジン
 */
class AmiEngine {
private:
    std::vector<LLMGear> gear_table;     ///< 3つのギア（Q2, Q4, 高ビット）を仲良く保持するテーブル
    int32_t total_history_coord = 0;    ///< 会話の歴史（記憶）が今どこまで進んだかを示す大切な「座標」
    std::vector<float> target_vector = {0.1f}; ///< 質問がどのクラスターの場所にあるかを示すインデックス
    std::chrono::_V2::system_clock::time_point query_start_time = std::chrono::high_resolution_clock::now();

    /**
     * @brief 2つの数字の並び（ベクトル）がどれくらい同じ方向（クラスター）を向いているか計算する
     * @param vecA 部屋が必死に導き出したナンバーワンの気配（ロジット）
     * @param vecB 私たちが「いぬ」などで指定したターゲットの確定座標
     * @param dim 全体の語彙数（空間の解像度のこと）
     * @return コサイン類似度（0.0〜1.0で、1に近いほど大正解！）
     */
    float calculate_cosine_similarity(const float* vecA, const float* vecB, size_t dim) {
        float dot_product = 0.0f, normA = 0.0f, normB = 0.0f;
        for (size_t i = 0; i < dim; ++i) {
            dot_product += vecA[i] * vecB[i];
            normA += vecA[i] * vecA[i];
            normB += vecB[i] * vecB[i];
        }
        return (normA == 0.0f || normB == 0.0f) ? 0.0f : (dot_product / (std::sqrt(normA) * std::sqrt(normB)));
    }

    void llama_batch_add(struct llama_batch & batch, llama_token id, llama_pos pos, const std::vector<llama_seq_id> & seq_ids, bool logits) {
        batch.token[batch.n_tokens] = id;
        batch.pos[batch.n_tokens] = pos;
        batch.n_seq_id[batch.n_tokens] = seq_ids.size();
        for (size_t i = 0; i < seq_ids.size(); ++i) batch.seq_id[batch.n_tokens][i] = seq_ids[i];
        batch.logits[batch.n_tokens] = logits;
        batch.n_tokens++;
    }

public:
    // ポインタの二重解放によるクラッシュを防ぐ
    AmiEngine(const AmiEngine&) = delete;
    AmiEngine& operator=(const AmiEngine&) = delete;

    /**
     * @brief コンストラクタ：エンジンの起動時にすべてのギア（Q2, Q4, 高ビット）を一括でロードする
     */
    AmiEngine() {
        llama_backend_init();
        
        // 🛠️ テーブル保持による静的な変速ギア定義
        //  ベースが同じ量子化モデルを指定下さい。（言語モデルの宇宙は同じにしないと動きません）
        gear_table = {
            {0, "models/Meta-Llama-3.1-8B-Instruct-IQ2_M.gguf",   1.0f}, // 2ビット：大雑把だけど爆速の部屋
            {1, "models/Meta-Llama-3.1-8B-Instruct-Q4_K_M.gguf", 0.9f}, // 4ビット：動物クラスターの特定の場所が分かる部屋
            {2, "models/Meta-Llama-3.1-8B-Instruct-Q8_0.gguf",   -1.0f}  // 高ビット：高画質・品質のよいのコンパス（ミニPCでの最後の砦）
            // {0, "models/gemma-2-2b-it-Q2_K.gguf",   1.0f}, // 2ビット：大雑把だけど爆速の部屋
            // {1, "models/gemma-2-2b-it-Q4_K_M.gguf", 0.9f}, // 4ビット：動物クラスターの特定の場所が分かる部屋
            // {2, "models/gemma-2-2b-it.F16.gguf",    0.0f}  // F16：最高画質・絶対のコンパス（最後の砦）        
        };

        for (auto& gear : gear_table) {
            gear.model = llama_model_load_from_file(gear.model_path.c_str(), llama_model_default_params());
            if (!gear.model) {
                std::cerr << "【エラー】モデルファイルが読み込めなかった: " << gear.model_path << std::endl;
                continue;
            }
            //gear.ctx = llama_init_from_model(gear.model, llama_context_default_params());
            llama_context_params ctx_params = llama_context_default_params();
            // ここはそれぞれのPCにあわせてください。
            ctx_params.n_ctx = 256; // 🌟 1つの部屋の計算スペースを256（軽量化）に制限！
            ctx_params.n_batch  = 8;   // 🌟 一度に計算する塊を 8 に制限（超軽量化！）
            ctx_params.n_ubatch = 8;   // 🌟 ミニPCのVulkanに最適化

            // 🛠️ 32GB環境向け：超爆速・常駐トランスミッションセッティング
            // ctx_params.n_ctx   = 1024; // 🌟 記憶の部屋を1024マス（4倍）に拡張！長文の文脈も完全に保持
            //   16GB環境の「256マス」から「1024マス」へ4倍に拡張することで、複数ターンの複雑な対話の文脈（KVキャッシュ）を、1ミリの記憶喪失も起こさずに完璧にホールドできるようになります。
            //   これだけ増やしても、消費するKVキャッシュ容量は各部屋数十メガバイト程度。32GBのRAM空間にとっては、かすり傷（ノーダメージ）です。
            //
            // ctx_params.n_batch = 32;   // 🌟 一度に処理する塊を「32」に引き上げ、Vulkanの並列演算をフル駆動！
            //   一度に計算する塊を「8」から「32」に引き上げることで、GMKtec M7の内蔵グラフィックスの演算コア（Tensorコア/ストリームプロセッサー）へ、途切れなく均等に計算データを流し込めるようになります。
            //   並列処理効率が最大化され、処理速度は理論上数倍〜10倍以上へと跳ね上がります。
            //
            // ctx_params.n_ubatch = 16;  // 🌟 メモリ帯域を使い切る、超高速マイクロバッチ
            //   Q2（2.97GB）[1] ➔ Q4（4.82GB）[1] ➔ Q8（8.54GB）[1] の総容量は約16.3GB[1]。
            //   32GBの物理メモリがあれば、OSのシステム領域を差し引いても、すべての変速ギア（重み宇宙）が最速の物理RAM上に「完全常駐」します。

            gear.ctx = llama_init_from_model(gear.model, ctx_params);
            if (!gear.ctx) {
                std::cerr << "【エラー】計算用のお部屋を作れなかった: " << gear.model_path << std::endl;
            }
        }
    }

    /**
     * @brief デストラクタ：使い終わったらパソコンの重いメモリを綺麗にお片付けする優しさ設計
     */
    ~AmiEngine() {
        for (auto& gear : gear_table) {
            // 存在確認（nullptrチェック）を絶対に行ってから、正しい順序（Context ➔ Model）で安全に解放する
            if (gear.ctx != nullptr) {
                llama_free(gear.ctx);       // ① 先にお部屋（コンテキスト）を解放
            }
            if (gear.model != nullptr) {
                llama_model_free(gear.model); // ② 次に脳みそ本体（モデル）を解放
            }
        }
        llama_backend_free();
    }
    /**
     * @brief 質問（トークン配列）を受け取って、各部屋の近似値を同期・変速しながら合格した回答文字列を返す核心の関数
     * @param question_tokens 刻まれた質問のID配列（単語の区切りベースは共通な）
     * @return 完成した、要約などの回答文字列
     */
    std::string process_question(const std::vector<llama_token>& question_tokens) {
        std::string final_response = "";
        if (question_tokens.empty()) return final_response;

        for (size_t g = 0; g < gear_table.size(); ++g) {
            if (!gear_table[g].ctx || !gear_table[g].model) continue;

            //int32_t n_vocab = llama_n_vocab(gear_table[g].model);
            int32_t n_vocab = llama_vocab_n_tokens(llama_model_get_vocab(gear_table[g].model));

            // ターゲットベクトルのサイズが足りなければ、大きい語彙空間全体（n_vocab）まで動的に広げてあげる
            if (target_vector.size() < static_cast<size_t>(n_vocab)) {
                target_vector.resize(n_vocab, 0.1f); 
            }

            // 🔄 【歴史の同期】1つ前のギアから過去の記憶を「シリアライズ転送」で確実に引き継ぐ
            if (g > 0 && total_history_coord > 0) {
                // バイト配列への確定シリアライズ転送にリファクタリングした
                size_t size_g = llama_state_seq_get_size(gear_table[g-1].ctx, 0);
                std::vector<uint8_t> kv_data(size_g);
                llama_state_seq_get_data(gear_table[g-1].ctx, kv_data.data(), kv_data.size(), 0);
                llama_state_seq_set_data(gear_table[g].ctx, kv_data.data(), kv_data.size(), 0);
            }
            
            // 今回の質問トークンを入力するためのバッチ初期化（最後のトークンだけロジットを要求する）
            llama_batch batch = llama_batch_init(question_tokens.size(), 0, 1);
            for (size_t i = 0; i < question_tokens.size(); ++i) {
                bool is_last = (i == question_tokens.size() - 1);
                llama_batch_add(batch, question_tokens[i], total_history_coord + static_cast<int32_t>(i), {0}, is_last);
            }
            
            if (llama_decode(gear_table[g].ctx, batch) != 0) {
                std::cerr << "【警告】デコードに失敗した（ギア " << g << "）" << std::endl;
                llama_batch_free(batch);
                continue;
            }
            
            float* logits = llama_get_logits(gear_table[g].ctx);
            llama_batch_free(batch);

            if (!logits) continue;

            // 確定行列からコサイン類似度を100%正しく弾き出す
            float score = calculate_cosine_similarity(logits, target_vector.data(), n_vocab);
            // 🔍 【デバッグ①】計算されたスコアと、その部屋の閾値を表示
            AMI_LOG(std::cerr << "[DEBUG 1] ギア: " << g << ", スコア: " << score << ", 閾値: " << gear_table[g].threshold << std::endl;)
        
            // 🎯 【大正解ロジック】閾値を超えたら、このお部屋で文字の生成をスタート
            if (score >= gear_table[g].threshold) {
                auto query_end_time = std::chrono::high_resolution_clock::now();
                auto total_boot_ms = std::chrono::duration_cast<std::chrono::milliseconds>(query_end_time - query_start_time).count();
                double query_seconds = total_boot_ms / 1000.0;
                AMI_LOG(std::cerr << "[DEBUG 1-SUCCESS] ➔ 閾値を突破！この部屋で生成を開始します。[経過時間： " << query_seconds << " 秒]" << std::endl;)

                int32_t output_count = 0;
                //const int32_t MAX_OUTPUT_TOKENS = 2048; // 非力なミニPCではmmapとの闘いになるため、大幅削減しています。
                const int32_t MAX_OUTPUT_TOKENS = 24; // POC 出力検証


                // 質問トークンがデコードされたので、ここで歴史の座標をその分だけ確実に進める
                // これで、次の返答トークンが「質問のすぐ直後」の正しい座標の配置により、記憶喪失を防ぐ
                total_history_coord += static_cast<int32_t>(question_tokens.size());

                // 🔄 「出力 ➡️ 片付け ➡️ 次のトークン」のストリーミング循環ループ
                while (output_count < MAX_OUTPUT_TOKENS) {
                    llama_token reply_token = 0;
                    float max_logit = -10000.0f; // 安全な最小値を設定

                    // 👑 今のお部屋での「ナンバーワン（最大値）」の単語IDをガチッと掴み取る
                    for (int32_t v = 0; v < n_vocab; ++v) {
                        if (logits[v] > max_logit) { 
                            max_logit = logits[v]; 
                            reply_token = v; 
                        }
                    }
                    // 🔍 【デバッグ②】掴んだトークンIDと、それがEOS（終わり）かどうかを表示
                    AMI_LOG(std::cerr << "[DEBUG 2] ループ回数: " << output_count << ", 選択トークンID: " << reply_token << ", EOS_ID: " << llama_vocab_eos(llama_model_get_vocab(gear_table[g].model)) << std::endl;)


                    // 【Llama 3.1 最適化・3重の鉄壁ブレーキ】
                    // 標準EOS(128009) か メッセージ終わり（チャット用EOM）(128008) が来たら終了！(ここはモデルにより変わる）
                    if (reply_token == llama_vocab_eos(llama_model_get_vocab((gear_table[g].model))) ||
                        reply_token == 128008) {  
                        AMI_LOG(std::cerr << "[DEBUG 2-BREAK] EOSトークンを検知したためループを抜けます。" << std::endl;)
                        break; 
                    }

                    // 🔤 刻まれたIDを安全な人間の言葉（文字列のピース）に戻す処理
                    std::string piece = "";
                    char buf[1024]; // 1024バイト安全バッファ複数バイト文字対応
                    int n = llama_token_to_piece(llama_model_get_vocab(gear_table[g].model), reply_token, buf, sizeof(buf), 0, true);

                    if (n >= 0) {
                        // 【修正】n >= 0 にして、0文字以上の有効な変換をすべて確実に回収する
                        piece = std::string(buf, n);
                        final_response += piece;
                    } else {
                        // 戻り値がマイナスの場合は「必要なバッファサイズ」を意味するので、動的に広げて再取得
                        std::vector<char> dyn_buf(-n);
                        int retry_n = llama_token_to_piece(llama_model_get_vocab(gear_table[g].model), reply_token, dyn_buf.data(), dyn_buf.size(), 0, true);
                        if (retry_n >= 0) {
                            final_response += std::string(dyn_buf.data(), retry_n);
                        }
                    }

                    // 👑 【Llama 3.1 結合の核心】
                    // 回収した文字（パーツ）が空でなければ、歴史の最終回答にガチッと結合して、その場でターミナルにも出す
                    if (!piece.empty()) {
                        final_response += piece;
                        // 🔍 【リアルタイム・デバッグ】いま復元できて、最終回答に合流した実際の文字を表示！
                        std::cerr << "[🎯 変換成功文字]: " << piece << std::endl;
                    } else {
                        // 1文字の途中の日本語パーツ（バイト列）などの場合、ここを通ります
                        // std::cerr << "トークンID " << reply_token << " は文字パーツのため、次の結合にすすみます。" << std::endl;
                    }

                    output_count++;

                    llama_batch next_batch = llama_batch_init(1, 0, 1);
                    llama_batch_add(next_batch, reply_token, total_history_coord, {0}, true);
                    
                    if (llama_decode(gear_table[g].ctx, next_batch) != 0) {
                        llama_batch_free(next_batch);
                        break;
                    }
                    
                    logits = llama_get_logits(gear_table[g].ctx);
                    llama_batch_free(next_batch);
                    
                    if (!logits) break;

                    // 🛡️ 同じ文章が繰り返されたら途中で強制終了するブレーキ
                    // 直前のフレーズがすでにこれまでの回答に含まれているかチェック
                    if (!piece.empty() && final_response.length() > piece.length()) {
                        std::string previous_text = final_response.substr(0, final_response.length() - piece.length());
                        // 🌟 「です。」などの句切れが2回目に出現したら、その瞬間にスマートに終了！
                        if (piece == "。" || piece == "です" || piece == "。" || piece == "\n") {
                            if (previous_text.find(piece) != std::string::npos && output_count > 10) {
                                std::cerr << "[繰り返し自動検知]: 同じ文末表現を検知したため、スマートに途中で終了します。" << std::endl;
                                break;
                            }
                        }
                    }

                    // AIが1文字喋り終わったので、綺麗に歴史をインクリメント
                    total_history_coord++; 
                }

                // 👑 【歴史の逆同期リレー】
                // 16ビット（合格ギア）が指し示した正しい歴史の場所を、他のすべての部屋へ「逆渡し」する
                for (size_t target_g = 0; target_g < gear_table.size(); ++target_g) {
                    if (target_g != g && gear_table[target_g].ctx) {
                        // これで4ビットも2ビットも、自分たちの部屋の近似値に戻されて位置がカチッと確定します。
                        size_t size_g = llama_state_seq_get_size(gear_table[g].ctx, 0);
                        std::vector<uint8_t> kv_data(size_g);
                        llama_state_seq_get_data(gear_table[g].ctx, kv_data.data(), kv_data.size(), 0);
                        llama_state_seq_set_data(gear_table[target_g].ctx, kv_data.data(), kv_data.size(), 0);
                    }
                }
                break; // 合格した最高のギアで処理が終わったので、ギアの探索ループを終了する
            }
        }

        total_history_coord += question_tokens.size();
        return final_response; 
    }

    /**
     * @brief 会話の歴史（記憶）を完全にリセットして、最初からリフレッシュする
     */
    void clear_memory() {
        for (auto& gear : gear_table) {
            if (gear.ctx) llama_kv_cache_clear(gear.ctx); 
        }
        total_history_coord = 0;
    }

    /**
     * @brief 人間の言葉（文字列）を安全にトークン配列（ID列）に分解する
     * @param text 入力された質問文字列
     * @param add_special 特殊トークン（BOSなど）を付与するかどうか
     * @return 分解されたトークン配列
     */
    std::vector<llama_token> tokenize(const std::string& text, bool add_special) {
        // 部屋が空っぽ、またはロードに失敗していれば空の配列を返す安全ブレーキ
        if (gear_table.empty() || !gear_table[0].model) {
            return std::vector<llama_token>();
        }
        
        // 0番目の部屋（Q2）の脳みそを使って文字を刻む
        std::vector<llama_token> res(text.length() + 4);
        int n = llama_tokenize(llama_model_get_vocab(gear_table[0].model), text.c_str(), text.length(), res.data(), res.size(), add_special, false);
        if (n < 0) {
            res.resize(-n);
            n = llama_tokenize(llama_model_get_vocab(gear_table[0].model), text.c_str(), text.length(), res.data(), res.size(), add_special, false);
        }
        res.resize(n);
        return res;
    }


    void set_query_start_time(auto querystarttime) {
        query_start_time = querystarttime;
    }
};
