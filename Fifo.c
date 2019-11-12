// Fifo.c
// Runs on LM4F120/TM4C123
// Provide functions that implement the Software FiFo Buffer
// Last Modified: November 14, 2018
// Student names: Ryan Root
// Last modification date: 4/22/19

#include <stdint.h>
// --UUU-- Declare state variables for Fifo
//        buffer, put and get indexes
#define FIFO_SIZE 10
int32_t *PutPt;
int32_t *GetPt;
int32_t Fifo[FIFO_SIZE];
int32_t length;

// *********** Fifo_Init**********
// Initializes a software FIFO of a
// fixed size and sets up indexes for
// put and get operations
void Fifo_Init(){
	uint32_t ind = 0;
	while(ind < FIFO_SIZE){
		Fifo[ind] = 0;
		ind++;
	}
	PutPt = GetPt = &Fifo[FIFO_SIZE-1];
	length = 0;
}

// *********** Fifo_Put**********
// Adds an element to the FIFO
// Input: Character to be inserted
// Output: 1 for success and 0 for failure
//         failure is when the buffer is full
uint32_t Fifo_Put(char data){
	int32_t *tempPt;
  tempPt = PutPt-1;    // see if there is room
  if(PutPt==&Fifo[0]){
    tempPt = &Fifo[FIFO_SIZE-1];
  }
  if(length == FIFO_SIZE){
    return(0);         // full! 
  } else {
    *PutPt = data;   // save
    PutPt = tempPt;    // OK 
		length++;
    return(1);
	}
}

// *********** FiFo_Get**********
// Gets an element from the FIFO
// Input: Pointer to a character that will get the character read from the buffer
// Output: 1 for success and 0 for failure
//         failure is when the buffer is empty
uint32_t Fifo_Get(char *datapt){ 
//--UUU-- Complete this routine
	if(length == 0){
    return(0);   // Empty 
  }
  else{
    *datapt = (char)*(GetPt);
    if(GetPt==&Fifo[0]){
			GetPt = &Fifo[FIFO_SIZE-1];
    } else {
			GetPt--;
		}
		length--;
    return(1);
  }
}
