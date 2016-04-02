-------- PROJECT GENERATOR --------
PROJECT NAME :	SemiAutoMahjong
PROJECT DIRECTORY :	D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong
CPU SERIES :	SH-2
CPU TYPE :	SH7125
TOOLCHAIN NAME :	Renesas SuperH RISC engine Standard Toolchain
TOOLCHAIN VERSION :	9.4.3.0
GENERATION FILES :
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\dbsct.c
        Setting of B,R Section
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\typedefine.h
        Aliases of Integer Type
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\sbrk.c
        Program of sbrk
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\iodefine.h
        Definition of I/O Register
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\intprg.c
        Interrupt Program
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\vecttbl.c
        Initialize of Vector Table
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\vect.h
        Definition of Vector
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\resetprg.c
        Reset Program
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\SemiAutoMahjong.c
        Main Program
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\sbrk.h
        Header file of sbrk file
    D:\Users\yuhei\Documents\SemiAutoMahjong\SemiAutoMahjong\stacksct.h
        Setting of Stack area
START ADDRESS OF SECTION :
 H'000000000	DVECTTBL,DINTTBL,PIntPRG
 H'000000800	PResetPRG
 H'000001000	P,C,C$BSEC,C$DSEC,D
 H'0FFFFA000	B,R
 H'0FFFFBC00	S

* When the user program is executed,
* the interrupt mask has been masked.
* 
* Program start H'1000.
* RAM start H'FFFFA000.

DATE & TIME : 2016/04/03 4:17:14
