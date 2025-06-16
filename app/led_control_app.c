/**
 * @file led_control_app.c
 * @brief Code for final‐user application to control the GPIO LED via /dev/gpioled.
 * @author David Ramírez Betancourth
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define DEVICE_PATH  "/dev/gpioled"

static void usage(const char *prog)
{
    fprintf(stderr,
        "Usage: %s <on|off|status>\n"
        "  on      Turn LED on\n"
        "  off     Turn LED off\n"
        "  status  Show current LED state\n",
        prog);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    int fd;
    char buf[2] = {0};

    if (argc != 2)
        usage(argv[0]);

    if (strcmp(argv[1], "on") == 0)
        buf[0] = '1';
    else if (strcmp(argv[1], "off") == 0)
        buf[0] = '0';
    else if (strcmp(argv[1], "status") == 0) {
        fd = open(DEVICE_PATH, O_RDONLY);
        if (fd < 0) {
            perror("open");
            return EXIT_FAILURE;
        }
        if (read(fd, buf, 2) < 0) {
            perror("read");
            close(fd);
            return EXIT_FAILURE;
        }
        close(fd);
        printf("LED is %s\n", (buf[0] == '1') ? "ON" : "OFF");
        return EXIT_SUCCESS;
    } else {
        usage(argv[0]);
    }

    /* for on/off commands: open write-only and send control byte */
    fd = open(DEVICE_PATH, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }
    if (write(fd, buf, 1) < 0) {
        perror("write");
        close(fd);
        return EXIT_FAILURE;
    }
    close(fd);

    printf("LED turned %s\n", (buf[0] == '1') ? "ON" : "OFF");
    return EXIT_SUCCESS;
}
