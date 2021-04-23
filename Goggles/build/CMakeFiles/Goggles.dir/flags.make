# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# compile ASM with /usr/local/bin/arm-none-eabi-gcc
# compile C with /usr/local/bin/arm-none-eabi-gcc-9.2.1
# compile CXX with /usr/local/bin/arm-none-eabi-g++
ASM_DEFINES = -DCFG_TUSB_DEBUG=1 -DCFG_TUSB_MCU=OPT_MCU_RP2040 -DCFG_TUSB_OS=OPT_OS_PICO -DPICO_BIT_OPS_PICO=1 -DPICO_BOARD=\"pico\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Debug\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_DIVIDER_HARDWARE=1 -DPICO_DOUBLE_PICO=1 -DPICO_FLOAT_PICO=1 -DPICO_INT64_OPS_PICO=1 -DPICO_MEM_OPS_PICO=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_PRINTF_PICO=1 -DPICO_STDIO_UART=1 -DPICO_STDIO_USB=1 -DPICO_TARGET_NAME=\"Goggles\" -DPICO_USE_BLOCKED_RAM=0

ASM_INCLUDES = -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_stdlib/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_gpio/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_base/include -I/Users/JJ/Desktop/SmartGoggles/Goggles/build/generated/pico_base -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/boards/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_platform/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2040/hardware_regs/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_base/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2040/hardware_structs/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_claim/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_sync/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_uart/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_divider/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_time/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_timer/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_sync/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_util/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_runtime/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_clocks/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_resets/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_watchdog/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_xosc/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_pll/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_vreg/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_irq/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_printf/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_bootrom/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_bit_ops/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_divider/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_double/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_int64_ops/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_float/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_malloc/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/boot_stage2/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_binary_info/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_stdio/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_stdio_usb/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/lib/tinyusb/src -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/lib/tinyusb/src/common -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/lib/tinyusb/hw -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_i2c/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_pwm/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_spi/include

ASM_FLAGS = -mcpu=cortex-m0plus -mthumb -Og -g -ffunction-sections -fdata-sections

C_DEFINES = -DCFG_TUSB_DEBUG=1 -DCFG_TUSB_MCU=OPT_MCU_RP2040 -DCFG_TUSB_OS=OPT_OS_PICO -DPICO_BIT_OPS_PICO=1 -DPICO_BOARD=\"pico\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Debug\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_DIVIDER_HARDWARE=1 -DPICO_DOUBLE_PICO=1 -DPICO_FLOAT_PICO=1 -DPICO_INT64_OPS_PICO=1 -DPICO_MEM_OPS_PICO=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_PRINTF_PICO=1 -DPICO_STDIO_UART=1 -DPICO_STDIO_USB=1 -DPICO_TARGET_NAME=\"Goggles\" -DPICO_USE_BLOCKED_RAM=0

C_INCLUDES = -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_stdlib/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_gpio/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_base/include -I/Users/JJ/Desktop/SmartGoggles/Goggles/build/generated/pico_base -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/boards/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_platform/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2040/hardware_regs/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_base/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2040/hardware_structs/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_claim/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_sync/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_uart/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_divider/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_time/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_timer/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_sync/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_util/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_runtime/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_clocks/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_resets/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_watchdog/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_xosc/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_pll/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_vreg/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_irq/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_printf/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_bootrom/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_bit_ops/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_divider/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_double/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_int64_ops/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_float/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_malloc/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/boot_stage2/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_binary_info/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_stdio/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_stdio_usb/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/lib/tinyusb/src -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/lib/tinyusb/src/common -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/lib/tinyusb/hw -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_i2c/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_pwm/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_spi/include

C_FLAGS = -mcpu=cortex-m0plus -mthumb -Og -g -ffunction-sections -fdata-sections

CXX_DEFINES = -DCFG_TUSB_DEBUG=1 -DCFG_TUSB_MCU=OPT_MCU_RP2040 -DCFG_TUSB_OS=OPT_OS_PICO -DPICO_BIT_OPS_PICO=1 -DPICO_BOARD=\"pico\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Debug\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_DIVIDER_HARDWARE=1 -DPICO_DOUBLE_PICO=1 -DPICO_FLOAT_PICO=1 -DPICO_INT64_OPS_PICO=1 -DPICO_MEM_OPS_PICO=1 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_PRINTF_PICO=1 -DPICO_STDIO_UART=1 -DPICO_STDIO_USB=1 -DPICO_TARGET_NAME=\"Goggles\" -DPICO_USE_BLOCKED_RAM=0

CXX_INCLUDES = -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_stdlib/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_gpio/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_base/include -I/Users/JJ/Desktop/SmartGoggles/Goggles/build/generated/pico_base -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/boards/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_platform/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2040/hardware_regs/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_base/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2040/hardware_structs/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_claim/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_sync/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_uart/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_divider/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_time/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_timer/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_sync/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_util/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_runtime/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_clocks/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_resets/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_watchdog/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_xosc/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_pll/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_vreg/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_irq/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_printf/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_bootrom/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_bit_ops/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_divider/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_double/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_int64_ops/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_float/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_malloc/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/boot_stage2/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/common/pico_binary_info/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_stdio/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_stdio_usb/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/lib/tinyusb/src -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/lib/tinyusb/src/common -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/lib/tinyusb/hw -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/pico_fix/rp2040_usb_device_enumeration/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_i2c/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_pwm/include -I/Users/JJ/Desktop/SmartGoggles/pico-sdk/src/rp2_common/hardware_spi/include

CXX_FLAGS = -mcpu=cortex-m0plus -mthumb -Og -g -ffunction-sections -fdata-sections -fno-exceptions -fno-unwind-tables -fno-rtti -fno-use-cxa-atexit
