# Cortex-M4 Inline Assembly — STM32F407G Discovery

## 1. Objective

The objective of this exercise is to understand how ARM Cortex-M4 assembly instructions can be embedded directly into C programs using GCC Inline Assembly.

The exercise implements five fundamental processor operations using ARM assembly instructions: addition, subtraction, bitwise AND, bitwise OR, and bitwise XOR.

The results of these operations are displayed using the four onboard LEDs of the STM32F407G Discovery board. This demonstrates how low-level processor instructions can interact with GPIO peripherals to control physical hardware.

The implementation uses Embedded C, GCC Extended Inline Assembly, and direct register-level programming without relying on STM32 HAL functions.

## 2. Hardware and Software Requirements

### Hardware
- STM32F407G Discovery development board
- STM32F407VG ARM Cortex-M4 microcontroller
- Four onboard LEDs (Green, Orange, Red, and Blue)

### Software and Tools
- STM32CubeIDE
- Visual Studio Code
- WSL Ubuntu
- ARM GNU Toolchain (`arm-none-eabi-gcc`)
- Custom Makefile
- Git and GitHub

## 3. ARM Cortex-M4 General-Purpose Registers

The ARM Cortex-M4 processor contains general-purpose registers used for arithmetic, logical operations, and data manipulation.

Registers R0–R12 are general-purpose registers. The processor executes most arithmetic and logical instructions using values stored in these registers.

In GCC Inline Assembly, register constraints allow the compiler to select suitable registers and transfer values between C variables and assembly instructions.

This exercise uses the `r` constraint to allow GCC to allocate general-purpose registers for the input and output operands.

## 4. GCC Extended Inline Assembly

GCC provides an inline assembly feature that allows ARM assembly instructions to be written directly inside C programs.

The general syntax used in this exercise is:

```c
__asm volatile (
    "assembly instruction"
    : output operands
    : input operands
    : clobbered registers
);
```

### Explanation of the syntax

- `__asm`: Introduces an assembly instruction inside C code.
- `volatile`: Prevents the compiler from removing the assembly statement as an unnecessary operation.
- Assembly instruction: Specifies the ARM instruction to execute.
- Output operands: Define where the result of the assembly instruction is stored.
- Input operands: Supply values from C variables to the assembly instruction.
- Clobbers: Specify registers or processor state modified by the assembly statement.

### Register Constraints Used

The `r` constraint tells GCC to use a general-purpose register.

The `=` modifier indicates an output-only operand.

For example:

```c
__asm volatile(
    "ADD %0,%1,%2"
    : "=r"(sum)
    : "r"(a), "r"(b)
);
```

Here:
- `%0` represents the output operand (`sum`).
- `%1` represents the first input operand (`a`).
- `%2` represents the second input operand (`b`).

GCC handles register allocation and transfers the result back into the C variable.

## 5. ARM Assembly Instructions Implemented

Five ARM assembly instructions are implemented in this exercise.

### 5.1 ADD — Addition

The `ADD` instruction performs arithmetic addition.

**Operation:**

```asm
ADD destination, operand1, operand2
```

It adds two values and stores the result in the destination register.

**C function:** `asm_add()`

### 5.2 SUB — Subtraction

The `SUB` instruction performs arithmetic subtraction.

**Operation:**

```asm
SUB destination, operand1, operand2
```

It subtracts the second operand from the first operand and stores the result.

**C function:** `asm_sub()`

### 5.3 AND — Bitwise AND

The `AND` instruction performs a bitwise AND operation.

A result bit is set to 1 only when both corresponding input bits are 1.

**Operation:**

```asm
AND destination, operand1, operand2
```

**C function:** `asm_and()`

### 5.4 ORR — Bitwise OR

The `ORR` instruction performs a bitwise OR operation.

A result bit is set to 1 when at least one of the corresponding input bits is 1.

**Operation:**

```asm
ORR destination, operand1, operand2
```

**C function:** `asm_orr()`

### 5.5 EOR — Bitwise Exclusive OR

The `EOR` instruction performs a bitwise Exclusive OR operation.

A result bit is set to 1 when the corresponding input bits are different.

**Operation:**

```asm
EOR destination, operand1, operand2
```

**C function:** `asm_eor()`

## 6. GPIO Configuration

