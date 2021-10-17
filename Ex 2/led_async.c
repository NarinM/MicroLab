/*******************************************************
This program was created by the
CodeWizardAVR V3.14 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 8 LED Sync
Version : 
Date    : 10/17/2021
Author  : 
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>

int counter;
int canCount = 0;
int ledNumber = 0;
int lights[] = {0b11111110, 0b11111101, 0b11111011, 0b11110111, 0b11101111, 0b11011111, 0b10111111, 0b01111111};

interrupt[TIM0_OVF] void timer0_ovf_isr(void)
{
    if(canCount == 1) 
    {
        counter = counter + 1;

        if (counter == 2)
        {
            PORTB = lights[ledNumber];
            
            ledNumber = ledNumber + 1;
            if(ledNumber > 7)
                ledNumber = 0;

            counter = 0;
        }
    } else PORTB = 0xFF;

    TCNT0 = 0x00;
}

void main(void)
{
    DDRB = 0xFF;
    DDRA = 0x00;

    TIMSK = (0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
    TCCR0 = (0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0 = 0x00;
    OCR0 = 0x00;
    
    PORTB = 0xFF;

    #asm("sei")

    while (1)
    {
        if(PINA.0 == 1)
        {
            if(canCount == 1)
                canCount = 0;
            else
                canCount = 1;
        }
    }
}
