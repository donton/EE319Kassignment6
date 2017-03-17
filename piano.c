// Piano.c
// This software configures the off-board piano keys
// Runs on LM4F120 or TM4C123
// Program written by: put your names here
// Date Created: 8/25/2014 
// Last Modified: 3/6/2015 
// Section 1-2pm     TA: Wooseok Lee
// Lab number: 6
// Hardware connections
// TO STUDENTS "REMOVE THIS LINE AND SPECIFY YOUR HARDWARE********

// Code files contain the actual implemenation for public functions
// this file also contains an private functions and private data
#include <stdint.h>
#include "tm4c123gh6pm.h"
volatile uint32_t del;
// **************Piano_Init*********************
// Initialize piano key inputs, called once 
// Input: none 
// Output: none
void Piano_Init(void){
		SYSCTL_RCGC2_R |= 0x01;  								// 1) enable clock to A
		del = SYSCTL_RCGC2_R;  									// 2) no need to unlock
		GPIO_PORTA_LOCK_R |= 0x4C4F434B;
		GPIO_PORTA_CR_R 	|= 0xBC;							// allow changes to PA6,PA4-PA2
		GPIO_PORTA_DIR_R	&= 0xC3;							// PA4-PA2 are intputs
		GPIO_PORTA_DIR_R  |= 0x80;
		GPIO_PORTA_DEN_R	|= 0xBC;							// digital enable	
}

// **************Piano_In*********************
// Input from piano key inputs 
// Input: none 
// Output: 0 to 7 depending on keys
// 0x01 is just Key0, 0x02 is just Key1, 0x04 is just Key2
uint32_t Piano_In(void){
  uint32_t inp;
	inp = GPIO_PORTA_DATA_R;
	inp = inp >> 2;														//because the given input is in PA4-PA2
	return inp;
}
