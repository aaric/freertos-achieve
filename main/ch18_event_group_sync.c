#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#define BIT_0 (1 << 0)
#define BIT_1 (1 << 1)
#define BIT_2 (1 << 2)
#define BIT_G_012 (BIT_0 | BIT_1 | BIT_2)

static const char *TAG = "ch18_event_group_sync.c";

void myTask1(void *pvParam)
{
    EventBits_t uxBits;
    EventGroupHandle_t *pxEventGroupSync = (EventGroupHandle_t *)pvParam;
    if (NULL != pxEventGroupSync)
    {
        ESP_LOGI(TAG, "myTask1 begin, pxEventGroupSync is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask1 start");

        // xEventGroupSync
        uxBits = xEventGroupSync(*pxEventGroupSync,
                                 BIT_0,
                                 BIT_G_012,
                                 portMAX_DELAY);

        ESP_LOGI(TAG, "myTask1 end --> uxBits = 0x%x", uxBits);

        vTaskDelay(pdMS_TO_TICKS(10000));
    }

    vTaskDelete(NULL);
}

void myTask2(void *pvParam)
{
    EventBits_t uxBits;
    EventGroupHandle_t *pxEventGroupSync = (EventGroupHandle_t *)pvParam;
    if (NULL != pxEventGroupSync)
    {
        ESP_LOGI(TAG, "myTask2 begin, pxEventGroupSync is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask2 start");

        // xEventGroupSync
        uxBits = xEventGroupSync(*pxEventGroupSync,
                                 BIT_1,
                                 BIT_G_012,
                                 portMAX_DELAY);

        ESP_LOGI(TAG, "myTask2 end --> uxBits = 0x%x", uxBits);

        vTaskDelay(pdMS_TO_TICKS(10000));
    }

    vTaskDelete(NULL);
}

void myTask3(void *pvParam)
{
    EventBits_t uxBits;
    EventGroupHandle_t *pxEventGroupSync = (EventGroupHandle_t *)pvParam;
    if (NULL != pxEventGroupSync)
    {
        ESP_LOGI(TAG, "myTask3 begin, pxEventGroupSync is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask2 start");

        // xEventGroupSync
        uxBits = xEventGroupSync(*pxEventGroupSync,
                                 BIT_2,
                                 BIT_G_012,
                                 portMAX_DELAY);

        ESP_LOGI(TAG, "myTask3 end --> uxBits = 0x%x", uxBits);

        vTaskDelay(pdMS_TO_TICKS(10000));
    }

    vTaskDelete(NULL);
}

void app_main(void)
{
    // xEventGroupCreate
    EventGroupHandle_t xEventGroupHandle = xEventGroupCreate();

    if (NULL != xEventGroupHandle)
    {
        // vTaskSuspendAll
        vTaskSuspendAll();

        // xTaskCreate
        xTaskCreate(myTask1, "myTask1", 1024 * 5, (void *)&xEventGroupHandle, 1, NULL);
        xTaskCreate(myTask2, "myTask2", 1024 * 5, (void *)&xEventGroupHandle, 1, NULL);
        xTaskCreate(myTask3, "myTask3", 1024 * 5, (void *)&xEventGroupHandle, 1, NULL);

        // xTaskResumeAll
        xTaskResumeAll();
    }
    else
    {
        ESP_LOGI(TAG, "xEventGroupHandle create error");
    }

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
