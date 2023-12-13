// Program to implement pass-1 macro processor
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    FILE *f1, *f2, *f3;
    char opcode[10], operand[10], label[10];

    f1 = fopen("SOURCE.txt", "r");
    f2 = fopen("NAMTAB.txt", "w+");
    f3 = fopen("DEFTAB.txt", "w+");

    fscanf(f1, "%s%s%s", label, opcode, operand);

    while (!feof(f1))
    {
        if (strcmp(opcode, "MACRO") == 0)
        {
            fprintf(f2, "%s\n", label);
            fprintf(f3, "%s\t%s\n", label, operand);
	    fscanf(f1, "%s%s%s", label, opcode, operand);
	    while(strcmp(opcode,"MEND")!=0)
	    {
		 fprintf(f3, "%s\t%s\n", opcode, operand);
		 fscanf(f1, "%s%s%s", label, opcode, operand);
	    }
	    fprintf(f3, "%s\t-\n", opcode);
	    
       }
        fscanf(f1, "%s%s%s", label, opcode, operand);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);

    printf("Macro processor Pass 1 implemented successfully\n");

    return 0;
}

