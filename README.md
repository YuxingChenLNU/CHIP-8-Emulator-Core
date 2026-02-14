# CHIP-8 Emulator Core Implementation (Academic Research Track)

> **Migration Note**: This repository represents the transition of the **CHIP-8-Emulator-Core** project from a private development environment to this public profile. This migration is intended to facilitate academic evaluation for the **University of Alberta** and to provide a modular foundation for my upcoming **6502/NES architecture research**. All core logic was developed and tested locally prior to this public release.

## 1. Project Overview
This project is a high-fidelity implementation of the **CHIP-8 Instruction Set Architecture (ISA)** using modern C++17. The primary goal is to simulate the **COSMAC VIP** hardware environment. This project serves as a practical application of **Data Structures** (specifically stacks and memory-mapped arrays) and **Bitwise Logic Operations**.

## 2. Technical Specifications
The emulator is modeled after the original 1970s hardware constraints to ensure legacy compatibility:

| Component | Specification | Implementation Detail |
| :--- | :--- | :--- |
| **CPU** | 8-bit Instruction Set | 35 Opcodes, Big-Endian |
| **Memory** | 4096 Bytes RAM | `std::array<uint8_t, 4096>` |
| **Stack** | 16-level Subroutine Stack | Manual SP (Stack Pointer) management |
| **Timers** | 60Hz Delay & Sound | Cycle-accurate decrement logic |

## 3. Core Implementation Methodology

### 3.1 Instruction Decoding (指令译码)
Each opcode is 16-bit (2 bytes). The interpreter extracts instructions using **bitwise masking and shifting**:
`uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];`
This demonstrates $O(1)$ efficiency in the fetch-decode cycle. I chose this manual approach to better understand how CPU hardware reads binary data streams.



### 3.2 Graphics & XOR Logic
Graphics use a $64 \times 32$ monochrome buffer. Sprites are drawn using **XOR operations**. 
* **Collision Detection**: If a pixel is flipped from 1 to 0, the $V_F$ register is set to 1. This is the hardware-level basis for game physics in the CHIP-8 system.

## 4. Design Challenges & Solutions (设计挑战与解决)

### 4.1 Carry Flag (VF) Logic in ALU Operations
Implementing the `8xy4` (ADD Vx, Vy) opcode required careful handling of the **Carry Flag**. Since registers are `uint8_t`, a direct addition will lead to silent overflow in C++.
* **Solution**: I implemented a pre-calculation check: `V[0xF] = (V[X] + V[Y] > 255) ? 1 : 0;`. This simulates the **Carry-out** logic of a physical ALU, reflecting hardware-accurate states.

### 4.2 Stack Pointer (SP) Alignment
During early testing with the `PONG` ROM, the game crashed due to stack overflow. I discovered I was not properly decrementing the **SP** *before* fetching the return address. I resolved this by re-aligning the return logic with the standard stack behaviors taught in my Data Structures course.

## 5. Architectural Integrity & Memory Safety
* **Fixed-Width Integers**: I strictly used `uint8_t` and `uint16_t` from `<cstdint>`. This prevents unexpected behavior from standard `int` types across different CPU architectures.
* **Modern C++ Standards**: Instead of using raw C-style pointers, I utilized `std::array`. This ensures **zero-overhead** access while providing better memory safety, which is a key focus of my current system programming studies.

## 6. Future Roadmap: Toward NES & AI
* **Step 1**: Complete the SDL2 abstraction layer for real-time sound and video.
* **Step 2**: Implement the **MOS 6502 ISA** (NES CPU) to explore more complex bus architectures.
* **Step 3**: Explore **LLM-based binary analysis** to automatically annotate legacy ROM files.

## 7. References & Bibliography (参考资料)
This project would not be possible without the extensive documentation provided by the emulation community:

* **Cowgod's Chip-8 Technical Reference (v1.1)**: The primary source for opcode specifications and memory layout.
* **Mastering CHIP-8 by Matthew Mikolay**: Provided deep insights into the timing and history of the RCA COSMAC VIP.
* **RCA COSMAC VIP Instruction Manual (1978)**: Used for verifying the original hardware-level XOR sprite behavior.
* **Chip-8 Extensions and Variations**: A comparative study used to differentiate between original VIP and later SCHIP/XO-CHIP implementations.

---
*Developed for Academic Research - Yuxing Chen (LNU) - 为学术研究目的开发*
