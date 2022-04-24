#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "esp_log.h"

static const char *TAG = "ch12_timer_create.c";

void myTimer(TimerHandle_t xTimer)
{
    ESP_LOGI(TAG, "myTimer, many timers");
}

void app_main(void)
{
    // xTimerCreate
    TimerHandle_t xMyTimer = xTimerCreate("myTimer", pdMS_TO_TICKS(1000), pdTRUE, (void *)0, myTimer);

    // xTimerStart
    xTimerStart(xMyTimer, 0);

    // xTimerStop
    vTaskDelay(pdMS_TO_TICKS(5000));
    xTimerStop(xMyTimer, 0);

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
