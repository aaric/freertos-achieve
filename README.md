# freertos-achieve

[![License](https://img.shields.io/badge/License-MIT-important.svg?style=flat&logo=github)](https://www.mit-license.org)
[![C++](https://img.shields.io/badge/C++-11-success.svg?style=flat&logo=cplusplus)](https://isocpp.org)
[![CMake](https://img.shields.io/badge/CMake-3.5-success.svg?style=flat&logo=cmake)](https://cmake.org/cmake/help/v3.5)
[![ESP-IDF](https://img.shields.io/badge/ESP_IDF-4.4-success.svg?style=flat&logo=espressif)](https://dl.espressif.com/dl/esp-idf/?idf=4.4)
[![ESP32](https://img.shields.io/badge/ESP32-S3-success.svg?style=flat&logo=espHome)](https://docs.espressif.com/projects/esp-idf/zh_CN/v4.4/esp32s3/get-started/index.html)
[![Release](https://img.shields.io/badge/Release-0.4.0-informational.svg)](https://github.com/aaric/freertos-achieve/releases)

> [FreeRTOS Kernel Developer Docs](https://www.freertos.org/features.html)  
> [FreeRTOS_Reference_Manual_V10.0.0.pdf](https://www.freertos.org/Documentation/FreeRTOS_Reference_Manual_V10.0.0.pdf)

## 1 [FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/release-v4.4/esp32/api-reference/system/freertos.html)

### 1.1 [vTaskList](https://www.freertos.org/a00021.html#vTaskList)

|No.|Key|Value|Remark|
|:---:|:---:|:---:|-----|
|1|`USE_TRACE_FACILITY`|`1`|*Enable FreeRTOS trace facility*|
|2|`USE_STATS_FORMATTING_FUNCTIONS`|`1`|*Enable FreeRTOS to collect run time stats*|

## 2 [ESP32 API Reference](https://docs.espressif.com/projects/esp-idf/zh_CN/release-v4.4/esp32/api-reference/index.html)

### 2.1 [Watchdogs](https://docs.espressif.com/projects/esp-idf/en/release-v4.4/esp32/api-reference/system/wdts.html)

|No.|Key|Value|Remark|
|:---:|:---:|:---:|-----|
|1|`CONFIG_ESP_INT_WDT_TIMEOUT_MS`|`5`|*Task Watchdog timeout period (seconds)*|
