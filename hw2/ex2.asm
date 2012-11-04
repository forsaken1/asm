.686
.model flat, stdcall

include \masm32\include\masm32rt.inc

.data
      

.code
start:

    call main
    inkey
    exit

main proc
    

    ret

main endp

end start
