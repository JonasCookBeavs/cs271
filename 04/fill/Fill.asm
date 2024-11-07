// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.
@SCREEN
D=A
(LOOP)
//Setup
@16
M=D
D=M
A=M

//Check key press
@KBD
D=M
@4
M=D
@BLACK
D;JGT
@WHITE
D;JEQ

//Black loop
(BLACK)
@16
D=M
A=D
M=-1
@16
M=M+1
D=M
@LOOP_CONT
0;JMP

//White loop
(WHITE)
//Check if @16 is negative
@16
D=M
@RESET
D;JLT

//Continue White loop
@16
D=M
A=D
M=0
@16
M=M-1
D=M
@LOOP_CONT
0;JMP

(LOOP_CONT)
//Check for fucked @16 value
@16
D=M
@RESET
D;JLT

@SCREEN
D=A
@16
D=D|M
@RESET
D;JEQ

//Jump back to top of loop
@LOOP
0;JMP

(RESET)
//Reset @16 value
@SCREEN
D=A
@16
M=D
@LOOP
0;JMP

(INF_LOOP)
@INF_LOOP
0;JMP