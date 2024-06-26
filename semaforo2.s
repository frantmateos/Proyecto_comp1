.text 
.global semaforo
.extern velocidad
.extern disp_binary
.extern leds
.extern retardo
.extern setup_nonblocking_input

semaforo:
    PUSH {R5, R6, LR}
    BL setup_nonblocking_input
    MOV R2, #1

while_loop:
    MOV R5, #0xC0
    MOV R6, #4

    CMP R2, #0
    BEQ exit_loop

for_loop:
    MOV R0, R5
    BL disp_binary

    MVN R0, R5
    BL leds 

    LDR R0, =speed
    LDR R6, [R0]
    MOV R0, R6 
    BL retardo

    ASR R5, R5, #2 

    LDR R0, =speed
    BL velocidad       
    CMP R0, #0
    BEQ exit_loop 

    SUBS R6, R6, #1
    BNE for_loop

    BL next

next:
    MOV R5, #0xFF

    MOV R0, R5
    BL disp_binary

    MVN R0, R5
    BL leds

    MOV R5, #0x00
    
    MOV R0, R5
    BL disp_binary

    MVN R0, R5 
    BL leds

    BL while_loop

exit_loop:
    POP {R5, R6, PC}
