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
    TaskHandle_t pxMyTask = NULL;
    // xTaskCreate(myTask, "myTask", 2048, NULL, 1, NULL);
    xTaskCreate(myTask, "myTask", 2048, NULL, 1, &pxMyTask);

    UBaseType_t uxPriority = uxTaskPriorityGet(pxMyTask);
    ESP_LOGI(TAG, "myTask uxPriority = %d", uxPriority);
}
