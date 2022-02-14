#include "Arduino.h"
#include <avr/interrupt.h>
unsigned int adcvalue;
unsigned int remapped_adc;
void InitPWM()
{
 TCNT0 = 0;
 OCR0A = 0;
 TCCR0A = 0b00000001;
 TIMSK0 |= 0b10;
}
void startPWM()
{
 TCCR0B = 0b00000100;
}
ISR(TIMER0_COMPA_vect)
{
// Provide your code for the ISR
}
ISR(ADC_vect)
{
// Provide your code for the ISR
}
void setup() {
 // put your setup code here, to run once:
 PRR &= 0b11111110;
 ADCSRA = 0b10001111;
 ADMUX = 0b01000000;
 DDRB |= 0b00100000;
 
 InitPWM();
 startPWM();
 sei();
 ADCSRA |= 0b01000000;
}
void loop() {}
