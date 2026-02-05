#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxLetter 1000
struct record{
    char city[maxLetter];
    char date[maxLetter];
    float temperature;
    };
/*========================================================================*/
//create a binary file from a text file
void CreteBinaryFileFromTextFile(FILE*textFile,FILE*binaryFile){
  struct record R;
    while(fscanf(textFile,"%s %s %f",R.city,R.date,&R.temperature)==3){
        fwrite(&R,sizeof(struct record),1,binaryFile);
    }
}
/*========================================================================*/
//display the content of a binary file
void DisplayBinaryFile(FILE*binaryFile){
    struct record R;
    while(fread(&R,sizeof(struct record),1,binaryFile)){
      printf("the city: %s / the date: %s / the temperature: %f \n",R.city,R.date,R.temperature);
   }
}
/*========================================================================*/
//display the content of text file
void DisplayTextFile(FILE*textFile){
    char line[maxLetter];
    while(fgets(line,maxLetter,textFile)){
        printf("%s",line);
    }
}
void DisplayTextFile2(FILE*textFile){
    struct record R;
    while(fscanf(textFile,"%s %s %f",R.city,R.date,&R.temperature)==3){
        printf("%s %s %f\n",R.city,R.date,R.temperature);
    }
}
/*========================================================================*/
//Determine the minimum temperatures for a given city
float minimumTemp(FILE*binaryFile,char*c){
    float Min,n=0;
    struct record R;
    while(fread(&R,sizeof(struct record),1,binaryFile)){
        if(strcmp(R.city,c)==0){
            if(n==0){
               Min=R.temperature;
            }else{
               if(Min>R.temperature){
                Min=R.temperature;
               }
            }
            n++;
        }
    }
 return Min;
}
//Determine the maximum temperatures for a given city
float maximumTemp(FILE*binaryFile,char*c){
    float Max,n=0;
    struct record R;
    while(fread(&R,sizeof(struct record),1,binaryFile)){
        if(strcmp(R.city,c)==0){
                if(n==0){
                    Max=R.temperature;
                }else{
                    if(Max<R.temperature){
                        Max=R.temperature;
                    }
                }
            n++;
        }
    }
 return Max;
}
//Determine the average temperatures for a given city
float averageTemp(FILE*binaryFile,char*c){
    float average=0;
    int n=0;
    struct record R;
    while(fread(&R,sizeof(struct record),1,binaryFile)){
            if(strcmp(R.city,c)==0){
                n++;
                average+=R.temperature;
            }
    }
 return average/n;
}
/*========================================================================*/
char* ConvertDate(char*day,char*month,char*year){
    static char date[maxLetter];
    date[0]=day[0];
    date[1]=day[1];
    date[2]='-';
    date[3]=month[0];
    date[4]=month[1];
    date[5]='-';
    date[6]=year[0];
    date[7]=year[1];
    date[8]=year[2];
    date[9]=year[3];
    return date;
}
//Add a new record to the file
void AddRecord(FILE*binaryFile,char*date,char*city,float tem){
    struct record R;
    fseek(binaryFile,0,SEEK_END);
    strcpy(R.city,city);
    strcpy(R.date,date);
    R.temperature=tem;
    fwrite(&R,sizeof(struct record),1,binaryFile);
}
/*========================================================================*/
//Modify the temperature for a given city on a specific date
void ModifyTemp(){
}
/*========================================================================*/
//Delete all records related to a given city
void DeleteRecords(){
}
/*========================================================================*/
int main()
{
    FILE*textFile=NULL,*binaryFile=NULL;
    int choi;
    float temp;
    char city[maxLetter],day[maxLetter],year[maxLetter],month[maxLetter];
    textFile=fopen("test.txt","r");
    binaryFile=fopen("test.bin","wb+");
    if(textFile==NULL || binaryFile==NULL ){
        printf("filed to open the file\n");
        return 1;
    }
    DisplayTextFile(textFile);
    fseek(textFile,0,SEEK_SET);
    CreteBinaryFileFromTextFile(textFile,binaryFile);
    fseek(textFile,0,SEEK_SET);
    fseek(binaryFile,0,SEEK_SET);
    printf("\n");
    DisplayBinaryFile(binaryFile);
    fseek(binaryFile,0,SEEK_SET);
    first:
    printf("\n===============================================================================\n");
    printf(" enter your choice \n");
    printf("    1->Determine the minimum, maximum, and average temperatures for a given city\n");
    printf("    2->Add a new record to the file\n");
    printf("    3->Modify the temperature for a given city on a specific date\n");
    printf("    4->Delete all records related to a given city\n");
    printf("    5->Exit\n");
    printf("===============================================================================\n");
    scanf("%d",&choi);
    switch(choi){
      case 1:
          printf("Enter the name of the city you want to determine its minimum, maximum, and average temperatures\n");
          scanf("%s",city);
          printf("the minimum temperatures of %s %f\n",city,minimumTemp(binaryFile,city));
          fseek(binaryFile,0,SEEK_SET);
          printf("the maximum temperatures of %s %f\n",city,maximumTemp(binaryFile,city));
          fseek(binaryFile,0,SEEK_SET);
          printf("the average temperatures of %s %f\n",city,averageTemp(binaryFile,city));
          fseek(binaryFile,0,SEEK_SET);
          goto first;
      case 2:
          printf("\n enter the data of the new record\n");
          printf("    enter the city : ");
          scanf("%s",city);
          printf("\n    enter the date\n");
          printf("         enter the day : ");
          scanf("%s",day);
          printf("\n         enter the month : ");
          scanf("%s",month);
          printf("\n         enter the year : ");
          scanf("%s",year);
          printf("\n    enter the temperatures\n");
          scanf("%f",&temp);
          AddRecord(binaryFile,ConvertDate(day,month,year),city,temp);
          fseek(binaryFile,0,SEEK_SET);
          DisplayBinaryFile(binaryFile);
          fseek(binaryFile,0,SEEK_SET);
          goto first;
      case 3:
          printf("Enter the name of the city you want to modify its temperature\n");
          printf("Enter the date\n");
          goto first;
      case 4:
          printf("Enter the name of the city you want to delete all its records\n");
          goto first;
      case 5:
          printf("Exit\n");
          goto finally;
      default:
          printf("This option does not exist\n");
          goto first;
    }
    finally:
    return 0;
}
