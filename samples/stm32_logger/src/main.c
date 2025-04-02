/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Author: Sudarshan Jagannathan
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>


/* By setting severity level as LOG_LEVEL_DBG during registration, we ensure that all the log messages will be printed. The hierarchy of severity levels is - DBG, INF, WRN, ERR. */

LOG_MODULE_REGISTER(hello_world_logger, LOG_LEVEL_DBG);  /* TO-DO: Change the severity level to a higher one and observe the change in the output. */

int data[] = {3, 3, 3, 4, 5, 6, 7, 
			  4, 5, 6, 7, 8, 9, 10};	/* Dummy data for Hexdump. */



int main(void)
{	

	while(1)
	{
		/* Note the way these messages are printed and note the change when the minimum severity level is changed! */
		LOG_INF("Hello world\n");  
		LOG_DBG("Hello world\n");
		LOG_WRN("Hello world\n");
		LOG_ERR("Hello world\n");

		/* TODO: Hexdump for other severity levels. */
		LOG_HEXDUMP_INF(data, sizeof(data), "Samples\n");	/* Hexdump of the data buffer. */
		k_msleep(1000);
		
	}

	return 0;
}

