//Program to implement Pass 2 of two pass assembler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE *fp1,*fp2,*fp3,*fp4,*fp5,*fp6;
	char label[10],opcode[10],operand[10],code[10],mnemonic[10],locctr[10],length[10],sym[10],symloc[10];
	int i,start;
	fp1=fopen("intermediate.txt","r");
	fp2=fopen("optab.txt","r");
	fp3=fopen("symtab.txt","r");
	fp4=fopen("Pgmlen.txt","r");
	fp5=fopen("objectprgm.txt","w");
	fp6=fopen("assemblylisting.txt","w");
	fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
	fscanf(fp4,"%s",length);
	if(strcmp(opcode,"START")==0)
	{
		fprintf(fp5,"H^%s^00%s^0000%s\n",label,operand,length);
		fprintf(fp6,"\t%s\t%s\t%s",label,opcode,operand);
		start=atoi(operand);
		fprintf(fp5,"T^00%s^%s",operand,length);
		fscanf(fp1,"%s\t%s\t%s\t%s",locctr,label,opcode,operand);
	}
	while(!feof(fp1))
	{
		fprintf(fp6,"\n%s\t%s\t%s\t%s\t",locctr,label,opcode,operand);
		fscanf(fp2,"%s\t%s",code,mnemonic);
		while(!feof(fp2))
		{
			if(strcmp(opcode,code)==0)
			{
				fprintf(fp5,"^%s",mnemonic);
				fprintf(fp6,"%s",mnemonic);
				break;
			}
			fscanf(fp2,"%s\t%s",code,mnemonic);
		}
		rewind(fp2);
		fscanf(fp3,"%s\t%s",sym,symloc);
		while(!feof(fp3))
		{
			if(strcmp(sym,operand)==0)
			{
				fprintf(fp5,"%s",symloc);
				fprintf(fp6,"%s",symloc);
				break;
			}
			fscanf(fp3,"%s\t%s",sym,symloc);
		}
		rewind(fp3);
		if (strcmp(opcode,"WORD")==0)
		{
			fprintf(fp5,"^00000%s",operand);
			fprintf(fp6,"00000%s",operand);
		}
		else if (strcmp(opcode,"BYTE")==0)
		{
			fprintf(fp5,"^");
			for (i=0;i<6-(strlen(operand)-3);i++)
			{
				fprintf(fp5,"0");
				fprintf(fp6,"0");
			}
			for (i=2;i<strlen(operand)-1;i++)
			{
				fprintf(fp5,"%c",operand[i]);
				fprintf(fp6,"%c",operand[i]);
			}
		}
		fscanf(fp1,"%s\t%s\t%s\t%s",locctr,label,opcode,operand);
	}
	fprintf(fp5,"\nE^00%d",start);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
	return 0;
}

