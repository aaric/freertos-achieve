#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "ch10_queue_controller.c";

void myTaskSend(void *pvParam)
{
    int iNum = 0;
    BaseType_t xStatus;
    QueueHandle_t xQueue = (QueueHandle_t)pvParam;

    for (;;)
    {
        xStatus = xQueueSend(xQueue, &iNum, 0);
        xStatus = xQueueSend(xQueue, &pcText, 0);
        if (pdPASS == xStatus)
        {
            ESP_LOGI(TAG, "myTaskSend send ok, iNum = %d", iNum);
        }
        else
        {
            ESP_LOGI(TAG, "myTaskSend send error");
        }

        iNum++;

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void myTaskRec(void *pvParam)
{
    int iNum = 0;
    QueueHandle_t xQueue = (QueueHandle_t)pvParam;

    for (;;)
    {
        if (0 != uxQueueMessagesWaiting(xQueue))
        {
            xStatus = xQueueReceive(xQueue, &iNum, 0);

            if (pdPASS == xStatus)
            {
                ESP_LOGI(TAG, "myTaskRec rec ok, iNum=%d", iNum);

                free(pcText);
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
    QueueHandle_t xQueueHandle = xQueueCreate(5, sizeof(int));
    if (NULL != xQueueHandle)
    {
        // myTaskSend
        xTaskCreate(myTaskSend, "myTaskSend", 1024 * 5, (void *)xQueueHandle, 1, NULL);

        // myTaskRec
        xTaskCreate(myTaskRec, "myTaskRec", 1024 * 5, (void *)xQueueHandle, 1, NULL);
    }

    while (1)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
