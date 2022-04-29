#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#define BIT_0 (1 << 0)
#define BIT_4 (1 << 4)

static const char *TAG = "ch17_event_group_wait.c";

void myTask1(void *pvParam)
{
    EventBits_t uxBits;
    EventGroupHandle_t *pxEventGroupWait = (EventGroupHandle_t *)pvParam;
    if (NULL != pxEventGroupWait)
    {
        ESP_LOGI(TAG, "myTask1 begin, pxEventGroupWait is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask1 start");

        // xEventGroupWaitBits
        // uxBits = xEventGroupWaitBits(*pxEventGroupWait,
        //                              BIT_0 | BIT_4,
        //                              pdTRUE,
        //                              pdFALSE,
        //                              portMAX_DELAY);
        uxBits = xEventGroupWaitBits(*pxEventGroupWait,
                                     BIT_0 | BIT_4,
                                     pdTRUE,
                                     pdTRUE,
                                     portMAX_DELAY);

        // ESP_LOGI(TAG, "myTask1, bit0 or bit4 is setted --> uxBits = 0x%x", uxBits);
        ESP_LOGI(TAG, "myTask1, bit0 and bit4 is setted --> uxBits = 0x%x", uxBits);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    vTaskDelete(NULL);
}

void myTask2(void *pvParam)
{
    EventBits_t uxBits;
    EventGroupHandle_t *pxEventGroupWait = (EventGroupHandle_t *)pvParam;
    if (NULL != pxEventGroupWait)
    {
        ESP_LOGI(TAG, "myTask2 begin, pxEventGroupWait is not null");
    }

    for (;;)
    {
        ESP_LOGI(TAG, "myTask2 start");

        // xEventGroupSetBits
        uxBits = xEventGroupSetBits(*pxEventGroupWait, BIT_0);
        ESP_LOGI(TAG, "myTask2, bit0 is setted --> uxBits=0x%x", uxBits);

        vTaskDelay(pdMS_TO_TICKS(5000));

        // xEventGroupSetBits
        uxBits = xEventGroupSetBits(*pxEventGroupWait, BIT_4);
        ESP_LOGI(TAG, "myTask2, bit4 is setted --> uxBits=0x%x", uxBits);

        vTaskDelay(pdMS_TO_TICKS(5000));
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
        xTaskCreate(myTask1, "myTask1", 1024 * 5, (void *)&xEventGroupHandle, 2, NULL);
        xTaskCreate(myTask2, "myTask2", 1024 * 5, (void *)&xEventGroupHandle, 1, NULL);

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
