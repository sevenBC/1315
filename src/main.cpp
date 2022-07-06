#include <Arduino.h>
#include <iostream>
#include <driver/i2c.h>
#include <freertos/queue.h>
#include <freertos/task.h>

using namespace std;

static QueueHandle_t iic_transfer;	
static uint8_t iic_receive;	



esp_err_t iic_init()
{
	const i2c_config_t iiccfg = 
	{
  		.mode = I2C_MODE_MASTER,
  		.sda_io_num = 23,
 		.scl_io_num = 22,
 		.sda_pullup_en = true,
 		.scl_pullup_en = true,
 		.master{.clk_speed = 100000},
 		.clk_flags = 0
	};
  	esp_err_t err;
  	err = i2c_driver_install(0,I2C_MODE_MASTER,0,0,0);
 	err = i2c_param_config(0, &iiccfg);
  	return err;
}

void queue_init()
{ 
    iic_transfer = xQueueCreate(NULL,NULL);
}


void setup() {
	iic_init();
  	queue_init();

  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}