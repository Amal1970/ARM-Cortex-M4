# NVIC External Interrupt Demo — STM32F407G Discovery

## 1. Objective

The objective of this exercise is to understand how external interrupts work on the STM32F407VG microcontroller and how the Nested Vectored Interrupt Controller (NVIC) manages them.

The onboard user button connected to PA0 is configured to generate an external interrupt. When the button is pressed, the interrupt handler toggles the onboard green LED connected to PD12.

This exercise uses direct register-level programming in Embedded C without relying on the STM32 HAL GPIO or interrupt functions.

## 2. Hardware Requirements

- STM32F407G Discovery development board
- STM32F407VG ARM Cortex-M4 microcontroller
- Onboard user push button connected to PA0
- Onboard green LED connected to PD12
- USB connection for programming and testing

## 3. System Overview

The system uses the following peripherals:

- **GPIO:** Configures PA0 as an input and PD12 as an output.
- **SYSCFG:** Routes the PA0 signal to external interrupt line EXTI0.
- **EXTI:** Detects the configured edge on PA0 and generates an interrupt request.
- **NVIC:** Enables EXTI0 and assigns its interrupt priority.
- **Interrupt Service Routine (ISR):** Handles the interrupt by clearing its pending flag and toggling the green LED.

### Interrupt Flow

1. The user presses the onboard button connected to PA0.
2. EXTI detects the rising edge on EXTI0.
3. EXTI sets its pending flag and requests an interrupt.
4. The NVIC checks whether the interrupt is enabled and eligible to execute.
5. The Cortex-M4 enters `EXTI0_IRQHandler()`.
6. The handler clears the EXTI0 pending flag and toggles PD12.
7. The processor returns to the interrupted program.

## 4. GPIO Configuration

### Enabling GPIO Clocks

The GPIOA and GPIOD peripheral clocks are enabled through the RCC AHB1 peripheral clock enable register, `RCC_AHB1ENR`.

- Bit 0 enables the GPIOA clock.
- Bit 3 enables the GPIOD clock.

Enabling the peripheral clock is necessary before accessing the GPIO configuration and data registers.

### Configuring PA0 as Input

The `GPIOA_MODER` register controls the operating mode of each GPIO pin. Each pin uses two mode bits.

For PA0, bits 1:0 are cleared to `00`, selecting input mode. This allows the microcontroller to receive the button signal.

### Configuring PD12 as Output

PD12 is configured as a general-purpose output by clearing bits 25:24 of `GPIOD_MODER` and setting the mode bits to `01`.

The green LED is controlled through `GPIOD_ODR`:

- Setting bit 12 turns the LED on.
- Clearing bit 12 turns the LED off.
- XOR with bit 12 toggles the LED state.

The `led_off()` and `led_toggle()` functions make these operations reusable.

## 5. SYSCFG and EXTI Configuration

### Enabling the SYSCFG Clock

The SYSCFG peripheral clock is enabled by setting bit 14 of `RCC_APB2ENR`.

SYSCFG provides the external interrupt routing configuration needed to connect a GPIO port to an EXTI line.

### Routing PA0 to EXTI0

The `SYSCFG_EXTICR1` register selects which GPIO port supplies the signal for EXTI lines 0–3.

The lowest four bits correspond to EXTI0. Clearing these bits selects GPIOA, connecting PA0 to EXTI0.

### Configuring the Trigger

The `EXTI_RTSR` register controls rising-edge detection. Setting bit 0 enables a rising-edge trigger on EXTI0.

The `EXTI_IMR` register controls whether EXTI events are allowed to generate interrupt requests. Setting bit 0 unmasks EXTI0.

When the configured edge is detected, the EXTI hardware sets the pending flag in `EXTI_PR`.

## 6. NVIC Configuration

The Nested Vectored Interrupt Controller manages interrupt enable states, priorities, and delivery to the processor.

### Interrupt Number

EXTI0 corresponds to external interrupt number 6.

### Interrupt Priority

The priority byte for IRQ 6 is located at address `0xE000E406`. The priority is configured as logical priority 2.

On the Cortex-M4 implementation used by the STM32F407VG, the implemented priority bits occupy the upper portion of the priority byte. Therefore, logical priority 2 is represented by shifting the value left by four bits.

A lower numerical priority represents a higher priority. Priority settings become particularly important when multiple interrupts are active.

### Enabling EXTI0

`NVIC_ISER0` is the first NVIC interrupt set-enable register. Setting bit 6 enables EXTI0.

Both the EXTI interrupt mask and the NVIC enable must be configured for the interrupt to be delivered to the processor.

## 7. Interrupt Service Routine

The interrupt handler is named `EXTI0_IRQHandler()`.

When the processor accepts EXTI0, it executes this handler using the interrupt vector table configured by the startup code.

The handler performs two main operations:

1. **Clear the pending flag:** Writing a one to bit 0 of `EXTI_PR` clears the EXTI0 pending flag. This register uses write-one-to-clear behavior.
2. **Toggle the LED:** The `led_toggle()` function uses XOR on bit 12 of `GPIOD_ODR` to change the LED state.

The handler should remain short and should avoid unnecessary delays or lengthy processing.

The startup vector table must contain the correct entry for `EXTI0_IRQHandler()` so that the processor reaches the application handler instead of the default handler.

## 8. Main Program Execution

The `main()` function performs the following sequence:

1. Calls `gpio_init()` to enable clocks and configure the GPIO pins.
2. Calls `led_off()` to initialize the green LED to the OFF state.
3. Calls `exti_init()` to configure SYSCFG, EXTI, and the NVIC.
4. Enters an infinite loop.

The main loop does not repeatedly read the button input. The LED state changes in response to interrupts, demonstrating event-driven operation instead of continuous polling.

## 9. Important Registers Used

| Register | Purpose |
|---|---|
| `RCC_AHB1ENR` | Enables GPIOA and GPIOD clocks |
| `RCC_APB2ENR` | Enables the SYSCFG clock |
| `GPIOA_MODER` | Configures PA0 as input |
| `GPIOD_MODER` | Configures PD12 as output |
| `GPIOD_ODR` | Controls and toggles the green LED |
| `SYSCFG_EXTICR1` | Routes PA0 to EXTI0 |
| `EXTI_IMR` | Unmasks EXTI0 |
| `EXTI_RTSR` | Enables rising-edge detection |
| `EXTI_PR` | Reports and clears pending EXTI events |
| `NVIC_IPR6` | Sets the priority byte for EXTI0 |
| `NVIC_ISER0` | Enables EXTI0 in the NVIC |

## 10. Testing and Expected Results

The firmware is intended to be tested on the STM32F407G Discovery board.

Expected behavior:

- The green LED starts in the OFF state.
- Pressing the onboard user button triggers EXTI0.
- The interrupt handler executes and toggles the green LED.
- The main program remains in its infinite loop without polling the button.

Mechanical button bounce can occasionally cause multiple interrupts from a single press. Debouncing can be implemented as a future improvement.

## 11. Concepts Learned

- Direct register-level Embedded C programming
- GPIO input and output configuration
- RCC peripheral clock control
- SYSCFG external interrupt routing
- EXTI rising-edge detection
- NVIC interrupt enable and priority configuration
- Interrupt service routines
- Write-one-to-clear hardware registers
- Interrupt-driven programming versus polling
- Startup vector table and exception handling

## 12. Future Improvements

- Implement software or timer-based button debouncing.
- Demonstrate how different interrupt priorities behave when multiple interrupts are active.
- Add a second interrupt source and compare interrupt handling behavior.
- Explore interrupt latency and the Cortex-M4 exception entry and return process.
