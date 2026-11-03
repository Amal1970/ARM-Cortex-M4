# Exercise 08 – SVC Exception Demo

## Objective
To understand and demonstrate the Supervisor Call (SVC) exception in the ARM Cortex-M4 processor and extract the SVC number from the instruction that triggered the exception.

## Hardware
- STM32F407G Discovery Board
- STM32F407VG microcontroller (ARM Cortex-M4)

## Concepts Learned
- Supervisor Call (SVC) exception
- Exception entry and return
- Automatic exception stack frame
- MSP and PSP stack selection
- EXC_RETURN value
- IPSR register
- Inline assembly instructions: `MRS`, `TST`, `ITE`
- Extracting the SVC immediate value

## Implementation
The program executes an SVC instruction with an immediate value, such as `SVC #2`.

When the processor executes this instruction:
1. It generates an SVC exception.
2. The processor automatically saves the basic exception stack frame.
3. Execution transfers to `SVC_Handler()`.
4. The handler identifies whether MSP or PSP was used.
5. It reads the stacked PC and locates the SVC instruction at `PC - 2`.
6. It extracts the lower 8 bits to obtain the SVC number.
7. It reads IPSR to identify the active exception number.

## Expected Results

| Variable | Expected Value |
|---|---:|
| SVC number | 2 |
| Active exception number | 11 |

Changing the instruction to `SVC #5` should result in an extracted SVC number of 5.

## Key Learning
SVC allows Thread mode software to request services through an exception. The SVC handler executes in privileged Handler mode, even when the calling Thread mode code is unprivileged.

## Build
```bash
make clean
make
```

## Future Improvements
- Implement multiple SVC numbers for different services.
- Use SVC to create a simple system-call mechanism.