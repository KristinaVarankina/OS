	org 7c00h
metka1:
	xor ax,ax
	mov ss,ax
	mov sp,ax
	mov es,ax
	mov ds,sp

	mov ah,2h
	mov al,4h
	mov ch,0h
	mov cl,2h
	mov dh,0h
	mov bx,metka3
	int 13h

	cmp ah,00h
	jne read_error

	cli
	lgdt ptr GDTptr
	lidt ptr IDTptr
	mov	eax,cr0
	or al,1
	mov	cr0,eax
	jmp	8:metka2
metka2:
	sti
	int	10
	jmp	read_okay
read_error:
	mov	al,1h
	mov	bl,1h
	mov	bh,0h
	mov	cx,metka3-error
	mov	bp,error
	mov	ah,13h
	int	10h
read_okay:
	cli
	hlt
another_int:
	push cx
	push dx
	mov cx,msg2-msg1
	mov	dx,msg1
	call 	print
	pop	dx
	pop	cx
	iret
int_10:
	push cx
	push dx
	mov cx,error-msg2
	mov	dx,msg2
	call print
	pop	dx
	pop	cx
	iret
print:
	push ax
	push si
	push di
	push ds
	push es
	mov	ax,8*2
	mov	es,ax
	xor	di,di
	mov	ds,di
	mov	si,dx
	mov	al,10h
cycle:
	movsb
	stosb
	loop cycle
	pop	es
	pop	ds
	pop	di
	pop	si
	pop	ax
	ret	
GDTptr:
dw GDTlen-1
dd GDT
IDTptr:
dd metka3
dw 256*8
GDT:
db 8 dup (0)
db 0xFF, 0xFF, 0x00, 0x00, 0x00, 10011000b, 00000000b, 0x00
db 0x00, 0x10, 0x00, 0x80, 0x0B, 10010010b, 00000000b, 0x00
db 0xFF, 0xFF, 0x00, 0x00, 0x00, 10010010b, 00001111b, 0x00
GDTlen = metka1-GDT

msg1 db 'another_int'
msg2 db 'int_10'	
error db "error!"
metka3:
db 510-(metka3-metka1) dup(0)
db 55h,0aah
IDT:
	repeat 10
dw another_int, 8
db 0, 10000110b
dw 0
	end repeat

dw int_10, 8
db 0, 10000110b
dw 0

	repeat 256 - (10+1)
dw another_int, 8
db 0, 10000110b
dw 0
	end repeat