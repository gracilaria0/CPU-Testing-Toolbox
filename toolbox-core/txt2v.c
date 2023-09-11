#include <stdio.h>

int main()
{
    int num;
    printf("form test?.v\n?=");
    scanf("%d",&num);

    int decCount=0, hexCount=0;

    char writeName[32], readName[32], instrucion[16];
    sprintf(readName,"test%d.txt",num,num);
    sprintf(writeName,"test%d.v",num,num);

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

    return 0;
}