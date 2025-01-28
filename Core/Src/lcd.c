#include "lcd.h"
#include "stdlib.h"
#include "spi.h"
//#include "dma.h"
#include "u8g2.h"
 
 
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_BYTE_SEND: /*??SPI??arg_int?????*/
//          HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)arg_ptr, arg_int);while(hspi1.TxXferCount);
			//??DMA??????????,?????DMA?????
			HAL_SPI_Transmit(&hspi2,(uint8_t *)arg_ptr,arg_int,200);
            break;
        case U8X8_MSG_BYTE_INIT: /*?????*/
            break;
        case U8X8_MSG_BYTE_SET_DC: /*??DC??,????????????*/
			HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,arg_int);
            break;
        case U8X8_MSG_BYTE_START_TRANSFER: 
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_enable_level);
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->post_chip_enable_wait_ns, NULL);
            break;
        case U8X8_MSG_BYTE_END_TRANSFER: 
            u8x8->gpio_and_delay_cb(u8x8, U8X8_MSG_DELAY_NANO, u8x8->display_info->pre_chip_disable_wait_ns, NULL);
            u8x8_gpio_SetCS(u8x8, u8x8->display_info->chip_disable_level);
            break;
        default:
            return 0;
    }
    return 1;
}
 
uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,
    U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int,
    U8X8_UNUSED void *arg_ptr) 
{
    switch (msg)
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT: /*delay?GPIO????,?main?????????*/
            break;
        case U8X8_MSG_DELAY_MILLI: /*????*/
            HAL_Delay(arg_int);     //???stm32??????
            break;
        case U8X8_MSG_GPIO_CS: /*????*/ //??????SPI??,????????????????????
            HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, arg_int);
            break;
        case U8X8_MSG_GPIO_DC: /*??DC??,????????????*/
            HAL_GPIO_WritePin(LCD_DC_GPIO_Port,LCD_DC_Pin,arg_int);
            break;
        case U8X8_MSG_GPIO_RESET:
            break;
    }
    return 1;
}
 
 
void u8g2Init(u8g2_t *u8g2)
{
	MD_OLED_RST_Set(); //???????
	//u8g2_Setup_ssd1306_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi,u8x8_stm32_gpio_and_delay);  // ???0.96?OLED u8g2 ???
	u8g2_Setup_st7565_lx12864_f(u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi,u8x8_stm32_gpio_and_delay);  // ???0.96?OLED u8g2 ???
	//u8g2_Setup_uc1601_128x64_f(u8g2, U8G2_R1, u8x8_byte_4wire_hw_spi,u8x8_stm32_gpio_and_delay);  // ???0.96?OLED u8g2 ???
	
	u8g2_InitDisplay(u8g2);     //?????
	u8g2_SetPowerSave(u8g2, 0); //????
}

