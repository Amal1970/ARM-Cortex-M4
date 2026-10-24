# GPIO Register Programming — STM32F407

## Objective
Control the four onboard LEDs using direct GPIO register access in Embedded C.

## Hardware
- STM32F407G Discovery board
- STM32F407VG microcontroller

## What I Implemented
- Enabled the GPIOD peripheral clock.
- Configured PD12–PD15 as output pins.
- Used bitwise operations to turn LEDs ON and OFF.
- Created functions for GPIO initialization, LED control, and software delay.
- Implemented a repeating sequence: Green → Orange → Red → Blue.

## Concepts Learned
- Memory-mapped registers
- `volatile` pointers
- GPIO configuration
- Bitwise operations and masks
- Embedded C functions

## Testing
Built and tested using STM32CubeIDE. The LED sequence worked successfully on the board.

**Note:** The software delay is approximate, not an accurate 500 ms timer.
