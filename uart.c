/*
 * uart.c
 *
 *  Created on: Nov 14, 2015
 *      Author: Sean
 */


#include <msp430.h>


int Configure_BlueSMiRF()
{
	UCA0CTL1 |= UCSSEL_2;			// SMCLK as source
	UCA0BR0 = 104;					// 9600 Baudrate with 1Mhz clock
	UCA0BR1 = 0;

	UCA0MCTL = UCBRS0;				// Modulation UCBRSx = 1
									// CHECK ME
	UCA0CTL1 &= ~UCSWRST;			// Initialize USCI
	IE2 |= UCA0TXIE;                // Enable USCI_A0 TX interrupt
}

int Send_Data(char byte)
{
	while (!(IFG2&UCA0TXIFG));                // Wait until USCI_A0 TX buffer ready
	UCA0TXBUF = byte;                    // Send byte
}


#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
	// Received character. Do something?
}
