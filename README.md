# CHIP-8 Emulator (C++17)

A modular implementation of the CHIP-8 virtual machine written in modern C++17. This repository consolidates and documents a previously developed emulator project, reorganized for clarity and public presentation.

## Overview

CHIP-8 is a simple interpreted programming language created for the RCA COSMAC VIP in the 1970s. This project recreates the core runtime architecture, focusing on instruction-level execution and memory modeling.

### System Specifications
* **Memory:** 4KB RAM address space (0x000 - 0xFFF).
* **Registers:** 16 general-purpose 8-bit registers (V0–VF).
* **Stack:** 16-level call stack for subroutines.
* **Index Register:** 16-bit register (I) for memory addressing.
* **Timers:** 60Hz Delay and Sound timers.
* **Display:** 64x32 monochrome display buffer.
* **Instruction Set:** Full 35-opcode set.

## Architecture

### Memory Model
* **RAM:** Implemented via `std::array<uint8_t, 4096>`.
* **Program Counter:** Initialized at `0x200` (standard for most ROMs).
* **Fontset:** Loaded into the reserved interpreter memory region.
* **Stack:** Fixed-size array with manual stack pointer (SP) control.

### Fetch-Decode-Execute Cycle
The CPU cycle follows a standard fetch-decode-execute pipeline:
1. **Fetch:** `uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];`
2. **Decode:** Bitwise masking and shifting extract instruction fields (X, Y, N, NNN).
3. **Execute:** Handled through a structured switch-based opcode dispatch.

### Graphics Logic
* **Buffer:** 64x32 monochrome pixel array.
* **Rendering:** XOR-based sprite drawing logic.
* **Collision Detection:** If a pixel flips from 1 to 0 during rendering, VF is set to 1.

## Implementation Highlights

### Hardware-Accurate Carry (8xy4)
To mirror hardware behavior and prevent silent overflows:

    uint16_t sum = V[X] + V[Y];
    V[0xF] = (sum > 0xFF); // Carry flag set on overflow
    V[X] = static_cast<uint8_t>(sum & 0xFF);

### Stack Management
* Subroutine calls push the current PC to the stack before jumping.
* Manual stack pointer increment/decrement ensures proper return alignment.
* Validated against standard test ROMs for nested call stability.

## Design Decisions
* **Type Safety:** Use of fixed-width integers (uint8_t, uint16_t) for cross-platform consistency.
* **Memory Safety:** Utilized std::array instead of raw pointers for memory bounds safety.
* **Modularity:** Clear separation between CPU logic and the rendering/IO layer.
* **Low Abstraction:** Explicit control over memory and stack to maintain performance and transparency.

## Project Structure

    .
    ├── include/
    │   └── Chip8.hpp    # Core emulator class & state definition
    ├── src/
    │   └── Chip8.cpp    # Opcode implementations & CPU logic
    └── main.cpp         # Entry point & emulation loop

## Current Status
* [x] Core CPU implementation complete.
* [x] Stable Fetch-Decode-Execute cycle.
* [x] Verified with classic ROMs (e.g., PONG).
* [ ] Sound support (Beeper).
* [ ] Graphical Front-end (SDL2/SFML).

## References
* Cowgod's CHIP-8 Technical Reference
* RCA COSMAC VIP Manual (1978)
* Mastering CHIP-8 (Matthew Mikolay)
