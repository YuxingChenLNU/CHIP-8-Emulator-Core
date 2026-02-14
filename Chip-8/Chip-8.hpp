#ifndef CHIP8_HPP  
#define CHIP8_HPP

#include <cstdint>// Required for fixed-width integers. 
// We need exact 8-bit and 16-bit types to simulate hardware registers 
// accurately across different platforms. 

#include <array>// Use array for fixed size. Vector's dynamic resizing (heap allocation) 
                 // is unnecessary and slow for a 4KB fixed-memory system.   

#include <string>

class Chip8 {      // chip-8 encapsulate the entire computer as an object
public:
    Chip8();       // equal to press the start button
    ~Chip8() = default;

    bool LoadROM(const std::string& filename); // loading data to memory
    void Cycle();                              // cycling running
    void Initialize();
private:
    // core hardware simulation

    // Current Opcode: The 16-bit instruction being processed.
    uint16_t opcode{ 0 };

    // memory:4096B 
	std::array<uint8_t, 4096> memory{};

    // 16 GPR (V0-VF). 
    // Named in Hex (0-F). These are built into the CPU for ultra-fast access.
    std::array<uint8_t, 16> V{};

    // IPR fast find memory address
    uint16_t index{ 0 };

    // PC Program Counter, tracking the memory address of the next instruction.
    uint16_t pc{ 0 };

    // Stack 16-level stack to store return addresses (uint16_t).
    // Supports "Last-In, First-Out" (LIFO) for nested subroutine calls.
    std::array<uint16_t, 16> stack{};

    // Stack Pointer 
    uint8_t sp{ 0 }; //initializing at the bottom

    // Fixed 60Hz timers as per CHIP-8 hardware spec. 
    // Do not increase to modern high frequencies, or game logic will accelerate!
    uint8_t delay_timer{ 0 };
    uint8_t sound_timer{ 0 };

    // 64x32 pixels. Using uint32_t to store RGBA color values for easy rendering.
    std::array<uint32_t, 64 * 32> display{};

    // Hex Keypad (0-F): Tracks the state of each of the 16 keys.
    std::array<uint8_t, 16> keypad{};
};

#endif
