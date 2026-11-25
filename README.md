\# MAX30102 FIFO Reading with FreeRTOS on STM32 Nucleo-L476RG



C firmware (STM32 HAL, generated with STM32CubeMX) that configures the

MAX30102 sensor over I2C and reads its FIFO from a FreeRTOS task.



\## Hardware

\- STM32 Nucleo-L476RG

\- MAX30102 sensor (I2C)



\## Tools

\- STM32CubeMX, STM32CubeIDE

\- FreeRTOS (CMSIS-RTOS v2)



\## Status

Raw sample reading.



\## Planned

\- Queue between tasks

\- Detection threshold with LED toggling

\- Hysteresis

