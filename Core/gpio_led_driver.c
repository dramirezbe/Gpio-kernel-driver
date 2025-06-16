/**
 * @file gpio_led_driver.c
 * @brief Code of kernel‐type driver, that uses maximum privileges to read & write
 *        a GPIO pin to drive an LED via a character device.
 * @author David Ramírez Betancourth
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/uaccess.h>

#define DRIVER_NAME    "gpio_led"
#define DEVICE_NAME    "gpioled"
#define GPIO_LED_PIN   17     /* adjust to the physical pin you wired your LED to */

static dev_t         dev_num;
static struct cdev   gpio_cdev;
static struct class *gpio_class;
static int           led_state = 0;

/* File operations prototypes */
static int     gpio_open(struct inode *inode, struct file *filp);
static int     gpio_release(struct inode *inode, struct file *filp);
static ssize_t gpio_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);
static ssize_t gpio_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos);

/* File operations structure */
static const struct file_operations gpio_fops = {
    .owner   = THIS_MODULE,
    .open    = gpio_open,
    .release = gpio_release,
    .read    = gpio_read,
    .write   = gpio_write,
};

static int __init gpio_init(void)
{
    int ret;

    /* Allocate character device numbers */
    ret = alloc_chrdev_region(&dev_num, 0, 1, DRIVER_NAME);
    if (ret) {
        pr_err("Failed to alloc chrdev region\n");
        return ret;
    }

    /* Initialize and add cdev */
    cdev_init(&gpio_cdev, &gpio_fops);
    gpio_cdev.owner = THIS_MODULE;
    ret = cdev_add(&gpio_cdev, dev_num, 1);
    if (ret) {
        pr_err("Failed to add cdev\n");
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }

    /* Create device class and device node in /dev */
    gpio_class = class_create(THIS_MODULE, DRIVER_NAME);
    if (IS_ERR(gpio_class)) {
        pr_err("Failed to create class\n");
        cdev_del(&gpio_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(gpio_class);
    }
    device_create(gpio_class, NULL, dev_num, NULL, DEVICE_NAME);

    /* Request and configure GPIO */
    ret = gpio_request(GPIO_LED_PIN, "LED_GPIO");
    if (ret) {
        pr_err("Failed to request GPIO %d\n", GPIO_LED_PIN);
        device_destroy(gpio_class, dev_num);
        class_destroy(gpio_class);
        cdev_del(&gpio_cdev);
        unregister_chrdev_region(dev_num, 1);
        return ret;
    }
    gpio_direction_output(GPIO_LED_PIN, led_state);

    pr_info("gpio_led_driver loaded (dev=%d:%d, GPIO=%d)\n",
            MAJOR(dev_num), MINOR(dev_num), GPIO_LED_PIN);
    return 0;
}

static void __exit gpio_exit(void)
{
    /* Turn LED off, free GPIO, remove devices */
    gpio_set_value(GPIO_LED_PIN, 0);
    gpio_free(GPIO_LED_PIN);

    device_destroy(gpio_class, dev_num);
    class_destroy(gpio_class);
    cdev_del(&gpio_cdev);
    unregister_chrdev_region(dev_num, 1);

    pr_info("gpio_led_driver unloaded\n");
}

static int gpio_open(struct inode *inode, struct file *filp)
{
    return 0;
}

static int gpio_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static ssize_t gpio_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
    char kbuf[2];
    int len;

    kbuf[0] = led_state ? '1' : '0';
    kbuf[1] = '\n';
    len = 2;

    if (*f_pos >= len)
        return 0;
    if (count > len - *f_pos)
        count = len - *f_pos;
    if (copy_to_user(buf, kbuf + *f_pos, count))
        return -EFAULT;
    *f_pos += count;
    return count;
}

static ssize_t gpio_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
    char kbuf[2] = {0};

    if (count < 1 || count > sizeof(kbuf))
        return -EINVAL;
    if (copy_from_user(kbuf, buf, 1))
        return -EFAULT;

    if (kbuf[0] == '1')
        led_state = 1;
    else if (kbuf[0] == '0')
        led_state = 0;
    else
        return -EINVAL;

    gpio_set_value(GPIO_LED_PIN, led_state);
    return 1;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Ramírez Betancourth");
MODULE_DESCRIPTION("Simple GPIO LED character driver");
MODULE_VERSION("1.0");

module_init(gpio_init);
module_exit(gpio_exit);
