.text
.global sirena
.export velocidad
.export disp_binary
.export leds
.export retardo
.export setup_nonblocking_input

sirena:
    bl setup_nonblocking_input

    ldr r1, =tabla
    mov r2, #1   
    mov r3, #4   

while_loop:
    cmp r2, #0
    beq exit_loop
    
    mov r4, #0
    ldrb r5, [r1, r4]      

    for_loop:
        bl leds
        bl disp_binary

        ldr r0, =speed
        ldr r0, [r0]
        bl retardo

        ldr
        bl velocidad

        add r4, r4, #1

        cmp r4, r3
    
        blt for_loop        

b while_loop 

exit_loop:
    pop {lr} 
    bx lr

.section .data
tabla:
    .byte 0xF0, 0x0F, 0xCC, 0x33

.global speed
speed:
    .word 100000000
