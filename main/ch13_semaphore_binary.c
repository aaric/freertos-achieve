#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch13_semaphore_binary.c";

void app_main(void)
{
    while (1)
    {
        ESP_LOGI(TAG, "hello world");

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
