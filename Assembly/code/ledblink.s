PIO_PER EQU  0x400E0E00	
PIO_SODR EQU 0x400E0E30
PIO_OER EQU  0x400E0E10 
PIO_PDSR EQU 0x400E0E3C
PIO_ISR EQU  0x400E0E4C
PIO_CODR EQU 0x400E0E34

		
		AREA myLEDBlinkCode, CODE, READONLY
		EXPORT __main
		entry

__main
	BL EnablePio_1  ;branch and link =>call EnablePio_1
	BL EnablePio_2  ;branch and link =>call EnablePio_2
	BL EnablePio_3  ;branch and link =>call EnablePio_3
	
BEGIN
	LDR R1, =PIO_ISR ;R1=PIO_ISR
	LDR R2, [R1] ; R2 be loaded with location of 0x400E0E4C
	CMP R2,#2_100000 ;compare for chooshing which button is pressed
	BEQ loop ;branch if equal =>Z=1
	B BEGIN ;if Z=0
	
	
Finish
	BL LEDOff_1 ;branch and link =>call LEDOff_1
	BL LEDOff_2 ;branch and link =>call LEDOff_2
	BL LEDOff_3 ;branch and link =>call LEDOff_3
	B BEGIN ;branch the begin

loop
	LDR R1, =PIO_ISR ;R1=PIO_ISR
	LDR R2, [R1]  ; R2 be loaded with location of 0x400E0E4C
	CMP R2, #2_1000000  
	BEQ Finish  ;branch if equal =>Z=1
	
    ;if Z=0
	BL LEDOn_1 ;branch and link =>call LEDOn_1
	BL LEDOn_2 ;branch and link =>call LEDOn_2
	BL LEDOn_3 ;branch and link =>call LEDOn_3
	
	BL Delay   ;call Delay
	
	LDR R1, =PIO_ISR ;R1=PIO_ISR
	LDR R2, [R1] ; R2 be loaded with location of 0x400E0E4C
	CMP R2, #2_1000000
	BEQ Finish ;branch if equal =>Z=1
	
	;if Z=0
	BL LEDOff_1 ;branch and link =>call LEDOff_1
	BL LEDOn_2 ;branch and link =>call LEDOn_2
	BL LEDOn_3 ;branch and link =>call LEDOn_3
	BL Delay ;call Delay
	
	LDR R1, =PIO_ISR ;R1=PIO_ISR
	LDR R2, [R1] ; R2 be loaded with location of 0x400E0E4C
	CMP R2, #2_1000000
	BEQ Finish ;branch if equal =>Z=1
	
	BL LEDOn_1 ;branch and link =>call LEDOn_1
	BL LEDOff_2 ;branch and link =>call LEDOff_2
	BL LEDOn_3 ;branch and link =>call LEDOn_3
	BL Delay ;call Delay
	
	LDR R1, =PIO_ISR ;R1=PIO_ISR
	LDR R2, [R1] ; R2 be loaded with location of 0x400E0E4C
	CMP R2, #2_1000000
	BEQ Finish ;branch if equal =>Z=1
	
	BL LEDOff_1 ;branch and link =>call LEDOff_1
    BL LEDOff_2 ;branch and link =>call LEDOff_1
	BL LEDOff_3 ;branch and link =>call LEDOff_3
	BL Delay ;call Delay
	
	LDR R1, =PIO_ISR ;R1=PIO_ISR
	LDR R2, [R1]  ; R2 be loaded with location of 0x400E0E4C
	CMP R2, #2_1000000
	BEQ Finish ;branch if equal =>Z=1
	
	BL LEDOn_2 ;branch and link =>call LEDOn_2
	BL LEDOn_1 ;branch and link =>call LEDOn_1
	BL LEDOff_3 ;branch and link =>call LEDOff_3
	BL Delay ;call Delay
	
	LDR R1, =PIO_ISR ;R1=PIO_ISR
	LDR R2, [R1]  ; R2 be loaded with location of 0x400E0E4C
	CMP R2, #2_1000000
	BEQ Finish ;branch if equal =>Z=1
	
	BL LEDOff_1 ;branch and link =>call LEDOff_1
	BL LEDOn_2 ;branch and link =>call LEDOn_2
	BL LEDOff_3 ;branch and link =>call LEDOff_3
	BL Delay ;call Delay
	
	LDR R1, =PIO_ISR ;R1=PIO_ISR
	LDR R2, [R1]  ; R2 be loaded with location of 0x400E0E4C
	CMP R2, #2_1000000 ;branch if equal =>Z=1
	
	BEQ Finish
	BL LEDOff_1 ;branch and link =>call LEDOff_1
	BL LEDOff_2 ;branch and link =>call LEDOff_2
	BL LEDOff_3 ;branch and link =>call LEDOff_3
	
	BL loop ;return to loop 

