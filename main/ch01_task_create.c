#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch01_task_create";

void myTask(void *pvParam)
{
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    vTaskDelete(NULL);
}

void app_main(void)
{
    TaskHandle_t pxMyTaskHandle = NULL;
    // xTaskCreate(myTask, "myTask", 2048, NULL, 1, NULL);
    xTaskCreate(myTask, "myTask", 2048, NULL, 1, &pxMyTaskHandle);

    UBaseType_t uxPriority = uxTaskPriorityGet(pxMyTaskHandle);
    ESP_LOGI(TAG, "myTask uxPriority = %d", uxPriority);
}
