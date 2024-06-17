.global semaforo

semaforo:
        PUSH {R4, R5, R6, LR}
        LDR R0, =str_semaforo
        BL printf
        BL setup_nonblocking_input
        MOV R4, #1
        MOV R5, #0xC0

main_loop:
        CMP R4, #1
        BNE exit_semaforo
        MOV R6, #4

loop:
        MOV R0, R5
        BL leds
        BL disp_binary
        MOV R0, R1
        BL retardo
        ASR R5, R5, #2
        BL velocidad
        MOV R4, R0
        CMP R4, #0
        BEQ exit_semaforo
        SUBS R6, R6, #1
        BNE loop

        MOV R5, #0xFF
        BL leds
        BL disp_binary
        MOV R5, #0x00
        BL leds
        BL disp_binary
        BL velocidad
        MOV R4, R0
        CMP R4, #0
        BEQ exit_semaforo
        MOV R5, #0xC0
        B main_loop

exit_semaforo:
        POP {R4, R5, R6, PC}

.data

str_semaforo:
    .asciz "Semaforo...\n"
