#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/adc.h"

#include "sensor_component.h"

#define LED_PIN GPIO_NUM_2

void sensor_init(void)
{
    // LED output
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    // ADC setup
    adc1_config_width(ADC_WIDTH_BIT_12);

    // LDR
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);

    // Potmeter
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
}

void sensor_task(void)
{
    int lightValue;
    int potValue;

    while (1)
    {
        // ADC uitlezen
        lightValue = adc1_get_raw(ADC1_CHANNEL_6);

        potValue = adc1_get_raw(ADC1_CHANNEL_7);

        printf("Light: %d | Pot: %d\n", lightValue, potValue);

        // Vergelijking
        if (lightValue < potValue)
        {
            gpio_set_level(LED_PIN, 1);
        }
        else
        {
            gpio_set_level(LED_PIN, 0);
        }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}