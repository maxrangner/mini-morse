#include "morse_decoder.h"

#include "esp_log.h"

#include "morse_key.h"
#include "app_types.h"

static const char *TAG = "morse_decoder";

MorseDecoder::MorseDecoder() {}

void MorseDecoder::init(QueueHandle_t app_queue)
{
    app_queue_ = app_queue;

    button_service_init();
    button_cfg_t btn_cfg = {
        .gpio_num = 9,
        .hasPullup = true,
        .debounce = 25,
        .long_press_dur = 300,
        .btn_callback = btn_cb,
        .user_data = this,
    };
    button_init(&btn_cfg, &btn_);

    xTaskCreate(
        morse_task,
        "morseTask",
        8192,
        this,
        1,
        &task_morse_decoder_
    );

    input_timer_ = xTimerCreate(
        "input_timer_",
        pdMS_TO_TICKS(1200),
        pdFALSE,
        this,
        input_timer_cb
    );
    word_timer_ = xTimerCreate(
        "word_timer_",
        pdMS_TO_TICKS(1000),
        pdFALSE,
        nullptr,
        nullptr
    );
}

void MorseDecoder::morse_task(void* pvParameters)
{
    auto* self = static_cast<MorseDecoder*>(pvParameters);

    while(1) {
        vTaskDelay(portMAX_DELAY);
    }
}

void MorseDecoder::append_symbol(char c)
{
    size_t len = strlen(input_buffer_);
    if (len < kInputBufferSize - 1) {
        input_buffer_[len] = c;
        input_buffer_[len + 1] = '\0';
    }
}

void MorseDecoder::btn_cb(button_event_t btn_event, uint8_t gpio_num, void* user_data)
{
    auto *self = (MorseDecoder *)user_data;

    if (gpio_num == 9) {
        if (btn_event == BTN_SHORT_PRESS) {
            ESP_LOGI(TAG, "Short btn press");

            char symbol = '.';
            self->append_symbol(symbol);
        }
        if (btn_event == BTN_LONG_PRESS) {
            ESP_LOGI(TAG, "Long btn press");

            char symbol = '-';
            self->append_symbol(symbol);
        }
        xTimerReset(self->input_timer_, 0);
    }

    // if (event.msg_event != AppEventType::NONE) {
    //     self->post_event(event);
    // }
}

void MorseDecoder::input_timer_cb(TimerHandle_t timer)
{
    auto *self = static_cast<MorseDecoder *>(pvTimerGetTimerID(timer));

    app_event_t event;
    event.event = AppEventType::INPUT_CHAR;

    char input_char = self->decode_symbol(self->input_buffer_);
    event.input_char = input_char;

    xQueueSend(self->app_queue_, &event, 0);

    memset(&self->input_buffer_[0], 0, sizeof(self->input_buffer_));
}

char MorseDecoder::decode_symbol(char* c)
{
    char return_char = {};
    for (uint8_t i = 0; i < morseKeyLen; i++) {
        if (strcmp(morseKey[i].morse, c) == 0) {
            return_char = morseKey[i].latin;
        }
    }
    return return_char;
}
