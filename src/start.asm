	;; ****************************************
	;; Beginning of module
	;; BANKED: checked
	.title	"Runtime"
	.module	Runtime
	.area	_HEADER (ABS)

	;; Standard header for the GB
	.org	0x00
	RET			; Empty function (default for interrupts)

	.org	0x10
	.byte	0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01
	.byte	0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80

	;; Interrupt vectors
	.org	0x40		; VBL
.int_VBL:
	jp .vbl
	RETI

	.org	0x48		; LCD
.int_LCD:
	RETI

	.org	0x50		; TIM
.int_TIM:
	RETI

	.org	0x58		; SIO
.int_SIO:
	RETI

	.org	0x60		; JOY
.int_JOY:
	RETI

	;; GameBoy Header

	.org	0x100
.header:
	NOP
	JP	0x150
	.byte	0xCE,0xED,0x66,0x66
	.byte	0xCC,0x0D,0x00,0x0B
	.byte	0x03,0x73,0x00,0x83
	.byte	0x00,0x0C,0x00,0x0D
	.byte	0x00,0x08,0x11,0x1F
	.byte	0x88,0x89,0x00,0x0E
	.byte	0xDC,0xCC,0x6E,0xE6
	.byte	0xDD,0xDD,0xD9,0x99
	.byte	0xBB,0xBB,0x67,0x63
	.byte	0x6E,0x0E,0xEC,0xCC
	.byte	0xDD,0xDC,0x99,0x9F
	.byte	0xBB,0xB9,0x33,0x3E

	;; Title of the game
	.org	0x134
	.asciz	"Title"

	.org	0x144
	.byte	0,0,0

	;; Cartridge type is ROM only
	.org	0x147
	.byte	0

	;; ROM size is 32kB
	.org	0x148
	.byte	0

	;; RAM size is 0kB
	.org	0x149
	.byte	0

	;; Maker ID
	.org	0x14A
	.byte	0x00,0x00

	;; Version number
	.org	0x14C
	.byte	0x01

	;; Complement check
	.org	0x14D
	.byte	0x00

	;; Checksum
	.org	0x14E
	.byte	0x00,0x00

	;; ****************************************
	.org	0x150
.code_start:
	;; Beginning of the code
	DI			; Disable interrupts
	
	;; Initialize the stack
	LD	SP,#0xFFFF
	
	call _main

	;; Ordering of segments for the linker
	;; Code that really needs to be in bank 0
	.area	_HOME
	;; Similar to _HOME
	.area	_BASE
	;; Code
	.area	_CODE
	
.vbl:
	push af
	push hl
	push bc
	
	; load SCX
	ld a, (#_worldpos)
	ld (#0xFF43), a
	
	call #0xFF80
	
	ld a, #1
	ld (#_vsync), a
	
	pop bc
	pop hl
	pop af
	
	reti
	
.globl _oamdma
_oamdma:
	ld	a, #0xC0
	ld  (#0xFF46), a		; start DMA transfer, a=start address/100h
	ld  a, #0x28			; delay...
.wait:					; total 5x40 cycles, approx 200ms
	dec a				;   1 cycle
	jr  nz, .wait		;   4 cycles
	ret
oamdmaend:

.globl _enable_ints
_enable_ints:
	ei
	ret

	;; Constant data
	.area	_LIT
	;; Constant data used to init _DATA
	.area	_GSINIT
	.area	_GSINITTAIL
	.area	_GSFINAL
	;; Initialised in ram data
	.area	_DATA
	;; Uninitialised ram data
	.area	_BSS
	;; For malloc
	.area	_HEAP

	.area	_BSS