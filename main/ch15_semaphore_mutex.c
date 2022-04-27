#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "ch15_semaphore_mutex.c";

void myTask1(void *pvParam)
{
    BaseType_t iMutexState;
    SemaphoreHandle_t *pxSemaphoreMutex = (SemaphoreHandle_t *)pvParam;
    if (NULL != pxSemaphoreMutex)
    {
        ESP_LOGI(TAG, "myTask1 begin, pxSemaphoreMutex is not null");
    }

    for (;;)
    {
        iMutexState = xSemaphoreTake(*pxSemaphoreMutex, 1000);
        if (pdPASS == iMutexState)
        {
            ESP_LOGI(TAG, "myTask1 taked");
            for (int i = 0; i < 10; i++)
            {
                ESP_LOGI(TAG, "myTask1 --> i = %d", i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            xSemaphoreGive(*pxSemaphoreMutex);
            ESP_LOGI(TAG, "myTask1 gived");

            vTaskDelay(pdMS_TO_TICKS(5000));
        }
        else
        {
            ESP_LOGI(TAG, "myTask1 can't take");
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

    vTaskDelete(NULL);
}

void myTask2(void *pvParam)
{
    SemaphoreHandle_t *pxSemaphoreMutex = (SemaphoreHandle_t *)pvParam;
    if (NULL != pxSemaphoreMutex)
    {
        ESP_LOGI(TAG, "myTask2 begin, pxSemaphoreMutex is not null");
    }

    for (;;)
    {
        ;
    }

    vTaskDelete(NULL);
}

void myTask3(void *pvParam)
{
    BaseType_t iMutexState;
    SemaphoreHandle_t *pxSemaphoreMutex = (SemaphoreHandle_t *)pvParam;
    if (NULL != pxSemaphoreMutex)
    {
        ESP_LOGI(TAG, "myTask3 begin, pxSemaphoreMutex is not null");
    }

    for (;;)
    {
        iMutexState = xSemaphoreTake(*pxSemaphoreMutex, 1000);
        if (pdPASS == iMutexState)
        {
            ESP_LOGI(TAG, "myTask3 taked");
            for (int i = 0; i < 10; i++)
            {
                ESP_LOGI(TAG, "myTask3 --> i = %d", i);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }

            xSemaphoreGive(*pxSemaphoreMutex);
            ESP_LOGI(TAG, "myTask3 gived");

            vTaskDelay(pdMS_TO_TICKS(5000));
        }
        else
        {
            ESP_LOGI(TAG, "myTask3 can't take");
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // xSemaphoreCreateMutex
    SemaphoreHandle_t xSemaphoreHandle = xSemaphoreCreateMutex();

    // vTaskSuspendAll
    vTaskSuspendAll();

    // xTaskCreate
    xTaskCreate(myTask1, "myTask1", 1024 * 5, (void *)&xSemaphoreHandle, 1, NULL);
    xTaskCreate(myTask2, "myTask2", 1024 * 5, (void *)&xSemaphoreHandle, 2, NULL);
    xTaskCreate(myTask3, "myTask3", 1024 * 5, (void *)&xSemaphoreHandle, 3, NULL);

    // xTaskResumeAll
    xTaskResumeAll();

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
