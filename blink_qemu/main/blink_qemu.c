#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define BLINK_GPIO GPIO_NUM_2

static const char *TAG = "BLINK_DEMO";

void app_main(void)
{
	gpio_reset_pin(BLINK_GPIO);
	gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
	while(1)
	{
	gpio_set_level(BLINK_GPIO, 1);
	ESP_LOGI(TAG, "LED ON");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	gpio_set_level(BLINK_GPIO, 0);
	ESP_LOGI(TAG, "LED OFF");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
