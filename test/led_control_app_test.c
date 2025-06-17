/**
 * @file led_control_app_test.c 
 * @brief Test for led control app
 * @author Leandro Zapata Marin
 */

// led_control_app_test.c
// Test suite for the user-space application that controls the GPIO LED

#include <stdio.h>
#include <stdlib.h>

// Helper function to run a shell command and print its result
void run_command(const char *desc, const char *cmd) {
    printf("[TEST] %s: `%s`\n", desc, cmd);
    int result = system(cmd);  // Execute the command
    if (result != 0) {
        printf("❌ Command failed: %s\n\n", cmd);
    } else {
        printf("✔️ Command executed successfully\n\n");
    }
}

int main() {
    printf("===== Starting tests for led_control_app =====\n\n");

    // Test: Turn on the LED
    run_command("Turn ON the LED", "./led_control_app on");

    // Test: Check status (expected to be ON)
    run_command("Check status (should be ON)", "./led_control_app status");

    // Test: Turn off the LED
    run_command("Turn OFF the LED", "./led_control_app off");

    // Test: Check status (expected to be OFF)
    run_command("Check status (should be OFF)", "./led_control_app status");

    // Test: Provide an invalid argument
    run_command("Test with invalid argument", "./led_control_app foo");

    printf("===== Test suite completed =====\n");
    return 0;
}
