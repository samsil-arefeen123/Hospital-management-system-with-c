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
        FILE *adminpass=fopen("admin passkey.txt","r");
        printf("Welcome to VitalPro Hospital yoyoyo\n");
        printf("Are you Admin or Customer ? Press a if you are admin and press c if you are Customer");
        char custmer_or_admin;
        scanf(" %c",&custmer_or_admin);
        getchar();
        custmer_or_admin=tolower(custmer_or_admin);
        if(custmer_or_admin=='a')
        {
             if(verifyadmin(adminpass)){
               //something to do with admin
             }
             else{
                exit(0);
             }
        }

}