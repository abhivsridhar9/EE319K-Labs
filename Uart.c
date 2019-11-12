// Uart.c
// Runs on LM4F120/TM4C123
// Use UART1 to implement bidirectional data transfer to and from 
// another microcontroller in Lab 9.  This time, interrupts and FIFOs
// are used.
// Daniel Valvano
// November 14, 2018
// Modified by EE345L students Charlie Gough && Matt Hawk
// Modified by EE345M students Agustinus Darmawan && Mingjie Qiu

/* Lab solution, Do not post
 http://users.ece.utexas.edu/~valvano/
*/

// This U0Rx PC4 (in) is connected to other LaunchPad PC5 (out)
// This U0Tx PC5 (out) is connected to other LaunchPad PC4 (in)
// This ground is connected to other LaunchPad ground

#include <stdint.h>
#include "Fifo.h"
#include "Uart.h"
#include "../inc/tm4c123gh6pm.h"

uint32_t DataLost; 
// Initialize UART1
// Baud rate is 115200 bits/sec
// Make sure to turn ON UART1 Receiver Interrupt (Interrupt 6 in NVIC)
// Write UART1_Handler
void Uart_Init(void){
   // --UUU-- complete with your code
	Fifo_Init();
	SYSCTL_RCGCUART_R|=0x0002;
	SYSCTL_RCGCGPIO_R|=0x0002;
	
	UART1_CTL_R&=~0x0001;
	UART1_IBRD_R=43;
	UART1_FBRD_R=26;//sets baud rate as fixed pt decimal
	
	UART1_LCRH_R = 0x0070;  // 8-bit length, enable FIFO
  UART1_CTL_R = 0x0301;   // enable RXE, TXE and UART
  GPIO_PORTC_AFSEL_R |= 0x30; // alt funct on PB1-0
  GPIO_PORTC_PCTL_R = 
            (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_DEN_R |= 0x30;   // digital I/O on PB1-0
  GPIO_PORTC_AMSEL_R &= ~0x30; // No analog on PB1-0

	
	
	

	
	
	
	
}

// input ASCII character from UART
// spin if RxFifo is empty
// Receiver is interrupt driven
char Uart_InChar(void){
	
	
    while((UART1_FR_R&0x0010) != 0); 
  // wait until RXFE is 0
  return((uint8_t)(UART1_DR_R&0xFF));

}

//------------UART1_InMessage------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until ETX is typed
//    or until max length of the string is reached.
// Input: pointer to empty buffer of 8 characters
// Output: Null terminated string
// THIS FUNCTION IS OPTIONAL
void UART1_InMessage(char *bufPt){
	
}

//------------UART1_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
// Transmitter is busywait
void Uart_OutChar(char data){
  // --UUU-- complete with your code
	
while((UART1_FR_R&0x0020) != 0){};  
  // wait until TXFF is 0
  UART1_DR_R = data;

}

// hardware RX FIFO goes from 7 to 8 or more items
// UART receiver Interrupt is triggered; This is the ISR
void UART1_Handler(void){
  // --UUU-- complete with your code
		//UART1 interrupt enabling 
	NVIC_EN0_R|=0x40; //enable bit 6 of the NVIC register, UART1 bit
	UART1_IFLS_R|=0x10 ; 
	UART1_IM_R|=0x10 ; //makes interrupt to get triggered on half full
	UART1_ICR_R|=0x10 ; //clears the interrupt bit manually
	
}
