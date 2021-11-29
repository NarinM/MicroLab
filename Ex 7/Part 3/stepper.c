#include <mega16.h>
#include <delay.h>
#include <alcd.h>
#include <stdio.h>

char stepperInputs[] = {
  0b0011,
  0b0010,
  0b0110,
  0b0100,
  0b1100,
  0b1000,
  0b1001,
  0b0001
};
int currentInput = 0;
int i;

void main(void) {
  char buffer[10];

  DDRC = 0x0F;
  DDRD = 0x00;

  PORTC = 0x00;
  PORTD = 0x00;

  lcd_init(10);

  while (1) {
    sprintf(buffer, "Angle: %d", currentInput * 45);
    lcd_gotoxy(0, 0);
    lcd_puts(buffer);

    if (PIND .0 == 0) {
      currentInput = currentInput++;
      if(currentInput > 8)
        currentInput = 0;

      delay_ms(50);
    } else if (PIND .1 == 0) {
      delay_ms(50);
      for (i = 0; i < currentInput; i++) {
        PORTC = stepperInputs[i];
        delay_ms(50);
      }
    }
  }
}