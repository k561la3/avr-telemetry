#include <mega8.h>
#include <delay.h>
#include <stdio.h>
#include <stdint.h>

#define FIRST_ADC_INPUT 0
#define LAST_ADC_INPUT 5
unsigned char adc_data[LAST_ADC_INPUT-FIRST_ADC_INPUT+1];
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (1<<ADLAR))
uint8_t i;

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{ #asm("cli")

TCNT1=0x85EE;
putchar('S');
for(i = 0; i < 6; i++){
    putchar(adc_data[i]);
    } 
putchar('E');
#asm("sei")    
}




interrupt [ADC_INT] void adc_isr(void)
{#asm("cli")
static unsigned char input_index=0;
adc_data[input_index]=ADCH;
if (++input_index > (LAST_ADC_INPUT-FIRST_ADC_INPUT))
   input_index=0;
ADMUX=(FIRST_ADC_INPUT | ADC_VREF_TYPE)+input_index;
delay_us(10);
ADCSRA|=(1<<ADSC);
#asm("sei")
}

void main(void)
{
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (0<<CS10);
TCNT1H=0x85;
TCNT1L=0xEE;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<TOIE0);



// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: Off
// USART Transmitter: On
// USART Mode: Asynchronous
// USART Baud Rate: 38400
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x0C;



ADMUX=FIRST_ADC_INPUT | ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (1<<ADSC) | (0<<ADFR) | (0<<ADIF) | (1<<ADIE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ACME);
#asm("sei")

while (1)
      {
      

      }
}
