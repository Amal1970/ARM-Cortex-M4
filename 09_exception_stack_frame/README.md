# Exercise 09 – Exception Stack Frame Demo

## Objective
To understand how the ARM Cortex-M4 automatically saves CPU registers onto the stack during exception entry and how these values can be accessed inside an exception handler.

## Hardware
- STM32F407G Discovery Board
- STM32F407VG microcontroller (ARM Cortex-M4)

## Concepts Learned
- Exception entry and exception return
- Automatic exception stacking
- Basic exception stack frame
- Main Stack Pointer (MSP)
- Process Stack Pointer (PSP)
- EXC_RETURN value
- Stack frame register indexing
- SVC exception handling

## Implementation
The program loads known values into R0, R1, R2 and R3 before executing `SVC #0`.

When the SVC exception occurs:
1. The processor automatically saves the basic exception stack frame.
2. Execution transfers to `SVC_Handler()`.
3. The handler identifies whether MSP or PSP was used.
4. It accesses the saved stack frame.
5. It extracts the saved R0, R1, R2, R3 and PC values.
6. The extracted values are stored in global variables for debugging.

## Basic Exception Stack Frame

| Index | Register |
|---|---|
| 0 | R0 |
| 1 | R1 |
| 2 | R2 |
| 3 | R3 |
| 4 | R12 |
| 5 | LR |
| 6 | PC |
| 7 | xPSR |

Each register occupies 4 bytes. The basic exception stack frame occupies 32 bytes.

## Expected Results

| Variable | Expected Value |
|---|---:|
| stacked_r0 | 10 |
| stacked_r1 | 20 |
| stacked_r2 | 30 |
| stacked_r3 | 40 |
| stacked_pc | Address after SVC instruction |

## Key Learning
The Cortex-M4 automatically preserves the interrupted program's execution context during exception entry. The exception handler can access this saved information through the stack pointer.

## Build Instructions
```bash
make clean
make
```

## Future Improvements
- Extract R12, LR and xPSR.
- Compare MSP and PSP exception stacking.
- Inspect the exception stack frame using GDB.