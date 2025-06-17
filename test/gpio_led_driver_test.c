/**
 * @file gpio_led_driver_test.c 
 * @brief Test for gpio led driver, kernel driver
 * @author Leandro Zapata Marin
 */

// gpio_led_driver_test.c
// Unit test for the custom GPIO LED character device driver

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define DEVICE_PATH "/dev/gpioled"

// Helper function to test writing a value to the device
void test_write(int fd, const char *value) {
    printf("[TEST] Writing '%s' to the device...\n", value);
    if (write(fd, value, strlen(value)) < 0) {
        // Print error if the write fails
        perror("Error writing to device");
    } else {
        printf("✔️ Write operation successful\n");
    }
}

// Helper function to test reading the current value from the device
void test_read(int fd) {
    char buf[4] = {0};  // Buffer to store the read value

    // Reset file offset before reading
    lseek(fd, 0, SEEK_SET);

    // Attempt to read from the device
    ssize_t n = read(fd, buf, sizeof(buf));
    if (n < 0) {
        perror("Error reading from device");
    } else {
        printf("📥 Value read from device: '%s'\n", buf);
    }
}

int main() {
    // Open the device file for read and write operations
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        perror("❌ Failed to open the device");
        return 1;
    }

    printf("✅ Device opened successfully\n");

    // Test: Turn on the LED
    test_write(fd, "1");
    test_read(fd);

    // Test: Turn off the LED
    test_write(fd, "0");
    test_read(fd);

    // Test: Send an invalid command
    test_write(fd, "x");
    test_read(fd);

    // Close the device
    close(fd);
    return 0;
}
