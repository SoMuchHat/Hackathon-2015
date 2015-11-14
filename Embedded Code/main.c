#include <msp430.h> 
#include "uart.h"
#include "main.h"
/*
 * main.c
 */

char sine_wave[200];
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

    i = 0;
    while(1)
    {

    }
}

void Setup_Sine()
{
	while(i < 200)
	{
		sine_wave[i] = 100 - (i%10);
		i++;
	}
}

void Send_Sine()
{
	Send_Data(sine_wave[i]);
	i++;
	if(i == 100)
	{
		i = 0;
	}
}
