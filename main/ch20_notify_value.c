#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ch20_notify_value.c";

void myTask1(void *pvParam)
{
    uint32_t ulNotifyValue;
    ESP_LOGI(TAG, "myTask1 begin");

    for (;;)
    {
        ESP_LOGI(TAG, "myTask1 start");

        xTaskNotifyWait(0x00, ULLONG_MAX, &ulNotifyValue, portMAX_DELAY);

        if (0 != (ulNotifyValue & (0x01 << 0)))
        {
            ESP_LOGI(TAG, "myTask1 process bit0 event");
        }
        else if (0 != (ulNotifyValue & (0x01 << 1)))
        {
            ESP_LOGI(TAG, "myTask1 process bit1 event");
        }
        else if (0 != (ulNotifyValue & (0x01 << 2)))
        {
            ESP_LOGI(TAG, "myTask1 process bit2 event");
        }
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

        // xTaskNotify
        ESP_LOGI(TAG, "myTask2 set bit0");
        xTaskNotify(pxMyTask1, 0x01 << 0, eSetValueWithoutOverwrite);

        // sleep 5s
        vTaskDelay(pdMS_TO_TICKS(5000));

        // xTaskNotify
        ESP_LOGI(TAG, "myTask2 set bit1");
        xTaskNotify(pxMyTask1, 0x01 << 1, eSetValueWithoutOverwrite);

        // sleep 5s
        vTaskDelay(pdMS_TO_TICKS(5000));

        // xTaskNotify
        ESP_LOGI(TAG, "myTask2 set bit2");
        xTaskNotify(pxMyTask1, 0x01 << 2, eSetValueWithoutOverwrite);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // xEventGroupCreate
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
