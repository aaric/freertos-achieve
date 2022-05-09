#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch19_notify_sync.c";

void myTask1(void *pvParam)
{
    ESP_LOGI(TAG, "myTask1 begin");

    for (;;)
    {
        ESP_LOGI(TAG, "myTask1 start");
        ESP_LOGI(TAG, "myTask1 wait notify");

        // ulTaskNotifyTake
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        ESP_LOGI(TAG, "myTask1 notify take");
    }

    vTaskDelete(NULL);
}

void myTask2(void *pvParam)
{
    TaskHandle_t pxMyTask1 = (TaskHandle_t)pvParam;
    if (NULL != pxMyTask1)
    {
        ESP_LOGI(TAG, "myTask2 begin, pxMyTask1 is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask2 start");

        // sleep 5s
        vTaskDelay(pdMS_TO_TICKS(5000));

        // xTaskNotifyGive
        xTaskNotifyGive(pxMyTask1);

        ESP_LOGI(TAG, "myTask2 notify give");
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // Init
    TaskHandle_t pxMyTask1;

    // vTaskSuspendAll
    vTaskSuspendAll();

    // xTaskCreate
    xTaskCreate(myTask1, "myTask1", 1024 * 5, NULL, 1, &pxMyTask1);
    xTaskCreate(myTask2, "myTask2", 1024 * 5, (void *)pxMyTask1, 1, NULL);

    // xTaskResumeAll
    xTaskResumeAll();

    while (1)
    {
        // sleep 5s
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
