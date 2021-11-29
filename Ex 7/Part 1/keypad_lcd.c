#include <mega16.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>

char numbers[] = {
  0b00111111,
  0b00000110,
  0b01011011,
  0b01001111,
  0b01100110,
  0b01101101,
  0b01111101,
  0b00000111,
  0b01111111,
  0b01101111
};

void main(void) {
  char c;
  char k;
  char buffer[10];

  lcd_init(10);

  DDRB = 0xFF;
  PORTB = 0x00;
  DDRD = 0xF0;

  while (1) {
    PORTD.4 = 0;
    c = PIND & 0x07;
    if (c != 0x07) {
      switch (c) {
      case 0b110:
        k = 1;
        break;
      case 0b101:
        k = 2;
        break;
      case 0b011:
        k = 3;
        break;
      }
    }
    PORTD.4 = 1;
    PORTD.5 = 0;
    c = PIND & 0x07;
    if (c != 0x07) {
      switch (c) {
      case 0b110:
        k = 4;
        break;
      case 0b101:
        k = 5;
        break;
      case 0b011:
        k = 6;
        break;
      }
    }
    PORTD.5 = 1;
    PORTD.6 = 0;
    c = PIND & 0x07;
    if (c != 0x07) {
      switch (c) {
      case 0b110:
        k = 7;
        break;
      case 0b101:
        k = 8;
        break;
      case 0b011:
        k = 9;
        break;
      }
    }
    PORTD.6 = 1;

    PORTD.7 = 0;
    if (!PIND.1) k = 0;
    PORTD.7 = 1;

    PORTD = 0xFF;
    if (k != 0xFF) {
      sprintf(buffer, "Number: %d", numbers[k]);
      lcd_gotoxy(0, 0);
      lcd_puts(buffer);
    } else PORTB = 0x00;

    delay_ms(50);
  }
}