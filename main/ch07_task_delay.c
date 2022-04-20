#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch07_task_delay.c";

void myTaskDelay(void *pvParam)
{
    char *pcText = (char *)pvParam;

    for (;;)
    {
        ESP_LOGI(TAG, "myTask pcText = %s", pcText);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void myTaskDelayUnit(void *pvParam)
{
    char *pcText = (char *)pvParam;
    TickType_t pxPreviousWakeTime = xTaskGetTickCount();

    for (;;)
    {
        ESP_LOGI(TAG, "myTask pcText = %s", pcText);

        vTaskDelayUntil(&pxPreviousWakeTime, 1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // myTaskDelay
    char *pcMyTaskDelayParam = "myTaskDelay running";
    xTaskCreate(myTaskDelay, "myTaskDelay", 2048, (void *)pcMyTaskDelayParam, 1, NULL);

    // myTaskDelay
    char *pcMyTaskDelayUnitParam = "myTaskDelayUnit running";
    xTaskCreate(myTaskDelayUnit, "myTaskDelayUnit", 2048, (void *)pcMyTaskDelayUnitParam, 1, NULL);

    while (1)
    {
        ESP_LOGI(TAG, "hello world");

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
