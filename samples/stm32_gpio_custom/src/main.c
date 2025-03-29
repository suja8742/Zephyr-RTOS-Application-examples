/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

 #include <stdio.h>
 #include <zephyr/drivers/gpio.h>
 #include <zephyr/sys/printk.h>
 #include <zephyr/kernel.h>
 
 /* 1000 msec = 1 sec */
 #define SLEEP_TIME_MS   (1000 * 60 * 100)
 
 #define LED0_NODE DT_ALIAS(led0)
 #define BUTTON_NODE DT_ALIAS(sw0)
 
 static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
 static const struct gpio_dt_spec sw_bt = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);
 
 static struct gpio_callback button_cb_data;
 
 void button_pressed(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
 {
     gpio_pin_toggle_dt(&led);
 }
 
 int main(void)
 {
 
     int ret = 0;
 
     if (!gpio_is_ready_dt(&led)) {
         printk("LED not ready - %d\n", ret);
         return 0;
     }
 
     if (!gpio_is_ready_dt(&sw_bt)) {
         printk("Switch not ready - %d\n", ret);
         return 0;
     }
 
     
     ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
     if (ret != 0) {
         printk("LED not configured to output - %d\n", ret);
         return 0;
     }
 
     ret = gpio_pin_configure_dt(&sw_bt, GPIO_INPUT);
     if (ret != 0) {
         printk("Switch not configured to input - %d\n", ret);
         return 0;
     }
 
     ret = gpio_pin_interrupt_configure_dt(&sw_bt, GPIO_INT_EDGE_RISING);
     if(ret != 0) {
         printk("Switch interrupt not configured - %d\n", ret);
         return 0;
     }
 
     gpio_init_callback(&button_cb_data, button_pressed, BIT(sw_bt.pin));
     
     ret = gpio_add_callback(sw_bt.port, &button_cb_data);
     if(ret != 0) {
         printk("Switch interrupt callback not added - %d\n", ret);
         return 0;
     }
 
     while(1)
     {
         k_msleep(SLEEP_TIME_MS);
     }
 
     return 0;
 }
 