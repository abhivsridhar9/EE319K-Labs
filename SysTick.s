; SysTick.s
; Module written by: Ryan Root and Abhi Sridhar
; Date Created: 2/14/2017
; Last Modified: 3/3/2019
; Brief Description: Initializes SysTick

NVIC_ST_CTRL_R        EQU 0xE000E010
NVIC_ST_RELOAD_R      EQU 0xE000E014
NVIC_ST_CURRENT_R     EQU 0xE000E018

        AREA    |.text|, CODE, READONLY, ALIGN=2
        THUMB
; -UUU- You add code here to export your routine(s) from SysTick.s to main.s
        EXPORT SysTick_Init
;------------SysTick_Init------------
; ;-UUU-Complete this subroutine
; Initialize SysTick running at bus clock.
; Make it so NVIC_ST_CURRENT_R can be used as a 24-bit time
; Input: none
; Output: none
; Modifies: ??
SysTick_Init
 ; **-UUU-**Implement this function****
	LDR R0, =NVIC_ST_CTRL_R
	MOV R1, #0
	STR R1, [R0]
	
	LDR R0, =NVIC_ST_RELOAD_R
	LDR R1, =0x00FFFFFF
	STR R1, [R0]
	
	LDR R0, =NVIC_ST_CURRENT_R
	MOV R1, #0
	STR R1, [R0]
	
	LDR R0, =NVIC_ST_CTRL_R
	LDR R1, =0x0005
	STR R1, [R0]
	
	BX  LR                          ; return
	

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file
