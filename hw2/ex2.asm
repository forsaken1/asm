.686
.model flat, stdcall

include \masm32\include\masm32rt.inc

.data
    fi      db  '%d', 0
    fo      db  '%d', 0
    nextstr db  13, 10
    msg     db  'Enter number:', 13, 10, 0
    v       db  100 dup (0)
    p       db  100 dup (0)
    used    db  100 dup (0)
    n       db  ?

.code
start:
    invoke  crt_printf, addr msg
    invoke  crt_scanf, addr fi, addr [n]
    
    mov     eax, 0

cycle:
    mov     dword ptr v[eax], eax
    inc     eax
    cmp     eax, dword ptr [n]
    jne     cycle    

    push    0
    call    lex
    
    inkey
    exit

lex PROC
    mov     ebx, 0
    pop     ebx
    cmp     ebx, dword ptr [n]
    jne     IfFalse

    mov     ecx, 0

Print:
    mov     eax, 0
    mov     eax, dword ptr p[ecx]
    mov     eax, dword ptr v[eax]
    add     eax, 1
    invoke  crt_printf, addr fo, eax
    inc     ecx
    cmp     ecx, dword ptr [n]
    jne     Print

    invoke  crt_printf, addr nextstr
    ret

IfFalse:
    mov     ecx, 0
    
ForBegin:
    cmp     ecx, dword ptr [n]
    je      ForEnd

    mov     eax, 0
    mov     eax, dword ptr used[ecx]
    cmp     eax, 1
    je      UsedTrue

    mov     used[ecx], 1
    mov     dword ptr p[ebx], ecx
    mov     edx, 0
    mov     edx, ebx
    add     edx, 1
    push    edx
    call    lex
    mov     p[ebx], 0
    mov     used[ecx], 0

UsedTrue:

    inc     ecx
    jmp     ForBegin

ForEnd:
    
    ret

lex ENDP

end start
