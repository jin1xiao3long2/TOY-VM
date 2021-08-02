#pragma once

#include <cstdint>

namespace csvm {
    enum class buildin_types : std::uint8_t
    {
        vm_ptr   = 0x00, // 64-bit Unsigned Integer
        vm_int   = 0x01, // 64-bit Integer
        vm_float = 0x02, // Double precision Float(64-bit)
    };

    /**
     * Variable Life Cycle
     * 
     * 0: Reachable(for Garbage Collection)
     * 1: Degradable(for Runtime Degeneration)
     * 2: Static Variable
     * 3: Stack Variable
     * 4: Heap Variable
     * 5: Foreign Referenced
     * 6-7: Reserved
     */
    enum class life_cycle_mask : std::uint8_t
    {
        reachable  = 0b10000000,
        degradable = 0b01000000,
        in_static  = 0b00100000,
        in_stack   = 0b00010000,
        in_heap    = 0b00001000,
        foreign    = 0b00000100
    };

    struct type_tag_impl
    {
		std::uint16_t extend_type  = 0;
		std::uint8_t building_type = 0;
		type_tag_impl(std::uint32_t t)
		{
			building_type = (t & 0x000000ff);
			extend_type = (t & 0x00ffff00) >> 8;
		}
	};

    struct variable_impl
    {
        std::uint8_t life_cycle = 0;
        type_tag_impl type_tag;
        void *extension_field;
        void *data;
    };
}