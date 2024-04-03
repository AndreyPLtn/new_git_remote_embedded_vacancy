#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#pragma warning(suppress : 4996)

enum BUTTONS {
    OK_BUTTON,
    CANCEL_BUTTON,
    PREV_BUTTON,
    NEXT_BUTTON
};

static volatile char pin_no[4] = { 0, 1, 2, 3 };

void gpio_IRQ(uint8_t pin_no) {
    bool button_clicks;
    if (pin_no == OK_BUTTON) {
        gpio_check((0 << OK_BUTTON), &button_clicks);
    if (pin_no == CANCEL_BUTTON)
        gpio_check((1 << CANCEL_BUTTON), &button_clicks);
    if (pin_no == PREV_BUTTON)
        gpio_check((2 << PREV_BUTTON),&button_clicks);
    if (pin_no == NEXT_BUTTON)
        gpio_check((3 << NEXT_BUTTON),&button_clicks);
    }
}
void buttons_process_task(int button_no)
{
    printf("Pressed: %c\n", pin_no[button_no]);

    if (OK_BUTTON == 0)
        printf("Pressed: %s\n", pin_no[0]);
    else if (CANCEL_BUTTON == 1)
        printf("Pressed: %s\n", pin_no[1]);
    else if (PREV_BUTTON == 2)
        printf("Pressed: %s\n", pin_no[2]);
    else if (NEXT_BUTTON == 3)
        printf("Pressed: %s\n", pin_no[3]);
}

void start_buttons_processing(void* arg) {
    xTaskCreate(buttons_process_task, "buttons_task", 1024, NULL, 1, NULL);
        
    char button_no;
        if (button_no & (OK_BUTTON << 0))
            printf("OK_BUTTON Pressed\n");
        if (button_no & (CANCEL_BUTTON << 1))
            printf("CANCEL_BUTTON Pressed\n");
        if (button_no & (PREV_BUTTON << 2))
            printf("PREV_BUTTON Pressed\n");
        if (button_no & (NEXT_BUTTON << 3))
            printf("NEXT_BUTTON Pressed\n");
        else
            printf("Incorrect\n");
        
        enableGPIO_IRQ();
}

int main() {
    int buttons_pressed = OK_BUTTON | CANCEL_BUTTON | PREV_BUTTON | PREV_BUTTON;
    button_clicks(buttons_pressed);


    return 0;
}