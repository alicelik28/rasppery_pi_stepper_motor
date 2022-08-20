/*
 * stepper_motor.c
 *
 *  Created on: Aug 14, 2022
 *      Author: Ali Celik
 */

#include "stepper_motor.h"
#include "gpio.h"

static volatile uint8_t step_status = select_motor_cahannel_1;

int stepper_init(stepper_motor_t *inst)
{
	int fd=0;
	fd=gpio_export(inst->channel_1);
	fd=gpio_export(inst->channel_2);
	fd=gpio_export(inst->channel_3);
	fd=gpio_export(inst->channel_4);

	fd=gpio_set_config(inst->channel_1, GPIO_OUTPUT);
	fd=gpio_set_config(inst->channel_2, GPIO_OUTPUT);
	fd=gpio_set_config(inst->channel_3, GPIO_OUTPUT);
	fd=gpio_set_config(inst->channel_4, GPIO_OUTPUT);

	fd=gpio_write_value(inst->channel_1, GPIO_LOW);
	fd=gpio_write_value(inst->channel_2, GPIO_LOW);
	fd=gpio_write_value(inst->channel_3, GPIO_LOW);
	fd=gpio_write_value(inst->channel_4, GPIO_LOW);

	return fd;
}

void stepper_clear_all_channels(stepper_motor_t *inst)
{
	gpio_write_value(inst->channel_1, GPIO_LOW);
	gpio_write_value(inst->channel_2, GPIO_LOW);
	gpio_write_value(inst->channel_3, GPIO_LOW);
	gpio_write_value(inst->channel_4, GPIO_LOW);
}


/*
 * full step clockwise
 *
 * stepper_ch1 | stepper_ch2 | stepper_ch_3 | stepper_ch_4
 * 		1				0			0				0
 * 		0				1			0				0
 * 		0				0			1				0
 * 		0				0			0				1
 *
 * The steps move from the current location to the next location.
 * The steps continue as follows ch1->ch2->ch3->ch4->ch1->ch2...
 */
void stepper_full_step_clockwise(stepper_motor_t *inst)
{
	switch(step_status)
	{
	case select_motor_cahannel_1:
		gpio_write_value(inst->channel_1, GPIO_LOW);
		gpio_write_value(inst->channel_2, GPIO_HIGH);
		step_status = select_motor_cahannel_2;
		break;
	case select_motor_cahannel_2:
		gpio_write_value(inst->channel_2, GPIO_LOW);
		gpio_write_value(inst->channel_3, GPIO_HIGH);
		step_status = select_motor_cahannel_3;
		break;
	case select_motor_cahannel_3:
		gpio_write_value(inst->channel_3, GPIO_LOW);
		gpio_write_value(inst->channel_4, GPIO_HIGH);
		step_status = select_motor_cahannel_4;
		break;
	case select_motor_cahannel_4:
		gpio_write_value(inst->channel_4, GPIO_LOW);
		gpio_write_value(inst->channel_1, GPIO_HIGH);
		step_status = select_motor_cahannel_1;
		break;
	}
}



/*
 * full step counterclockwise
 *
 * stepper_ch1 | stepper_ch2 | stepper_ch_3 | stepper_ch_4
 * 		1				0			0				0
 * 		0				0			0				1
 * 		0				0			1				0
 * 		0				1			0				0
 *
 * The steps move from the current location to the next location.
 * The steps continue as follows ch1->ch4->ch3->ch2->ch1->ch4...
 */
void stepper_full_step_counterclockwise(stepper_motor_t *inst)
{
	switch(step_status)
	{
	case select_motor_cahannel_1:
		gpio_write_value(inst->channel_1, GPIO_LOW);
		gpio_write_value(inst->channel_4, GPIO_HIGH);
		step_status = select_motor_cahannel_4;
		break;
	case select_motor_cahannel_4:
		gpio_write_value(inst->channel_4, GPIO_LOW);
		gpio_write_value(inst->channel_3, GPIO_HIGH);
		step_status = select_motor_cahannel_3;
		break;
	case select_motor_cahannel_3:
		gpio_write_value(inst->channel_3, GPIO_LOW);
		gpio_write_value(inst->channel_2, GPIO_HIGH);
		step_status = select_motor_cahannel_2;
		break;
	case select_motor_cahannel_2:
		gpio_write_value(inst->channel_2, GPIO_LOW);
		gpio_write_value(inst->channel_1, GPIO_HIGH);
		step_status = select_motor_cahannel_1;
		break;

	}
}

