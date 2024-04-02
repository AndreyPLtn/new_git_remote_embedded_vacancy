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
//перечисление, определяющее название констант, обозначающее название кнопок

static volatile char pin_no[4] = { 0, 1, 2, 3 };
//Массив, содержащий номера пинов с подключенными кнопками. Размер 4 => 4 кнопки

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
//Обработка прерывание от GPIO. Проверяет, какая кнопка была нажата, и вызывает функцию gpio_check с соответствующим параметром. 
// Функция gpio_check проверяет уровень сигнала на соответствующем выводе и
//устанавливает переменную button_clicks в соответствии с этим уровнем.

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
//Обработка и вывод на экран соответствующей кнопки

void start_buttons_processing(void* arg) {
    xTaskCreate(buttons_process_task, "buttons_task", 1024, NULL, 1, NULL);
        // Ожидание уведомлений о нажатиях кнопок
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
//Эта функция создает задачу для обработки нажатий кнопок.
//Затем функция ожидает уведомления о нажатии кнопок и проверяет, какая кнопка была нажата.
//Для этого она использует переменную button_no.
//Если кнопка соответствует одной из заданных констант (OK_BUTTON, CANCEL_BUTTON, PREV_BUTTON или NEXT_BUTTON),
//то выводится соответствующее сообщение. В противном случае выводится сообщение “Incorrect” (Неверно).
//В конце функция enableGPIO_IRQ() активирует обработку прерываний GPIO.

int main() {

    int buttons_pressed = OK_BUTTON | CANCEL_BUTTON | PREV_BUTTON | PREV_BUTTON;
    button_clicks(buttons_pressed);


    return 0;
}
//Принимает аргумент buttons_pressed, который представляет собой битовую маску,
//и вызывает функцию button_clicks с этим аргументом.
//Функция button_clicks обрабатывает нажатия кнопок и выводит сообщения о том, какие кнопки были нажаты.