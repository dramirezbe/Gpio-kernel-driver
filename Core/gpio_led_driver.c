/**
 * @file gpio_led_driver.c
 * @brief Code of kernel-type driver, that uses maximum privileges to read & write in gpio config files
 * @author David Ramírez Betancourth
 */


#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include<linux/fs.h>