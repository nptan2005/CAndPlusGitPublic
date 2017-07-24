.model small
.data
.code

public _event_handler

extrn _event_processor:near

eactive db 0

_event_handler PROC FAR
  push bp
  mov bp,sp
  sub sp, 8

  push ds
  push ax
  mov ax, DGROUP
  mov ds, ax

  cmp eactive, 0
  jne norecurse

  mov eactive, 1

  pop ax
  push dx
  push cx
  push bx
  push ax

  call _event_processor

  add sp, 8

  mov eactive, 0
  jmp normend

norecurse:
  pop ax

normend:
  pop ds
  mov sp, bp
  pop bp

  ret
_event_handler ENDP

END