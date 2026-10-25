# SysTick Digital Timer — STM32F407

## Objective
Configure the Cortex-M4 SysTick timer using direct register access and interrupts to generate millisecond timing delays.

## Hardware
- STM32F407G Discovery board
- STM32F407VG microcontroller

## What I Implemented
- Configured the SysTick timer for a 1 ms interval.
- Enabled SysTick interrupts.
- Implemented `SysTick_Handler()` to maintain a millisecond counter.
- Created a reusable `systick_delay_ms()` function.
- Used the timer to blink the green onboard LED (PD12) at 500 ms intervals.

## Concepts Learned
- SysTick registers: CTRL, LOAD, and VAL
- Hardware timer configuration
- Interrupt handling
- `volatile` variables
- Millisecond timekeeping
- Register-level Embedded C programming

## Testing
Built and tested on the STM32F407G Discovery board. The green LED blinked successfully using the interrupt-driven SysTick timer.

## Notes
The reload value assumes a 16 MHz SysTick clock. The configured clock source and frequency must match the actual MCU clock configuration.