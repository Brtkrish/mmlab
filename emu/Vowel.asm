DATA SEGMENT
    STR1 DB 100 DUP('$')
    VOWEL_COUNT DW 0
    MSG1 DB 10,13,'Enter a string: $'
    MSG2 DB 10,13,'The vowel count is: $'
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, DATA
    MOV DS, AX

    LEA DX, MSG1
    MOV AH, 9
    INT 21H

    LEA DX, STR1
    MOV AH, 0AH
    INT 21H

    LEA SI, STR1
    ADD SI, 2
    MOV BX, 0

LOOP1:
    MOV AL, [SI]
    CMP AL, 13
    JE EXIT
    CMP AL, 'A'
    JE VOWEL_FOUND
    CMP AL, 'E'
    JE VOWEL_FOUND
    CMP AL, 'I'
    JE VOWEL_FOUND
    CMP AL, 'O'
    JE VOWEL_FOUND
    CMP AL, 'U'
    JE VOWEL_FOUND
    CMP AL, 'a'
    JE VOWEL_FOUND
    CMP AL, 'e'
    JE VOWEL_FOUND
    CMP AL, 'i'
    JE VOWEL_FOUND
    CMP AL, 'o'
    JE VOWEL_FOUND
    CMP AL, 'u'
    JE VOWEL_FOUND
    JMP NEXT_CHAR

VOWEL_FOUND:
    INC BX

NEXT_CHAR:
    INC SI
    JMP LOOP1

EXIT:
    MOV VOWEL_COUNT, BX
    LEA DX, MSG2
    MOV AH, 9
    INT 21H
    MOV AX, VOWEL_COUNT
    CALL PRINT_NUM
    MOV AH, 4CH
    INT 21H

PRINT_NUM PROC
    PUSH AX
    PUSH BX
    PUSH CX
    PUSH DX
    MOV CX, 0
    MOV BX, 10
REPEAT1:
    XOR DX, DX
    DIV BX
    PUSH DX
    INC CX
    CMP AX, 0
    JNE REPEAT1
PRINT_LOOP:
    POP DX
    ADD DL, 30H
    MOV AH, 02H
    INT 21H
    LOOP PRINT_LOOP
    POP DX
    POP CX
    POP BX
    POP AX
    RET
PRINT_NUM ENDP

CODE ENDS
END START
