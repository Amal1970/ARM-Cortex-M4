# Exercise 11 – Startup Code Analysis

## Objective

To understand the startup sequence of an ARM Cortex-M4 microcontroller and analyze how startup code initializes the system before transferring execution to the main() function.

## Hardware

- STM32F407G Discovery Board
- STM32F407VG microcontroller
- ARM Cortex-M4 processor

## Concepts Learned

- Reset sequence
- Reset Handler
- Vector table
- Stack pointer initialization
- .data section initialization
- .bss section initialization
- System initialization
- Calling main()
- Default interrupt handlers

## 1. What is Startup Code?

Startup code is the low-level code executed immediately after the microcontroller comes out of reset.

It prepares the processor and memory environment required by the C program before execution reaches main().

## 2. Startup Sequence

The general startup sequence is:

1. Processor reset occurs.
2. Initial Main Stack Pointer (MSP) is loaded from the vector table.
3. The Reset Handler address is loaded into the Program Counter (PC).
4. Execution begins at Reset_Handler.
5. The .data section is initialized.
6. The .bss section is initialized.
7. System initialization is performed.
8. The main() function is called.

## 3. Memory Initialization

### .data Section

The .data section contains initialized global and static variables.

During startup, initial values are copied from Flash memory into SRAM.

Example:

```c
int count = 10;
```

The initial value is stored in Flash and copied into RAM during startup.

### .bss Section

The .bss section contains uninitialized or zero-initialized global and static variables.

During startup, this section is cleared to zero.

Example:

```c
int counter;
```

After startup initialization, counter has a value of zero.

## 4. Reset Handler

Reset_Handler is the first function executed after the processor loads its address from the vector table.

Its responsibilities generally include:

- Setting up the runtime environment.
- Initializing memory sections.
- Performing system initialization.
- Calling main().

## 5. Default Interrupt Handlers

Startup code also provides default handlers for exceptions and interrupts.

If a specific interrupt handler is not implemented, the corresponding vector may point to a default handler.

A user-defined handler can replace a weak default handler using the same function name.

Examples:

- HardFault_Handler
- SVC_Handler
- SysTick_Handler
- PendSV_Handler

## 6. Relationship Between Startup Code and Linker Script

Startup code uses linker-defined symbols to identify memory section boundaries.

For example, linker symbols can specify:

- Start and end addresses of .data.
- Load address of .data in Flash.
- Start and end addresses of .bss.

These addresses allow startup code to initialize memory correctly.

## 7. Key Learning

Startup code prepares the processor and memory before the application begins executing.

Understanding startup code helps in learning bare-metal programming, firmware initialization, vector table configuration and embedded system debugging.

## Future Improvements

- Trace Reset_Handler execution using GDB.
- Inspect .data and .bss initialization
- Analyze the startup assembly and linker symbols.
- Compare custom startup code with STM32 HAL startup files.