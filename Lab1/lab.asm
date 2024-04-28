default rel

global Y: function
global factorial: function
global S: function

extern pow                                             
extern sin                                              

SECTION .text   align=1 exec                            

Y:      ; Function begin
        endbr64                                        
        push    rbp                                    
        mov     rbp, rsp                                
        sub     rsp, 16                                
        movss   dword [rbp-4], xmm0                    
        fld     dword [rbp-4]                          
        fstp    qword [rbp-10H]                         
        movsd   xmm0, qword [rbp-10H]                   
        call    sin                                     
        movsd   qword [rbp-10H], xmm0                   
        fld     qword [rbp-10H]                         
        fstp    dword [rbp-10H]                         
        movss   xmm0, dword [rbp-10H]                   
        leave                                           
        ret                                            
; Y End of function

factorial:; Function begin
        endbr64                                        
        push    rbp                                     
        mov     rbp, rsp                               
        mov     dword [rbp-14], edi                    
        mov     dword [rbp-8], 1                       
        mov     dword [rbp-4], 1                      
        jmp     fact_loop                                 

fact_mul:  
        mov     eax, dword [rbp-8]                     
        imul    eax, dword [rbp-4]                    
        mov     dword [rbp-8], eax                    
        add     dword [rbp-4], 1                       
fact_loop:  
        mov     eax, dword [rbp-4]                    
        cmp     eax, dword [rbp-14]                    
        jle     fact_mul                                  
        mov     eax, dword [rbp-8]                     
        pop     rbp                                     
        ret                                            
; factorial End of function

S:      ; Function begin
        endbr64                                        
        push    rbp                                   
        mov     rbp, rsp                              
        sub     rsp, 48                                 
        movss   dword [rbp-14], xmm0                   
        mov     dword [rbp-18], edi                   
        fldz                                            
        fstp    dword [rbp-8]                          
        mov     dword [rbp-4], 0                      
        jmp     s_loop                                   

s_calc:  
        fild    dword [rbp-4]                         
        fstp    qword [rbp-32]                         
        movsd   xmm1, qword [rbp-32]                  
        mov     rax, qword [rel end]                  
        movq    xmm0, rax                              
        call    pow                                     
        movsd   qword [rbp-32], xmm0                
        mov     eax, dword [rbp-4]                     
        add     eax, eax                                
        add     eax, 1                                 
        mov     dword [rbp-28], eax                    
        fild    dword [rbp-28]                        
        fstp    qword [rbp-28]                        
        fld     dword [rbp-14]                        
        fstp    qword [rbp-30H]                         
        movsd   xmm0, qword [rbp-30H]                   
        movsd   xmm1, qword [rbp-28]                   
        call    pow                                     
        movsd   qword [rbp-28], xmm0                  
        fld     qword [rbp-32]                         
        fmul    qword [rbp-28]                         
        fstp    qword [rbp-32]                        
        mov     eax, dword [rbp-4]                     
        add     eax, eax                              
        add     eax, 1                                 
        mov     edi, eax                                
        call    factorial                              
        mov     dword [rbp-28], eax                    
        fild    dword [rbp-28]                         
        fld     qword [rbp-32]                        
        fdivrp  st1, st(0)                             
        fld     dword [rbp-8]                          
        faddp   st1, st(0)                              
        fstp    dword [rbp-8]                          
        add     dword [rbp-4], 1                       
s_loop:  mov     eax, dword [rbp-4]                     
        cmp     eax, dword [rbp-18]                    
        jle     s_calc                                   
        fld     dword [rbp-8]                          
        fstp    dword [rbp-32]                         
        movss   xmm0, dword [rbp-32]                   
        leave                                           
        ret                                            
; S End of function


SECTION .data   align=1 noexec                          ; section number 2, data


SECTION .bss    align=1 noexec                          ; section number 3, bss


SECTION .rodata align=8 noexec                          ; section number 4, const

end:                                                 
        dq 0BFF0000000000000H                           
