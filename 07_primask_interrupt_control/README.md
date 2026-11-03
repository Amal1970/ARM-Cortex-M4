# Exercise 07 – PRIMASK Interrupt Control

## 1. Objective

The objective of this exercise is to understand how the ARM Cortex-M4 processor controls configurable interrupts using the PRIMASK special-purpose register.

This exercise focuses on reading PRIMASK, disabling interrupts, enabling interrupts and understanding critical sections.

## 2. Introduction to PRIMASK

PRIMASK is a special-purpose 1-bit register in the ARM Cortex-M4 processor.

It controls the activation of configurable-priority exceptions.

| PRIMASK | Behaviour |
|---|---|
| 0 | Configurable interrupts are enabled, subject to other interrupt masks and priorities |
| 1 | Configurable interrupts are disabled |

**Important:** NMI and HardFault exceptions are not masked by PRIMASK.

## 3. Assembly Instructions

### A. Reading PRIMASK – MRS

```asm
MRS R0, PRIMASK
```

- Reads the current PRIMASK value.
- Stores the value in a general-purpose register.

### B. Disabling Interrupts – CPSID i

```asm
CPSID i
```

- Sets PRIMASK to 1.
- Prevents configurable-priority exceptions from being activated.

### C. Enabling Interrupts – CPSIE i

```asm
CPSIE i
```

- Clears PRIMASK to 0.
- Allows configurable-priority exceptions to be activated again, subject to other conditions.

## 4. Critical Sections

A critical section is a section of code that must execute without interference from configurable-priority interrupts.

PRIMASK can be used to protect such sections.

General execution sequence:

1. Disable interrupts using `CPSID i`.
2. Execute the critical section.
3. Re-enable interrupts using `CPSIE i`.

In production firmware, the previous PRIMASK state should be saved and restored instead of blindly enabling interrupts.

## 5. Behaviour During Interrupt Masking

When PRIMASK is set to 1:

- The SysTick timer continues counting.
- Configurable interrupts cannot execute.
- An eligible interrupt can become pending.
- After PRIMASK is cleared, pending exceptions can be serviced according to their priority.

## 6. Important Registers and Instructions

| Register / Instruction | Purpose |
|---|---|
| PRIMASK | Controls configurable interrupt masking |
| MRS | Reads a special-purpose register |
| CPSID i | Disables configurable interrupts |
| CPSIE i | Enables configurable interrupts |

## 7. Concepts Learned

- PRIMASK special-purpose register.
- Global configurable interrupt masking.
- CPSID and CPSIE instructions.
- Reading special registers using MRS.
- Critical sections.
- Pending interrupt behaviour.
- Difference between interrupt masking and stopping a timer.

## 8. Conclusion

PRIMASK provides a simple mechanism for controlling configurable interrupts in the ARM Cortex-M4 processor. Understanding this register is important when developing embedded firmware that requires protected critical sections and controlled interrupt execution.