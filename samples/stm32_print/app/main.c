/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Author: Sudarshan Jagannathan
 */


#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>


int main(void)
{

    printk("Hello from STM32\n");
    return 0;
}