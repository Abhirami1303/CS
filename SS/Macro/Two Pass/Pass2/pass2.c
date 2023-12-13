#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2, *f3, *f4, *f5;
    int i, len, flag = 0;
    char opcode[20], operand[20], label[20], name[20], opcode1[20], operand1[20], arg[20];

    f1 = fopen("SOURCE.txt", "r");
    f2 = fopen("NAMTAB.txt", "r");
    f3 = fopen("DEFTAB.txt", "r");
    f4 = fopen("ARGTAB.txt", "w+");
    f5 = fopen("EXPANDED.txt", "w");

    fscanf(f1, "%s%s%s", label, opcode, operand);

    while (strcmp(opcode, "END") != 0)
    {
        if (strcmp(opcode, "MACRO") == 0)
        {
            fscanf(f1, "%s%s%s", label, opcode, operand);
            while (strcmp(opcode, "MEND") != 0)
                fscanf(f1, "%s%s%s", label, opcode, operand);
        }
        else
        {
            rewind(f2);
            fscanf(f2, "%s", name);
            flag = 0;

            while (!feof(f2))
            {
                if (strcmp(opcode, name) == 0)
                {
                    flag = 1;
                    len = strlen(operand);
		                fseek(f4,0,SEEK_SET);
                    for (i = 0; i < len; i++)
                    {
                        if (operand[i] != ',')
                            fprintf(f4, "%c", operand[i]);
                        else
                            fprintf(f4, "\n");
                    }
		                fprintf(f4, "\n");
                    rewind(f2);
                    rewind(f4);
                    rewind(f3);

                    fscanf(f3, "%s%s", opcode1, operand1);

                    while (strcmp(opcode1, opcode) != 0)
                    {
                        fscanf(f3, "%s%s", opcode1, operand1);
                    }

                    fprintf(f5, ".\t%s\t%s\n", opcode1, operand);
                    fscanf(f3, "%s%s", opcode1, operand1);

                    while (strcmp(opcode1, "MEND") != 0)
                    {
                        if (operand1[0] == '&')
                        {
                            fscanf(f4, "%s", arg);
                            fprintf(f5, "-\t%s\t%s\n", opcode1, arg);
                        }
                        else
                        {
                            fprintf(f5, "-\t%s\t%s\n", opcode1, operand1);
                        }
                        fscanf(f3, "%s%s", opcode1, operand1);
                    }
		            break;
                }
                fscanf(f2, "%s", name);
            }

            if (flag == 0)
            {
                fprintf(f5, "%s\t%s\t%s\n", label, opcode, operand);
            }
        }
        fscanf(f1, "%s%s%s", label, opcode, operand);
    }

    fprintf(f5, "%s\t%s\t%s\n", label, opcode, operand);

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);

    printf("Macro processor Pass 2 implemented successfully\n");

    return 0;
}

