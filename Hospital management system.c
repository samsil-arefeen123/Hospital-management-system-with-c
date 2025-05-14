#include<stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include<string.h>

struct patient{
    char serial_number[20];
    char name[20];
    char cabinroom[20];
    char doctor[20];
    char disease[20];
    char drugname[20];
    char recovery_time[20];
};
struct doctor
{
    char name[20];
    char expertise[20];
    char checking_day[20];
    char contactinfo[20];
    char visit_fee[20];
};
int split(char *str,char arr[][40]){
    //strtok is used to split the string into tokens based on the delimiter
    //in this case the delimiter is "-"
    //token takes the string each time it is called and then it changes to next string
    //at the end it returns the value size of the array
    char *token;
    token = strtok(str, "-");
    int i=0;
    while(token != NULL){
        strcpy(arr[i],token);
        token = strtok(NULL, "-");
        i++;
    }
    return i;
}
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0'; // Remove trailing newline if present
}
int verifyadmin(FILE *passkeytxt){
     //actualpassword and actualusername are the paword and username that are stored in the file
    char *actualpassword, *actualusername;
    actualusername=(char*)malloc(20*sizeof(char));
    actualpassword=(char*)malloc(20*sizeof(char));
    //checking if the memory allocation was successful or not
    if(actualusername==NULL || actualpassword==NULL){
        printf("Memory allocation failed\n");
        return 0;
    }
    fgets(actualusername, 20, passkeytxt);
    remove_newline(actualusername);
   actualusername= realloc(actualusername,  ( strlen(actualusername)+1)*sizeof(char));
    fgets(actualpassword, 20, passkeytxt);
    remove_newline(actualpassword);
   actualpassword= realloc(actualpassword,  ( strlen(actualpassword)+1)*sizeof(char));
  
    char *username, *password;
    username=(char*)malloc(20*sizeof(char));
    password=(char*)malloc(20*sizeof(char));
    //checking if the memory allocation was successful or not
    if(username==NULL || password==NULL){
        printf("Memory allocation failed\n");
        return 0;
    }
    int counter=0;
    int maxattempts=3;
    while(1){
    //I will use malloc to allocate memory for the username and password
    printf("Enter your admin username ");
   // username=(char*)malloc(20*sizeof(char));
    //checking if the memory allocation was successful or not
    /*if(username==NULL){
        printf("Memory allocation failed\n");
        return 0;
    }*/
    //clear_input_buffer(); 
    //since I need to take the username with space I will use fgets
    fgets(username, 20, stdin);
    remove_newline(username);
    //reallocating memory for username to get the exact size I need removing unnecessary memory spaces
  //  username=(char*)realloc(username,  ( strlen(username)+1)*sizeof(char));
    printf("Enter your admin password ");
   /* password=(char*)malloc(20*sizeof(char));
    if(password==NULL){
        printf("Memory allocation failed\n");
        return 0;
    }
    */

    //since I need to take the password with space I will use fgets
    fgets(password, 20, stdin);
    remove_newline(password);
    //reallocating memory for password to get the exact size I need removing unnecessary memory spaces
    //password=(char*)realloc(password,  ( strlen(password)+1)*sizeof(char));
    printf("%s and %s \n", actualusername,username);
    printf("%s and %s \n", actualpassword,password);
    if(strcmp(username, actualusername)==0 && strcmp(password, actualpassword)==0){
        printf("Welcome Admin\n");
        printf("You have successfully logged in\n");
        free(actualusername);
        free(actualpassword);
        free(username);
        free(password);
        fclose(passkeytxt);
        //freeing the memory allocated for the username and password
        return 1;
    }
    else{
        printf("Invalid username or password\n");
        printf("Try again\n");
        counter++;
        printf("You have %d attempts left\n", maxattempts-counter);
    }
    if(counter==maxattempts){
        printf("You have exceeded the maximum number of attempts\n");
        return 0;
    }

}
    //Identify if the Identity of the admin is correct or not

}
int main(){
       char arr[20][40];
       char patients[100][7][40];
       char doctors[100][5][40];
        char input[] = "hello-My name Samsil Arefeen-How are you-so u are working-right"; 
       int length=split(input,arr);
         for(int i=0;i<length;i++){
            printf("%s\n",arr[i]);
         }
        FILE *adminpass=fopen("admin passkey.txt","r");
       // FILE 
        printf("Welcome to VitalPro Hospital yoyoyo\n");
        printf("Are you Admin or Customer ? Press a if you are admin and press c if you are Customer");
        char custmer_or_admin;
        char option;
        scanf(" %c",&custmer_or_admin);
        getchar();
        custmer_or_admin=tolower(custmer_or_admin);
        if(custmer_or_admin=='a')
        {
             if(verifyadmin(adminpass)){
               //something to do with admin
               printf("What do you want to do?\n");
               printf("Press p for if related patient info\n");
               scanf(" %c",&option);
               if(option=='p'){
                //something to do with patient
                FILE *patienttxt=fopen("patientinfo.txt","r");

                printf("Here are serveral options for you\n");
                printf("Press 1 to add a new patient\n");
                printf("Press 2 to view all patients\n");
                printf("Press 3 to search for a patient\n");
                printf("Press 4 to update a patient\n");
                printf("Press 5 to delete a patient\n");
                printf("Press 6 to exit\n");
                scanf(" %c",&option);
                if(option=='1'){
                    //add a new patient
                    if(patienttxt==NULL){
                        patienttxt=fopen("patientinfo.txt","w");
                    }
                    char total_string [200];
                    int count=0;
                    while(fgets(total_string, sizeof(total_string), patienttxt) != NULL){
                        remove_newline(total_string);
                        split(total_string, patients[count]);
                        count++;

                    }
                    for(int i=0;i<count;i++){
                        printf("%s-%s-%s-%s-%s-%s-%s\n", patients[i][0], patients[i][1], patients[i][2], patients[i][3], patients[i][4], patients[i][5], patients[i][6]);
                    }
                    printf("%d\n",count);
                    
                }
               }

             }
             else{
                exit(0);
             }
        }

}