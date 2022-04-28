#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch17_event_group_wait.c";

void myTask(void *pvParam)
{
    ESP_LOGI(TAG, "myTask begin");

    for (;;)
    {
        ESP_LOGI(TAG, "hello world");

        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // vTaskSuspendAll
    vTaskSuspendAll();

    // xTaskCreate
    xTaskCreate(myTask, "myTask", 1024 * 5, NULL, 1, NULL);

    // xTaskResumeAll
    xTaskResumeAll();

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
