#pragma once

enum class AppEventType {
    NONE,
    INPUT_CHAR,
    SPACE,
};

struct app_event_t {
    AppEventType event;
    char input_char;
};
