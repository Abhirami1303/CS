
//program to implement Pass 1 of two pass assembler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE *fp1,*fp2,*fp3,*fp4,*fp5;
	char label[10],opcode[10],operand[10],code[10],mnemonic[10];
	int locctr,start,length;
	fp1=fopen("input.txt","r");
	fp2=fopen("optab.txt","r");
	fp3=fopen("symtab.txt","w");
	fp4=fopen("intermediate.txt","w");
	fp5=fopen("Pgmlen.txt","w");
	fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
	if(strcmp(opcode,"START")==0)
	{
		start=atoi(operand);
		locctr=start;
		fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand);
		fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
	}
	else
	{
		locctr=0;
	}
	while(strcmp(opcode,"END")!=0)
	{
		fprintf(fp4,"%d\t%s\t%s\t%s\n",locctr,label,opcode,operand);
		fscanf(fp2,"%s\t%s",code,mnemonic);
		while(!feof(fp2))
		{
			if(strcmp(opcode,code)==0)
			{
				locctr+=3;
				break;
			}
			fscanf(fp2,"%s\t%s",code,mnemonic);
		}
		if(strcmp(label,"**")!=0)
			fprintf(fp3,"%s\t%d\n",label,locctr);
		if(strcmp(opcode,"WORD")==0)
			locctr+=3;
		else if(strcmp(opcode,"RESB")==0)
			locctr+=atoi(operand);
		else if(strcmp(opcode,"RESW")==0)
			locctr+=(3*atoi(operand));
		else if(strcmp(opcode,"BYTE")==0)
		{
			if(operand[0]=='X')
				locctr+=1;
			else if(operand[0]=='C')
				locctr+=(strlen(operand)-3);
		}
		fscanf(fp1,"%s\t%s\t%s",label,opcode,operand);
	}
	fprintf(fp4,"\t%s\t%s\t%s\n",label,opcode,operand);
	length=locctr-start;
	printf("Program Length = %d\n",length);
	fprintf(fp5,"%d",length);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	return 0;
}
