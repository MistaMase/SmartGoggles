# What CMake to start at
cmake_minimum_required(VERSION 3.12)
 
# Include the subsidiary .cmake file to get the SDK
include(pico_sdk_import.cmake)
 
# Set the name and version of the project
project(Goggles VERSION 1.0.0)
 
# Link the Project to a source file
add_executable(Goggles src/main.c src/display.c src/touch.c src/interrupt.c src/imu.c)
 
# Link the Project to the pico_stdlib library
target_link_libraries(Goggles pico_stdlib)

# Link the Project to the hardware i2c library
target_link_libraries(Goggles hardware_i2c)

# Link the Project to the hardware pwm library
target_link_libraries(Goggles hardware_pwm)

# Link the Project to the spi library
target_link_libraries(Goggles hardware_spi)
 
# Initalise the SDK
pico_sdk_init()
 
# Enable USB, UART output
pico_enable_stdio_usb(Goggles 1)
pico_enable_stdio_uart(Goggles 1)
 
# Enable extra outputs (SWD?)
pico_add_extra_outputs(Goggles)

