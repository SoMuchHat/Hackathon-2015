/*
 * uart.c
 *
 *  Created on: Nov 14, 2015
 *      Author: Sean
 */




int Configure_BlueSMiRF()
{
	UCA0CTL1 |= UCSSEL_2;			// SMCLK as source
	UCA0BR0 = 104;					// 9600 Baudrate with 1Mhz clock
	UCA0BR1 = 0;


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
	while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
	UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
}
