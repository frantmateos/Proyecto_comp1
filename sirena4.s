.text 
.global sirena
.extern velocidad
.extern disp_binary
.extern leds
.extern retardo
.extern setup_nonblocking_input

sirena:
    PUSH {R4, R5, R6, LR}
    BL setup_nonblocking_input
    MOV R4, #4
    MOV R2,#1

while_loop:
    LDR R5, =tabla
    MOV R7,#0
    CMP R2, #0
    BEQ exit_loop



for_loop:
    LDRB R6, [R5,R7]
    ADD R7,R7,#1

    MOV R0, R6
    BL disp_binary

    MVN R0, R6 
    BL leds 

    LDR R0, =speed
    LDR R6, [R0]
    MOV R0, R6
    BL retardo

    LDR R0, =speed
    BL velocidad       
    CMP R0, #0
    BEQ exit_loop 

    SUBS R4, R4, #1 
    BNE for_loop

    MOV R4,#4

    BL while_loop

exit_loop:
    POP {R4, R5, R6, PC}

.data 

tabla:
    .byte 0xF0 
    .byte 0x0F 
    .byte 0xCC
    .byte 0x33

.global speed
speed:
    .word 100000000
