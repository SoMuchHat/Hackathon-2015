#include <msp430.h> 
#include "uart.h"
#include "main.h"
/*
 * main.c
 */

char output[6];
int sine_wave[10];
int i = 0;

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;			// Stop watchdog timer
	
    if (CALBC1_1MHZ==0xFF)				// If calibration constant erased
    {
        while(1);                       // do not load, trap CPU!!
    }

    DCOCTL = 0;							// Select lowest DCOx and MODx settings
    BCSCTL1 = CALBC1_1MHZ;              // Set DCO
    DCOCTL = CALDCO_1MHZ;

    P1SEL = BIT1 + BIT2;				// P1.1 = RXD, P1.2 = TXD
    P1SEL2 = BIT1 + BIT2;

    P1SEL |= BIT6 + BIT7;				// P1.6 and 1.7 for USCI_B0
    P1SEL2 |= BIT6 + BIT7;

    Setup_Sine();

    Configure_BlueSMiRF();
    __enable_interrupt();

    // These never change
    output[4] = 0x0D;					// ASCII value for newline
    output[5] = 0x0A;

    i = 0;
    while(1)
    {
    	__delay_cycles(999999);
    	Send_Sine();
    }
}


unsigned long Dec2BCD(unsigned int Value)
{
	unsigned int i;
	unsigned long Output;
	for (i = 16, Output = 0; i; i--) // BCD Conversion, 16-Bit
	{
		Output = __bcd_add_long(Output, Output);
		if (Value & 0x8000)
			Output = __bcd_add_long(Output, 1);
			Value <<= 1;
	}
	return Output;
}


void Setup_Sine()
{
	while(i < 10)
	{
		sine_wave[i] = 1000 - (i*100);
		i++;
	}
}

void Send_Sine()
{
	unsigned long bcd = Dec2BCD(sine_wave[i]);
	output[0] = ((bcd & 0x0000F000L) >> 12) + 48;
	output[1] = ((bcd & 0x00000F00L) >> 8) + 48;
	output[2] = ((bcd & 0x000000F0L) >> 4) + 48;
	output[3] = ((bcd & 0x0000000FL)) + 48;
	i++;
	if (i == 10)
	{
		i = 0;
	}
	Send_Data();

}
