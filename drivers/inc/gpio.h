/*
 * gpio.h
 *
 *  Created on: Aug 11, 2022
 *      Author: Ali Celik
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stdint.h"
#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "fcntl.h"
#include "errno.h"

#define GPIO_INPUT			0
#define GPIO_OUTPUT 		1
#define GPIO_HIGH			1
#define GPIO_LOW			0
#define GPIO_RISING_EDGE 	"rising"
#define GPIO_FALLING_EDGE 	"falling"

int gpio_export(uint16_t gpio_num);
int gpio_set_config(uint16_t gpio_num, uint8_t value);
int gpio_write_value(uint16_t gpio_num, uint8_t value);
int gpio_read_value(uint16_t gpio_num);
int gpio_configure_edge(uint16_t gpio_num, char *edge);

#endif /* INC_GPIO_H_ */
