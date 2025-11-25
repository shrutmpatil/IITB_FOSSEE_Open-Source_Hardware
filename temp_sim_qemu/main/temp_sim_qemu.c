#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

float generate_simulated_temp(float min_temp, float max_temp);
static const char *TAG = "TEMP_SIM";

float generate_simulated_temp(float min_temp, float max_temp)
{
	float random_unit = (float)rand() / (float)RAND_MAX;
	return (min_temp + random_unit * (max_temp - min_temp));
}

void app_main(void)
{
	srand(time(NULL));
	float min_temp = 20.0;
	float max_temp = 25.0;
	ESP_LOGI(TAG, "Temperature Sensor Simulation Starting...");
	while(1)
	{
		float temperature = generate_simulated_temp(min_temp, max_temp);
		printf("Temperature: %.2f C\n", temperature);
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}
