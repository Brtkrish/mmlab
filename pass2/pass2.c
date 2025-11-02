#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORD_LEN 60 // Max bytes in one T record (30 instructions)

int main() {
    FILE *intermediate, *optab, *symtab, *lengthFile, *output;
    char label[20], opcode[20], operand[20], locctr_str[20];
    char symLabel[20], symAddr_str[20], opCode[20], opVal[20];
    char startAddr_str[20], progName[20], record[MAX_RECORD_LEN + 1];
    int length, startAddr, locctr, record_len = 0, record_start_addr = 0;

    intermediate = fopen("intermediate.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "r");
    lengthFile = fopen("length.txt", "r");
    output = fopen("objectcode.txt", "w");

    if (!intermediate || !optab || !symtab || !lengthFile || !output) {
        printf("Error opening files.\n");
        exit(1);
    }


    fscanf(lengthFile, "%x", &length);


    fscanf(intermediate, "\t%s\t%s\t%s", progName, opcode, startAddr_str);
    startAddr = (int)strtol(startAddr_str, NULL, 16);
    locctr = startAddr;
    record_start_addr = startAddr;


    fprintf(output, "H^%-6s^%06s^%06X\n", progName, startAddr_str, length);


    fscanf(intermediate, "%s\t%s\t%s\t%s", locctr_str, label, opcode, operand);
    locctr = (int)strtol(locctr_str, NULL, 16);
    record_start_addr = locctr;
    strcpy(record, "");


    while (strcmp(opcode, "END") != 0) {
        int found = 0;
        char obj_code_part[7];
        strcpy(obj_code_part, "");

        rewind(optab);
        while (fscanf(optab, "%s\t%s", opCode, opVal) != EOF) {
            if (strcmp(opcode, opCode) == 0) {

                rewind(symtab);
                char operand_addr_str[5] = "0000";
                if (strcmp(operand, "**") != 0) {
                    while (fscanf(symtab, "%s\t%s", symLabel, symAddr_str) != EOF) {
                        if (strcmp(operand, symLabel) == 0) {
                            strcpy(operand_addr_str, symAddr_str);
                            break;
                        }
                    }
                }
                sprintf(obj_code_part, "%s%s", opVal, operand_addr_str);
                found = 1;
                break;
            }
        }


        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                sprintf(obj_code_part, "%06X", atoi(operand));
            } else if (strcmp(opcode, "BYTE") == 0) {

                if (operand[0] == 'C' || operand[0] == 'c') { 
                    for (int i = 2; i < strlen(operand) - 1; i++) {
                        char hex_char[3];
                        sprintf(hex_char, "%X", operand[i]);
                        strcat(obj_code_part, hex_char);
                    }
                }

                else if (operand[0] == 'X' || operand[0] == 'x') {
                    for (int i = 2; i < strlen(operand) - 1; i++) {
                        strncat(obj_code_part, &operand[i], 1);
                    }
                }
            }
        }

        int part_len = strlen(obj_code_part);
        

        if (part_len > 0) {

            if (record_len + part_len > MAX_RECORD_LEN) {

                fprintf(output, "T^%06X^%02X^%s\n", record_start_addr, record_len / 2, record);
  
                strcpy(record, obj_code_part);
                record_len = part_len;
                record_start_addr = locctr;
            } else {
                strcat(record, obj_code_part);
                record_len += part_len;
            }
        }

  
        if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) {
            if (record_len > 0) {
                fprintf(output, "T^%06X^%02X^%s\n", record_start_addr, record_len / 2, record);
            }
            strcpy(record, "");
            record_len = 0;

            int next_locctr = 0;
            fscanf(intermediate, "%s\t%s\t%s\t%s", locctr_str, label, opcode, operand);
            next_locctr = (int)strtol(locctr_str, NULL, 16);
            record_start_addr = next_locctr;
            locctr = next_locctr;
            continue;
        }


        fscanf(intermediate, "%s\t%s\t%s\t%s", locctr_str, label, opcode, operand);
        locctr = (int)strtol(locctr_str, NULL, 16);
    }


    if (record_len > 0) {
        fprintf(output, "T^%06X^%02X^%s\n", record_start_addr, record_len / 2, record);
    }


    fprintf(output, "E^%06s\n", startAddr_str);

    fclose(intermediate);
    fclose(optab);
    fclose(symtab);
    fclose(lengthFile);
    fclose(output);

    printf("PASS 2 Completed Successfully.\n");
    return 0;
}
