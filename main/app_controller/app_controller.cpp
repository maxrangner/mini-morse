#include "app_controller.h"

#include "morse_decoder.h"
#include "app_types.h"

#include "esp_log.h"

static const char *TAG = "app_controller";

AppController::AppController() {}

void AppController::init()
{
    in_queue_ = xQueueCreate(10, sizeof(app_event_t));

    xTaskCreate(
        app_task,
        "appTask",
        8192,
        this,
        1,
        &task_app_controller_
    );
}

QueueHandle_t AppController::get_app_queue()
{
    return in_queue_;
}

void AppController::app_task(void* pvParameters)
{
    auto* self = static_cast<AppController*>(pvParameters);

    MorseDecoder morse;
    morse.init(self->get_app_queue());

    app_event_t event;

    while(1) {
        if (xQueueReceive(self->in_queue_, &event, portMAX_DELAY)) {
            if (event.event == AppEventType::INPUT_CHAR) {
                ESP_LOGI(TAG, "Received input char: %c", event.input_char);
            }
        }
    }
}
