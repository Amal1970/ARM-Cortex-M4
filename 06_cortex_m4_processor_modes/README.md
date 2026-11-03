# Exercise 06 – Cortex-M4 Processor Modes

## 1. Objective

The objective of this exercise is to understand the execution modes and privilege levels of the ARM Cortex-M4 processor.

This exercise demonstrates switching Thread mode from privileged to unprivileged execution and generating an SVC exception to observe the transition into Handler mode.

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

## 3. Introduction to Processor Modes

The ARM Cortex-M4 operates in two main execution modes:

### Thread Mode
- Used for normal application execution.
- Executes the main program and application functions.
- Can operate in privileged or unprivileged state.

### Handler Mode
- Used for exception and interrupt handling.
- Always executes with privileged access.
- Uses the Main Stack Pointer (MSP).

## 4. Privileged and Unprivileged Execution

Thread mode supports two privilege levels.

| Feature | Privileged | Unprivileged |
|---|---|---|
| Execute application code | Yes | Yes |
| Access restricted system registers | Yes | No |
| Modify privilege state directly | Yes | No |
| Execute normal instructions | Yes | Yes |

Handler mode always executes with privileged access.

## 5. CONTROL Register

The CONTROL register determines the privilege level and stack selection in Thread mode.

| Bit | Name | Function |
|---|---|---|
| Bit 0 | nPRIV | Selects privilege level |
| Bit 1 | SPSEL | Selects stack pointer |

The nPRIV bit determines the privilege level:

- 0 – Privileged Thread mode
- 1 – Unprivileged Thread mode

## 6. Implementation

The program performs the following operations:

1. Reads the initial CONTROL register using MRS.
2. Sets bit 0 of CONTROL to enter unprivileged Thread mode.
3. Executes ISB to synchronize instruction execution.
4. Reads CONTROL again to verify the change.
5. Generates an SVC exception using the SVC instruction.
6. Executes the SVC handler in privileged Handler mode.
7. Records the active exception number and updates an exception status variable.

## 7. SVC Exception

SVC stands for Supervisor Call.

It is a software-generated exception used by unprivileged application code to request privileged services.

The instruction used in this exercise is:

```asm
SVC #0
```

When executed, the processor enters Handler mode and executes the SVC handler.

The SVC exception number is 11.

## 8. ARM Assembly Instructions Used

| Instruction | Description |
|---|---|
| MRS | Reads a special register |
| MSR | Writes a special register |
| ORR | Performs a bitwise OR operation |
| ISB | Instruction Synchronization Barrier |
| SVC | Generates a Supervisor Call exception |

## 9. GDB Debugging

GDB is used to verify the CONTROL register and exception execution.

Useful commands:

```gdb
break SVC_Handler
continue
info registers
p exception_status
p active_exception
```

The expected active exception number is 11, indicating execution of the SVC handler.

## 10. Concepts Learned

- Thread mode and Handler mode.
- Privileged and unprivileged execution.
- CONTROL register and nPRIV bit.
- Software-generated exceptions.
- SVC exception handling.
- Exception entry and return.
- Reading special registers using inline assembly.
- Debugging processor execution using GDB.

## 11. Conclusion

This exercise demonstrates the different execution modes and privilege levels of the ARM Cortex-M4 processor. It provides practical experience in modifying the CONTROL register, entering unprivileged Thread mode and generating an SVC exception to execute privileged Handler-mode code.