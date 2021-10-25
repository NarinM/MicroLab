#include <mega16.h>

int numbers[] = {0b01000000,0b01111001,0b00100100,0b00110000,0b00011001,0b00010010,0b00000010,0b01111000,0b00000000,0b00011000};

int currentNumber = 0;
int timerOverflow = 0;

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    timerOverflow = timerOverflow + 1;
    if(timerOverflow == 30)
    {
        PORTA = numbers[currentNumber];
        
        currentNumber = currentNumber + 1;
        if(currentNumber > 9)
            currentNumber = 0;

        timerOverflow = 0;
    }

    TCNT1H=0xFF;
    TCNT1L=0xF0;
}

void main(void)
{
    DDRA = 0xFF;
    PORTA = 0xFF;
    
    TCCR1A=0x00;
    TCCR1B=0x01;
    TCNT1H=0xFF;
    TCNT1L=0xF0;
    MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR=(0<<ISC2);
    TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

    #asm("sei")    

    while (1)
    {

    }
}
