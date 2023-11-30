# STM32 System Configuration Final Project (Hardware_Inturrpts)

## Overview

This project contains the C++ code for configuring the system clock and external interrupt handler on an STM32 microcontroller. It has been converted and documented from an original C codebase and is specifically tailored for STM32 platforms using the Hardware Abstraction Layer (HAL).

## Project Structure

- `main.h`: The main header file for the project, typically including STM32 HAL libraries and definitions.
- `main.cpp`: The main C++ source file containing the `SystemConfig` class and the `main` function.

## Features

- **System Clock Configuration**: Configures the system clock of the STM32 microcontroller using the Phase Locked Loop (PLL) with settings that can be adjusted for different board revisions.
- **External Interrupt Handler Configuration (EXTI0)**: Configures the external interrupt handler for handling specific pin interrupts.
- **LED Control**: Includes functionality to toggle an LED when an external interrupt is triggered.

## Requirements

- STM32CubeMX or a similar tool for generating initialization code.
- STM32 HAL libraries corresponding to your specific STM32 microcontroller.
- An Integrated Development Environment (IDE) like STM32CubeIDE or Keil uVision.

## Building the Project

1. **Set up your environment**: Make sure you have all the required STM32 HAL libraries and a compatible IDE installed.
2. **Project configuration**: Open the project in your IDE and configure it for your specific STM32 microcontroller model.
3. **Compile**: Build the project using the IDE's build tools.

## Running the Code

1. **Upload the binary**: After a successful build, upload the compiled binary to your STM32 microcontroller.
2. **Monitor the output**: The program will run the configured system clock and listen for interrupts on the specified pin. Toggling the corresponding pin should trigger the external interrupt and toggle the LED.

## Debugging

In case of errors or unexpected behavior:
- Verify the clock settings and interrupt configuration in `SystemConfig::SystemClock_Config` and `SystemConfig::EXTI0_IRQHandler_Config`.
- Ensure that the correct pin is being used for the external interrupt.
- Use the `assert_failed` function for debugging assertions.

## Contributing

Contributions to this project are welcome. Please adhere to standard coding conventions and provide documentation for any changes.


---

For further details or support, refer to the STM32 HAL documentation or contact the project maintainers.
