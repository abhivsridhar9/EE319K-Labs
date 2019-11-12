// put implementations for functions, explain how it works
// put your names here, date
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"


//DAC_Init 
//Subroutine that initializes the DAC to 6 bits

void DAC_Init (void){
	SYSCTL_RCGCGPIO_R|=0x02;
	__nop();
	__nop();
	GPIO_PORTB_DIR_R |=0x3F;
	GPIO_PORTB_DEN_R |=0x3F;
}

//DAC Out
void DAC_Out (uint32_t data){
	GPIO_PORTB_DATA_R=data;
}
//***********Buttons to play music**********
//The reset button will play music along with resetting the game 

void Reset_Init(void){
	SYSCTL_RCGCGPIO_R|=0x10;//initializes Port E to be for all buttons
	__nop();
	__nop();
	GPIO_PORTE_DIR_R|=0x03;
	GPIO_PORTE_DEN_R|=0x03;//will initialize the rest of Port E buttons as needed
}
//2 keys, output is 0 to 3 depending on the keys

//bit n is set if key n is pressed
uint32_t Reset_In (void){
	if((GPIO_PORTE_DATA_R&0x03)==0x01){
		return 0x01;
		//this is when the reset button is pressed
	}
	if((GPIO_PORTE_DATA_R &0x03)==0x02){
		return 0x02;
		//this is when the pause button is pressed
	}
	return 0x00;
	//if nothing at all is pressed 
}