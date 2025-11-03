DATA SEGMENT
    ARRAY   DW 1111H, 5555H, 2222H, 8888H, 4444H
    COUNT   DW 05H
    MSG     DB 'LARGEST NUMBER (HEX): $'
    LARGEST DW ?
DATA ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA
START:
    MOV AX, @DATA
    MOV DS, AX

    LEA SI, ARRAY       ; point SI to start of array
    MOV CX, COUNT       ; CX = number of elements
    MOV AX, [SI]        ; AX = first element

    DEC CX
    JZ DISPLAY          ; if only one element, skip loop

FIND_MAX:
    ADD SI, 2           ; move to next word
    CMP AX, [SI]        ; compare with current max
    JGE SKIP
    MOV AX, [SI]        ; update largest value
SKIP:
    LOOP FIND_MAX

    MOV LARGEST, AX

DISPLAY:
    LEA DX, MSG         ; display message
    MOV AH, 09H
    INT 21H

    MOV AX, LARGEST
    CALL DISP_HEX       

    MOV AH, 4CH
    INT 21H

DISP_HEX PROC
    PUSH CX
    PUSH DX
    MOV CX, 4           
HEX_LOOP:
    ROL AX, 4           
    MOV DL, AL
    AND DL, 0FH         
    CMP DL, 9
    JBE DIGIT
    ADD DL, 7           
DIGIT:
    ADD DL, 30H         
    MOV AH, 02H
    INT 21H
    LOOP HEX_LOOP
    POP DX
    POP CX
    RET
DISP_HEX ENDP

CODE ENDS
END START
