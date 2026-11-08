# Exercise 10 – Vector Table Inspection

## Objective

To understand the vector table structure of the ARM Cortex-M4 processor and how it uses the vector table to locate exception and interrupt handler addresses.

## Hardware

- STM32F407G Discovery Board
- STM32F407VG microcontroller
- ARM Cortex-M4 processor

## Concepts Learned

- Vector table
- Initial Main Stack Pointer (MSP)
- Reset Handler
- Exception handler addresses
- Interrupt Request (IRQ) mapping
- Vector Table Offset Register (VTOR)
- Exception vector numbering
- Relationship between startup code and vector table

## 1. What is a Vector Table?

The vector table is a data structure stored in memory that contains the initial stack pointer value and addresses of exception and interrupt handlers.

When the processor starts or an exception occurs, it uses the vector table to determine the appropriate address for execution.

## 2. Structure of the Vector Table

The first two entries are:

| Entry | Description |
|---|---|
| 0 | Initial Main Stack Pointer (MSP) value |
| 1 | Reset Handler address |

The remaining entries contain addresses of processor exception handlers and external interrupt handlers.

### Important Cortex-M4 Exception Entries

| Exception Number | Exception |
|---|---|
| 1 | Reset |
| 2 | NMI |
| 3 | HardFault |
| 4 | MemManage |
| 5 | BusFault |
| 6 | UsageFault |
| 11 | SVCall |
| 12 | Debug Monitor |
| 14 | PendSV |
| 15 | SysTick |

External interrupts start from exception number 16.

## 3. How the Vector Table Works

During processor startup:

1. The processor reads the initial MSP value from the first vector table entry.
2. It reads the Reset Handler address from the second entry.
3. It loads the Reset Handler address into the Program Counter (PC).
4. Execution begins at the Reset Handler.
5. The startup code performs the required initialization before calling main().

When an exception occurs, the processor uses its exception number to locate the corresponding handler entry in the vector table.

## 4. Vector Table Offset Register (VTOR)

The Vector Table Offset Register (VTOR) determines the memory address of the vector table.

For the Cortex-M4, VTOR is located at:

`0xE000ED08`

It allows the vector table to be relocated to another valid memory location, subject to alignment requirements.

## 5. Relationship with Startup Code

The startup file defines the vector table and maps exception and interrupt entries to their corresponding handler functions.

For example:

- Reset_Handler
- NMI_Handler
- HardFault_Handler
- SVC_Handler
- PendSV_Handler
- SysTick_Handler
- EXTI0_IRQHandler

The vector table connects processor exceptions and interrupts to the appropriate functions defined in the firmware.

## 6. Key Learning

The vector table is essential for exception and interrupt handling in ARM Cortex-M4. It provides the processor with the initial stack pointer and the addresses of all exception and interrupt handlers.

Understanding the vector table helps in understanding startup code, interrupt handling and low-level embedded firmware development.

## Future Improvements

- Inspect vector table entries using GDB.
- Examine the vector table in the ELF file.
- Understand vector table relocation using VTOR.