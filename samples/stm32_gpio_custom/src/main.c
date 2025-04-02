/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Author: Sudarshan Jagannathan
 */

 #include <stdio.h>
 #include <zephyr/drivers/gpio.h>
 #include <zephyr/sys/printk.h>
 #include <zephyr/kernel.h>
 
 /* 1000 msec = 1 sec */
 #define SLEEP_TIME_MS   (1000 * 60 * 100) 
 
 #define LED0_NODE DT_ALIAS(led0)       /* DT_ALIAS - https://docs.zephyrproject.org/latest/doxygen/html/group__devicetree-generic-id.html#gaa49e19bbc39dc0d6f16b78a5d02482c9 */
 #define BUTTON_NODE DT_ALIAS(sw0)      
 
 static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);   /* gpio_dt_spec structure is populated with all the device information for LED0 and the Button. This is done using the GPIO_DT_SPEC_GET() macro.  */
 static const struct gpio_dt_spec sw_bt = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);
 
 static struct gpio_callback button_cb_data;    /* For hardware interrupts, a callback function is mandatory. It is of type static struct to match the template provided in GPIO API documentation. */
 

 /* Simple function that performs what the callback does when an interrupt is received. In this case, an LED is toggled when a button interrupt is recieved. */

 void button_pressed(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins)
 {
     gpio_pin_toggle_dt(&led);              
 }
 
 int main(void)
 {
 
     int ret = 0;
    /* STEP 1 in registering a hardware module - Always check if the device is ready. */   
     if (!gpio_is_ready_dt(&led)) {
         printk("LED not ready - %d\n", ret);
         return 0;
     }
 
     if (!gpio_is_ready_dt(&sw_bt)) {
         printk("Switch not ready - %d\n", ret);
         return 0;
     }
 
     /* STEP 2 - Manage the pin controller configuration. */

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
     /* Configure an interrupt on a pin once you have configured the pin as input, and added other relevant config flags. */

     ret = gpio_pin_interrupt_configure_dt(&sw_bt, GPIO_INT_EDGE_RISING);
     if(ret != 0) {
         printk("Switch interrupt not configured - %d\n", ret);
         return 0;
     }
     
     /* For all hardware modules that you configure an interrupt for, a callback function must be initialized and added. Note the parameters accepted by these function calls on the GPIO docs. */
     gpio_init_callback(&button_cb_data, button_pressed, BIT(sw_bt.pin));
     
     ret = gpio_add_callback(sw_bt.port, &button_cb_data);
     if(ret != 0) {
         printk("Switch interrupt callback not added - %d\n", ret);     /* A good use of printk() - Since the program is simply asked to exit on failure, printk() provide a sufficient level of sophistication here. */
         return 0;
     }
 
     while(1)
     {
         k_msleep(SLEEP_TIME_MS);
     }
 
     return 0;
 }
 