#include <iostream>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

// Correctly define GPIO pins as gpio_num_t
#define LED GPIO_NUM_2
#define SW GPIO_NUM_23

extern "C" void app_main() {
    // Reset pins
    gpio_reset_pin(LED);
    gpio_reset_pin(SW);

    // Set directions
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(SW, GPIO_PULLUP_ONLY); // Set pull-up mode separately
    gpio_set_direction(SW, GPIO_MODE_INPUT);

    while (true) {
        // Read the status of the switch
        int status = gpio_get_level(SW);

        // Control the LED based on the switch status
        if(status == 0){
            gpio_set_level(LED, true);
        }
        else{
            gpio_set_level(LED, false);
        }

        // Delay for debouncing
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}
