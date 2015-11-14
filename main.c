#include <msp430.h> 
#include "uart.h"
/*
 * main.c
 */
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


    Configure_BlueSMiRF();

    while(1)
    {

    }
	return 0;
}
