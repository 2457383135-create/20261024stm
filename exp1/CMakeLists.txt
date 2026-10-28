cmake_minimum_required(VERSION 3.16)

project(atk_f407 LANGUAGES C ASM)

# ============================================================
# 芯片与编译器设置
# ============================================================
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY      arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP      arm-none-eabi-objdump)
set(CMAKE_SIZE         arm-none-eabi-size)

# 跳过编译器检查（交叉编译环境下必须设）
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# ============================================================
# 源码路径
# ============================================================
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(DRIVERS      ${PROJECT_ROOT}/Drivers)
set(USER_DIR     ${PROJECT_ROOT}/User)

# ============================================================
# 宏定义（与 Keil 保持一致）
# ============================================================
add_compile_definitions(
    USE_HAL_DRIVER
    STM32F407xx
)

# ============================================================
# 头文件搜索路径
# ============================================================
include_directories(
    ${DRIVERS}
    ${DRIVERS}/CMSIS/Include
    ${DRIVERS}/CMSIS/Device/ST/STM32F4xx/Include
    ${DRIVERS}/STM32F4xx_HAL_Driver/Inc
    ${USER_DIR}
    ${DRIVERS}/SYSTEM/sys
    ${DRIVERS}/SYSTEM/delay
    ${DRIVERS}/SYSTEM/usart
    ${DRIVERS}/BSP/LED
)

# ============================================================
# 编译选项
# ============================================================
add_compile_options(
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=softfp
    -Wall
    -Wextra
    -Wno-unused-parameter
    -Wno-unused-variable
    -Wno-unused-but-set-variable
    -ffunction-sections
    -fdata-sections
    -std=c99
    -g3
    -O2
)



# 链接选项
add_link_options(
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=softfp
    -Wl,--gc-sections
    -Wl,-Map=${PROJECT_NAME}.map
    -T${PROJECT_ROOT}/STM32F407ZGTx_FLASH.ld
    --specs=nano.specs
    --specs=nosys.specs
)

# ============================================================
# 源文件（与 Keil 工程编译列表保持一致）
# ============================================================
set(SOURCES
    # Startup
    ${DRIVERS}/CMSIS/Device/ST/STM32F4xx/Source/Templates/arm/startup_stm32f407xx.s

    # User
    ${USER_DIR}/main.c
    ${USER_DIR}/stm32f4xx_it.c
    ${DRIVERS}/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c

    # SYSTEM
    ${DRIVERS}/SYSTEM/sys/sys.c
    ${DRIVERS}/SYSTEM/delay/delay.c
    ${DRIVERS}/SYSTEM/usart/usart.c

    # HAL 库（只编译 Keil 里启用的那 6 个）
    ${DRIVERS}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    ${DRIVERS}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
    ${DRIVERS}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    ${DRIVERS}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    ${DRIVERS}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    ${DRIVERS}/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_uart.c

    # BSP
    ${DRIVERS}/BSP/LED/led.c
)

# ============================================================
# 生成目标
# ============================================================
add_executable(${PROJECT_NAME}.elf ${SOURCES})

# ELF → HEX / BIN
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
    COMMENT "Generating HEX / BIN and showing size..."
)