org 7c00h

metka1:
	xor	ax, ax
	mov sp, ax
	mov es, ax
	mov	ss, ax

	mov ah, 02h
	mov al, 01h
	mov ch, 00h
	mov cl, 02h
	mov dh, 00h
	mov bx, metka2
	int 13h

	mov al, 01h
	mov bl, 01h
	mov bh, 00h

	cmp ah, 00h
	jne read_error

	mov cx, metka3-message
        mov si, metka2
        jmp print

read_error:
        mov cx, metka2-message_error
        mov si, message_error

print:

        xor di, di
        mov ax, 0xb800
        push ax
        pop es
        mov ah, 2
cycle:
        lodsb
        cmp al,0
        je fin
        stosw
        jmp cycle
fin: 
	cli
	hlt
	
message_error db "Error!",00h
metka2:
db 510 - (metka2 - metka1) dup(0)
db 55h
db 0aah
message db "good",00h
metka3:
db 1024 - (metka3 - message) dup(0)