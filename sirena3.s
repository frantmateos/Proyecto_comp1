.text
.global sirena
.extern velocidad
.extern disp_binary
.extern leds
.extern retardo
.extern setup_nonblocking_input
.extern speed 

sirena:
    push {lr} 

    bl setup_nonblocking_input

    ldr r1, =tabla
    mov r2, #1
    mov r3, #4

while_loop:
    cmp r2, #0
    beq exit_loop

    mov r4, #0

for_loop:
    ldrb r5, [r1],#1
    mov R0,R5
    bl disp_binary
    mvn R0,R5
    bl leds

    ldr r0, =speed
    ldr r6, [r0]       @ Load the value of speed into r6
    mov r0, r6
    bl retardo

    ldr r0, =speed
    bl velocidad       @ Call velocidad with address of speed
    cmp r0, #0
    beq exit_loop 

    subs r4, r4, #1
    BNE for_loop

    b while_loop

exit_loop:
    pop {lr} 
    bx lr

.data
tabla:
    .byte 0xF0 
    .byte 0x0F 
    .byte 0xCC
    .byte 0x33

