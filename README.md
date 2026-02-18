# CHIP-8 Emulator (C++17)

A modular implementation of the CHIP-8 virtual machine written in modern C++17.

This repository consolidates and documents a previously developed emulator project, reorganized for clarity and public presentation.

---

## Overview

CHIP-8 is a simple interpreted programming language created for the RCA COSMAC VIP in the 1970s.

This project recreates the core runtime architecture:

- 4KB memory space
- 16 general-purpose 8-bit registers (V0–VF)
- 16-level call stack
- 16-bit index register
- Delay and sound timers
- 64×32 monochrome display buffer
- Full 35-opcode instruction set

The focus of this implementation is instruction-level execution and memory modeling rather than graphical interface design.

---

## Architecture

### Memory Model

- RAM: `std::array<uint8_t, 4096>`
- Program Counter initialized at `0x200`
- Fontset loaded into reserved memory region
- Fixed-size stack with manual stack pointer control

---

### Fetch–Decode–Execute Cycle

Each CPU cycle performs:

```cpp
uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
Bitwise masking and shifting extract instruction fields.

Execution is handled through structured switch-based opcode dispatch.

Graphics Logic
64×32 monochrome display buffer

XOR-based sprite rendering

Collision detection via VF register

If a pixel flips from 1 to 0 during rendering, VF is set to indicate collision.

Implementation Highlights
Carry Handling (8xy4)
uint16_t sum = V[X] + V[Y];
V[0xF] = (sum > 0xFF);
V[X] = sum & 0xFF;
This approach prevents silent overflow of uint8_t registers and mirrors hardware-style carry propagation.

Stack Management
Subroutine calls push the current program counter to the stack.

Manual stack pointer increment/decrement ensures proper return alignment.

Stack behavior was validated through ROM testing.

Design Decisions
Fixed-width integers (uint8_t, uint16_t) for predictable behavior

std::array instead of raw pointers for safer memory handling

Clear separation between CPU logic and rendering layer

Explicit control over memory and stack without heavy abstraction

Project Structure
/include
    Chip8.hpp
/src
    Chip8.cpp
main.cpp
Current Status
Core CPU implementation complete

Stable execution cycle

Verified with classic CHIP-8 ROMs (e.g., PONG)

References
Cowgod’s CHIP-8 Technical Reference

RCA COSMAC VIP Manual (1978)

Mastering CHIP-8 (Matthew Mikolay)
