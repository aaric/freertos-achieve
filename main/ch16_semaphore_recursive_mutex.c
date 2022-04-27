#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "ch16_semaphore_recursive_mutex.c";

void myTask1(void *pvParam)
{
    SemaphoreHandle_t *pxSemaphoreRecursiveMutex = (SemaphoreHandle_t *)pvParam;
    if (NULL != pxSemaphoreRecursiveMutex)
    {
        ESP_LOGI(TAG, "myTask1 begin, pxSemaphoreRecursiveMutex is not null");
    }

    for (;;)
    {
        xSemaphoreTakeRecursive(*pxSemaphoreRecursiveMutex, portMAX_DELAY);
        ESP_LOGI(TAG, "myTask1 (A) taked");

        for (int i = 0; i < 10; i++)
        {
            ESP_LOGI(TAG, "myTask1 (A) --> i = %d", i);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        xSemaphoreTakeRecursive(*pxSemaphoreRecursiveMutex, portMAX_DELAY);
        ESP_LOGI(TAG, "myTask1 (B) taked");

        for (int i = 0; i < 10; i++)
        {
            ESP_LOGI(TAG, "myTask1 (B) --> i = %d", i);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        xSemaphoreGiveRecursive(*pxSemaphoreRecursiveMutex);
        ESP_LOGI(TAG, "myTask1 (B) gived");

        xSemaphoreGiveRecursive(*pxSemaphoreRecursiveMutex);
        ESP_LOGI(TAG, "myTask1 (A) gived");

        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    vTaskDelete(NULL);
}

void myTask2(void *pvParam)
{
    SemaphoreHandle_t *pxSemaphoreRecursiveMutex = (SemaphoreHandle_t *)pvParam;
    if (NULL != pxSemaphoreRecursiveMutex)
    {
        ESP_LOGI(TAG, "myTask2 begin, pxSemaphoreRecursiveMutex is not null");
    }

    for (;;)
    {
        xSemaphoreTakeRecursive(*pxSemaphoreRecursiveMutex, portMAX_DELAY);
        ESP_LOGI(TAG, "myTask2 taked");

        for (int i = 0; i < 10; i++)
        {
            ESP_LOGI(TAG, "myTask2 --> i = %d", i);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        xSemaphoreGiveRecursive(*pxSemaphoreRecursiveMutex);
        ESP_LOGI(TAG, "myTask2 gived");

        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // xSemaphoreCreateMutex
    SemaphoreHandle_t xSemaphoreHandle = xSemaphoreCreateRecursiveMutex();

    // vTaskSuspendAll
    vTaskSuspendAll();

    // xTaskCreate
    xTaskCreate(myTask1, "myTask1", 1024 * 5, (void *)&xSemaphoreHandle, 1, NULL);
    xTaskCreate(myTask2, "myTask2", 1024 * 5, (void *)&xSemaphoreHandle, 2, NULL);

    // xTaskResumeAll
    xTaskResumeAll();

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
