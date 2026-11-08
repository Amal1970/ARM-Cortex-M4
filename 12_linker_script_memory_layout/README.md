# Exercise 12: Linker Script and Memory Layout

## Objective
To understand how a linker script defines the memory layout of a microcontroller and how program sections are assigned to Flash and RAM.

## Hardware
- STM32F407G Discovery Board
- STM32F407VG Microcontroller
- ARM Cortex-M4 Processor

## Concepts Covered
- Linker script
- Flash and SRAM memory regions
- MEMORY and SECTIONS directives
- Program sections: `.text`, `.rodata`, `.data`, and `.bss`
- Load Memory Address (LMA) and Virtual Memory Address (VMA)
- Linker symbols
- ELF and map files

## 1. What is a Linker Script?

A linker script is a file that tells the linker how to organize a program in the microcontroller's memory.

It defines:
- Available memory regions.
- Starting addresses and sizes of memory regions.
- Where program sections should be placed.
- Symbols used by startup code.

In our project, the linker script is named `stm32_ls.ld`.

## 2. STM32F407VG Memory Layout

The STM32F407VG contains the following main memory regions:

| Memory | Starting Address | Size |
|---|---|---|
| Flash | 0x08000000 | 1 MB |
| Main SRAM | 0x20000000 | 128 KB |
| CCM SRAM | 0x10000000 | 64 KB |

Flash is non-volatile memory and stores the program even when power is removed.

SRAM is volatile memory used for variables, stack, and other runtime data.

CCM (Core Coupled Memory) is a separate RAM region intended for CPU access. It is not accessible by DMA.

## 3. MEMORY Directive

The `MEMORY` directive defines the available memory regions in the linker script.

Each region is described using:
- Name
- Access permissions
- Origin (starting address)
- Length (size)

For example, a linker script can define FLASH and RAM regions using their starting addresses and sizes.

## 4. SECTIONS Directive

The `SECTIONS` directive tells the linker where to place different program sections.

Important sections include:

| Section | Purpose | Typical Location |
|---|---|---|
| `.isr_vector` | Interrupt vector table | Flash |
| `.text` | Program instructions and code | Flash |
| `.rodata` | Read-only constants | Flash |
| `.data` | Initialized global and static variables | RAM |
| `.bss` | Uninitialized or zero-initialized global and static variables | RAM |

The initial values of `.data` are stored in Flash and copied into RAM during startup.

The `.bss` section is cleared to zero during startup.

## 5. LMA and VMA

- **LMA (Load Memory Address):** The address where a section's initial data is stored in the program image.
- **VMA (Virtual Memory Address):** The address where the section is located when the program runs.

For the `.data` section:
- LMA is normally in Flash.
- VMA is normally in SRAM.

This allows initialized variables to be stored in Flash and used in RAM during execution.

## 6. Linker Symbols

The linker script can define symbols that are used by startup code.

Common examples include:

- `_estack` – Initial stack pointer value.
- `_sidata` – Start address of the initial `.data` values in Flash.
- `_sdata` – Start of the `.data` section in RAM.
- `_edata` – End of the `.data` section.
- `_sbss` – Start of the `.bss` section.
- `_ebss` – End of the `.bss` section.

The exact symbol names depend on the linker script.

## 7. Relationship Between Linker Script and Startup Code

The linker script and startup code work together.

1. The linker script defines memory regions and section boundaries.
2. The linker places the program sections in the appropriate memory regions.
3. The linker provides symbols representing section addresses.
4. Startup code uses these symbols to copy `.data` from Flash to RAM.
5. Startup code clears the `.bss` section.
6. The program proceeds to `main()`.

## 8. ELF and Map Files

- **ELF file:** Contains the linked program, including code, data, and debugging information.
- **Map file:** Provides information about memory addresses, section placement, and symbol locations.

These files help developers understand how the program occupies memory.

## Conclusion

The linker script is an important part of embedded software development. It defines how program sections are arranged in memory and provides the addresses required by startup code. Understanding memory layout helps when developing bare-metal firmware and debugging embedded applications.