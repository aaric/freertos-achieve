#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"

static const char *TAG = "ch14_semaphore_counting.c";

void caInTask(void *pvParam)
{
    int iParkingSpaceLeft = 0;
    BaseType_t iTakeRst;
    SemaphoreHandle_t *pxSemaphoreCounting = (SemaphoreHandle_t *)pvParam;
    if (NULL != pxSemaphoreCounting)
    {
        ESP_LOGI(TAG, "myTask1 begin, pxSemaphoreCounting is not null");
    }

    for (;;)
    {
        iParkingSpaceLeft = uxSemaphoreGetCount(*pxSemaphoreCounting);
        ESP_LOGI(TAG, "caInTask --> iParkingSpaceLeft = %d", iParkingSpaceLeft);

        iTakeRst = xSemaphoreTake(*pxSemaphoreCounting, 0);
        if (pdPASS == iTakeRst)
        {
            ESP_LOGI(TAG, "caInTask, one car in");
        }
        else
        {
            ESP_LOGI(TAG, "caInTask, no parking space");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    vTaskDelete(NULL);
}

void carOutTask(void *pvParam)
{
    SemaphoreHandle_t *pxSemaphoreCounting = (SemaphoreHandle_t *)pvParam;
    if (NULL != pxSemaphoreCounting)
    {
        ESP_LOGI(TAG, "carOutTask begin, pxSemaphoreCounting is not null");
    }

    for (;;)
    {
        xSemaphoreGive(*pxSemaphoreCounting);
        ESP_LOGI(TAG, "carOutTask, one car out");

        vTaskDelay(pdMS_TO_TICKS(6000));
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // xSemaphoreCreateCounting
    SemaphoreHandle_t xSemaphoreHandle = xSemaphoreCreateCounting(5, 5);
    xSemaphoreGive(xSemaphoreHandle);

    // xTaskCreate
    xTaskCreate(caInTask, "caInTask", 1024 * 5, (void *)&xSemaphoreHandle, 1, NULL);
    xTaskCreate(carOutTask, "carOutTask", 1024 * 5, (void *)&xSemaphoreHandle, 1, NULL);

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
