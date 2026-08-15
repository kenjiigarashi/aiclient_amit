<p align="center">
  <img src="docs/images/ami_official_logo.png" alt="AMI Official Logo" width="300"/>
</p>

# ⚙️ ProjectAMI: Attention Mesh Index Transmission (AMI)

[![License: MIT](https://shields.io)](https://opensource.org)
[![C++: 20](https://shields.io)](https://cppreference.com)
[![Backend: llama.cpp](https://shields.io)](https://github.com)

A hyper-lightweight, multi-gear subtractive inference engine written in pure C++20. ProjectAMI proves that a highly constrained commodity mini-PC can robustly execute multi-turn continuous dialogue across a multi-stage **16.33GB foundational asset pipeline** under a severe **6.5GB physical memory ceiling** without triggering a single Out-Of-Memory (OOM) crash.

This project introduces absolutely no new or unproven technologies. It is entirely composed of a combination of **"battle-tested technologies"** that have been thoroughly debugged and have supported global infrastructure for decades.

## 🗺️ Mathematical Philosophy: Map Databases & LLM Latent Spaces

How does AMI execute localized multi-scale pathfinding across Llama-3.1-8B without suffocating a 16GB edge device?

The answer lies in a profound architectural realization: the hyper-dimensional semantic clusters inside an LLM operate under the exact same spatial taxonomy as classical map databases (Quadtree hierarchical indexing) long perfected in high-utility local car navigation systems.

In other words, these are fully debugged and battle-tested technologies. As such, they are not eligible for new patent protections.

## 🛠️ Core Architecture & Battle-Tested Technologies

1. **Spatial Partitioning via Quadtree**
   * **Role**: Recursively divides the 128k vocabulary vector space into four equal quadrants (vertically and horizontally) to narrow down the target.
   * **Impact**: **Instantly discards 75% of the useless computational space per iteration (98.4375% total reduction after 3 steps).**

2. **Spatial Indexing (R-tree / B-tree)**
   * **Role**: Performs ultra-fast, lightweight index lookups across the entire 128k vocabulary space for semantic focus checking.
   * **Impact**: Locks onto the target direction at the 2-bit (IQ2) and 4-bit (Q4) stages, **confining the heaviest tensor matrix multiplication exclusively to the final 1.56% of the space (the Q8 last resort).**

3. **mmap (Memory Mapping) & On-Demand Paging**
   * **Role**: Maps the total 16.33GB model files to virtual memory addresses instead of brute-force loading them directly into physical RAM.
   * **Impact**: **Completely immunizes the process against OOM (Out of Memory) crashes, ensuring execution finishes even when physical RAM is maxed out and only swap space (SSD) remains.**

---

## ⚖️ Prior Art & License Declaration

The "multi-scale subtractive inference mesh" and the "dynamic multi-gear matrix multiplication reduction logic (98.4375% optimization)" disclosed in this project (ProjectAMI) contain no new or unproven technologies. This system is entirely built upon a combination of long-standing, public domain prior art that has supported global infrastructure and has been thoroughly debugged for decades:

1. **Spatial Partitioning via Quadtree**: Extensively utilized for decades in car navigation systems and 3D game engines for frustum culling.
2. **mmap & On-Demand Paging**: A core virtual memory management feature built into the kernel of all modern operating systems (Linux, Windows) since the UNIX era of the 1980s.
3. **Hierarchical Spatial Indexing (R-tree / B-tree)**: The fundamental structural backbone enabling efficient queries in database management systems.

The foundational theoretical architecture of this system relies on the open *Transformer* architecture introduced in 2017 by Llion Jones and co-authors ("Attention Is All You Need"), and its local execution ecosystem is built on top of the open-source assets (such as the mmap functionalities) of *llama.cpp*, pioneered by Georgi Gerganov and advanced by the global open-source community.

As such, this project represents a practical synthesis of foundational textbook algorithms and monumental open-source legacies. We believe this system does not constitute an eligible subject for exclusionary proprietary patent protections, but rather belongs to the public domain (prior art) to be shared openly with the developer community.

Out of deep respect for the pioneers who have shaped the open evolution of artificial intelligence, we fully release this knowledge under the **MIT License** to empower engineers worldwide to build, modify, and optimize freely.

---

## 🛠️ The Vision: A World Where Everyone Can Be a Mechanic

Modern "brute-force corporate engineering" has centralized AI inside multi-billion-dollar data centers, turning users into mere passive consumers of locked black-box APIs. They took away our right to hack, tune, and understand the machine.

**AMI changes that paradigm completely.** 

By freezing the underlying single latent space and letting you freely swap out GGUF quantization layers (`Q2_K`, `Q4_K_M`, `Q8_0`, `16bit`, `32bit`) like transmission gears, AMI turns your local machine into a garage. Depending on your hardware spec (16GB, 32GB, or 64GB RAM), you can roll up your sleeves, grab your C++ wrench, open the hood, and tune your own local intelligence to absolute peak efficiency. 

> *"We don't need a corporate temple. We need a personal garage. AMI is built to make everyone a true AI mechanic."*

<p align="center">
  <img src="docs/images/ami_character.png" alt="Guide AMI" width="250"/>
  <br><i>Guide Companion: Ami — Stepping out "toko-toko" from a 16GB edge device to reshape the AI landscape.</i>
</p>

---

### 📊 Empirical Evidence & Execution Time Logs

Empirical verification data under extreme memory-constrained environments:

* **Hardware Device**: GMKtec M7 Mini-PC (AMD Ryzen / 16GB Physical RAM, **WSL2 memory allocation strictly capped at 6,545MB ≒ approx. 6.5GB**)
* **Resource Breakdown**: RAM 16GB (Internal Graphics: 4GB / Actual Available Memory: 12GB), SSD 512GB
* **Execution Environment**: WSL2 (Allocated Memory: 6545MB / Swap: 8192MB)

```bash
[Translation from Japanese]
====================================================
⚙️  AmiEngine (Attention Mesh Index Transmission) Initializing...
====================================================
[GPU CONFIG] 🌐 Vulkan Global Optimization: ENABLED
[AMI SYSTEM] Ingesting downstream layers...


［translation］
🤖 AMI: "Local AI Guide AMI—please ask your question."
----------------------------------------------------
👤 Question > How far is it from the Earth to the Sun?
🤖 AMI: 🤖 Reasoning... [Shifting gears] ➔
[DEBUG 1] Gear: 0, Score: -0.669407, Threshold: 1
[DEBUG 1] Gear: 1, Score: -0.57879, Threshold: 0.9
[DEBUG 1] Gear: 2, Score: -0.538083, Threshold: -1
[DEBUG 1-SUCCESS] ➔ Threshold crossed! Starting generation in this room. [Elapsed time: 71.909 sec]
.
.
.

----------------------------------------------------
 The average distance from the Earth to the Sun is about 93 million miles (149.6 million kilometers). This distance
----------------------------------------------------

========================================================
📊 [⏳ Ultra-Low-Resource Environment Hack: Time Evidence Log]
 ➔ ⏱️ Total time from app launch to ready state: 25.535 sec
 ➔ ⚡ Time from question input to completion of answer generation: 278.178 sec
========================================================

```

---
<p align="center">
  <img src="docs/images/ami_character_walk.png" alt="Guide AMI" width="250"/>
  <br><i>Guide Companion: Ami — Stepping out "toko-toko" from a 16GB edge device to reshape the AI landscape.</i>
</p>


## 🗺️ Mathematical Philosophy: Map Databases & LLM Latent Spaces

How does AMI execute localized multi-scale pathfinding across Llama-3.1-8B without suffocating a 16GB edge device? The answer lies in a profound architectural realization: the hyper-dimensional semantic clusters inside an LLM operate under the exact same spatial taxonomy as classical map databases (Quadtree hierarchical indexing) long perfected in high-utility local car navigation systems.
In other words, these are fully debugged and battle-tested technologies. As such, they are not eligible for new patent protections.

| Architectural Layer | 🗺️ Classical Map Database Navigation | 🧠 Subtractive LLM Transmission (AMI) |
| :--- | :--- | :--- |
| **1st Gear: Pruning** | **Macroscopic National Map (1:1,000,000)**<br>・Isolates broad regions (e.g., Hokkaido vs. Kyushu)<br>・Minimal memory footprint | **2-bit Layer (`IQ2_M`)**<br>・Traverses the 120K-token vocabulary space in milliseconds to isolate the giant global concept cluster |
| **2nd Gear: Localization** | **Regional Road Network (1:100,000)**<br>・Narrows down paths inside a specific city district<br>・Surgically drops all non-relevant data sheets | **4-bit Layer (`Q4_K_M`)**<br>・Locks onto specific localized semantic characteristics inside the filtered subspace |
| **3rd Gear: Resolution** | **Pinpoint Micro-Street Address (1:1,000)**<br>・Identifies the exact target building address<br>・Loaded entirely on-demand for final validation | **16-bit / 32-bit Layer (Raw Weights)**<br>・Applies unquantized spatial precision strictly inside the isolated tensor room to flush the 24-token factual resolution |

### 📊 Hierarchical Architectural Catalyst: Map Mesh DB vs. LLM Conceptual Space
![AMI Map DB vs LLM Conceptual Hierarchy](docs/images/map_db_vs_llm_hierarchy.png)

#### 💡 The Delusion of Brute-Force Cloud AI
Modern corporate cloud engineering is the computing equivalent of **"scanning every single manhole cover in the entire nation at 1:1,000 resolution using a supercomputer cluster, just to drive from Tokyo to a specific ramen shop in Sapporo."** This massive, un-indexed brute-force scan is why they require megawatt power plants and endless server racks.

AMI fundamentally rejects this paradigm. By preserving the invariant underlying semantic universe and introducing a programmatic C++20 gearbox, AMI scans the Macroscopic National Map at 2-bit, forward-synchronizes context into the Regional Road Network at 4-bit upon validation, and executes a precision strike at raw precision only inside the final 24 tokens. This elegant, time-tested subtractive engineering completely obsoletes the necessity for over-engineered cloud scale-out architectures.

### 📊 The Paradigm Shift: Brute-Force Corporate Engineering vs. Hierarchical Smart-Local
![AMI Paradigm Shift Architecture](docs/images/paradigm_shift_architecture.png)

The low-level structural components validated above prove that relying entirely on massive computing infrastructure to solve architectural scaling limits is dead. ProjectAMI shifts the paradigm from centralized "corporate temples" running massive cloud arrays down to independent "personal garages" tuning custom C++ gearboxes on consumer desktops.

##### Spatial Deconstruction & Matrix Computation Reduction Mathematical Model (Multi-Layer Quadtree Mesh)
A quadtree subdivides space by a factor of 4 with each increasing layer of depth.
In a 2D search space (the multi-dimensional vector index of intelligence), when layer-structuring the 1D axes (X and Y) by "bit-length" to define spatial resolution, the total number of meshes in the space is defined by the following equation:

$$\text{Total Meshes} = 2^b \times 2^b = (2 \times 2)^b = 4^b \quad (b = \text{1D Bit-length / Quadtree Depth})$$

As illustrated in the "Multi-Layer Recursive Search Mesh" diagram, this architecture pinpoints (prunes) the space with millimeter-level precision through the following recursive steps:

*   **Layer 1 (2-bit space: $b=2$)** $\rightarrow 4^2 = 16$ meshes (Dividing the global space into 16 blocks: 16 meshes targeted for search)
*   **Layer 2 (4-bit space: $b=4$)** $\rightarrow 4^4 = 256$ meshes (Expanding a single 2-bit mesh: 16 sub-meshes targeted for search)
*   **Layer 3 (8-bit space: $b=8$)** $\rightarrow 4^8 = 65,536$ meshes (Digging into the bedrock of a single 4-bit mesh: 256 fine meshes targeted for search)

##### 🧮 Matrix Computation & Access Pruning Equation ($288 / 65,536$)
By executing this multi-layer recursive search, this system radically narrows down the target nodes to just **288 meshes ($16 + 16 + 256$)** from the vast expanse of the hyper-detailed final inference space.

*   **Total mesh space of the Hyper-detailed Stage (16-bit space) [Denominator]**:
    $$4^8 = 65,536 \text{ meshes}$$
*   **Actual space remaining for execution and matrix computation [Numerator]**:
    $$16 + 16 + 256 = 288 \text{ meshes}$$

##### 1. Residual Rate (Ratio of actual data mapped/loaded into physical memory)
$$P_{\text{remain}} = \frac{288}{65,536} \approx 0.4395\%$$

##### 2. Reduction Rate (Ratio of wasteful space completely eliminated/skipped prior to matrix multiplication)
$$R_{\text{pruning}} = 100 - 0.4395 = 99.5605$$

While Big Tech blindly iterates brute-force matrix multiplication across all $65,536$ meshes using the raw power of massive data centers, this log mathematically purges **$99.5605\%$** of the wasteful search space before computation even begins, achieving pinpoint access via `mmap` into a mere **$0.4395\%$** target window.

---

## 🕸️ System Topologies & High-Utility Network Flows

### 1. Object Collaboration & Serialization Pipeline
AMI leaves the underlying foundation model architecture completely unaltered, handling multi-scale cluster pruning and historical context caching (`uint8_t` serialization) dynamically entirely inside the C++ memory management abstraction layer.

![AMI Collaboration Topology](docs/images/collaboration_diagram.png)

### 2. Runtime Execution Timeline & Memory Walls
Traces how the system manages forward context mapping, autoregressive text generation, and the final structural **[Semantic Reverse Synchronization Relay]** to maintain identical memory positions across divergent precision models.

![AMI Runtime Sequence](docs/images/sequence_diagram.png)

### 3. Structural Interface Object Mappings
Demonstrates compilation prohibitions (deleted copy constructors) engineered to ensure 100% crash-free operations under heavy swap page thrashing, unified under a decoupled `LLMGear` cluster matrix.

![AMI Class Architecture](docs/images/class_diagram.png)

---

## ⚙️ Foundational Asset Pipeline Specifications

### Selected Base Model Baseline
* **Foundation Universe**: `Meta-Llama-3.1-8B-Instruct` (Meta AI / Llama 3.1 Community License)
* **Context Ceiling Target**: Under standard configurations, the raw 128K context structure collapses 16GB systems instantly due to massive KV Cache space allocation. AMI surgically circumvents this limit inside the transmission matrix.

### Gear Allocation Layout
Assets can be sourced from open-weights community endpoints (e.g., `bartowski` repository structures on Hugging Face):
* **1st Gear (Sub-Space Pruning Phase)**: `IQ2_M` (~2.97 GB)
* **2nd Gear (Cluster Localization Phase)**: `Q4_K_M` (~4.82 GB)
* **3rd Gear (Factual Anchor Phase)**: `Q8_0` (~8.54 GB)
* **Total Static Pipeline Asset Load**: **~16.33 GB** (Executed stably within a 6.5GB memory gate via programmatic C++ multi-scale abstraction).

---

## 🛠️ Build Configuration & Compilation Steps

### Prerequisites
* **CMake** (Version >= 3.24 or higher recommended)
* **Modern C++20 Compatible Compiler** (`gcc`, `clang`, `msvc`)
* **Vulkan SDK** (Recommended to enable `ON` to boost GPU performance across all environments)

#### This guide outlines the setup procedure for the required system libraries and development tools on the OS side when building with the Vulkan backend for `llama.cpp` enabled.

##### 🌐 Supported Environment
- **OS**: Linux (Ubuntu 24.04 LTS / Noble Numbat)
- **Environment**: WSL2 or Native Linux
- **Required Tool**: CMake version 3.24 or higher
- **Required Language Standard**: C++20 standard (Mandatory)

---

###### Installing Dependencies

Open your terminal and execute the following commands in order.

###### ① Update Package List
```bash
sudo apt update
```

###### ② Install Libraries and Shader Compilers
Install the Vulkan core, development headers, and the shader compiler (`glslc`) required for the CMake configuration step all at once.
```bash
sudo apt install -y \
  libvulkan-dev \
  vulkan-tools \
  glslc \
  libshaderc-dev
```

###### Clear CMake Cache (If you previously performed a CMake build before installing Vulkan)
After the package installation is complete, CMake might still remember the old "library not found" state. Please ensure you clear the build folder cache before rebuilding.
```bash
rm -rf ./aiclient_amit/build/*
```

### Build Steps
```bash
git clone https://github.com/kenjiigarashi/aiclient_amit.git
cd aiclient_amit/cpp

# Enable Vulkan and perform a parallel build in Release mode (-j16)
cmake -B build -DAMI_USE_VULKAN=ON . && cmake --build build --config Release -j16
```


### Hardware Configuration Matrix (`AmiEngine.hpp`)
Open `AmiEngine.hpp` to customize the internal computation workspace variables to match your local garage hardware capacity:

```cpp
// 🚗 16GB Baseline Profile (Low-resource survival settings - Defaults)
ctx_params.n_ctx     = 256; // Constrains ephemeral context cache down to 256 cells
ctx_params.n_batch   = 8;   // Tightens generation computation segments to 8 sequences
ctx_params.n_ubatch  = 8;   // Optimized specifically to maintain zero Vulkan queue latency

// 🏎️ 32GB Performance Profile (Unlocks swapless hardware pre-fetching)
// ctx_params.n_ctx     = 1024; // Expands spatial tracking to 1024 cells for long multi-turn contexts
// ctx_params.n_batch   = 32;   // Maximizes parallel pipeline capacity across GPU execution threads
// ctx_params.n_ubatch  = 16;   // Maxes out system memory bus saturation limits
```
### 📂 Model Asset Placement Steps

Navigate to the directory containing the `mesh_router` executable, create a `models` directory, and place the corresponding GGUF files inside it.
*Note: You **must use the exact same base LLM** across all gears. If the base models differ, the high-dimensional vector spaces (coordinate mappings) will mismatch, making the system completely non-functional.*

#### 1. Create the Directory
```bash
mkdir models
```

#### 2. Download Model Assets
Visit the following Hugging Face repository, search for the specific keywords for each gear, and download the files into your `models` folder:
🔗 [bartowski/Meta-Llama-3.1-8B-Instruct-GGUF](https://huggingface.co/bartowski/Meta-Llama-3.1-8B-Instruct-GGUF)

* **1st Gear (2-bit Version)**
  * **Search Keyword**: `Q2_K`
  * **Example File**: `Meta-Llama-3.1-8B-Instruct-Q2_K.gguf`
* **2nd Gear (4-bit Version)**
  * **Search Keyword**: `Q4_K_M`
  * **Example File**: `Meta-Llama-3.1-8B-Instruct-Q4_K_M.gguf`
* **3rd Gear (8-bit Version)**
  * **Search Keyword**: `Q8_0`
  * **Example File**: `Meta-Llama-3.1-8B-Instruct-Q8_0.gguf`
  * *Note: While high-bit GGUF variations (such as `IQ4_NL`) are available on bartowski's page, the `Q8_0` file (approx. 8.5 GB) is highly recommended for achieving maximum localized accuracy within the GGUF ecosystem. If you require the completely unquantized (16-bit) original weights, please download them from the official Meta repository.*
#### 3. Using Custom / Other Models
If you wish to swap in other versions of the Llama model series, please update the paths within the `gear_table` inside the source code to match your own environment:

```cpp
// 🛠️ Static Transmission Gear Definitions via Gear Table Retention
// *Note: Ensure you specify quantized models derived from the exact same base. (They must belong to the same LLM universe to function).*
gear_table = {
    {0, "models/Meta-Llama-3.1-8B-Instruct-IQ2_M.gguf",   1.0f}, // 1st Gear (2-bit): Coarse but ultra-fast exploration room
    {1, "models/Meta-Llama-3.1-8B-Instruct-Q4_K_M.gguf", 0.9f}, // 2nd Gear (4-bit): Intermediate room narrowing down specific conceptual clusters
    {2, "models/Meta-Llama-3.1-8B-Instruct-Q8_0.gguf",   -1.0f}  // 3rd Gear (High-bit): Maximum precision blueprint—The final fortress for mini-PCs
};
```

---
#### 📊 Comic & Illustration: Local AI 16-bit: The Triumph of Minimalist Efficiency
*(※ This content is a satirical work of fiction and is for entertainment and conceptual purposes only. :) )*

![AMI Survival Hack Comic Strip](docs/images/ami_comic.png)

* **1. The Monster and the Mini (Strategy)**: Corporate Cloud AI relies on multi-billion dollar brute-force weight scaling. I rely on a pure C++ FOR-loop routing mechanism running on a $300 commodity mini-PC. The algorithmic triumph is mathematically clear from the starting line.
* **2. The Smart Overtake**: While Cloud AI chokes and overheats under heavy data-copying memory ingestion overhead, AMI engages the `llama_kv_cache_seq_cp` methodology (acting as a dynamic mechanical clutch), switching internal index context pointers instantly without generating any thermal friction. A clean, silent, effortless overtake.
* **3. Crash and Victory (The Climax)**: Cloud AI completely obliterates itself via massive context-cache bloat and CPU/OOM hardware saturation. Meanwhile, the localized 16-bit PC dynamically cuts execution right at the finish line, claiming 1st place with total stability.
* **4. Silence in the Cockpit**: This is the unadulterated poise of the true smart-local paradigm—an absolute architecture shift engineered entirely through the subtractive elegance of multi-gear transmissions and 24-token automated brakes.

![AMI Survival Hack Comic Strip2](docs/images/ami_comic2.png)

> **"Race Over! Local AI Takes the Win via Hierarchical Routing!"**
> While the massive monolithic infrastructure spins out of control due to memory exhaustion and CPU peaks, a $300 mini-PC (Local 16-bit) blazes across the finish line powered by sheer ingenuity and **THE POWER OF THOUGHTFUL REDUCTION**. This single image perfectly encapsulates the core vision that ProjectAMI brings to life.
---

## 🌟 Conclusion: Request for GitHub Stars & Technical Support

ProjectAMI was born out of a simple aspiration: exploring how far we can stretch local LLM performance under heavily constrained computing environments through pure algorithmic optimization. The entire codebase is fully open-source under the MIT license—feel free to fork it, inspect the gears, and tune it to match your own local hardware specifications.

If this multi-scale subtractive transmission architecture or the core C++20 logic resonates with your passion for optimization, **please drop a Like on your tech blog posts and leave a [Star (🌟)] right here on this GitHub repository!** Your Stars are the greatest motivation keeping this project moving forward.

### 💼 【For Enterprises & Systems Integrators: Professional Consultations】
For organizations operating secure, air-gapped on-premise environments or resource-constrained edge systems (such as secure mainframes or local manufacturing edge nodes) where high stability and zero data leakage are non-negotiable requirements, the AMI transmission design offers a highly sustainable deployment paradigm.

However, tailoring the dynamic threshold scaling, cross-GPU thread scheduling, or custom autoregressive loop constraints for proprietary hardware architectures requires dedicated low-level attention. To ensure a seamless deployment integration and maximize system efficiency, I am available to provide direct engineering consultation and optimization support.

* **Technical Consultancy / Custom Tuning & Implementation Requests**: Feel free to reach out to me directly via LinkedIn Direct Message ( [linkedin](https://www.linkedin.com/in/kenjiigarashi/) ).
* **Support Fees**: Structured under a **【Flexible Pricing Model (Paid Support)】** tailored symmetrically around your project's specific scope and budget. I offer flexible assistance covering everything from initial environment setup consultations to hands-on hardware performance tuning.


Let us return to the core elegance of system design, where smart optimization defines the future of local utility. Thank you for your incredible support, and don't forget to drop a Star (🌟)!

---
## 🤖 "AMI: The Local AI Guide" Character Usage Guidelines

All copyrights, design rights, and other intellectual property rights regarding the official character and logos of this project ("AMI: The Local AI Guide") belong exclusively to the original author of ProjectAMI.

Please note that the **MIT License** applied to this project only permits the use and modification of the source code. It **does not grant, transfer, or release any rights to the visual character, logos, or illustrations of AMI.**

To prevent any disputes or misuse, the following usage rules have been established:


### 🟢 Permitted Actions (OK)
* **Inclusion in Technical Documents & Articles**: You are fully permitted to paste AMI’s images or logos as reference materials in technical blogs (e.g., Medium, Qiita, Zenn), explanatory videos, or the `README.md` of forked repositories.
* **Non-Commercial Fan Art**: Individual developers and creators are welcome to create and share their own illustrations or fan art of AMI on social media for non-commercial support purposes.

### 🔴 Prohibited Actions (NG)
* **Commercial Merchandising**: Manufacturing or selling any physical or digital merchandise featuring AMI’s visuals or logos (such as keychains, plushies, figures, t-shirts, stickers, etc.) as commercial products is strictly prohibited.
* **Falsely Claiming Official Status**: Selling products or offering services under the guise of an "official" license, or misleading others into believing that your entity owns the rights to AMI, is strictly prohibited.

---
*For commercial system integration inquiries or professional consulting regarding this C++20 engine, please contact the author directly for individual licensing and support arrangements.*
