.text
.global sirena
.extern velocidad
.extern disp_binary
.extern leds
.extern retardo
.extern setup_nonblocking_input

sirena:
    push {lr} @PUSH {R4, R5, R6, R7, LR}

    bl setup_nonblocking_input

    ldr r1, =tabla
    mov r2, #1
    mov r3, #4

while_loop:
    cmp r2, #0
    beq exit_loop

    mov r4, #0

for_loop:
    ldrb r5, [r1, r4]

    bl disp_binary
    bl leds

    ldr r0, =speed
    ldr r0, [r0]
    bl retardo

    ldr r0, =speed
    bl velocidad
    cmp r0, #0
    beq exit_loop

    add r4, r4, #1
    cmp r4, r3
    blt for_loop

    b while_loop

exit_loop:
    pop {lr}  @{R4, R5, R6, R7, PC} sin el bx lr
    bx lr

.section .data
tabla:
    .byte 0xF0, 0x0F, 0xCC, 0x33

.global speed
speed:
    .word 100000000
