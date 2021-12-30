#include <mega16.h>
#include <alcd.h>

void changeDirection(int);

void main(void) {
    DDRB = 0xFF;
    PORTB = 0x00;

    DDRA = 0x00;
    PORTA = 0x00;

    lcd_init(26);

    TCCR0 = 0x00;
    TCNT0 = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    ICR1H = 0x00;
    ICR1L = 0x00;
    OCR1AH = 0x00;
    OCR1AL = 0x00;
    OCR1BH = 0x00;
    OCR1BL = 0x00;
    ASSR = 0x00;
    TCCR2 = 0x00;
    TCNT2 = 0x00;
    OCR2 = 0x00;
    MCUCR = 0x00;
    TIMSK = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;

    while (1) {
        changeDirection(PINA);
    }
}

void changeDirection(int input) {
    switch (0b00011111 & input) {
        case 0b00000100:
        case 0b00001110:
        case 0b11110001:
        case 0b11111011:
            PORTB = 0b001010;
            lcd_gotoxy(0, 0);
            lcd_putsf("The Robot is going forward");
            break;

        case 0b00011100:
        case 0b00001000:
        case 0b00011000:
        case 0b00010000:
        case 0b00001100:
        case 0b11100011:
        case 0b11100111:
        case 0b11101111:
        case 0b11110111:
        case 0b11110011:
            PORTB = 0b000110;
            lcd_gotoxy(0, 0);
            lcd_putsf("The Robot is going right   ");
            break;

        case 0b00000000:
            PORTB = 0b00000000;
            lcd_gotoxy(0, 0);
            lcd_putsf("The Robot is stopped        ");
            break;

        default:
            PORTB = 0b001001;
            lcd_gotoxy(0, 0);
            lcd_putsf("The Robot is going left   ");
            break;
    }
}