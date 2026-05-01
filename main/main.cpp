#include <stdio.h>
#include "app_controller.h"

extern "C" void app_main(void)
{
    AppController app_ctrl;
    app_ctrl.init();
    
    while(1) {
        vTaskDelay(portMAX_DELAY);
    }
}
