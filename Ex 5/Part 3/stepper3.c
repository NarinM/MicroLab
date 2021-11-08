#include <mega16.h>

int stepperMotorInputs[4] = {0b00001001 , 0b00001010 , 0b00000110 , 0b00000101};
int stepperMotorCurrentInput = 0;

int timerZeroOverflow = 0;

int canRun;
int buttonState;

int currentSpeed;
const int minSpeed = 15;

const int delayForMaxSpeed = 20;
int currentDelayForMaxSpeed;

enum controllerDirection {
    Direct, 
    Reverse
} direction;

int isUpward;

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    if(canRun)
    {
        timerZeroOverflow++;
        if(timerZeroOverflow == currentSpeed)
        {
            CHANGE_DIRECTION:
            if(direction == Direct)
            {
                stepperMotorCurrentInput++;
                if(stepperMotorCurrentInput > 3)
                    stepperMotorCurrentInput = 0;
            }else
            {
                stepperMotorCurrentInput--;
                if(stepperMotorCurrentInput < 0)
                    stepperMotorCurrentInput = 3;
            }
            
            CHANGE_IS_UPWARD:
            
            if(isUpward == 1)
            {
                if(currentSpeed > 2)
                {
                    currentSpeed--;
                }else
                {
                    if(currentDelayForMaxSpeed < delayForMaxSpeed)
                        currentDelayForMaxSpeed++;
                    else
                    {
                        isUpward = 0;
                        currentDelayForMaxSpeed = 0;
                         
                        goto CHANGE_IS_UPWARD;
                    }
                }
            }else
            {
                if(currentSpeed < minSpeed)
                {
                    currentSpeed++;
                }
                else
                {
                    isUpward = 1;
                    
                    if(direction == Direct)
                        direction = Reverse;
                    else
                        direction = Direct;
                    
                    currentSpeed = minSpeed;
                    goto CHANGE_DIRECTION;
                }
            }
            
            PORTA = stepperMotorInputs[stepperMotorCurrentInput];
                     
            timerZeroOverflow = 0;
        }
    }
    
    TCNT0 = 0x00;                   
}

void main(void)
{
    currentSpeed = minSpeed;
    direction = Direct;
    isUpward = 1;
    currentDelayForMaxSpeed = 0;
    buttonState = 0;

    DDRA = 0xFF;
    DDRC = 0x00;

    TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
    TCNT0 = 0x00;
    OCR0 = 0x00;
    TIMSK = (0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
    MCUCR = (0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    MCUCSR = (0<<ISC2);
    
    #asm("sei")

    while (1)
    {
        if(PINC.2 == 1 && buttonState == 0)
        {
            buttonState = 1;
            if(canRun == 1)
            {
                canRun = 0;
                PORTA = 0x00;
                direction = Direct;
                isUpward = 1;
                currentDelayForMaxSpeed = 0;
            } else
                canRun = 1;
        } else if(PINC.2 == 0 && buttonState == 1)
        {
            buttonState = 0;
        }
    }
}
