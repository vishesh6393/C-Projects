// file handling using c
//file usually handle with the pointer database
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void insert_record();
void display_record();
void delete_record();
void update_record();
void search_record();



struct students{
int roll;
char name[40];
char sec[10];
float grade;

};
 struct students s;
int  main(){

int choices;
while(choices!=8){


    printf("\t**************************************************************************************\n ");
    printf("\t\t \t\t WELCOME TO THE STUDENT MANAGEMENT SYSTEM\n");
    printf("\t**************************************************************************************\n\n\n\n ");

    printf("\t\t\t\t 1)ENTER STUDENT DATA\n\n");
    printf("\t\t\t\t 2)DISPLAY STUDENT DATA\n\n");
    printf("\t\t\t\t 3)DELETE STUDENT DATA\n\n");
    printf("\t\t\t\t4)SEARCH STUDENT DATA \n\n");
    printf("\t\t\t\t5)UPDATE STUDENT DATA\n\n");
    // printf("\t\t\t\t6)SORT STUDENT DATA\n\n");
    printf("\t\t\t\t 6)EXIT  STUDENT DATA\n\n");
    printf("\t**************************************************************************************\n ");
    printf ("Enter your choice\n\n ");
    scanf("%d",&choices);


        // int choice;
        switch (choices) {

            case 1:
                insert_record();
                break;

            case 2:
                display_record();
                break;
            case 3:
                delete_record();
                break;

            case 4:
                    search_record();
                    break;   

            case 5:
                update_record();
                break;

            case 6:
                exit(1);

            default:
            printf("\n\t\t You have entered the wrong choice \n");
        }


        printf("\n\tEnter any key to continue\n\n");//this will take to the starting loop where all the conditions are displayed 
        // main();
        getch();
    }

}
void insert_record(){
    FILE *fp;
    fp=fopen("student.txt","ab+");
    if (fp==NULL)
    {
        printf("\n \t !!!!!!!!!!!!!!!!!!!! ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
        return;

    }
    printf(" **************** PREVIOUS STORED DATA OF THE FILE *******************\n\n");
    display_record();
    printf("\n **************** ENTER THE NEW DATA OF THE STUDENT ******************\n\n");
    printf ("\t ENTER STUDENT ROLL NUMBER\n\n");
    scanf("%d",&s.roll);
    fflush(stdin);
    printf ("\t ENTER STUDENT NAME\n\n");
    gets(s.name);
    fflush(stdin);
    printf ("\t ENTER STUDENT SECTION\n\n");
    gets(s.sec);
    fflush(stdin);
    printf ("\tENTER STUDENT GRADE\n\n");
    scanf("%f",&s.grade);
    fflush(stdin);
    fwrite(&s,sizeof(s),1,fp);//this method is used in writing information(user input in the file)to the file..
    {
     printf ("\t**** FILE WRITTEN SUCCESSFULLLYYYYY!!!!!!!!!!!!!!\n\n");
    }
fclose(fp);

}

void display_record(){
    FILE *fp;
    int flag=0;
    fp=fopen("student.txt","rb");
    if(fp==NULL){
        printf("\n\t\t ERROR OCCURED FILE NOT FOUND \n\n");
    }
    else{
        printf("\t\t***********************  THE INFORMATION OF STUDENT ARE AS FOLLOWS********************************\n\n");
    }
    
    while(fread(&s,sizeof(s),1,fp)>0 && flag==0){  //yha ye check karega agar file me conntent hai it means ==1 ie true 
 
        printf("name:%s\n roll:%d\n  section:%s\n grade:%.2f\n \n\n",s.name,s.roll,s.sec,s.grade);
        // flag=1;
        // flag++;// here u have to fetchout the information of the students 
    }

    fclose(fp);
 
}


void delete_record(){

    int flag=0;
    FILE *fp,*fp1;
    int roll;
    // fp=fopen("student.txt","wb");
    if(fp==NULL){
        printf("\t\t***********ERROR OCCURED IN OPENING THE FILE**********\n\n");
        exit(0);
    }
    printf("\t ENTER THE ROLL NUMBER OF THE STUDENT WHOSE DATA TO BE DELETED\n\n");
    scanf("%d",&roll);
    fp=fopen("student.txt","rb");
    fp1=fopen("copy.txt","ab+");
    while(fread(&s,sizeof(s),1,fp)==1 && flag==0){
        if(s.roll!=roll){
        flag=1;//iska ye matlb hai jiska bhi roll no. entered roll no. ke equal nhi hai wo print hojayenge aur jiska equal hai wo delete hojayga wo write nhi hoga
            printf("\t\t RECORD DELETED SUCCESSFULLY!!!!!!!!!\n");
            fwrite(&s,sizeof(s),1,fp1);
        }
    }
    fclose(fp);
    fclose(fp1);
    remove("student.txt");
    rename("copy.txt","student.txt");
}



void search_record(){
    int rol;
    int flag=0;
    FILE *fp;

    fp=fopen("student.txt","rb+");
  
    printf("\n\t ENTER THE ROLL NO FOR SEARCHING OF STUDENTS\n");
    scanf("%d",&rol);
    if (fp==NULL){
        printf("ERROR OCCURED WHILE OPENING THE FILE!!!!!!!!!!!!!!!!!!\n");
        // exit(1);
    }
    while(fread(&s,sizeof(s),1,fp)==1 && flag==0){
        if(s.roll == rol){
            flag=1;
            printf("file successfully searched .............\n\n");
          
            printf("Name:%s\n Roll:%d\n sec:%s\n grade:%f\n",s.name,s.roll,s.sec,s.grade);
         
            }
            if (flag==0){
                printf("\t\t\t THERE IS NO SUCH RECORD\n");
            }
      
    }
        fclose(fp);
}


void update_record(){

    int flag=0;
    FILE *fp;
    int ro;
//    char name[400];
    fp=fopen("student.txt","rb+");
     printf("\t\t ENTER THE ROLL NUMBER OF STUDENT WHOSE DATA TO BE UPDATED\n\n\n");
    scanf("%d",&ro);
    if (fp==NULL){
        printf("\n\tERROR ERROR ERROR\n");
    }   
  while(fread(&s,sizeof(s),1,fp)>0 && flag==0){
       if(s.roll==ro)
        {
               flag=1;
            printf("Name:%s\n Roll:%d\n sec:%s\n grade:%f\n",s.name,s.roll,s.sec,s.grade);
            printf("\t\t\t**************ENTER NEW DATA ************\n\n");
            printf("\n \t ENTER THE NEW ROLL NO.\n");
            scanf("%d",&s.roll);
            fflush(stdin);
            // break;
            printf("\n\t ENTER THE NEW NAME \n");
            gets(s.name);
            printf("name successfully updated\n");
            fseek(fp,-(long)sizeof(s),1);
            fwrite(&s,sizeof(s),1,fp);
             break;
        // }
       display_record();
       
  }  
}
fclose(fp);
}
