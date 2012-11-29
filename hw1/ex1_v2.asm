.686
.model flat, stdcall

include \masm32\include\masm32rt.inc

.data
    r		db   0
    l		db   0
    Right   db   0
    Left	db   0
    n       db   0
    string	db   100 dup(0)
    letter	db   256 dup(0)
    fi      db   '%s', 0
    fo      db   '%d', 13, 10, 0
    msg     db   'Enter string:', 13, 10, 0

.code
start:
    invoke  crt_printf, addr msg
    invoke  crt_scanf, addr fi, addr string
    mov     edx, 0

cycle:
    inc     edx
    cmp     string[edx], 0
    jnz     cycle

WhileBegin:
    cmp     [r], dl
    jge     WhileEnd

    mov     eax, 0
    mov     ebx, 0
    mov     al, [r]
    mov     bl, string[eax]
    cmp     letter[ebx], 0
    je      IfEnd
    
    mov     al, [l]
    mov     bl, string[eax]
    mov     letter[ebx], 0
    inc     l
    jmp     WhileBegin

IfEnd:
    mov     al, [r]
    mov     bl, string[eax]
    mov     letter[ebx], 1

    mov     al, [Right]
    sub     al, [Left]
    mov     bl, [r]
    sub     bl, [l]
    cmp     al, bl
    jge     SecondIfEnd

    mov     al, [r]
    mov     bl, [l]
    mov     [Right], al
    mov     [Left], bl

SecondIfEnd:
    inc     r
    jmp     WhileBegin
    
WhileEnd:
    mov     al, [Right]
    sub     al, [Left]
    add     al, 1
    
    invoke  crt_printf, addr fo, eax
    inkey
    exit
    
end start