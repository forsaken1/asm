.686
.model flat, stdcall

include \masm32\include\masm32rt.inc

.data
    i               db 0
    r               db 0
    l               db 0
    right           db 0
    left            db 0
    string          db 'worldwideweb'
    fi              db '%s', 0
    fo              db '%d', 13, 10, 0
    fostr           db '%s', 13, 10, 0
    
.code
start:
    mov     edx, 0
    mov     dl, sizeof string 
    
WhileBegin:
    cmp     [r], dl
    jge     WhileEnd

    mov     eax, 0
    mov     al, [l]
    mov     [i], al
    
ForBegin:
    mov     eax, 0
    mov     al, [i]
    cmp     al, [r]
    jge     ForEnd

    mov     eax, 0
    mov     ebx, 0
    mov     ecx, 0
    mov     al, [i]
    mov     bl, [r]
    mov     cl, string[ebx]
    cmp     cl, string[eax]
    jne     ForFalse

    mov     ecx, 0
    mov     cl, [i]
    add     cl, 1
    mov     [l], cl
    mov     [r], cl
    jmp     ForEnd
    
ForFalse:
    inc     i
    jmp     ForBegin
    
ForEnd:
    mov     eax, 0
    mov     al, [right]
    sub     al, [left]
    mov     ah, [r]
    sub     ah, [l]
    cmp     al, ah
    jge     IfFalse

    mov     eax, 0
    mov     al, [r]
    mov     [right], al
    mov     al, [l]
    mov     [left], al
    
IfFalse:
    inc     r
    jmp     WhileBegin
    
WhileEnd:    
    mov     eax, 0
    mov     al, [right]
    sub     al, [left]
    add     al, 1
    
    invoke crt_printf, addr fo, eax
    inkey
    exit

end start
