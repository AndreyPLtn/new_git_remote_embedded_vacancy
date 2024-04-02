#ifndef __MODULE_H__
#define __MODULE_H__

#include <stdint.h>
//Этот фрагмент кода является заголовочным файлом для модуля, который предоставляет функции для работы с сообщениями.
// Функции message_create и message_free_s используются для создания и удаления сообщений соответственно.
// Тип message_p_count_t используется для указания количества элементов в сообщении.

#ifdef __cplusplus
extern "C" {
#endif

struct Message;
typedef struct Message* Message; 

typedef uint8_t message_p_count_t;

Message message_create(message_p_count_t payloads_count);

void message_free_s(Message* message);
#define message_free(m) message_free_s(&(m)) 

#ifdef __cplusplus
}
#endif

#endif