#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class AppController {
    TaskHandle_t task_app_controller_ = nullptr;

    QueueHandle_t in_queue_;
    char outgoing_text_[50] = {};
    
    static void app_task(void* pvParameters);
public:
    AppController();
    void init();
    QueueHandle_t get_app_queue();
};