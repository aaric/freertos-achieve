#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch07_task_delay.c";

void myTask(void *pvParam)
{
    for (;;)
    {
        char *pcText = (char *)pvParam;
        ESP_LOGI(TAG, "myTask pcText = %s", pcText);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // myTask1
    TaskHandle_t pxMyTask1 = NULL;
    char *pcMyTaskName1 = "myTask1 running";
    xTaskCreate(myTask, "myTask1", 2048, (void *)pcMyTaskName1, 1, &pcMyTaskName1);

    // uxTaskGetStackHighWaterMark
    UBaseType_t iStack;
    while (1)
    {
        ESP_LOGI(TAG, "hello world");

        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}
