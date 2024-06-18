.text 
.global semaforo
.extern velocidad
.extern disp_binary
.extern leds
.extern retardo
.extern setup_nonblocking_input

semaforo:
    PUSH {R5, R6,R7, LR}
    BL setup_nonblocking_input
    MOV R2,#1

while_loop:
    MOV R5, #0xC0
    MOV R7, #4

    CMP R2, #0
    BEQ exit_loop

for_loop:
    MOV R0, R5
    BL disp_binary

    MVN R0, R5
    BL leds 

    LDR R0,=speed
    LDR R6,[R0]
    MOV R0, R6 
    BL retardo

    MOV R0, R5
    LSR R5,R5,#2

    LDR R0, =speed
    BL velocidad       
    CMP R0, #0
    BEQ exit_loop 

    SUBS R7, R7, #1
    BNE for_loop

    LDR R0,=speed
    LDR R6,[R0]
    MOV R0, R6 
    BL retardo

    BL next

next:
    MOV R5, #0XFF

    MOV R0, R5
    BL disp_binary

    MOV R0,R5
    BL leds

    LDR R0, =speed
    LDR R6, [R0]
    MOV R0, R6
    BL retardo

    LDR R0, =speed
    BL velocidad       
    CMP R0, #0
    BEQ exit_loop 

    MOV R5, #0X00
    
    MOV R0,R5
    BL disp_binary

    MVN R0,R5 
    BL leds

    LDR R0, =speed
    BL velocidad       
    CMP R0, #0
    BEQ exit_loop 

    BL while_loop

exit_loop:
    POP {R5, R6, R7, PC}


