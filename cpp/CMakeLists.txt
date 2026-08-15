cmake_minimum_required(VERSION 3.24) # FetchContentの機能拡張のため3.24以上を推奨
project(ProjectAMI CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 📦 [FetchContent] Gitからllama.cppを自動取得する魔法のモジュール
include(FetchContent)

# ==========================================
# 🛠️ 【手動フラグ設定】：新旧の知恵が完全に融合したGPU統合スイッチ
# ==========================================
option(AMI_USE_VULKAN          "Vulkan による全GPU共通の爆速化（推奨）" ON)
option(USE_NVIDIA_OPTIMIZATION "NVIDIA GeForce専用 (CUDA) 最適化を有効にする" OFF)
option(USE_AMD_OPTIMIZATION    "AMD Radeon専用 (ROCm/HIP) 最適化を有効にする" OFF)
option(USE_INTEL_OPTIMIZATION  "Intel専用 (oneAPI/SYCL) 最適化を有効にする" OFF)

# 💡 静的ライブラリ(.a)か動的ライブラリ(.so)かを切り替えるスイッチ
option(BUILD_SHARED_LIBS "ONにすると.so、OFFにすると.aを生成します" OFF)

# ==========================================
# 🧱 各ハードウェアに応じた最適化フラグの自動分岐（llama.cpp公式のフラグと連動）
# ==========================================
set(GPU_LIBS "")
set(BACKEND_DEFINITIONS "")

# llama.cpp公式のビルドオプションを、私たちのスイッチとカチッと連動させる
set(GGML_VULKAN OFF CACHE BOOL "" FORCE)
set(GGML_CUDA   OFF CACHE BOOL "" FORCE)
set(GGML_HIP    OFF CACHE BOOL "" FORCE)
set(GGML_SYCL   OFF CACHE BOOL "" FORCE)

if(AMI_USE_VULKAN)
    message(STATUS "[GPU CONFIG] 🌐 Vulkan Global Optimization: ENABLED")
    find_package(Vulkan REQUIRED)
    set(GGML_VULKAN ON CACHE BOOL "" FORCE) # llama.cpp側のVulkanビルドを強制ON
    list(APPEND BACKEND_DEFINITIONS GGML_USE_VULKAN)
    set(GPU_LIBS ${Vulkan_LIBRARIES})

elseif(USE_NVIDIA_OPTIMIZATION)
    message(STATUS "[GPU CONFIG] NVIDIA GPU (CUDA) Optimization: ENABLED")
    enable_language(CUDA)
    set(CMAKE_CUDA_ARCHITECTURES "native")
    set(GGML_CUDA ON CACHE BOOL "" FORCE) # llama.cpp側のCUDAビルドを強制ON
    list(APPEND BACKEND_DEFINITIONS GGML_USE_CUDA)

elseif(USE_AMD_OPTIMIZATION)
    message(STATUS "[GPU CONFIG] AMD GPU (ROCm/HIP) Optimization: ENABLED")
    find_package(HIP REQUIRED)
    set(AMD_GPU_TARGET "native")
    set(GGML_HIP ON CACHE BOOL "" FORCE) # llama.cpp側のHIPビルドを強制ON
    list(APPEND BACKEND_DEFINITIONS GGML_USE_HIP)
    set(GPU_LIBS ${HIP_LIBRARIES})

elseif(USE_INTEL_OPTIMIZATION)
    message(STATUS "[GPU CONFIG] Intel GPU (oneAPI) Optimization: ENABLED")
    set(INTEL_GPU_TARGET "intel_gpu_pvc")
    set(GGML_SYCL ON CACHE BOOL "" FORCE) # llama.cpp側のSYCLビルドを強制ON
    list(APPEND BACKEND_DEFINITIONS GGML_USE_SYCL)
endif()

# 余計なサンプルやテストのビルドをOFFにして、爆速でコアだけをビルドさせる設定
set(LLAMA_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LLAMA_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(LLAMA_BUILD_SERVER   OFF CACHE BOOL "" FORCE)

# ==========================================
# 📥 Gitから llama.cpp を自動ダウンロードして結合！
# ==========================================
message(STATUS "[AMI SYSTEM] Git から llama.cpp を自動取得中...")
FetchContent_Declare(
    llamacpp
    GIT_REPOSITORY https://github.com/ggml-org/llama.cpp
    GIT_TAG        b4731 # または検証を固定したい特定のコミットハッシュやタグを指定
)

# ダウンロードを実行して、プロジェクトの「サブディレクトリ」として内部ビルドに組み込む
FetchContent_MakeAvailable(llamacpp)

# 一般的なC++最適化フラグ
add_compile_options(-O3 -funroll-loops)

# ==========================================
# 🎯 ターゲット1：AmiCore ライブラリのビルド
# ==========================================
# BUILD_SHARED_LIBSがOFFなら自動的に「ami_core.a」が生成されます
add_library(ami_core AmiEngine.hpp)

# モダンCMakeの手法でマクロ定義を注入
target_compile_definitions(ami_core PRIVATE ${BACKEND_DEFINITIONS})

# 各社個別フラグごとの特有のコンパイルオプションをターゲットにインジェクション！
if(USE_NVIDIA_OPTIMIZATION AND NOT AMI_USE_VULKAN)
    target_compile_options(ami_core PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:--use_fast_math -O3>)
elseif(USE_AMD_OPTIMIZATION AND NOT AMI_USE_VULKAN)
    target_compile_options(ami_core PRIVATE --amdgpu-target=${AMD_GPU_TARGET} -O3)
elseif(USE_INTEL_OPTIMIZATION AND NOT AMI_USE_VULKAN)
    target_compile_options(ami_core PRIVATE -fsycl -fsycl-targets=${INTEL_GPU_TARGET} -O3)
endif()

# 💡 Gitから降ってきた「llama.cpp」本家が内部生成するターゲット名（llama）をそのままガチャンと結合！
# インクルードパスも自動で引き継がれるので、手動のincludeパス指定はいらなくなります
target_link_libraries(ami_core PUBLIC llama ggml ${GPU_LIBS})

# ==========================================
# 🎯 ターゲット2：デモ実行ファイルのビルド（mesh_router）
# ==========================================
add_executable(mesh_router main.cpp)
target_link_libraries(mesh_router PRIVATE ami_core)

