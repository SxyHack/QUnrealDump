
.code

CallFunc PROC
mov         qword ptr [rsp+8],rcx
push        rbp
push        rdi
sub         rsp,0E8h
lea         rbp, [rsp+20h]
; lea         rcx, [7FF6453E3029h]
call        rcx
cdqe
lea         rsp,[rbp+0C8h] 
pop         rdi
pop         rbp
ret
CallFunc ENDP

end