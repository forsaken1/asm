.686
.model flat, stdcall

include \masm32\include\masm32rt.inc

.data
    fi      db  '%d', 0
    fo      db  '%d', 0
    fon     db  '%d', 13, 10, 0
    nextstr db  13, 10
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

comment *
    mov     edx, 0
    mov     edx, [esp]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+4]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+8]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+12]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+16]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+20]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+24]
    invoke  crt_printf, addr fon, edx    
    
    inkey *
    
    jl      IfFalse

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
    jge     ForEnd

    mov     eax, 0
    mov     al, used[ecx]
    cmp     al, 1
    je      UsedTrue

    mov     used[ecx], 1
    mov     p[ebx], cl
    add     bl, 1
    push    ecx
    push    ebx
    call    lex
    mov     ebx, 0
    mov     ecx, 0

    ;comment *
    mov     edx, 0
    mov     edx, [esp]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+4]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+8]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+12]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+16]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+20]
    invoke  crt_printf, addr fon, edx

    mov     edx, 0
    mov     edx, [esp+24]
    invoke  crt_printf, addr fon, edx    
    
    inkey 

    pop     ebx
    pop     ecx
    mov     p[ebx], 0
    mov     used[ecx], 0

UsedTrue:
    inc     i
    jmp     ForBegin

ForEnd:
    ret    

lex endp

end start
