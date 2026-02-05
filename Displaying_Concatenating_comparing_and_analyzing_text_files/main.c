#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LETTER 1000
/*========================================================*/
/*display the content of a file*/
void displayFileContent(FILE* f){
    char line[MAX_LETTER];

    if(f==NULL){
     printf("Failed to open the file ");
     } else{
    while(fgets(line,MAX_LETTER,f)){
      printf("%s",line);
    }
  }
}
/*========================================================*/
/*concatenate two text files*/
void concateTowFiles(FILE* f1,FILE* f2,FILE* f3){
    char line[MAX_LETTER];
    if(f1==NULL || f2==NULL || f3==NULL){
        printf("Failed to open file");
    }else{
        while(fgets(line,MAX_LETTER,f1)){
            fputs(line,f3);
        }
        while(fgets(line,MAX_LETTER,f2)){
            fputs(line,f3);
        }
    }
}
/*========================================================*/
int NumberWordLine(char*line,char*word){
    int number=0;
    char *pos=line;
    while(strstr(pos,word)!=NULL){
        pos=strstr(pos,word);
            number++;
            pos+=strlen(word);
     }
        return number;
}
int numberWordFile(char*word,FILE* f){
    int WordNumber=0;
    char line[MAX_LETTER];
    while(fgets(line,MAX_LETTER,f)){
      WordNumber+=NumberWordLine(line,word);
    }
    return WordNumber;
}
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
    int cmp,count1=0;
    char lineFile1[MAX_LETTER] , lineFile2[MAX_LETTER];
     while(fgets(lineFile1,MAX_LETTER,f1) && fgets(lineFile2,MAX_LETTER,f2)){
        cmp=strcmp(lineFile1,lineFile2);
        if(cmp!=0){
            if(count1!=0){
                printf("the tow files are not identical\n");
                printf("The corresponding lines are : \n");
            }
            count1++;
            printf("The corresponding lines number %d :\n %s \n %s \n",count1,lineFile1,lineFile2);

        }
     }
     if(count1==0){
        printf("the tow files are identical");
     }
}
/*==========================================================*/
int main()
{
    FILE* f=fopen("new.txt","r");
    char word[MAX_LETTER];
    printf("\n====================================\n");
    printf("display the file 'new.txt' \n");
    printf("\n-------------------------------------\n");
    displayFileContent(f);
    /*==========================================*/
    printf("\n====================================\n");
    fseek(f, 0, SEEK_SET);
    FILE* f2=fopen("file2.txt","r");
    FILE* f3=fopen("file3.txt","w");
    concateTowFiles(f,f2,f3);
    fclose(f3);
    f3=fopen("file3.txt","r");
    printf("cocatinating of file2.txt and file3.txt  \n");
    printf("\n-------------------------------------\n");
    displayFileContent(f3);
    fclose(f);
    printf("\n====================================\n");
    /*==========================================*/
    f=fopen("new.txt","r");
    FILE* f4=fopen("file4.txt","r");
    printf("\n====================================\n");
    printf("display the file 'new.txt' \n");
    printf("\n-------------------------------------\n");
    displayFileContent(f4);
    fseek(f4, 0, SEEK_SET);
    printf("\n====================================\n");
    printf("\n Enter the word you need count it in the file file4.txt : ");
    scanf("%s",word);
    int number=numberWordFile(word,f4);
    printf("the number of this word in the file is %d ",number);
    fclose(f4);
    fclose(f2);
    fclose(f3);
    /*==========================================*/
    printf("\n====================================\n");
    f=fopen("new.txt","r");
    int line_number;
    line_number=textFileLinesNumbers(f);
    printf("the number of the lines in the file is new.txt %d",line_number);
    fclose(f);
    printf("\n====================================\n");
    /*==========================================*/
    return 0;
}
