#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LETTER 1000
/*==========================================================*/
/*calculate the number of lines in a text file*/
int textFileLinesNumbers(FILE* f){
    char line[MAX_LETTER];
    int lineNumber=0;
    if(f==NULL){
     printf("Failed to open the file ");
     return lineNumber;
    }else{
      while(fgets(line,MAX_LETTER,f)){
        lineNumber++;
      }
  }
  return lineNumber;
}
/*==========================================================*/
//Write a C program that checks if two text files are identical. In case of any difference, the program should display the corresponding lines.
void identicalFiles(FILE* f1,FILE* f2){
    int cmp,count1=0,LineFileNumber1=0,LineFileNumber2=0;
    char lineFile1[MAX_LETTER] , lineFile2[MAX_LETTER];
    LineFileNumber1=textFileLinesNumbers(f1);
    fseek(f1, 0, SEEK_SET);
    LineFileNumber2=textFileLinesNumbers(f2);
    fseek(f2, 0, SEEK_SET);
    printf("--------------------------------\n");
   if(LineFileNumber1==LineFileNumber2){
    while(fgets(lineFile1,MAX_LETTER,f1) && fgets(lineFile2,MAX_LETTER,f2)){
        cmp=strcmp(lineFile1,lineFile2);
        if(cmp!=0){
            if(count1!=0){
                printf("the tow files are not identical\n");
                printf("The corresponding lines are : \n");
                printf("--------------------------------\n");

            }
            count1++;
            printf("The corresponding lines number %d :\n %s \n %s \n",count1,lineFile1,lineFile2);
            printf("--------------------------------\n");

        }
     }
   }else{
       if(LineFileNumber1>LineFileNumber2){
            printf("the tow files are not identical\n");
            printf("The corresponding lines are : \n");
            printf("--------------------------------\n");

           for(int i=1;i<=LineFileNumber2;i++){
            fgets(lineFile1,MAX_LETTER,f1);
            fgets(lineFile2,MAX_LETTER,f2);
            cmp=strcmp(lineFile1,lineFile2);
            if(cmp!=0){
                    count1++;
                    printf("The corresponding lines number %d :\n %s \n %s \n",count1,lineFile1,lineFile2);
                    printf("--------------------------------\n");

            }
           }
           while(fgets(lineFile1,MAX_LETTER,f1)){
           count1++;
           printf("The corresponding lines number %d :\n %s \n ",count1,lineFile1);
           printf("File2 has no corresponding line\n");
           printf("--------------------------------\n");
           }
       }else{
            printf("the tow files are not identical\n");
            printf("The corresponding lines are : \n");
            printf("--------------------------------\n");

           for(int i=1;i<=LineFileNumber1;i++){
            fgets(lineFile1,MAX_LETTER,f1);
            fgets(lineFile2,MAX_LETTER,f2);
            cmp=strcmp(lineFile1,lineFile2);
            if(cmp!=0){
                    count1++;
                    printf("The corresponding lines number %d :\n %s \n %s \n",count1,lineFile1,lineFile2);
                    printf("--------------------------------\n");

            }
           }
           while(fgets(lineFile2,MAX_LETTER,f2)){
           count1++;
           printf("The corresponding lines number %d :\n %s \n ",count1,lineFile2);
           printf("File1 has no corresponding line\n");
           printf("--------------------------------\n");
           }
       }
   }
     if(count1==0){
        printf("the tow files are identical");
     }
}
/*==========================================================*/
int main()
{
    FILE* file1=fopen("file1.txt","r");
    FILE* file2=fopen("file2.txt","r");
    identicalFiles(file1,file2);
    fclose(file1);
    fclose(file2);
    return 0;
}
