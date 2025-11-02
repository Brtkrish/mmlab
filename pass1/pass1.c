
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *input, *optab, *symtab, *intermediate, *lengthFile;
    char label[20], opcode[20], operand[20], code[20], mnemonic[20];
    int locctr = 0, start = 0, length;

    input = fopen("input/input.txt", "r");
    optab = fopen("input/optab.txt", "r");
    symtab = fopen("output/symtab.txt", "w");
    intermediate = fopen("output/intermediate.txt", "w");
    lengthFile = fopen("output/length.txt", "w");

    if (!input || !optab || !symtab || !intermediate || !lengthFile) {
        printf("Error opening files\n");
        exit(1);
    }

    fscanf(input, "%s\t%s\t%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = (int)strtol(operand, NULL, 16);
        locctr = start;
        fprintf(intermediate, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    } else {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(intermediate, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "**") != 0) {
            fprintf(symtab, "%s\t%X\n", label, locctr);
        }

        rewind(optab);
        int found = 0;
        while (fscanf(optab, "%s\t%s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                locctr += 3;
            } else if (strcmp(opcode, "RESW") == 0) {
                locctr += (3 * atoi(operand));
            } 

            else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C' || operand[0] == 'c') {

                    locctr += (strlen(operand) - 3); 
                } else if (operand[0] == 'X' || operand[0] == 'x') {

                    locctr += (strlen(operand) - 3) / 2;
                } else {

                    locctr += 1;
                }

            } else if (strcmp(opcode, "RESB") == 0) {
                locctr += atoi(operand);
            } else {
                printf("Invalid opcode: %s\n", opcode);

            }
        }

        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    }

    fprintf(intermediate, "%X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    length = locctr - start;
    fprintf(lengthFile, "%X", length);

    printf("PASS 1 Completed Successfully.\n");
    printf("Program Length: %X\n", length);

    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(intermediate);
    fclose(lengthFile);

    return 0;
}
