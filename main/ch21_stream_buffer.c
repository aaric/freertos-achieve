#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/stream_buffer.h"
#include "esp_log.h"

static const char *TAG = "ch21_stream_buffer.c";

void myTask1(void *pvParam)
{
    int i = 0;
    char pvTxData[50];
    size_t xTxDataLen = 0;
    size_t xSendDataLen = 0;
    StreamBufferHandle_t xStreamBuffer = (StreamBufferHandle_t)pvParam;
    if (NULL != xStreamBuffer)
    {
        ESP_LOGI(TAG, "myTask1 begin, xStreamBuffer is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask1 start");

        // xStreamBufferSend
        i++;
        xTxDataLen = sprintf(pvTxData, "No.%d, Hello freeRTOS!", i);
        xSendDataLen = xStreamBufferSend(xStreamBuffer, (void *)pvTxData, xTxDataLen, portMAX_DELAY);

        ESP_LOGI(TAG, "myTask1 --> pvTxData = %s, xTxDataLen = %d, xSendDataLen = %d", pvTxData, xTxDataLen, xSendDataLen);

        // sleep 3s
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    vTaskDelete(NULL);
}

void myTask2(void *pvParam)
{
    char pvRxData[50];
    size_t xSendDataLen = 0;
    StreamBufferHandle_t xStreamBuffer = (StreamBufferHandle_t)pvParam;
    if (NULL != xStreamBuffer)
    {
        ESP_LOGI(TAG, "myTask2 begin, xStreamBuffer is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask2 start");

        // xStreamBufferReceive
        xSendDataLen = xStreamBufferReceive(xStreamBuffer, (void *)pvRxData, sizeof(pvRxData), portMAX_DELAY);

        ESP_LOGI(TAG, "myTask2 --> pvRxData = %s, xSendDataLen = %d", pvRxData, xSendDataLen);
    }

    vTaskDelete(NULL);
}

void myTask3(void *pvParam)
{
    size_t xCurrSpace = 0;
    size_t xMinSpace = 1000;
    StreamBufferHandle_t xStreamBuffer = (StreamBufferHandle_t)pvParam;
    if (NULL != xStreamBuffer)
    {
        ESP_LOGI(TAG, "myTask3 begin, xStreamBuffer is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask3 start");

        // xStreamBufferSpacesAvailable
        xCurrSpace = xStreamBufferSpacesAvailable(xStreamBuffer);
        if (xCurrSpace < xMinSpace)
        {
            xMinSpace = xCurrSpace;
        }

        ESP_LOGI(TAG, "myTask3 --> xCurrSpace = %d, xMinSpace = %d", xCurrSpace, xMinSpace);

        // sleep 3s
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // Init
    StreamBufferHandle_t xStreamBufferHandle = xStreamBufferCreate(1000, 10);

    if (NULL != xStreamBufferHandle)
    {
        // vTaskSuspendAll
        vTaskSuspendAll();

        // xTaskCreate
        xTaskCreate(myTask1, "myTask1", 1024 * 5, (void *)xStreamBufferHandle, 1, NULL);
        xTaskCreate(myTask2, "myTask2", 1024 * 5, (void *)xStreamBufferHandle, 1, NULL);
        xTaskCreate(myTask3, "myTask3", 1024 * 5, (void *)xStreamBufferHandle, 1, NULL);

        // xTaskResumeAll
        xTaskResumeAll();
    }

    while (1)
    {
        // sleep 5s
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
