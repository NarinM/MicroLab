#include <mega16.h>

int numbers[] = {0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};

int currentNumber[] = {0,0,0,0}; 
int activeSegment = 3;
int timerZeroOverflow = 0; 
int timerOneOverflow = 0;

int temp;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    timerZeroOverflow = timerZeroOverflow + 1;
    if(timerZeroOverflow == 1) 
    {    
        PORTD = numbers[currentNumber[activeSegment]];
                 
        activeSegment--;
        if(activeSegment < 0)
            activeSegment = 3;
            
        temp = temp >> 1;
        if(temp == 0b00000000)
            temp = 0b00001000;
            
        temp = temp ^ 0b11111111;
        PORTC = temp;
        
        timerZeroOverflow = 0; 
        temp = temp ^ 0b11111111;
    }
    
    TCNT0 = 0x00;
}

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    timerOneOverflow = timerOneOverflow + 1;
    if(timerOneOverflow == 400) {
        currentNumber[3] = currentNumber[3] + 1;
        
        if(currentNumber[3] == 10)
        {
            currentNumber[3] = 0;
            currentNumber[2] = currentNumber[2] + 1;
            
            if(currentNumber[2] == 10)
            {
                currentNumber[2] = 0;
                currentNumber[1] = currentNumber[1] + 1;
                
                if(currentNumber[1] == 10)
                {
                    currentNumber[1] = 0;
                    currentNumber[0] = currentNumber[0] + 1;
                    
                    if(currentNumber[0] == 10)
                        currentNumber[0] = 0;
                }
            }
        }
        
        timerOneOverflow=0;
    }
    
    TCNT1H = 0xFF;
    TCNT1L = 0xF0;
}

void main(void)
{
    DDRD = 0xFF;
    DDRC = 0xFF;

    PORTD = 0x00;
    PORTC = 0xFF;

    TIMSK = (0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);

    TCCR0 = (0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0 = 0x00;
    OCR0 = 0x00;

    TCCR1A = (0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B = (0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
    TCNT1H = 0xFF;
    TCNT1L = 0xF0;

    MCUCR = (0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR = (0<<ISC2);

    #asm("sei") 
    
    while (1)
    {
    
    }
}
