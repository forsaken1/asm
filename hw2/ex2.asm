.686
.model flat, stdcall

include \masm32\include\masm32rt.inc

.data
    fi      db  '%d', 0
    fo      db  '%d', 0
    fon     db  '%d', 13, 10, 0
    nextstr db  13, 10, 0
    msg     db  'Enter number:', 13, 10, 0
    v       db  100 dup (0)
    p       db  100 dup (0)
    used    db  100 dup (0)
    i       db  0

.data?
    n       db  ?

.code
start:
    invoke  crt_printf, addr msg
    invoke  crt_scanf, addr fi, addr n
    
Cycle:
    mov     eax, 0
    mov     al, [i]
    cmp     al, [n]
    je      EndCycle
    
    mov     v[eax], al
    inc     i
    jmp     Cycle

EndCycle:
    push    dword ptr 0
    call    lex
    
    inkey
    exit

lex proc
    mov     ebx, 0
    mov     ebx, [esp+4]
    cmp     bl, [n]
    jne     IfFalse

    mov     [i], 0

Print:
    mov     ecx, 0
    mov     cl, [i]
    cmp     cl, [n]
    je      PrintEnd

    mov     eax, 0
    mov     al, p[ecx]
    mov     al, v[eax]
    add     al, 1
    invoke  crt_printf, addr fo, eax
    inc     i
    jmp     Print

PrintEnd:
    invoke  crt_printf, addr nextstr
    jmp     ForEnd

IfFalse:
    mov     [i], 0
    
ForBegin:
    mov     ecx, 0
    mov     cl, [i]
    cmp     cl, [n]
    je      ForEnd
   
    cmp     used[ecx], 1
    je      UsedTrue

    mov     used[ecx], 1
    mov     p[ebx], cl
    add     bl, 1
    push    ecx
    push    ebx
    call    lex
    mov     ebx, 0
    mov     ecx, 0    
    pop     ebx
    pop     ecx
    mov     [i], cl
    ;invoke  crt_printf, addr fo, i
    ;inkey
    mov     p[ebx], 0
    mov     used[ecx], 0

UsedTrue:
    inc     i
    jmp     ForBegin

ForEnd:
    ret    

lex endp

end start
