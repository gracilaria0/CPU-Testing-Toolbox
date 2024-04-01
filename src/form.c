#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void txt2v(int);
void reformv(int);
void changeMacro(int,FILE *,FILE *,char);
void addInclude(int,FILE *,FILE *);


int main(int argc,char *argv[])
{
    int num = atoi(argv[1]);

    txt2v(num);
    reformv(num);

    return 0;
}

void txt2v(int num)
{
    int decCount=0, hexCount=0;

    char writeName[32], readName[32], instrucion[16];
    sprintf(readName,"../test%d/test%d.txt",num,num);
    sprintf(writeName,"../test%d/test%d.v",num,num);

    FILE *fileRead = fopen(readName,"r"),\
         *fileWrite = fopen(writeName,"w");

    fprintf(fileWrite,"`ifdef TEST%d\n",num);

    while(!feof(fileRead))
    {
        if(fgets(instrucion,10,fileRead) && instrucion[0]!='\n')
        {
            instrucion[8] = ';';
            instrucion[9] = '\n';
            instrucion[10] = '\0';
            fprintf(fileWrite,"    InstructionMemory[%3d/*%3x*/] <= 32'h%s",decCount++,hexCount,instrucion);
            hexCount += 4;
        }
    }

    fprintf(fileWrite,"`endif\n");

    fclose(fileRead);
    fclose(fileWrite);

    return;
}

void reformv(int num)
{
    char protoName[32];
    sprintf(protoName,"../../code/InstructionMemory.v");

    FILE *fileProto = fopen(protoName,"r"),
         *fileTemp = fopen("../../code/temp.v","w");

    changeMacro(num,fileProto,fileTemp,0);
    addInclude(num,fileProto,fileTemp);
    changeMacro(num,fileProto,fileTemp,1);

    return;
}

void changeMacro(int num,FILE *fileProto,FILE *fileTemp,char isUndef)
{
    size_t cpyLength;
    char cmpStr[16],prtStr[32];
    if(isUndef)
    {
        cpyLength = 11;
        sprintf(cmpStr,"`undef TEST");
        sprintf(prtStr,"`undef TEST%d\n",num);
    }
    else
    {
        cpyLength = 12;
        sprintf(cmpStr,"`define TEST");
        sprintf(prtStr,"`define TEST%d\n",num);
    }

    char proto[128], macro[16]={}, found=0;

    while(!feof(fileProto))
    {
        fgets(proto,128,fileProto);

        strncpy(macro,proto,cpyLength);
        if(!strcmp(macro,cmpStr) && !found)
        {
            fprintf(fileTemp,"%s",prtStr);
            if(!isUndef)
                break;
            else
                found = 1;
        }
        else
        {
            fprintf(fileTemp,"%s",proto);
        }
    }

    return;
}

void addInclude(int num,FILE *fileProto,FILE *fileTemp)
{
    char proto[128], addTag[16]={}, found=0;

    while(!feof(fileProto))
    {
        fgets(proto,128,fileProto);

        strncpy(addTag,proto,11);
        if(!strcmp(addTag,"//TEST CODE"))
        {
            fprintf(fileTemp,"//TEST CODE\n`include \"../test/test%d/test%d.v\"\n",num,num);
            break;
        }
        else
        {
            fprintf(fileTemp,"%s",proto);
        }
    }

    return;
}