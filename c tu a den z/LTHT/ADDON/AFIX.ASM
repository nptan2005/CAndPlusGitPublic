
; Some DOS utilities for IBM C
; Only use with the 'Small model'

DGROUP	GROUP	_DATA
_DATA	segment word public 'DATA'
	assume ds:DGROUP
	public	_ALLOCTAB

alc	struc
	d	dw	(?)
	mb	db	(?)
	spc	db	(?)
	nc	dw	(?)
	sss	dw	(?)
alc	ends

_ALLOCTAB	alc	<>	; The ALLOCTAB structure is shared with dfix.c

_DATA	ends

_TEXT	segment byte public 'CODE'
	assume	cs:_TEXT, ds:DGROUP

	public	_defaultdev, _devAlloc
IFNDEF	__TURBOC__
	public	_dosVersion
ENDIF
	public	_rdDevice, _wrDevice

_defaultdev proc	near
	push	bp
	mov	ah,19h
	int	21h
	xor	ah,ah		;clear msb			v1.1
	pop	bp
	ret
_defaultdev endp

_devAlloc proc	near
	push	bp
	push	di
	push	si
	push	ds
	mov	dx, _ALLOCTAB.d
	inc	dl		; A=1,...
	mov	ah,1ch
	int	21h
	mov	ah,ds:[bx]
	pop	ds
	mov	_ALLOCTAB.mb, ah
	mov	_ALLOCTAB.spc, al
	mov	_ALLOCTAB.nc, dx
	mov	_ALLOCTAB.sss, cx
	pop	si
	pop	di
	pop	bp
	ret
_devAlloc endp

IFNDEF __TURBOC__
_dosVersion proc	near
	push	bp
	mov	ah,30h
	int	21h
	pop	bp
	ret
_dosVersion endp
ENDIF

_rdDevice proc	near
	; rdDevice(dev, start_sector, number_of_sectors, buffer_address) 
	push	bp
	mov	bp,sp
	push	di
	push	si
	mov	al,[bp+4]	; device #
	mov	dx,[bp+6]	; logical sector number
	mov	cx,[bp+8]	; no. sectors
	mov	bx,[bp+0ah]	; buffer address
	int	25h
	pop	bx		; remove flags
	jc	err1
	 xor	ax,ax		; return 0 for no error			v1.1
err1:	pop	si
	pop	di
	pop	bp
	ret
_rdDevice endp

_wrDevice proc	near
	; wrDevice(dev, start_sector, number_of_sectors, buffer_address) 
	push	bp
	mov	bp,sp
	push	di
	push	si
	mov	al,[bp+4]	; device #
	mov	dx,[bp+6]	; logical sector number
	mov	cx,[bp+8]	; no. sectors
	mov	bx,[bp+0ah]	; buffer address
	int	26h
	pop	bx		; remove flags
	jc	err2
	 xor	ax,ax		; return 0 for no error			v1.1
err2:	pop	si
	pop	di
	pop	bp
	ret
_wrDevice endp

_TEXT	ends

	end
