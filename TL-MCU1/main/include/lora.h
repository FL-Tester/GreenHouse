#pragma once 


#define LORA_UART_NUM   UART_NUM_1
#define BUF_SIZE        (1024)
#define RD_BUF_SIZE     (BUF_SIZE)
#define lora_buf_size   (10)

void lora_init(void);
void lora_task(void *pvParameters);