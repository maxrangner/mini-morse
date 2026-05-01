#include "morse_decoder.h"

#include "esp_log.h"

#include "morse_key.h"

static const char *TAG = "morse_decoder";

MorseDecoder::MorseDecoder() {}

void MorseDecoder::init()
{
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

    uint8_t counter = 0;

    while(1) {
        // ESP_LOGI(TAG, "MorseDecoder: %d", counter++);
        vTaskDelay(pdMS_TO_TICKS(3000));
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

    char input_char = self->decode_symbol(self->input_buffer_);
    ESP_LOGI(TAG, "Morse: %s       Latin: %c", self->input_buffer_, input_char);

    memset(&self->input_buffer_[0], 0, sizeof(self->input_buffer_));
}

char MorseDecoder::decode_symbol(char* symbol)
{
    char return_char = {};
    for (uint8_t i = 0; i < morseKeyLen; i++) {
        if (strcmp(morseKey[i].morse, symbol) == 0) {
            return_char = morseKey[i].latin;
        }
    }
    return return_char;
}
