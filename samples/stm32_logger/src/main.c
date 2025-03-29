/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>



LOG_MODULE_REGISTER(hello_world_logger, LOG_LEVEL_DBG);

int data[] = {3, 3, 3, 4, 5, 6, 7, 
			  4, 5, 6, 7, 8, 9, 10};



int main(void)
{	

	while(1)
	{
		LOG_INF("Hello world\n");
		LOG_DBG("Hello world\n");
		LOG_WRN("Hello world\n");
		LOG_ERR("Hello world\n");
		LOG_HEXDUMP_INF(data, sizeof(data), "Samples\n");
		k_msleep(1000);
		
	}

	return 0;
}

