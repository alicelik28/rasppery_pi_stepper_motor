/*
 * gpio.c
 *
 *  Created on: Aug 11, 2022
 *      Author: Ali Celik
 */

#include "gpio.h"

#define SYS_GPIO_PATH "/sys/class/gpio"
#define BUFFER_SIZE 100

int gpio_export(uint16_t gpio_num)
{
	int fd, num;
	char buf[BUFFER_SIZE];

	fd = open(SYS_GPIO_PATH "/export", O_WRONLY);
	if( fd < 0)
	{
		perror("Error opening gpio export file\n");
	}

	num = snprintf(buf, sizeof(buf), "%d", gpio_num);
	write(fd, buf, num);
	close(fd);

	return 0;
}

int gpio_set_config(uint16_t gpio_num, uint8_t value)
{
	int fd;
	char buf[BUFFER_SIZE];

	snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/direction", gpio_num);

	fd=open(buf, O_WRONLY);
	if( fd < 0 )
	{
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "Error set config gpio%d\n", gpio_num);
		perror(buf);

		return fd;
	}

	if(value == GPIO_OUTPUT)
	{
		write(fd, "out", 4);
	}
	else{
		write(fd, "in", 3);
	}

	close(fd);

	return 0;
}

int gpio_write_value(uint16_t gpio_num, uint8_t value)
{
	int fd;
	char buf[BUFFER_SIZE];

	snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/value", gpio_num);

	fd=open(buf, O_WRONLY);
	if(fd < 0)
	{
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "Error writing value to gpio%d\n", gpio_num);
		perror(buf);

		return fd;
	}

	if(value == GPIO_HIGH)
	{
		write(fd, "1", 2);
	}
	else
	{
		write(fd, "0", 2);
	}

	close(fd);

	return fd;
}

int gpio_read_value(uint16_t gpio_num)
{
	int fd;
	uint8_t read_value=0;
	char buf[BUFFER_SIZE];

	snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/value", gpio_num);

	fd = open(buf, O_RDONLY);
	if(fd < 0)
	{
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "Error reading the value of gpio%d\n", gpio_num);
		perror(buf);

		return fd;
	}

	read(fd, &read_value, 1);
	close(fd);

	return read_value;
}

int gpio_configure_edge(uint16_t gpio_num, char *edge)
{
	int fd;
	char buf[BUFFER_SIZE];

	snprintf(buf, sizeof(buf), SYS_GPIO_PATH "/gpio%d/edge", gpio_num);

	fd=open(buf, O_WRONLY);
	if(fd < 0)
	{
		memset(buf, 0, sizeof(buf));
		snprintf(buf, sizeof(buf), "Edge configuration error of gpio%d\n", gpio_num);
		perror(buf);

		return fd;
	}

	write(fd, edge, sizeof(edge));
	close(fd);

	return 0;
}
