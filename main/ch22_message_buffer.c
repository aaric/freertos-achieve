#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include "esp_log.h"

static const char *TAG = "ch22_message_buffer.c";

void myTask1(void *pvParam)
{
    int i = 0;
    char pvTxData[50];
    size_t xTxDataLen = 0;
    size_t xSendDataLen = 0;
    MessageBufferHandle_t xMessageBuffer = (MessageBufferHandle_t)pvParam;
    if (NULL != xMessageBuffer)
    {
        ESP_LOGI(TAG, "myTask1 begin, xMessageBuffer is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask1 start");

        // xMessageBufferSend
        xTxDataLen = sprintf(pvTxData, "No.%d, Hello freeRTOS!", ++i);
        xSendDataLen = xMessageBufferSend(xMessageBuffer, (void *)pvTxData, xTxDataLen, portMAX_DELAY);

        ESP_LOGI(TAG, "myTask1 --> pvTxData = %s, xTxDataLen = %d, xSendDataLen = %d", pvTxData, xTxDataLen, xSendDataLen);

        // sleep 3s
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    vTaskDelete(NULL);
}

void myTask2(void *pvParam)
{
    char pvRxData[200];
    size_t xRecDataLen = 0;
    MessageBufferHandle_t xMessageBuffer = (MessageBufferHandle_t)pvParam;
    if (NULL != xMessageBuffer)
    {
        ESP_LOGI(TAG, "myTask2 begin, xMessageBuffer is not null");
    }

    // sleep 9s
    vTaskDelay(pdMS_TO_TICKS(9000));

    for (;;)
    {
        ESP_LOGI(TAG, "myTask2 start");

        // xMessageBufferReceive
        memset(pvRxData, 0, sizeof(pvRxData));
        xRecDataLen = xMessageBufferReceive(xMessageBuffer, (void *)pvRxData, sizeof(pvRxData), portMAX_DELAY);

        ESP_LOGI(TAG, "myTask2 --> pvRxData = %s, xRecDataLen = %d", pvRxData, xRecDataLen);

        // sleep 3s
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    vTaskDelete(NULL);
}

void myTask3(void *pvParam)
{
    size_t xCurrSpace = 0;
    size_t xMinSpace = 1000;
    MessageBufferHandle_t xMessageBuffer = (MessageBufferHandle_t)pvParam;
    if (NULL != xMessageBuffer)
    {
        ESP_LOGI(TAG, "myTask3 begin, xMessageBuffer is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask3 start");

        // xMessageBufferSpacesAvailable
        xCurrSpace = xMessageBufferSpacesAvailable(xMessageBuffer);
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
    MessageBufferHandle_t xMessageBufferHandle = xMessageBufferCreate(100);

    if (NULL != xMessageBufferHandle)
    {
        // xTaskCreate
        xTaskCreate(myTask1, "myTask1", 1024 * 5, (void *)xMessageBufferHandle, 1, NULL);
        xTaskCreate(myTask2, "myTask2", 1024 * 5, (void *)xMessageBufferHandle, 1, NULL);
        xTaskCreate(myTask3, "myTask3", 1024 * 5, (void *)xMessageBufferHandle, 1, NULL);
    }
    else
    {
        ESP_LOGI(TAG, "xMessageBufferHandle create error");
    }

    while (1)
    {
        // sleep 5s
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
