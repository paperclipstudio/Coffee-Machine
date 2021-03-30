/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
//#include "BSP_DISCO_F429ZI/Drivers/BSP/STM32F429I-Discovery/stm32f429i_discovery_lcd.h"
#include "LCD_DISCO_F429ZI.h"
#include "TS_DISCO_F429ZI.h"


// Blinking rate in milliseconds
#define BLINKING_RATE     50ms

TS_StateTypeDef TS_State;
uint8_t text[30];
uint16_t x, y, buttonState;
uint8_t buttonText[30];
int main()
{
    LCD_DISCO_F429ZI lcd;
    TS_DISCO_F429ZI ts;
    // Initialise the digital pin LED1 as an output
    DigitalOut led(LED1);
    DigitalIn  button(PA_0);
    lcd.Init();
    char message[] = "Hello world";

    lcd.DisplayStringAtLine(5, (uint8_t *)"Hello World");
    //BSP_LCD_Init();
    //BSP_LCD_LayerDefaultInit(0, 0);
    //BSP_LCD_SelectLayer(0);
    //BSP_LCD_DisplayOn();
    //BSP_LCD_DrawHLine(20, 20, 200);
    ts.Init(420, 272);
    while(true) {
        ts.GetState(&TS_State);      
        if (TS_State.TouchDetected) {
            x = TS_State.X;
            y = TS_State.Y;
            lcd.DisplayStringAt(0, LINE(0), (uint8_t *)&text, LEFT_MODE);
            sprintf((char*)text, "x=%d y=%d    ", x, y);
        }
        buttonState = button.read();
        sprintf((char*)buttonText, "state: %d   ", buttonState);
        sprintf((char*)text, "touch: %d x:%d y:%d", 
            TS_State.TouchDetected,
            TS_State.X,
            TS_State.Y);
    
        lcd.DisplayStringAtLine(3, (uint8_t *)&buttonText);
        lcd.DisplayStringAtLine(7, (uint8_t*)&text);
    }
    exit(0);
}
