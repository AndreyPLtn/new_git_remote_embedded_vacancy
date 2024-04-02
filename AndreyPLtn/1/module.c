/**
 * @file module.c
 * @author Dmitrii Fedin
 * @brief Абстрактный модуль для тестов
 * @version 0.1
 * @date 2022-01-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "module.h"
#include <stdlib.h>


#define PAYLOAD_DATA_LEN (50) //макрос со значением переменной 50 (например размер массива или структуры)

struct Payload {
    uint8_t data[PAYLOAD_DATA_LEN];
};
typedef struct Payload* Payload;
//Определяется структура данных Payload, которая содержит массив uint8_t длиной PAYLOAD_DATA_LEN.
// Затем создается указатель на эту структуру и ему присваивается имя Payload.


struct Message {
    uint32_t id;
    struct {
        message_p_count_t count;
        Payload elements;
    } payloads;
};
// После этого определяется структура Message, которая содержит поле id типа uint32_t и вложенную структуру payloads,
// которая, в свою очередь, содержит поля count(message_p_count_t) и elements(Payload).


Message message_create(message_p_count_t payloads_count) {
    if (payloads_count == 0) {
        return NULL;
    }
    Message ptr = (Message)calloc(1, sizeof(struct Message), 1);
    if (ptr == NULL) {
        return NULL;
    }
    ptr->payloads.elements = (Payload)calloc(payloads_count, sizeof(struct Payload)); // заменил -> на '.'; добавил struct
    if ((ptr->payloads.elements) == NULL) { // заменил -> на '.'
        free(ptr);
        return NULL;
    }
    ptr->payloads.count = payloads_count; //заменил elements на paylods; заменил -> на '.'
    return ptr;
}
//Эта функция создает структуру Message и выделяет для нее память.
// Если количество элементов payloads равно нулю, функция возвращает NULL.
// Если создать структуру не удалось, функция также возвращает NULL. 
// В противном случае функция устанавливает количество элементов payloads, 
// равным payloads_count и возвращает указатель на созданную структуру.


void message_free_s(Message* message) {
    if (message == NULL) {
        return;
    }
    Message ptr = *message;
    if (ptr == NULL) {
        return;
    }
    if ((ptr->payloads.elements) != NULL) {//заменил elements на paylods; заменил -> на '.'
        free(ptr->payloads.elements); //заменил elements на paylods; заменил -> на '.'
        ptr->payloads.elements = NULL;//заменил elements на paylods; заменил -> на '.'
    }
    free(ptr);
    *message = NULL;
}
//ptr->elements->elements заменить на ptr->payloads.elements (сработало)
//Эта функция освобождает память, выделенную для структуры Message.
// Если указатель message не равен NULL, функция создает копию указателя ptr и присваивает ее значение *message.
// Затем функция проверяет, является ли ptr нулевым указателем, и если да, то возвращает управление.
// Если ptr указывает на структуру Payload, функция освобождает выделенную для нее память и устанавливает указатель на NULL.
// Затем функция освобождает память, выделенную для ptr, и устанавливает значение *message в NULL.