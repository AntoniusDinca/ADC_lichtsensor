#include <stdio.h>

#include "sensor_component.h"

void app_main(void)
{
    sensor_init();

    sensor_task();
}