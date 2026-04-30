#include "app_controller.h"

AppController::AppController() {}

void AppController::init()
{
    xTaskCreate(
        app_task,
        "appTask",
        8192,
        this,
        1,
        &task_app_controller_
    );
}

void AppController::app_task(void* pvParameters)
{
    auto* self = static_cast<AppController*>(pvParameters);

    while(1) {

    }
}