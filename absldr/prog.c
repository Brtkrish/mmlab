/* Fixed SS/absoluteloader/program.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    FILE *fp_in, *fp_out;
    char record_type;
    char prog_name[10];
    int start_addr, exec_addr, record_addr, record_len, i;
    char hex_byte[3];

    fp_in = fopen("INPUT.txt", "r");
    fp_out = fopen("OUTPUT.txt", "w");

    if (fp_in == NULL || fp_out == NULL) {
        printf("Error opening files.\n");
        exit(1);
    }

    fscanf(fp_in, "%c^%s^%x^%*x", &record_type, prog_name, &start_addr);

    fscanf(fp_in, " %c", &record_type);
    while (record_type != 'E') {
        if (record_type == 'T') {
            fscanf(fp_in, "^%x^%x", &record_addr, &record_len);

            // Loop for record_len *bytes*
            for (i = 0; i < record_len; i++) {
                char c;

                // --- BUG FIX: Skip '^' delimiters ---
                while ((c = fgetc(fp_in)) == '^');

                hex_byte[0] = c;
                hex_byte[1] = fgetc(fp_in);
                hex_byte[2] = '\0';

                fprintf(fp_out, "%06X\t%s\n", record_addr + i, hex_byte);
            }
        }
        fscanf(fp_in, " %c", &record_type);
    }

    fscanf(fp_in, "^%x", &exec_addr);
    printf("Execution starts at address: %06X\n", exec_addr);

    fclose(fp_in);
    fclose(fp_out);
    printf("Program loaded successfully into OUTPUT.txt\n");
}
