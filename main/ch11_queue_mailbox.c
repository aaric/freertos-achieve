#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "ch11_queue_mailbox.c";

void myTaskSend(void *pvParam)
{
    int iNum = 0;
    BaseType_t xStatus;
    QueueHandle_t xQueue = (QueueHandle_t)pvParam;

    for (;;)
    {
        xStatus = xQueueOverwrite(xQueue, &iNum);
        if (pdPASS == xStatus)
        {
            ESP_LOGI(TAG, "myTaskSend send ok, iNum = %d", iNum);
        }
        else
        {
            ESP_LOGI(TAG, "myTaskSend send error");
        }

        iNum++;

        vTaskDelay(3000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void myTaskRec1(void *pvParam)
{
    int iNum = 0;
    BaseType_t xStatus;
    QueueHandle_t xQueue = (QueueHandle_t)pvParam;

    for (;;)
    {
        xStatus = xQueuePeek(xQueue, &iNum, 0);
        if (pdPASS == xStatus)
        {
            ESP_LOGI(TAG, "myTaskRec1 rec ok, iNum=%d", iNum);
        }
        else
        {
            ESP_LOGI(TAG, "myTaskRec1 rec error");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void myTaskRec2(void *pvParam)
{
    int iNum = 0;
    BaseType_t xStatus;
    QueueHandle_t xQueue = (QueueHandle_t)pvParam;

    for (;;)
    {
        xStatus = xQueuePeek(xQueue, &iNum, 0);
        if (pdPASS == xStatus)
        {
            ESP_LOGI(TAG, "myTaskRec2 rec ok, iNum=%d", iNum);
        }
        else
        {
            ESP_LOGI(TAG, "myTaskRec2 rec error");
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // xQueueCreate
    QueueHandle_t xQueueHandle = xQueueCreate(1, sizeof(int));

    if (NULL != xQueueHandle)
    {
        // myTaskSend
        xTaskCreate(myTaskSend, "myTaskSend", 1024 * 5, (void *)xQueueHandle, 1, NULL);

        // myTaskRec
        xTaskCreate(myTaskRec1, "myTaskRec1", 1024 * 5, (void *)xQueueHandle, 2, NULL);
        xTaskCreate(myTaskRec2, "myTaskRec2", 1024 * 5, (void *)xQueueHandle, 2, NULL);
    }

    while (1)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
