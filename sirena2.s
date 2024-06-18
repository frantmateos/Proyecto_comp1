.text 
.global sirena 
sirena:
    PUSH {R4, R5, R6, LR}
    MOV R4, #3 
    LDR R5, =tabla 

loop:
    LDRB R6, [R5], #1
    MOV R0, R6
    BL disp_binary
    MVN R0, R6 
    BL leds 
    SUBS R4, R4, #1 
    BNE loop
    POP {R4, R5, R6, PC}

.data 

tabla:
    .byte 0xF0 
    .byte 0x0F 
    .byte 0xCC
    .byte 0x33