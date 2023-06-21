/*
 * Automatically generated file. DO NOT EDIT.
 * Espressif IoT Development Framework (ESP-IDF) Configuration Header
 */
#pragma once
#define CONFIG_IDF_CMAKE 1
#define CONFIG_IDF_TARGET_ARCH_XTENSA 1
#define CONFIG_IDF_TARGET "esp32"
#define CONFIG_IDF_TARGET_ESP32 1
#define CONFIG_IDF_FIRMWARE_CHIP_ID 0x0000
#define CONFIG_SDK_TOOLPREFIX "xtensa-esp32-elf-"
#define CONFIG_APP_BUILD_TYPE_APP_2NDBOOT 1
#define CONFIG_APP_BUILD_GENERATE_BINARIES 1
#define CONFIG_APP_BUILD_BOOTLOADER 1
#define CONFIG_APP_BUILD_USE_FLASH_SECTIONS 1
#define CONFIG_BOOTLOADER_OFFSET_IN_FLASH 0x1000
#define CONFIG_BOOTLOADER_COMPILER_OPTIMIZATION_SIZE 1
#define CONFIG_BOOTLOADER_LOG_LEVEL_WARN 1
#define CONFIG_BOOTLOADER_LOG_LEVEL 2
#define CONFIG_BOOTLOADER_VDDSDIO_BOOST_1_9V 1
#define CONFIG_BOOTLOADER_REGION_PROTECTION_ENABLE 1
#define CONFIG_BOOTLOADER_WDT_ENABLE 1
#define CONFIG_BOOTLOADER_WDT_TIME_MS 9000
#define CONFIG_BOOTLOADER_RESERVE_RTC_SIZE 0x0
#define CONFIG_BOOTLOADER_FLASH_XMC_SUPPORT 1
#define CONFIG_ESPTOOLPY_BAUD_OTHER_VAL 115200
#define CONFIG_ESPTOOLPY_FLASHMODE_DIO 1
#define CONFIG_ESPTOOLPY_FLASH_SAMPLE_MODE_STR 1
#define CONFIG_ESPTOOLPY_FLASHMODE "dio"
#define CONFIG_ESPTOOLPY_FLASHFREQ_40M 1
#define CONFIG_ESPTOOLPY_FLASHFREQ "40m"
#define CONFIG_ESPTOOLPY_FLASHSIZE_8MB 1
#define CONFIG_ESPTOOLPY_FLASHSIZE "8MB"
#define CONFIG_ESPTOOLPY_FLASHSIZE_DETECT 1
#define CONFIG_ESPTOOLPY_BEFORE_RESET 1
#define CONFIG_ESPTOOLPY_BEFORE "default_reset"
#define CONFIG_ESPTOOLPY_AFTER_RESET 1
#define CONFIG_ESPTOOLPY_AFTER "hard_reset"
#define CONFIG_ESPTOOLPY_MONITOR_BAUD_115200B 1
#define CONFIG_ESPTOOLPY_MONITOR_BAUD_OTHER_VAL 115200
#define CONFIG_ESPTOOLPY_MONITOR_BAUD 115200
#define CONFIG_PARTITION_TABLE_CUSTOM 1
#define CONFIG_PARTITION_TABLE_CUSTOM_FILENAME "partitions.csv"
#define CONFIG_PARTITION_TABLE_FILENAME "partitions.csv"
#define CONFIG_PARTITION_TABLE_OFFSET 0x8000
#define CONFIG_PARTITION_TABLE_MD5 1
#define CONFIG_COMPILER_OPTIMIZATION_DEFAULT 1
#define CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_ENABLE 1
#define CONFIG_COMPILER_OPTIMIZATION_ASSERTION_LEVEL 2
#define CONFIG_COMPILER_HIDE_PATHS_MACROS 1
#define CONFIG_COMPILER_CXX_EXCEPTIONS 1
#define CONFIG_COMPILER_CXX_EXCEPTIONS_EMG_POOL_SIZE 0
#define CONFIG_COMPILER_STACK_CHECK_MODE_NONE 1
#define CONFIG_EFUSE_CODE_SCHEME_COMPAT_3_4 1
#define CONFIG_EFUSE_MAX_BLK_LEN 192
#define CONFIG_ESP32_REV_MIN_0 1
#define CONFIG_ESP32_REV_MIN 0
#define CONFIG_ESP32_DPORT_WORKAROUND 1
#define CONFIG_ESP32_DEFAULT_CPU_FREQ_160 1
#define CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ 160
#define CONFIG_ESP32_TRACEMEM_RESERVE_DRAM 0x0
#define CONFIG_ESP32_ULP_COPROC_RESERVE_MEM 0
#define CONFIG_ESP32_DEBUG_OCDAWARE 1
#define CONFIG_ESP32_BROWNOUT_DET 1
#define CONFIG_ESP32_BROWNOUT_DET_LVL_SEL_0 1
#define CONFIG_ESP32_BROWNOUT_DET_LVL 0
#define CONFIG_ESP32_TIME_SYSCALL_USE_RTC_FRC1 1
#define CONFIG_ESP32_RTC_CLK_SRC_INT_RC 1
#define CONFIG_ESP32_RTC_CLK_CAL_CYCLES 1024
#define CONFIG_ESP32_DEEP_SLEEP_WAKEUP_DELAY 2000
#define CONFIG_ESP32_XTAL_FREQ_40 1
#define CONFIG_ESP32_XTAL_FREQ 40
#define CONFIG_ESP32_DPORT_DIS_INTERRUPT_LVL 5
#define CONFIG_ESP_ERR_TO_NAME_LOOKUP 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_WIFI_STA 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_WIFI_AP 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_BT 1
#define CONFIG_ESP_MAC_ADDR_UNIVERSE_ETH 1
#define CONFIG_ESP32_UNIVERSAL_MAC_ADDRESSES_FOUR 1
#define CONFIG_ESP32_UNIVERSAL_MAC_ADDRESSES 4
#define CONFIG_ESP_SLEEP_RTC_BUS_ISO_WORKAROUND 1
#define CONFIG_ESP_SLEEP_FLASH_LEAKAGE_WORKAROUND 1
#define CONFIG_ESP_SYSTEM_PANIC_PRINT_REBOOT 1
#define CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE 32
#define CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE 2304
#define CONFIG_ESP_MAIN_TASK_STACK_SIZE 3584
#define CONFIG_ESP_MAIN_TASK_AFFINITY_CPU0 1
#define CONFIG_ESP_MAIN_TASK_AFFINITY 0x0
#define CONFIG_ESP_MINIMAL_SHARED_STACK_SIZE 2048
#define CONFIG_ESP_CONSOLE_UART_DEFAULT 1
#define CONFIG_ESP_CONSOLE_UART 1
#define CONFIG_ESP_CONSOLE_MULTIPLE_UART 1
#define CONFIG_ESP_CONSOLE_UART_NUM 0
#define CONFIG_ESP_CONSOLE_UART_BAUDRATE 115200
#define CONFIG_ESP_INT_WDT 1
#define CONFIG_ESP_INT_WDT_TIMEOUT_MS 300
#define CONFIG_ESP_INT_WDT_CHECK_CPU1 1
#define CONFIG_ESP_TASK_WDT 1
#define CONFIG_ESP_TASK_WDT_TIMEOUT_S 5
#define CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0 1
#define CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1 1
#define CONFIG_ESP_SYSTEM_CHECK_INT_LEVEL_5 1
#define CONFIG_FREERTOS_NO_AFFINITY 0x7FFFFFFF
#define CONFIG_FREERTOS_TICK_SUPPORT_CORETIMER 1
#define CONFIG_FREERTOS_CORETIMER_0 1
#define CONFIG_FREERTOS_SYSTICK_USES_CCOUNT 1
#define CONFIG_FREERTOS_HZ 100
#define CONFIG_FREERTOS_ASSERT_ON_UNTESTED_FUNCTION 1
#define CONFIG_FREERTOS_CHECK_STACKOVERFLOW_CANARY 1
#define CONFIG_FREERTOS_INTERRUPT_BACKTRACE 1
#define CONFIG_FREERTOS_THREAD_LOCAL_STORAGE_POINTERS 1
#define CONFIG_FREERTOS_ASSERT_FAIL_ABORT 1
#define CONFIG_FREERTOS_IDLE_TASK_STACKSIZE 1536
#define CONFIG_FREERTOS_ISR_STACKSIZE 1536
#define CONFIG_FREERTOS_MAX_TASK_NAME_LEN 16
#define CONFIG_FREERTOS_SUPPORT_STATIC_ALLOCATION 1
#define CONFIG_FREERTOS_TIMER_TASK_PRIORITY 1
#define CONFIG_FREERTOS_TIMER_TASK_STACK_DEPTH 2048
#define CONFIG_FREERTOS_TIMER_QUEUE_LENGTH 10
#define CONFIG_FREERTOS_QUEUE_REGISTRY_SIZE 0
#define CONFIG_FREERTOS_TASK_FUNCTION_WRAPPER 1
#define CONFIG_FREERTOS_CHECK_MUTEX_GIVEN_BY_OWNER 1
#define CONFIG_FREERTOS_DEBUG_OCDAWARE 1
#define CONFIG_FREERTOS_ENABLE_TASK_SNAPSHOT 1
#define CONFIG_HAL_ASSERTION_EQUALS_SYSTEM 1
#define CONFIG_HAL_DEFAULT_ASSERTION_LEVEL 2
#define CONFIG_LOG_DEFAULT_LEVEL_INFO 1
#define CONFIG_LOG_DEFAULT_LEVEL 3
#define CONFIG_LOG_MAXIMUM_EQUALS_DEFAULT 1
#define CONFIG_LOG_MAXIMUM_LEVEL 3
#define CONFIG_LOG_COLORS 1
#define CONFIG_LOG_TIMESTAMP_SOURCE_RTOS 1
#define CONFIG_NEWLIB_STDOUT_LINE_ENDING_CRLF 1
#define CONFIG_NEWLIB_STDIN_LINE_ENDING_CR 1
#define CONFIG_NEWLIB_NANO_FORMAT 1
#define CONFIG_SPI_FLASH_ROM_DRIVER_PATCH 1
#define CONFIG_SPI_FLASH_DANGEROUS_WRITE_ABORTS 1
#define CONFIG_SPI_FLASH_YIELD_DURING_ERASE 1
#define CONFIG_SPI_FLASH_ERASE_YIELD_DURATION_MS 20
#define CONFIG_SPI_FLASH_ERASE_YIELD_TICKS 1
#define CONFIG_SPI_FLASH_WRITE_CHUNK_SIZE 8192
#define CONFIG_SPI_FLASH_SUPPORT_ISSI_CHIP 1
#define CONFIG_SPI_FLASH_SUPPORT_MXIC_CHIP 1
#define CONFIG_SPI_FLASH_SUPPORT_GD_CHIP 1
#define CONFIG_SPI_FLASH_SUPPORT_WINBOND_CHIP 1
#define CONFIG_SPI_FLASH_ENABLE_ENCRYPTED_READ_WRITE 1

