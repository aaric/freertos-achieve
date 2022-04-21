#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "ch09_queue_create.c";

void myTaskSend(void *pvParam)
{
    int i = 0;
    BaseType_t xStatus;
    QueueHandle_t xQueue = (QueueHandle_t)pvParam;

    for (;;)
    {
        xStatus = xQueueSend(xQueue, &i, 0);
        if (pdPASS == xStatus)
        {
            ESP_LOGI(TAG, "myTaskSend send ok, i = %d", i);
        }
        else
        {
            ESP_LOGI(TAG, "myTaskSend send error");
        }

        i++;

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void myTaskRec(void *pvParam)
{
    int j = 0;
    BaseType_t xStatus;
    QueueHandle_t xQueue = (QueueHandle_t)pvParam;

    for (;;)
    {
        if (0 != uxQueueMessagesWaiting(xQueue))
        {
            xStatus = xQueueReceive(xQueue, &j, 0);

            if (pdPASS == xStatus)
            {
                ESP_LOGI(TAG, "myTaskRec rec ok, j=%d", j);
            }
            else
            {
                ESP_LOGI(TAG, "myTaskRec rec error");
            }
        }
        else
        {
            ESP_LOGI(TAG, "myTaskRec rec none");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // xQueueCreate
    QueueHandle_t xQueueHandle = xQueueCreate(3, sizeof(int));
    if (NULL != xQueueHandle)
    {
        // myTaskSend
        xTaskCreate(myTaskSend, "myTaskSend", 1024 * 5, (void *)xQueueHandle, 1, NULL);

        // myTaskRec
        xTaskCreate(myTaskRec, "myTaskRec", 1024 * 5, (void *)xQueueHandle, 1, NULL);

        // vTaskStartScheduler
        // vTaskStartScheduler(); -- error
    }

    while (1)
    {
        ESP_LOGI(TAG, "hello world");

        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
