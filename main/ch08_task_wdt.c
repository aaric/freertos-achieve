#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_task_wdt.h"

static const char *TAG = "ch08_task_wdt.c";

void myTask(void *pvParam)
{
    char *pcText = (char *)pvParam;

    esp_task_wdt_add(NULL);

    for (;;)
    {
        ESP_LOGI(TAG, "myTask --> pcText = %s", pcText);

        esp_task_wdt_reset();

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // myTask
    char *pcMyTaskParam = "myTask running";
    xTaskCreate(myTask, "myTask", 2048, (void *)pcMyTaskParam, 1, NULL);

    while (1)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
