#include "lora.h"
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "config.h"

uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
};

extern uint8_t*         recv_data;
extern TaskHandle_t     data_process_task_handle;
static QueueHandle_t    uart0_queue;   //串口队列

void lora_init(void){
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    //Install UART driver, and get the queue.   
    uart_driver_install(LORA_UART_NUM, BUF_SIZE * 2, 2 * BUF_SIZE, 20, &uart0_queue, 0); 
    uart_param_config(LORA_UART_NUM, &uart_config);
    uart_set_pin(LORA_UART_NUM, LORA_TX_PIN, LORA_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    //Set uart pattern detect function.
    uart_enable_pattern_det_baud_intr(LORA_UART_NUM, '+', 4, 9, 0, 0);
    //Reset the pattern queue length to record at most 20 pattern positions.
    uart_pattern_queue_reset(LORA_UART_NUM, 20);
};

//数据读取任务 读取lora数据
void lora_task(void *pvParameter){  
    uart_event_t event;
    uint8_t* dtmp = (uint8_t*) malloc(lora_buf_size);
    while(1) {
        if(xQueueReceive(uart0_queue, (void * )&event, (portTickType)portMAX_DELAY)) { 
            bzero(dtmp, lora_buf_size);
            switch(event.type) {
                case UART_DATA: 
                    uart_read_bytes(LORA_UART_NUM, dtmp, RECV_SIZE, portMAX_DELAY);
                    //printf ("data:%s\n data_size:%d\n",  dtmp, event.size);                  
                    recv_data = dtmp;
                    break;
                default:
                    break;
            }
            xTaskNotify (data_process_task_handle, 0x00, eNoAction);
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}