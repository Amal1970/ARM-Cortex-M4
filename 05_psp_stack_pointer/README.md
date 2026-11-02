# Exercise 05 – MSP and PSP Stack Pointer Demo

## 1. Objective

The objective of this exercise is to understand the two stack pointers available in the ARM Cortex-M4 processor: Main Stack Pointer (MSP) and Process Stack Pointer (PSP).

This exercise demonstrates how to read the stack pointer registers, configure the PSP with a new address, and switch Thread mode from MSP to PSP using the CONTROL register.

## 2. Hardware and Software Requirements

### Hardware
- STM32F407G Discovery Board
- STM32F407VG ARM Cortex-M4 microcontroller
- ST-Link debugger

### Software
- STM32CubeIDE
- Visual Studio Code
- ARM GNU Toolchain
- GDB
- OpenOCD
- WSL Ubuntu

## 3. Introduction to Stack Memory

A stack is a region of RAM used by the processor to temporarily store information during program execution.

It is commonly used for:
- Local variables
- Function return addresses
- Saved registers
- Function call information

The ARM Cortex-M4 uses a descending stack, meaning the stack grows from higher memory addresses towards lower memory addresses.

## 4. Main Stack Pointer (MSP)

The Main Stack Pointer is the default stack pointer after processor reset.

Important characteristics:
- The initial MSP value is loaded from the first entry of the vector table.
- It is used by the processor in Handler mode.
- It is also used in Thread mode by default.
- It is commonly used for exception and interrupt handling.

## 5. Process Stack Pointer (PSP)

The Process Stack Pointer is an alternative stack pointer available in the Cortex-M4.

Important characteristics:
- It can be selected for use in Thread mode.
- It is commonly used in RTOS-based applications.
- It allows application tasks to use separate stack regions.
- It is not used in Handler mode.

## 6. CONTROL Register

The CONTROL register determines which stack pointer is used in Thread mode.

The SPSEL bit (bit 1) selects the active stack pointer.

| SPSEL | Active stack in Thread mode |
|---|---|
| 0 | MSP |
| 1 | PSP |

Handler mode always uses MSP, regardless of the SPSEL bit.

## 7. Implementation

The program performs the following operations:

1. Reads the initial MSP value using the MRS instruction.
2. Reads the initial PSP value using the MRS instruction.
3. Loads a new address into PSP using the MSR instruction.
4. Reads PSP again to verify the updated value.
5. Reads the CONTROL register.
6. Sets bit 1 of CONTROL to select PSP in Thread mode.
7. Executes an ISB instruction to synchronize instruction execution.
8. Reads CONTROL again to verify the stack selection.

## 8. ARM Assembly Instructions Used

| Instruction | Description |
|---|---|
| MRS | Reads a special register into a general-purpose register |
| MSR | Writes a general-purpose register into a special register |
| ORR | Performs a bitwise OR operation |
| ISB | Instruction Synchronization Barrier |

### Switching Thread Mode from MSP to PSP

The following assembly operations are used:

```asm
MRS R0, CONTROL
ORR R0, R0, #2
MSR CONTROL, R0
ISB
```

- MRS reads the CONTROL register.
- ORR sets bit 1 (SPSEL).
- MSR writes the updated value back to CONTROL.
- ISB ensures subsequent instructions use the updated processor context.

## 9. GDB Debugging

GDB is used to inspect the special registers and verify the stack pointer configuration.

Useful commands:

```gdb
info registers
p/x $msp
p/x $psp
p/x $control
```

These commands help observe:
- The initial MSP value.
- The initial PSP value.
- The updated PSP value.
- The CONTROL register after switching.

## 10. Concepts Learned

- Stack memory organization in ARM Cortex-M4.
- Descending stack operation.
- Difference between MSP and PSP.
- Special-purpose processor registers.
- Reading and writing special registers using inline assembly.
- Thread mode stack pointer selection.
- Using the CONTROL register.
- Instruction Synchronization Barrier.
- Debugging processor registers using GDB.

## 11. Conclusion

This exercise demonstrates the operation of the Main Stack Pointer and Process Stack Pointer in the ARM Cortex-M4 processor. It provides practical experience in accessing special-purpose registers and switching Thread mode stack selection using inline assembly.

Understanding MSP and PSP is an important foundation for learning RTOS task management, exception handling, and advanced ARM Cortex-M architecture.