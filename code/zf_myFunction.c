/*
 * zf_myFunction.c
 *
 *  Created on: 2024Äê3ÔÂ17ÈÕ
 *      Author: 97329
 */
#include "zf_myFunction.h"

void wireless_uart_send_number(uint32 num)
{
    uint32 bit = 1;
    for (uint32 temp = num; temp >= 10; bit *= 10)
    {
        temp /= 10;
    }

    for (; bit > 0; bit /= 10)
    {
        wireless_uart_send_byte((uint8)(num / bit + '0'));
        num %= bit;
    }
}