EnablePio_1
	MOV R4, #2_1 ;mov the binary number of the specific led into the register
	LDR R5,=PIO_PER ;R5=PIO_PER
	STR R4, [R5]  ;store R4 in location 0x400E0E00
	LDR R5,=PIO_OER ;R5=PIO_OER
	STR R4, [R5] ;store R4 in location 0x400E0E10
	BX LR ;return to caller 
	
EnablePio_2
	MOV R4, #2_10 ;R4=10=>binary
	LDR R5,=PIO_PER ;R5=PIO_PER
	STR R4, [R5]  ;store R4 in location 0x400E0E00
	LDR R5,=PIO_OER ;R5=PIO_OER
	STR R4, [R5] ;store R4 in location 0x400E0E10
	BX LR ;return to caller 
	
EnablePio_3
	MOV R4, #2_100 ;R4=100=>binary
	LDR R5,=PIO_PER ;R5=PIO_PER
	STR R4, [R5] ;store R4 in location 0x400E0E00
	LDR R5,=PIO_OER ;R5=PIO_OER
	STR R4, [R5] ;store R4 in location 0x400E0E10
	
	BX LR
	
LEDOn_1
	MOV R4, #2_1 ;R4=1=>binary
	LDR R5,=PIO_SODR ;R5=PIO_SODR
	STR R4, [R5] ;store R4 in location 0x400E0E30
	BX LR ;return to caller 
	
LEDOn_2
	MOV R4, #2_10 ;R4=10=>binary
	LDR R5,=PIO_SODR ;R5=PIO_SODR
	STR R4, [R5] ;store R4 in location 0x400E0E30
	BX LR ;return to caller 
	
LEDOn_3
	MOV R4, #2_100 ;R4=100=>binary
	LDR R5,=PIO_SODR ;R5=PIO_SODR
	STR R4, [R5]  ;store R4 in location 0x400E0E30
	BX LR ;return to caller 
	
LEDOff_1
	MOV R4, #2_1 ;R4=1=>binary
	LDR R5,=PIO_CODR ;R5=PIO_CODR
	STR R4, [R5] ;store R4 in location 0x400E0E34
	BX LR ;return to caller 
	
LEDOff_2
	MOV R4, #2_10 ;R4=10=>binary
	LDR R5,=PIO_CODR ;R5=PIO_CODR
	STR R4, [R5] ;store R4 in location 0x400E0E34
	BX LR ;return to caller 

LEDOff_3
	MOV R4, #2_100 ;R4=100=>binary
	LDR R5,=PIO_CODR ;R5=PIO_CODR
	STR R4, [R5] ;store R4 in location 0x400E0E34
	BX LR ;return to caller 
	
Delay
	MOV R4, #0 ;R4=0
	LDR R5, =0x00C0000 ;R5 =0x00C0000 
	
LoopDelay
	ADD R4,R4,#1 ;R4=R4+1
	CMP R4,R5 ;compare R4 with R5
	BNE LoopDelay 
	BX LR ;return to caller 
	
	END