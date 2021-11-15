#include <mega16.h>
#include <delay.h>
#include <stdio.h>
#include <alcd.h>

int temperature;
int input;

void main(void) {
  char buffer[10];

  DDRA = 0x00;
  PORTA = 0x00;

  ADMUX = ((0 << REFS1) | (1 << REFS0) | (0 << ADLAR));
  ADCSRA = (1 << ADEN) | (0 << ADSC) | (0 << ADATE) | (0 << ADIF) | (0 << ADIE) | (0 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
  SFIOR = (0 << ADTS2) | (0 << ADTS1) | (0 << ADTS0);

  lcd_init(10);
  lcd_clear();

  while (1) {
    lcd_clear();

    ADMUX = 0 | ((0 << REFS1) | (1 << REFS0) | (0 << ADLAR));

    delay_us(50);

    ADCSRA |= (1 << ADSC);
    while ((ADCSRA & (1 << ADIF)) == 0);
    ADCSRA |= (1 << ADIF);
    temperature = ADCW / 2;

    sprintf(buffer, "Temperature: %d", temperature);
    lcd_puts(buffer);

    ADMUX = 1 | ((0 << REFS1) | (1 << REFS0) | (0 << ADLAR));

    delay_us(50);

    ADCSRA |= (1 << ADSC);
    while ((ADCSRA & (1 << ADIF)) == 0);
    ADCSRA |= (1 << ADIF);
    input = ADCW / 20;

    if (temperature > (60 + input)) {
      PORTB .3 = 1;
    }
    if (temperature < (60 - input)) {
      PORTB .3 = 0;
    }

    delay_ms(500);
  }
}