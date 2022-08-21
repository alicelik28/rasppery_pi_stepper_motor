/*
 * stepper_motor.h
 *
 *  Created on: Aug 14, 2022
 *      Author: Ali Celik
 */

#ifndef INC_STEPPER_MOTOR_H_
#define INC_STEPPER_MOTOR_H_

#include "stdint.h"
#include <unistd.h>

enum select_motor_steps
{
	select_motor_cahannel_1,   // full step position
	select_motor_cahannel_1_2, // half step position
	select_motor_cahannel_2,   // full step position
	select_motor_cahannel_2_3, // half step position
	select_motor_cahannel_3,   // full step position
	select_motor_cahannel_3_4, // half step position
	select_motor_cahannel_4,   // full step position
	select_motor_cahannel_4_1, // half step position
};

typedef struct stepper_
{
	uint8_t channel_1;
	uint8_t channel_2;
	uint8_t channel_3;
	uint8_t channel_4;
	uint8_t step_status;
	int (*init)(struct stepper_ *);
	void (*full_step_clockwise)(struct stepper_ *);
	void (*full_step_counterclockwise)(struct stepper_ *);
	void (*half_step_clockwise)(struct stepper_ *);
	void (*half_step_counterclockwise)(struct stepper_ *);
	void (*clear_all_channels)(struct stepper_ *);
} stepper_motor_t;

void stepper_full_step_clockwise(stepper_motor_t *inst);
void stepper_full_step_counterclockwise(stepper_motor_t *inst);
void stepper_half_step_clockwise(stepper_motor_t *inst);
void stepper_half_step_counterclockwise(stepper_motor_t *inst);

int stepper_init(stepper_motor_t *self);
void stepper_clear_all_channels(stepper_motor_t *self);

#endif /* INC_STEPPER_MOTOR_H_ */
