.global sirena

sirena:
        PUSH {R4, R5, R6, R7, LR}    
        LDR R0, =str_sirena          
        BL printf                    

        BL setup_nonblocking_input   

        MOV R4, #1                   

        LDR R5, =tabla               
main_loop:
        CMP R4, #1                   
        BNE exit_sirena              

        MOV R7, #4                  

loop:
        LDRB R6, [R5], #1            
        MOV R0, R6                   
        BL leds                      
        MOV R0, R6                   
        BL disp_binary               

        MOV R0, R1                   
        BL retardo                   

        MOV R0, R1                  
        BL velocidad                
        MOV R4, R0                   

        CMP R4, #0                   
        BEQ exit_sirena            

        SUBS R7, R7, #1           
        BNE loop                 

        B main_loop        

exit_sirena:
        POP {R4, R5, R6, R7, PC}     

.data

str_sirena:
    .asciz "Sirena...\n"

tabla:
    .byte 0xF0
    .byte 0x0F
    .byte 0xCC
    .byte 0x33
