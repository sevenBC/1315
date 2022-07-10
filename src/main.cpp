#include <Arduino.h>
#include <iostream>
#include <driver/i2c.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include "render.h"
#include "oled.h"

using namespace std;

static QueueHandle_t iic_transfer;	





void queue_init()
{ 
    iic_transfer = xQueueCreate(NULL,NULL);
}


void setup() {
\

  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}