#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_log.h"

static const char *TAG = "ch12_timer_create.c";

void myTimer(TimerHandle_t xTimer)
{
    BaseType_t iTimeId = (BaseType_t)pvTimerGetTimerID(xTimer);
    const char *pcTimeName = pcTimerGetName(xTimer);

    ESP_LOGI(TAG, "myTimer --> timerId = %d, timerName = %s", iTimeId, pcTimeName);
}

void app_main(void)
{
    // xTimerCreate
    TimerHandle_t xMyTimer1 = xTimerCreate("myTimer1", pdMS_TO_TICKS(1000), pdTRUE, (void *)1, myTimer);
    TimerHandle_t xMyTimer2 = xTimerCreate("myTimer2", pdMS_TO_TICKS(2000), pdTRUE, (void *)2, myTimer);

    // xTimerStart
    xTimerStart(xMyTimer1, 0);
    xTimerStart(xMyTimer2, 0);

    // xTimerStop
    // vTaskDelay(pdMS_TO_TICKS(5000));
    // xTimerStop(xMyTimer1, 0);

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