/* List of deprecated options */
#define CONFIG_BROWNOUT_DET CONFIG_ESP32_BROWNOUT_DET
#define CONFIG_BROWNOUT_DET_LVL CONFIG_ESP32_BROWNOUT_DET_LVL
#define CONFIG_BROWNOUT_DET_LVL_SEL_0 CONFIG_ESP32_BROWNOUT_DET_LVL_SEL_0
#define CONFIG_COMPILER_OPTIMIZATION_LEVEL_DEBUG CONFIG_COMPILER_OPTIMIZATION_DEFAULT
#define CONFIG_CONSOLE_UART CONFIG_ESP_CONSOLE_UART
#define CONFIG_CONSOLE_UART_BAUDRATE CONFIG_ESP_CONSOLE_UART_BAUDRATE
#define CONFIG_CONSOLE_UART_DEFAULT CONFIG_ESP_CONSOLE_UART_DEFAULT
#define CONFIG_CONSOLE_UART_NUM CONFIG_ESP_CONSOLE_UART_NUM
#define CONFIG_CXX_EXCEPTIONS CONFIG_COMPILER_CXX_EXCEPTIONS
#define CONFIG_CXX_EXCEPTIONS_EMG_POOL_SIZE CONFIG_COMPILER_CXX_EXCEPTIONS_EMG_POOL_SIZE
#define CONFIG_ESP32S2_PANIC_PRINT_REBOOT CONFIG_ESP_SYSTEM_PANIC_PRINT_REBOOT
#define CONFIG_ESP32_PANIC_PRINT_REBOOT CONFIG_ESP_SYSTEM_PANIC_PRINT_REBOOT
#define CONFIG_ESP32_RTC_CLOCK_SOURCE_INTERNAL_RC CONFIG_ESP32_RTC_CLK_SRC_INT_RC
#define CONFIG_FLASHMODE_DIO CONFIG_ESPTOOLPY_FLASHMODE_DIO
#define CONFIG_FOUR_UNIVERSAL_MAC_ADDRESS CONFIG_ESP32_UNIVERSAL_MAC_ADDRESSES_FOUR
#define CONFIG_INT_WDT CONFIG_ESP_INT_WDT
#define CONFIG_INT_WDT_CHECK_CPU1 CONFIG_ESP_INT_WDT_CHECK_CPU1
#define CONFIG_INT_WDT_TIMEOUT_MS CONFIG_ESP_INT_WDT_TIMEOUT_MS
#define CONFIG_LOG_BOOTLOADER_LEVEL CONFIG_BOOTLOADER_LOG_LEVEL
#define CONFIG_LOG_BOOTLOADER_LEVEL_WARN CONFIG_BOOTLOADER_LOG_LEVEL_WARN
#define CONFIG_MAIN_TASK_STACK_SIZE CONFIG_ESP_MAIN_TASK_STACK_SIZE
#define CONFIG_MONITOR_BAUD CONFIG_ESPTOOLPY_MONITOR_BAUD
#define CONFIG_MONITOR_BAUD_115200B CONFIG_ESPTOOLPY_MONITOR_BAUD_115200B
#define CONFIG_MONITOR_BAUD_OTHER_VAL CONFIG_ESPTOOLPY_MONITOR_BAUD_OTHER_VAL
#define CONFIG_NUMBER_OF_UNIVERSAL_MAC_ADDRESS CONFIG_ESP32_UNIVERSAL_MAC_ADDRESSES
#define CONFIG_OPTIMIZATION_ASSERTIONS_ENABLED CONFIG_COMPILER_OPTIMIZATION_ASSERTIONS_ENABLE
#define CONFIG_OPTIMIZATION_ASSERTION_LEVEL CONFIG_COMPILER_OPTIMIZATION_ASSERTION_LEVEL
#define CONFIG_OPTIMIZATION_LEVEL_DEBUG CONFIG_COMPILER_OPTIMIZATION_DEFAULT
#define CONFIG_SPI_FLASH_WRITING_DANGEROUS_REGIONS_ABORTS CONFIG_SPI_FLASH_DANGEROUS_WRITE_ABORTS
#define CONFIG_STACK_CHECK_NONE CONFIG_COMPILER_STACK_CHECK_MODE_NONE
#define CONFIG_SYSTEM_EVENT_QUEUE_SIZE CONFIG_ESP_SYSTEM_EVENT_QUEUE_SIZE
#define CONFIG_SYSTEM_EVENT_TASK_STACK_SIZE CONFIG_ESP_SYSTEM_EVENT_TASK_STACK_SIZE
#define CONFIG_TASK_WDT CONFIG_ESP_TASK_WDT
#define CONFIG_TASK_WDT_CHECK_IDLE_TASK_CPU0 CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU0
#define CONFIG_TASK_WDT_CHECK_IDLE_TASK_CPU1 CONFIG_ESP_TASK_WDT_CHECK_IDLE_TASK_CPU1
#define CONFIG_TASK_WDT_TIMEOUT_S CONFIG_ESP_TASK_WDT_TIMEOUT_S
#define CONFIG_TIMER_QUEUE_LENGTH CONFIG_FREERTOS_TIMER_QUEUE_LENGTH
#define CONFIG_TIMER_TASK_PRIORITY CONFIG_FREERTOS_TIMER_TASK_PRIORITY
#define CONFIG_TIMER_TASK_STACK_DEPTH CONFIG_FREERTOS_TIMER_TASK_STACK_DEPTH
#define CONFIG_TOOLPREFIX CONFIG_SDK_TOOLPREFIX
#define CONFIG_TRACEMEM_RESERVE_DRAM CONFIG_ESP32_TRACEMEM_RESERVE_DRAM
#define CONFIG_ULP_COPROC_RESERVE_MEM CONFIG_ESP32_ULP_COPROC_RESERVE_MEM
