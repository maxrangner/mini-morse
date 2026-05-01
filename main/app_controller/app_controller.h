#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class AppController {
    TaskHandle_t task_app_controller_ = nullptr;
    
    static void app_task(void* pvParameters);
public:
    AppController();
    void init();
};