/*
 * half step clockwise
 *
* stepper_ch1 | stepper_ch2 | stepper_ch_3 | stepper_ch_4
* 		1				0			0				0
* 		1				1			0				0
* 		0				1			0				0
* 		0				1			1				0
* 		0				0			1				0
* 		0				0			1				1
* 		0				0			0				1
* 		1				0			0				1
*/
void stepper_half_step_clockwise(stepper_motor_t *inst)
{
	switch(step_status)
	{
	case select_motor_cahannel_1:
		gpio_write_value(inst->channel_2, GPIO_HIGH);
		step_status = select_motor_cahannel_1_2;
		break;
	case select_motor_cahannel_1_2:
		gpio_write_value(inst->channel_1, GPIO_LOW);
		step_status = select_motor_cahannel_2;
		break;
	case select_motor_cahannel_2:
		gpio_write_value(inst->channel_3, GPIO_HIGH);
		step_status = select_motor_cahannel_2_3;
		break;
	case select_motor_cahannel_2_3:
		gpio_write_value(inst->channel_2, GPIO_LOW);
		step_status = select_motor_cahannel_3;
		break;
	case select_motor_cahannel_3:
		gpio_write_value(inst->channel_4, GPIO_HIGH);
		step_status = select_motor_cahannel_3_4;
		break;
	case select_motor_cahannel_3_4:
		gpio_write_value(inst->channel_3, GPIO_LOW);
		step_status = select_motor_cahannel_4;
		break;
	case select_motor_cahannel_4:
		gpio_write_value(inst->channel_1, GPIO_HIGH);
		step_status = select_motor_cahannel_4_1;
		break;
	case select_motor_cahannel_4_1:
		gpio_write_value(inst->channel_4, GPIO_LOW);
		step_status = select_motor_cahannel_1;
		break;
	}
}


/*
 * half step clockwise
 *
* stepper_ch1 | stepper_ch2 | stepper_ch_3 | stepper_ch_4
* 		1				0			0				0
* 		1				0			0				1
* 		0				0			0				1
* 		0				0			1				1
* 		0				0			1				0
* 		0				1			1				0
* 		0				1			0				0
* 		1				1			0				0
*/
void stepper_half_step_counterclockwise(stepper_motor_t *inst)
{
	switch(step_status)
	{
	case select_motor_cahannel_1:
		gpio_write_value(inst->channel_4, GPIO_HIGH);
		step_status = select_motor_cahannel_4_1;
		break;
	case select_motor_cahannel_4_1:
		gpio_write_value(inst->channel_1, GPIO_LOW);
		step_status = select_motor_cahannel_4;
		break;
	case select_motor_cahannel_4:
		gpio_write_value(inst->channel_3, GPIO_HIGH);
		step_status = select_motor_cahannel_3_4;
		break;
	case select_motor_cahannel_3_4:
		gpio_write_value(inst->channel_4, GPIO_LOW);
		step_status = select_motor_cahannel_3;
		break;
	case select_motor_cahannel_3:
		gpio_write_value(inst->channel_2, GPIO_HIGH);
		step_status = select_motor_cahannel_2_3;
		break;
	case select_motor_cahannel_2_3:
		gpio_write_value(inst->channel_3, GPIO_LOW);
		step_status = select_motor_cahannel_2;
		break;
	case select_motor_cahannel_2:
		gpio_write_value(inst->channel_1, GPIO_HIGH);
		step_status = select_motor_cahannel_1_2;
		break;
	case select_motor_cahannel_1_2:
		gpio_write_value(inst->channel_2, GPIO_LOW);
		step_status = select_motor_cahannel_1;
		break;
	}
}
