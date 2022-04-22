#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "ch10_queue_controller.c";

void myTaskSend1(void *pvParam)
{
    int iNum = 100;
    BaseType_t xStatus;
    QueueHandle_t xQueue = (QueueHandle_t)pvParam;

    for (;;)
    {
        xStatus = xQueueSend(xQueue, &iNum, 0);
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

void myTaskSend2(void *pvParam)
{
    int iNum = 200;
    BaseType_t xStatus;
    QueueHandle_t xQueue = (QueueHandle_t)pvParam;

    for (;;)
    {
        xStatus = xQueueSend(xQueue, &iNum, 0);
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
    BaseType_t xStatus;
    QueueSetMemberHandle_t xQueueSetMember;
    QueueSetHandle_t xQueueSet = (QueueSetHandle_t)pvParam;

    for (;;)
    {
        xQueueSetMember = xQueueSelectFromSet(xQueueSet, portMAX_DELAY);
        xStatus = xQueueReceive(xQueueSetMember, &iNum, portMAX_DELAY);
        if (pdPASS == xStatus)
        {
            ESP_LOGI(TAG, "myTaskRec rec ok, iNum=%d", iNum);
        }
        else
        {
            ESP_LOGI(TAG, "myTaskRec rec error");
        }
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // xQueueCreate
    QueueHandle_t xQueueHandle1 = xQueueCreate(5, sizeof(int));
    QueueHandle_t xQueueHandle2 = xQueueCreate(5, sizeof(int));

    // xQueueCreateSet
    QueueSetHandle_t xQueueSetHandle = xQueueCreateSet(5 + 5);
    xQueueAddToSet(xQueueHandle1, xQueueSetHandle);
    xQueueAddToSet(xQueueHandle2, xQueueSetHandle);

    if (NULL != xQueueHandle1 && NULL != xQueueHandle2 && NULL != xQueueSetHandle)
    {
        // myTaskSend
        xTaskCreate(myTaskSend1, "myTaskSend1", 1024 * 5, (void *)xQueueHandle1, 1, NULL);
        xTaskCreate(myTaskSend2, "myTaskSend2", 1024 * 5, (void *)xQueueHandle2, 1, NULL);

        // myTaskRec
        xTaskCreate(myTaskRec, "myTaskRec", 1024 * 5, (void *)xQueueSetHandle, 1, NULL);
    }

    while (1)
    {
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}
