    /**
     * @file main.cpp
     * @brief AmiEngine をターミナル（CUI）から自在に操るための標準入力インターフェース（極限最適化版）
     * @copyright Copyright (c) 2026 Kenji Igarashi
     * LinkedIn https://www.linkedin.com/in/kenjiigarashi
     * Licensed under the MIT License.
     */

    #include <chrono>
    #include <iostream>
    #include <string>
    #include <vector>
    #include "AmiEngine.hpp"

    int main() {

        // 🚀 【システム起動！】ミニPCの電源が入ったこの瞬間から計測スタート！
        auto ami_start_time = std::chrono::high_resolution_clock::now();

        std::cout << "====================================================" << std::endl;
        std::cout << "⚙️  AmiEngine (Attention Mesh Index Transmission) 起動中..." << std::endl;
        std::cout << "====================================================" << std::endl;


        // 🏎️ エンジンの起動（Q2, Q4, F16を一括ロード）
        AmiEngine engine;
        
        auto ami_end_time = std::chrono::high_resolution_clock::now();

        std::cout << "\n🤖 AMI: 「ローカルAIの案内人 AMI 質問をどうぞ」" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "※終了するには 'exit' または 'clear' で記憶をリフレッシュできる" << std::endl;

        std::string input_line;
        while (true) {
            std::cout << "\n👤 質問 > ";
            if (!std::getline(std::cin, input_line)) {
                break; 
            }

            if (input_line.empty()) continue;

            if (input_line == "exit") {
                std::cout << "🤖 AMI: 「バイバイまたね」" << std::endl;
                break;
            }

            if (input_line == "clear") {
                engine.clear_memory();
                std::cout << "🤖 AMI: 「会話の歴史（記憶）を綺麗にお片付けした」" << std::endl;
                continue;
            }

            // 🔤 1. 引っ越し完了！エンジンの持つ tokenize メソッドを直接呼び出すだけ！
            std::vector<llama_token> question_tokens = engine.tokenize(input_line, true);

            if (question_tokens.empty()) {
                std::cout << "🤖 AMI: 「言葉をうまく刻めなかったので、もう一度入力してね」" << std::endl;
                continue;
            }

            // 👤 ユーザーがプロンプトを入力し終わり、これから「LLM近似値検索」を開始する瞬間！
            auto query_start_time = std::chrono::high_resolution_clock::now();
            engine.set_query_start_time(query_start_time);

            std::cout << "🤖 AMI: 🤖 推論中... [変速ギア稼働] ➔ \n";
            
            // 🏎️ 2. 変速エンジンをブン回して最高の回答をストリーミング
            std::string response = engine.process_question(question_tokens);
            
            std::cout << "----------------------------------------------------" << std::endl;        
            std::cout << response << std::endl;
            std::cout << "----------------------------------------------------" << std::endl;

            // 3速F16のオンデマンド抽出と繰り返しブレーキが完全に終わった時刻を記録！
            auto query_end_time = std::chrono::high_resolution_clock::now();

                // 📊 各フェーズにかかった時間をミリ秒で計算して、秒数に直します！
            auto total_boot_ms = std::chrono::duration_cast<std::chrono::milliseconds>(ami_end_time - ami_start_time).count();
            auto query_proc_ms = std::chrono::duration_cast<std::chrono::milliseconds>(query_end_time - query_start_time).count();

            double boot_seconds  = total_boot_ms / 1000.0;
            double query_seconds = query_proc_ms / 1000.0;

            // 👑 【デモ本番用：大勝利の数値エビデンスログ！！】
            std::cerr << "\n========================================================" << std::endl;
            std::cerr << "📊 [⏳ 激貧環境ハック・タイムエビデンスログ]" << std::endl;
            std::cerr << " ➔ ⏱️ アプリ起動から準備完了までの総時間: " << boot_seconds << " 秒" << std::endl;
            std::cerr << " ➔ ⚡ 質問入力から解答生成完了までの時間: " << query_seconds << " 秒" << std::endl;
            std::cerr << "========================================================" << std::endl;

        }

        return 0;
    }

