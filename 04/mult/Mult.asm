// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

//// Replace this comment with your code.

@2
M=0
@0
M;JLE
@1
M;JLE
@1
D=M
@MULT_LOOP
M=D
D=0
(MULT_LOOP)
@2
D=M
@0
D=D+M
@MULT_LOOP
M=M-1
@2
M=D
@MULT_LOOP
D=A
@MULT_LOOP
M;JGT
(INF_LOOP)
@INF_LOOP
0;JMP