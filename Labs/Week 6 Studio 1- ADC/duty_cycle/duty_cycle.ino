#include "Arduino.h"
#include <avr/interrupt.h>
unsigned int adcvalue, loval, hival;

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
  OCR0A = remapped_adc;
  ledToggle();
}
ISR(ADC_vect)
{
 loval = ADCL;
 hival = ADCH;
 adcvalue = (hival << 8) | loval;
 remapped_adc = ((adcvalue-568)*255)/337;
 ADCSRA |= (1 << ADSC);
 
}

void ledToggle()
{
 PORTB ^= (1 << PORTB5);
}

void setup() {
 // put your setup code here, to run once:
 PRR &= 0b11111110;
 ADCSRA = 0b10001111;
 ADMUX = 0b01000000;
  // Set PortB Pin 5 as output
 DDRB |= (1 << DDB5);
 
 InitPWM();
 startPWM();
 sei();
 ADCSRA |= 0b01000000;
 Serial.begin(9600);
}
void loop() {}