The four onboard LEDs of the STM32F407G Discovery board are connected to GPIO Port D.

| LED | GPIO Pin | Bit Position |
|---|---|---|
| Green | PD12 | Bit 0 |
| Orange | PD13 | Bit 1 |
| Red | PD14 | Bit 2 |
| Blue | PD15 | Bit 3 |

### Enabling the GPIO Clock

The GPIOD peripheral clock is enabled by setting bit 3 of the `RCC_AHB1ENR` register.

This enables access to the GPIO Port D configuration and data registers.

### Configuring LED Pins as Outputs

The `GPIOD_MODER` register controls the operating mode of GPIO pins.

Each pin uses two mode bits. To configure PD12–PD15 as general-purpose outputs:

1. Clear the corresponding two-bit mode fields.
2. Set each field to `01`, selecting output mode.

### Controlling the LEDs

The `GPIOD_ODR` register controls the output state of the LEDs.

- Setting a pin's bit turns its LED ON.
- Clearing a pin's bit turns its LED OFF.

The `led_on()` and `led_off()` functions perform these operations using bitwise operations.

## 7. LED Result Display Logic

The `led_display()` function receives the result of an assembly operation and displays its lowest four bits using the onboard LEDs.

The function uses a loop to examine bit positions 0 through 3.

The expression:

```c
(value >> i) & 1U
```

shifts the selected bit to position zero and extracts its value.

- If the extracted bit is 1, the corresponding LED is turned ON.
- If the extracted bit is 0, the corresponding LED is turned OFF.

Since the four LED pins are consecutive, the LED pin number is calculated using `LED_GREEN + i`.

Only the lowest four bits are displayed. Higher bits of the operation result are ignored.

## 8. Main Program Execution

The main program follows these steps:

1. Initialize GPIO Port D and configure the four onboard LED pins as outputs.
2. Turn OFF all four LEDs initially.
3. Define two input operands, `a` and `b`.
4. Execute the `asm_add()` function and display its result.
5. Execute the `asm_sub()` function and display its result.
6. Execute the `asm_and()` function and display its result.
7. Execute the `asm_orr()` function and display its result.
8. Execute the `asm_eor()` function and display its result.
9. Introduce a software delay between operations so that the LED patterns can be observed.
10. Enter an infinite loop after displaying the final result.

## 9. Expected Results and LED Patterns

For the demonstration, the input operands are:

```c
uint32_t a = 6;
uint32_t b = 4;
```

The expected results are:

| Operation | Calculation | Decimal Result | Binary Result |
|---|---|---:|---|
| ADD | 6 + 4 | 10 | 1010 |
| SUB | 6 - 4 | 2 | 0010 |
| AND | 6 & 4 | 4 | 0100 |
| ORR | 6 \| 4 | 6 | 0110 |
| EOR | 6 ^ 4 | 2 | 0010 |

### LED Representation

| Binary Pattern (Blue to Green) | LEDs ON |
|---|---|
| 1010 | Blue, Orange |
| 0010 | Orange |
| 0100 | Red |
| 0110 | Red, Orange |

The LED patterns change after each assembly operation, providing a visual representation of the processor's output.

## 10. Important Registers Used

| Register | Purpose |
|---|---|
| `RCC_AHB1ENR` | Enables the GPIOD peripheral clock |
| `GPIOD_MODER` | Configures PD12–PD15 as outputs |
| `GPIOD_ODR` | Controls the onboard LED states |

## 11. Concepts Learned

- ARM Cortex-M4 general-purpose registers
- ARM Thumb instruction set
- GCC Extended Inline Assembly
- Assembly operand constraints
- Arithmetic instructions (`ADD`, `SUB`)
- Logical instructions (`AND`, `ORR`, `EOR`)
- Bitwise operations and binary representation
- Direct GPIO register programming
- Memory-mapped peripheral access
- Integrating assembly instructions with Embedded C
- Using processor operation results to control physical hardware

## 12. Conclusion

This exercise demonstrates how ARM Cortex-M4 assembly instructions can be integrated into Embedded C programs using GCC Inline Assembly.

By implementing arithmetic and logical operations directly using ARM instructions and displaying their results through onboard LEDs, the exercise provides practical experience in processor-level programming and hardware interaction.

It also builds a foundation for understanding ARM instruction execution, register usage, and low-level embedded software development.