#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch06_task_stack.c";

void myTask(void *pvParam)
{
    char *pcText = (char *)pvParam;

    for (;;)
    {
        ESP_LOGI(TAG, "myTask pcText = %s", pcText);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // myTask
    TaskHandle_t pxMyTask = NULL;
    char *pcMyTaskName = "myTask running";
    xTaskCreate(myTask, "myTask", 2048, (void *)pcMyTaskName, 1, &pcMyTaskName);

    // uxTaskGetStackHighWaterMark
    UBaseType_t iStack;
    while (1)
    {
        iStack = uxTaskGetStackHighWaterMark(pxMyTask);
        ESP_LOGI(TAG, "iStack = %d", iStack);

        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
}
