#include "app_controller.h"

#include "morse_decoder.h"

#include "esp_log.h"

static const char *TAG = "app_controller";

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

    MorseDecoder morse;
    morse.init();

    uint8_t counter = 0;

    while(1) {
        // ESP_LOGI(TAG, "AppController: %d", counter++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
