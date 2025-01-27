#ifndef PONGDEF_INC
#define PONGDEF_INC

; --- Constants ---
.equ PADELWIDTH = 2
.equ PADELHEIGHT = 20
.equ BALLWIDTH = 2
.equ PADELAREA = PADELWIDTH * PADELHEIGHT
.equ BALLAREA = BALLWIDTH * BALLWIDTH

.equ WIDTH = 0xA0
.equ HEIGHT = 0x80
.equ AREA = WIDTH*HEIGHT
.equ REFRESHRATE = 20 ; FPS
.equ PADEL_INCREMENTER = 6
.equ BALL_INCREMENTER = 4
.equ BALL_INIT_X = 4

.equ FIXED = 0 ; For padel state
.equ UP = 1
.equ DOWN = 2

; --- Main variables ---
.equ P1POSX = 0x100		   ; Padel 1 position x 
.equ P1POSY = 0x101		   ; Padel 1 position y 
 
.equ P2POSX = 0x102	       ; Padel 2 position x 
.equ P2POSY = 0x103	       ; Padel 2 position y 

.equ BPOSX = 0x104		   ; Ball position x 
.equ BPOSY = 0x105	       ; Ball position y 

.equ BVELX = 0x106		   ; Ball velocity x
.equ BVELY = 0x107		   ; Ball velocity y

.equ ARG0 = 0x108		   ; Arguments for functions
.equ ARG1 = 0x109
.equ ARG2 = 0x10A
.equ ARG3 = 0x10B
.equ ARG4 = 0x10C
.equ ARG5 = 0x10D
.equ ARG6 = 0x10E

.equ P1SCORE = 0x10F	   ; Player 1 Score
.equ P2SCORE = 0x110	   ; Player 2 score

;.equ P1STATE = 0x111	   ; 0 not moving 1 moving UP 2 moving DOWN
;.equ P2STATE = 0x112 

.equ P1VEL = 0x113	   ; PADDLE 1 Velocity
.equ P2VEL = 0x114	   ; PADDLE 2 Velocity


; --- For LCD ST7735R ---
.equ	SWRESET = 0x01 ; Software reset
.equ	SLPOUT = 0x11  ; Sleep out & booster on
.equ	DISPON = 0x29  ; Display on
.equ	CASET = 0x2A   ; Column Address Set
.equ	RASET = 0x2B   ; Rolumn Address Set
.equ	RAMWR = 0x2C   ; Memory write
.equ	MADCTL = 0x36  ; Memory Data Access Control
.equ	WHITE = 0xFF
.equ	BLACK = 0x00

; --- Macros ---
.MACRO INIT_STACK
	LDI R16, HIGH(RAMEND)
	OUT SPH, R16
	LDI R16, LOW(RAMEND)
	OUT SPL, R16
.ENDMACRO

.MACRO INIT_SPI
	LDI R17, 0x2D
	OUT DDRB, R17
	LDI R17, 0x50
	OUT SPCR, R17
.ENDMACRO

.MACRO INIT_LCD
	CBI PORTB, 0
	LDI R20, SWRESET ; software reset
	CALL TRANSMIT
	CALL DELAY_120ms
	LDI R20, SLPOUT ; sleep out
	CALL TRANSMIT
	CALL DELAY_120ms
	LDI R20, DISPON ; display on
	CALL TRANSMIT
	LDI R20, MADCTL ; Memory Data Access Control
	CALL TRANSMIT
	SBI PORTB, 0
	LDI R20, 0b1110000
	CALL TRANSMIT
.ENDMACRO

.MACRO INIT_ARGS
	LDI R20, @0
	STS ARG0, R20
	LDI R20, @1
	STS ARG1, R20
	LDI R20, @2
	STS ARG2, R20
	LDI R20, @3
	STS ARG3, R20
	LDI R20, @4
	STS ARG4, R20
	LDI R20, @5
	STS ARG5, R20
	LDI R20, @6
	STS ARG6, R20
.ENDMACRO

.MACRO POS_INIT
; Position Reset for ball and padel
	LDI R20, 0
	STS P1POSX, R20
	LDI R20, (HEIGHT/2)-(PADELHEIGHT/2)
	STS P1POSY, R20
	LDI R20, WIDTH-PADELWIDTH
	STS P2POSX, R20
	LDI R20, (HEIGHT/2)-(PADELHEIGHT/2)
	STS P2POSY, R20
	LDI R20, 0
	STS P1VEL, R20
	LDI R20, 0
	STS P2VEL, R20
	LDI R20, BALL_INIT_X
	STS BPOSX, R20
	LDI R20, (HEIGHT/2)
	STS BPOSY, R20
	LDI R20, BALL_INCREMENTER
	STS BVELX, R20
	LDI R20, 2
	STS BVELY, R20
	LDI R20, 0
	STS P1SCORE, R20
	LDI R20, 0
	STS P2SCORE, R20
.ENDMACRO

.MACRO INIT_TIMER
	LDI R20, HIGH(-((16*1000000*REFRESHRATE)/256))
	STS TCNT1H, R20
	LDI R20, LOW(-((16*1000000*REFRESHRATE)/256))
	STS TCNT1L, R20
	LDI R20, 0
	STS TCCR1A, R20
	LDI R20, 4				; Fclk / 256
	STS TCCR1B, R20
	LDI R20, (1<<TOIE1)     ; Enable interrupt
	STS TIMSK1, R20
.ENDMACRO
#endif
