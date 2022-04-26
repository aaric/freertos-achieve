#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "ch13_semaphore_binary.c";

static unsigned int iCount = 0;

void myTask1(void *pvParam)
{
    SemaphoreHandle_t *pxSemaphoreBinary = (SemaphoreHandle_t *)pvParam;
    if (NULL != pxSemaphoreBinary)
    {
        ESP_LOGI(TAG, "myTask1 begin, pxSemaphoreBinary is not null");
    }

    for (;;)
    {
        xSemaphoreTake(*pxSemaphoreBinary, portMAX_DELAY);
        for (int i = 0; i < 10; i++)
        {
            iCount++;
            ESP_LOGI(TAG, "myTask1 --> iCount = %d", iCount);

            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        xSemaphoreGive(*pxSemaphoreBinary);

        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    vTaskDelete(NULL);
}

void myTask2(void *pvParam)
{
    SemaphoreHandle_t *pxSemaphoreBinary = (SemaphoreHandle_t *)pvParam;
    if (NULL != pxSemaphoreBinary)
    {
        ESP_LOGI(TAG, "myTask2 begin, pxSemaphoreBinary is not null");
    }

    for (;;)
    {
        xSemaphoreTake(*pxSemaphoreBinary, portMAX_DELAY);
        for (int i = 0; i < 10; i++)
        {
            iCount++;
            ESP_LOGI(TAG, "myTask2 --> iCount = %d", iCount);

            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        xSemaphoreGive(*pxSemaphoreBinary);

        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // xSemaphoreCreateBinary
    SemaphoreHandle_t xSemaphoreHandle = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphoreHandle);

    // xTaskCreate
    xTaskCreate(myTask1, "myTask1", 1024 * 5, (void *)&xSemaphoreHandle, 1, NULL);
    xTaskCreate(myTask2, "myTask2", 1024 * 5, (void *)&xSemaphoreHandle, 1, NULL);

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
