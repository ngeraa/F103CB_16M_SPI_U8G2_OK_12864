#ifndef __OLED_H
#define __OLED_H
 
#include "stdlib.h"	  
#include "main.h"
#include "gpio.h"
#include "u8g2.h"
   
 
//---------------OLED????--------------//  					   
#define MD_OLED_RST_Clr() HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_RESET) //oled ??????
#define MD_OLED_RST_Set() HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,GPIO_PIN_SET)
 
//OLED?????
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr);
uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,U8X8_UNUSED void *arg_ptr) ;
void u8g2Init(u8g2_t *u8g2);
 
#endif  
