.text
.global sirena

semaforo:
    mov r0, =speed
    mov r1, 0xC0
    mov r2, #0


for_loop:

    cmp r2, #0      
    blt final_pattern
    
    bl disp_binary

    bl retardo
    
    lsr r1, r1, #2     # Realizar un corrimiento a la derecha de 2 bits

    subs r2, r2, #1    # Decrementar r2

    b for_loop

final_pattern:
    mov r1, #0xFF      # Valor para ********
    mov r0, r1         # Mover el valor de r1 a r0
    bl disp_binary     # Llamar a disp_binary

    ldr r0, =speed     # Cargar la dirección de speed
    ldr r0, [r0]       # Cargar el valor de speed en r0
    bl retardo         # Llamar a retardo

    mov r1, #0x00      # Valor para --------
    mov r0, r1         # Mover el valor de r1 a r0
    bl disp_binary     # Llamar a disp_binary

    ldr r0, =speed     # Cargar la dirección de speed
    ldr r0, [r0]       # Cargar el valor de speed en r0
    bl retardo         # Llamar a retardo

    bx lr              # Retornar de la función      

.global disp_binary
.global retardo