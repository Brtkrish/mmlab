DATA SEGMENT
    ARRAY      DW 0001H, 0002H, 0003H, 0004H, 0005H
    COUNT      DW 05H
    EVEN_COUNT DW 0
    ODD_COUNT  DW 0
    MSG1       DB 'Even count = $'
    MSG2       DB 0DH,0AH,'Odd count = $'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, @DATA
    MOV DS, AX

    LEA SI, ARRAY
    MOV CX, COUNT
    MOV BX, 0
    MOV DX, 0

LOOP_START:
    MOV AX, [SI]
    TEST AX, 0001H
    JZ EVEN_NUM

    INC DX
    JMP NEXT_NUM

EVEN_NUM:
    INC BX

NEXT_NUM:
    ADD SI, 2
    LOOP LOOP_START

    MOV EVEN_COUNT, BX
    MOV ODD_COUNT, DX

    LEA DX, MSG1
    MOV AH, 09H
    INT 21H

    MOV AX, EVEN_COUNT
    ADD AL, 30H
    MOV DL, AL
    MOV AH, 02H
    INT 21H

    LEA DX, MSG2
    MOV AH, 09H
    INT 21H

    MOV AX, ODD_COUNT
    ADD AL, 30H
    MOV DL, AL
    MOV AH, 02H
    INT 21H

    MOV AH, 4CH
    INT 21H
CODE ENDS
END START
