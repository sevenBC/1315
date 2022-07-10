#include <Arduino.h>
#include <iostream>
#include <driver/i2c.h>
#include <freertos/queue.h>
#include <freertos/task.h>
using namespace std;



void iic_init()
{
    const i2c_config_t i2c_cfg = 
	{
  		.mode = I2C_MODE_MASTER,
  		.sda_io_num = 23,
 		.scl_io_num = 22,
 		.sda_pullup_en = true,
 		.scl_pullup_en = true,
 		.master{.clk_speed = 100000},
 		.clk_flags = 0
	};

    i2c_param_config(I2C_NUM_0, &i2c_cfg);
    i2c_driver_install(I2C_NUM_0,I2C_MODE_MASTER,0,0,0);
}

void send(uint8_t * in_sender,int len_in)
{
	i2c_cmd_handle_t sender = i2c_cmd_link_create;
	
	i2c_master_start(sender);
	i2c_master_write(sender,in_sender,len_in,true);
	i2c_master_stop(sender);

	i2c_master_cmd_begin(I2C_NUM_0,sender,10/portTICK_PERIOD_MS);
	i2c_cmd_link_delete(sender);
}

void send_b(int in_value)
{	
	uint8_t converted = (u_int8_t) in_value;
	send(&converted, 1);
	
}

class oled
{	
	oled()
	{
		iic_init();
	};
	public:
	void init()
	{
		send_b(0xAE);
	};

	private:

};

