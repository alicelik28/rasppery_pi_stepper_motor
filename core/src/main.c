/*
 * main.c
 *
 *  Created on: Aug 14, 2022
 *      Author: Ali Celik
 */


#include "stdio.h"
#include "stepper_motor.h"
#include "unistd.h"
#include "gpio.h"
#include "main.h"

int main()
{
	int i=0;
	int fd=0;

	stepper_motor_t stepper_motor_1;

	printf("Step motor program\n");

	stepper_motor_1.channel_1 = MOTOR_CHANNEL_1;
	stepper_motor_1.channel_2 = MOTOR_CHANNEL_2;
	stepper_motor_1.channel_3 = MOTOR_CHANNEL_3;
	stepper_motor_1.channel_4 = MOTOR_CHANNEL_4;

	printf("Motor channels selected\n");

	stepper_motor_1.init=stepper_init;
	stepper_motor_1.clear_all_channels = stepper_clear_all_channels;
	stepper_motor_1.full_step_clockwise= stepper_full_step_clockwise;
	stepper_motor_1.full_step_counterclockwise= stepper_full_step_counterclockwise;
	stepper_motor_1.half_step_clockwise= stepper_half_step_clockwise;
	stepper_motor_1.half_step_counterclockwise = stepper_half_step_counterclockwise;

	stepper_motor_1.init(&stepper_motor_1);

	if( fd < 0) {
		perror("Stepper init error!\n");
	}
	else {
		printf("Stepper init successfully!\n");
	}

	for (i = 0; i < NUMBER_OF_STEP; i++)
	{
		stepper_motor_1.full_step_clockwise(&stepper_motor_1);
		usleep(100*1000);
		printf("Full STEP = %d\n", (i+1));
	}

	for (i = 0; i < NUMBER_OF_STEP; i++)
	{
		stepper_motor_1.full_step_counterclockwise(&stepper_motor_1);
		usleep(100 * 1000);
		printf("Full Counter STEP = %d\n", (i+1));
	}

	for (i = 0; i < NUMBER_OF_STEP; i++)
		{
			stepper_motor_1.half_step_clockwise(&stepper_motor_1);
			usleep(100 * 1000);
			printf("Half STEP = %d\n", (i+1));
		}

	for (i = 0; i < NUMBER_OF_STEP; i++)
		{
		stepper_motor_1.half_step_counterclockwise(&stepper_motor_1);
		usleep(100 * 1000);
			printf("Counter half STEP = %d\n", (i+1));
		}

	stepper_motor_1.clear_all_channels(&stepper_motor_1);

	printf("Done\n");

	return 0;
}
