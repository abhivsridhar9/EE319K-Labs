;****************** main.s ***************
; Program initially written by: Yerraballi and Valvano
; Author: Abhishek Sridhar
; Date Created: 1/15/2018 
; Last Modified: 2/4/2019 
; Brief description of the program: Spring 2019 Lab1
; The objective of this system is to implement odd-bit counting system
; Hardware connections: 
;  Output is positive logic, 1 turns on the LED, 0 turns off the LED
;  Inputs are negative logic, meaning switch not pressed is 1, pressed is 0
;    PE0 is an input 
;    PE1 is an input 
;    PE2 is an input 
;    PE3 is the output
; Overall goal: 
;   Make the output 1 if there is an odd number of 1's at the inputs, 
;     otherwise make the output 0
; The specific operation of this system 
;   Initialize Port E to make PE0,PE1,PE2 inputs and PE3 an output
;   Over and over, read the inputs, calculate the result and set the output

; NOTE: Do not use any conditional branches in your solution. 
;       We want you to think of the solution in terms of logical and shift operations

GPIO_PORTE_DATA_R  EQU 0x400243FC
GPIO_PORTE_DIR_R   EQU 0x40024400
GPIO_PORTE_DEN_R   EQU 0x4002451C
SYSCTL_RCGCGPIO_R  EQU 0x400FE608

      THUMB
      AREA    DATA, ALIGN=2
;global variables go here
      ALIGN
      AREA    |.text|, CODE, READONLY, ALIGN=2
      EXPORT  Start
Start
; code to execute once at start goes here
	LDR R0,=SYSCTL_RCGCGPIO_R
	MOV R1, #0x10 
	STR R1,[R0]
	
	NOP
	NOP
	NOP
	NOP
	
	LDR R0, =GPIO_PORTE_DIR_R
	MOV R1, #0x08 
	STR R1,[R0] ; assign the outputs and inputs to the different pins
	
	LDR R0, =GPIO_PORTE_DEN_R
	MOV R1, #0x0F
	STR R1,[R0] ; digital enable all pins to be used
	
	
loop
; code that runs over and over goes here
	
	LDR R3, =GPIO_PORTE_DATA_R
	LDR R3, [R3]
	
	
	AND R7, R7, #0
	AND R4, R3, #0x01
	LSL R4, #2
	
	AND R5, R3, #0x02
	LSL R5, #1
	AND R6, R3, #0x04
	
	MOV R7, R6
	EOR R7, R5
	EOR R7, R4
	
	EOR R7, #0x04
	
	LSL R7, #1 ; Shift it to the position of the output bit 
	
	LDR R0,= GPIO_PORTE_DATA_R
	STR R7, [R0]
	
    B   loop

    ALIGN        ; make sure the end of this section is aligned
    END          ; end of file
          