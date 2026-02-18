# CHIP-8 Emulator (C++17)

A modular implementation of the CHIP-8 virtual machine written in modern C++17. This project focuses on instruction-level execution, memory modeling, and stack-based control flow within a constrained hardware architecture.

---

## Overview

CHIP-8 is a simple interpreted programming language originally developed for the RCA COSMAC VIP. This implementation recreates the core runtime components:

* **Memory:** 4KB RAM address space (0x000 - 0xFFF).
* **Registers:** 16 general-purpose 8-bit registers (V0–VF).
* **Stack:** 16-level call stack for subroutines.
* **Index Register:** 16-bit register (I) for memory addressing.
* **Timers:** 60Hz Delay and Sound timers.
* **Display:** 64x32 monochrome display buffer.
* **Instruction Set:** Full 35-opcode set.

---

## Architecture

### Memory Model
* **RAM:** Implemented via `std::array<uint8_t, 4096>`.
* **Program Counter:** Initialized at `0x200` (standard for most ROMs).
* **Fontset:** Loaded into the reserved interpreter memory region (0x050 - 0x0A0).
* **Stack:** Fixed-size array with manual stack pointer (SP) control.

### Fetch–Decode–Execute Cycle
The CPU cycle follows a standard pipeline:
1. **Fetch:** `uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];`
2. **Decode:** Bitmasking and shifting extract instruction fields (X, Y, N, NNN).
3. **Execute:** Handled through a structured switch-based opcode dispatch.

### Graphics & Logic
* **Rendering:** XOR-based sprite drawing logic.
* **Collision Detection:** If a pixel flips from 1 to 0 during rendering, the VF register is set to 1.

---

## Implementation Highlights

### Hardware-Accurate Carry (8xy4)
Prevents silent overflow of 8-bit registers by using a wider temporary type:
```cpp
uint16_t sum = V[X] + V[Y];
V[0xF] = (sum > 0xFF); // Carry flag set on overflow
V[X] = static_cast<uint8_t>(sum & 0xFF);
```

### Stack Management
* **Subroutine Calls (2nnn):** Pushes the current Program Counter (PC) onto the stack and increments the stack pointer before jumping to address `nnn`.
* **Return Logic (00EE):** Restores the PC from the top of the stack and decrements the stack pointer, ensuring correct return alignment for nested calls.
* **Stability:** Verified against standard test ROMs to ensure stack pointer limits (0-15) are respected and return addresses are preserved.

---

## Usage

### Build
```bash
g++ -std=c++17 -Iinclude src/Chip8.cpp main.cpp -o chip8
```

### Run
```bash
./chip8 path/to/rom.ch8
```

---

## Project Structure
```text
.
├── include/
│   └── Chip8.hpp    # Core emulator class & state definition
├── src/
│   └── Chip8.cpp    # Opcode implementations & CPU logic
└── main.cpp         # Entry point & emulation loop
```

---

## Current Status

- [x] Core CPU instruction set implemented
- [x] Stable fetch/decode/execute loop
- [x] Verified with classic ROMs (e.g., PONG)
- [x] Display and collision logic functional
- [x] Stack and timers operational
- [ ] SDL2 graphical front-end (planned)
- [ ] Extended opcode variants (planned)
---

## References
* Cowgod’s CHIP-8 Technical Reference
* RCA COSMAC VIP Manual (1978)
* Mastering CHIP-8 (Matthew Mikolay)
