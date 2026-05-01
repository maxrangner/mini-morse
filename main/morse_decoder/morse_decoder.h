#pragma once

#include "button_driver.h"
#include "config.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "freertos/task.h"

class MorseDecoder {
    TaskHandle_t task_morse_decoder_ = nullptr;
    QueueHandle_t app_queue_;
    button_t btn_;

    char input_buffer_[kInputBufferSize] = {};
    TimerHandle_t input_timer_;
    TimerHandle_t word_timer_;
    
    static void morse_task(void* pvParameters);
    static void input_timer_cb(TimerHandle_t timer);
    static void btn_cb(button_event_t btn_event, uint8_t gpio_num, void* user_data);
    void append_symbol(char c);
public:
    MorseDecoder();
    void init(QueueHandle_t app_queue);
    char decode_symbol(char* c);
    
};