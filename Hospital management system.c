#include<stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include<string.h>
char *patient_print_string[7]={"","name","cabin room","doctor","disease","drug name","recovery time"};
char *doctor_print_string[6]={"","name","expertise","checking day","contact info","visit fee"};
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
    char serial_number[20];
    char name[20];
    char expertise[20];
    char checking_day[20];
    char contactinfo[20];
    char visit_fee[20];
};
char *str_to_lower(char str[]){
    //this function is used to convert the string to lower case
    //it returns the lower case string
    int length=strlen(str);
     char *newstr=(char*)malloc((length+1)*sizeof(char));
    for(int i=0;i<strlen(str);i++){
        newstr[i]=tolower(str[i]);
    }
    newstr[length]='\0';
    return newstr;
}
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {} // Clear the input buffer
}
void remove_newline(char *str) {
    str[strcspn(str, "\n")] = '\0'; // Remove trailing newline if present
}
void print_single_patient(char patients[][7][40],int index){
    printf("Serial number: %s\n", patients[index][0]);
    printf("Name: %s\n", patients[index][1]);
    printf("Cabin room: %s\n", patients[index][2]);
    printf("Doctor: %s\n", patients[index][3]);
    printf("Disease: %s\n", patients[index][4]);
    printf("Drug name: %s\n", patients[index][5]);
    printf("Recovery time: %s\n", patients[index][6]);
}
void print_single_doctor(char doctors[][7][40],int index){
    printf("Serial number: %s\n", doctors[index][0]);
    printf("Name: %s\n", doctors[index][1]);
    printf("Expertise: %s\n", doctors[index][2]);
    printf("Checking day: %s\n", doctors[index][3]);
    printf("Contact info: %s\n", doctors[index][4]);
    printf("Visit fee: %s\n", doctors[index][5]);
}
void print_patient(char patients[][7][40],int count){
    /*for(int i=0;i<count;i++)
    {
                        printf("%s-%s-%s-%s-%s-%s-%s\n", patients[i][0], patients[i][1], patients[i][2], patients[i][3], patients[i][4], patients[i][5], patients[i][6]);
    }*/
    for (int i=0;i<count;i++){
        print_single_patient(patients,i);
         printf("\n");
       /* printf("Serial number: %s\n", patients[i][0]);
        printf("Name: %s\n", patients[i][1]);
        printf("Cabin room: %s\n", patients[i][2]);
        printf("Doctor: %s\n", patients[i][3]);
        printf("Disease: %s\n", patients[i][4]);
        printf("Drug name: %s\n", patients[i][5]);
        printf("Recovery time: %s\n", patients[i][6]);*/
       
    }

}
void print_doctor(char doctors[][7][40],int count){
    for (int i=0;i<count;i++){
        print_single_doctor(doctors,i);
         printf("\n");

    }

}
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
int read_file_with_initializing(FILE *fp,char *filename,char arr[][7][40]){
    char str[200];
    //this function is used to read the file and initialize the array with the values from the file
    //it returns the count of the patients/doctors but if if the file is not found it returns 0 too since theres no info about the patients anyways
    fp=fopen(filename,"r");
    int count=0;
    if(fp==NULL){
        printf("File not found\n");
        return 0;
    }
    while(fgets(str, sizeof(str), fp) != NULL){
                        remove_newline(str);
                        split(str, arr[count]);
                        count++;

                    }
                    return count;
}
int get_total_contentby_filename(char *filename){
    int total_content;
    if(strcmp(filename,"patientinfo.txt")==0){
        total_content=7;
    }
    else if(strcmp(filename,"doctorinfo.txt")==0){
        //printf("This is the doctor file\n");
        total_content=6;
    }
    else{
        printf("Invalid file name\n");
        return -1;
    }
    return total_content;
}
/*int search_patient_by_serialnumber(char arr[][7][40],char serial_number){
    printf("This is the patient you are looking for\n");
    print_single_patient(arr,serial_number-1);
}*/
int search_patient_by_name(char arr[][7][40],char *name,int total_size){
    int store_serial[100];
    int count=0;
    printf("Possible patients");
    for(int i=0;i<total_size;i++){
        if(strstr(str_to_lower(arr[i][1]),str_to_lower(name))){
            store_serial[count]=i+1;
            count++;
            print_single_patient(arr,i);
            printf("\n");
        }
    }
   // printf("Patient not found\n");
    return 0;
}
int search_doctor_by_name(char arr[][7][40],char *name,int total_size){
    int store_serial[100];
    int count=0;
    printf("Possible doctors");
    for(int i=0;i<total_size;i++){
        if(strstr(str_to_lower(arr[i][1]),str_to_lower(name))){
            store_serial[count]=i+1;
            count++;
            print_single_doctor(arr,i);
            printf("\n");
        }
    }
   // printf("Doctor not found\n");
    return 0;
}
int update_array_content(char arr[][7][40],int index,int content_size){
     printf("What do you want to update?\n");
     int option;
     if(content_size==7){
        printf("Press 1 to update the name\n");
        printf("Press 2 to update the cabin room\n");
        printf("Press 3 to update the doctor\n");
        printf("Press 4 to update the disease\n");
        printf("Press 5 to update the drug name\n");
        printf("Press 6 to update the recovery time\n");
        scanf("%d",&option);
        if(!(option>=1&&option<=6)){
            printf("Invalid option\n");
            return -1;
        }
        getchar();
            printf("Enter the new %s of the patient\n",patient_print_string[option]);
            fgets(arr[index][option], sizeof(arr[index][option]),stdin);
            remove_newline(arr[index][option]);
        }
        
     else if(content_size==6){
        printf("Press 1 to update the name\n");
        printf("Press 2 to update the expertise\n");
        printf("Press 3 to update the checking day\n");
        printf("Press 4 to update the contact info\n");
        printf("Press 5 to update the visit fee\n");
        scanf("%d",&option);
        if(!(option>=1&&option<=5)){
            printf("Invalid option\n");
            return -1;
        }
            
        getchar();
            printf("Enter the new %s of the doctor\n",doctor_print_string[option]);
            fgets(arr[index][option], sizeof(arr[index][option]),stdin);
            remove_newline(arr[index][option]);
        }
        else{
            printf("Invalid option\n");
            return -1;
        }
     }
    

int add_any_specific_index(char arr[][7][40],int index,int content_size){
     char str[40];
    sprintf(arr[index][0],"%d",index+1);
    for (int i=1;i<content_size;i++){
        //this function is used to append the file with the array
        //it returns the count of the patients/doctors but if if the file is not found it returns -1
        //printf("%s\n",arr[*total_size][i]);
        if(content_size==7){
            printf("Enter the %s of the patient\n",patient_print_string[i]);
        /*switch(i){
            case 1:
                printf("Enter the name of the patient\n");
                
                break;
            case 2:
                printf("Enter the cabin room of the patient\n");
                break;
            case 3:
                printf("Enter the doctor of the patient\n");
                break;
            case 4:
                printf("Enter the disease of the patient\n");
                break;
            case 5:
                printf("Enter the drug name taken by the patient\n");
                break;
            case 6:
                printf("Enter the recovery time of the patient\n");
                break;
        }*/
    }
        else if(content_size==6){
            printf("Enter the %s of the Doctor\n",doctor_print_string[i]);
           /* switch(i){
                case 1:
                    printf("Enter the name of the doctor\n");
                    break;
                case 2:
                    printf("Enter the expertise of the doctor\n");
                    break;
                case 3:
                    printf("Enter the checking day of the doctor\n");
                    break;
                case 4:
                    printf("Enter the contact info of the doctor\n");
                    break;
                case 5:
                    printf("Enter the visit fee of the doctor\n");
                    break;
         }*/
    }
        fgets(str, sizeof(str),stdin);
        remove_newline(str);
        strcpy(arr[index][i],str);
    }

}
int append_file_update_array(char arr[][7][40],int *total_size,char *filename){
    int content_size=get_total_contentby_filename(filename);
    add_any_specific_index(arr,*total_size,content_size);
    *total_size=*total_size+1;
    /*char str[20];
    sprintf(arr[*total_size][0],"%d",*total_size);
    for (int i=1;i<content_size;i++){
        //this function is used to append the file with the array
        //it returns the count of the patients/doctors but if if the file is not found it returns -1
        //printf("%s\n",arr[*total_size][i]);
        if(content_size==7){
        switch(i){
            case 1:
                printf("Enter the name of the patient\n");
                
                break;
            case 2:
                printf("Enter the cabin room of the patient\n");
                break;
            case 3:
                printf("Enter the doctor of the patient\n");
                break;
            case 4:
                printf("Enter the disease of the patient\n");
                break;
            case 5:
                printf("Enter the drug name taken by the patient\n");
                break;
            case 6:
                printf("Enter the recovery time of the patient\n");
                break;
        }
    }
        else if(content_size==6){
            switch(i){
                case 1:
                    printf("Enter the name of the doctor\n");
                    break;
                case 2:
                    printf("Enter the expertise of the doctor\n");
                    break;
                case 3:
                    printf("Enter the checking day of the doctor\n");
                    break;
                case 4:
                    printf("Enter the contact info of the doctor\n");
                    break;
                case 5:
                    printf("Enter the visit fee of the doctor\n");
                    break;
         }
    }
        fgets(str, sizeof(str),stdin);
        remove_newline(str);
        strcpy(arr[*total_size][i],str);
    }
*/
//This function is used to update mainly at the end of the array
}
int update_file_add_newinfo_onindex_array(char arr[][7][40],int *total_size){
    //This function is used to add 
}
int update_file_change_info_onindex_array(char arr[][7][40],int *total_size){
    //This function is used to change the info of the patient
}
int copy_write_file(FILE *fp,char *filename,char arr[][7][40],int total_size){
    int total_content;
    total_content=get_total_contentby_filename(filename);

    //this function is used to write the file from the array
    //it returns the count of the patients/doctors but if if the file is not found it returns -1
    fp=fopen(filename,"w");
    if(fp==NULL||total_content==-1){
        printf("File not found\n");
        return -1;
    }
    for(int i=0;i<total_size;i++){
        for(int j=0;j<total_content;j++){
            fprintf(fp,"%s",arr[i][j]);
            if(j!=total_content-1){
                fprintf(fp,"-");
            }
            
        }
        if(i!=total_size-1){
            fprintf(fp,"\n");
        }
      //  fprintf(fp,"%s-%s-%s-%s-%s-%s-%s\n", arr[i][0], arr[i][1], arr[i][2], arr[i][3], arr[i][4], arr[i][5], arr[i][6]);
    }
    fclose(fp);
    return 1;
}
int delete_specific_index_array(char arr[][7][40],int index,int *total_size,int content_size){
    //this function is used to delete a specific index from the array
    for(int i=index;i<*total_size-1;i++){
        for(int j=1;j<content_size;j++){
            strcpy(arr[i][j],arr[i+1][j]);
        }
    }
    *total_size=*total_size-1;
    return 1;
}
int main(){
       
       char arr[20][40];
       int count=0;//this is the count of the patients
       char patients[100][7][40];
       char doctors[100][7][40];
       char total_single_line_string[100];
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
                FILE *patienttxt;
                char *patient_filename="patientinfo.txt";
                
                printf("Here are serveral options for you\n");
                printf("Press 1 to add a new patient\n");
                printf("Press 2 to view all patients\n");
                printf("Press 3 to search for a patient\n");
                printf("Press 4 to update a patient\n");
                printf("Press 5 to delete a patient\n");
                printf("Press 6 to exit\n");
                int patient_size=read_file_with_initializing(patienttxt,patient_filename,patients);

                scanf(" %c",&option);
                if(option=='1'){
                    //add a new patient

                   clear_input_buffer();
                    
                    /*
                    while(fgets(total_string, sizeof(total_string), patienttxt) != NULL){
                        remove_newline(total_string);
                        split(total_string, patients[count]);
                        count++;

                    }*/
                    append_file_update_array(patients,&patient_size,patient_filename);
                    print_patient(patients,patient_size);
                    printf("%d\n",patient_size );
                    copy_write_file(patienttxt,patient_filename,patients,patient_size);
                    
                }
                if(option=='2'){
                    //view all patients
                    print_patient(patients,patient_size);
                }
                if(option=='3'||option=='4'||option=='5'){
                    //search for a patient
                    if(option=='4'){ 
                        printf("To update a patient you need to search for the patient first\n");
                    }
                    char new_option;
                    char printoption[3][10]={"search","update","delete"};
                    
                    printf("How do you want to %s\n",printoption[option-'3']);
                    printf("Press 1 to %s by serial number\n",printoption[option-'3']);
                    printf("Press 2 to %s by name\n",printoption[option-'3']);
                    scanf(" %c",&new_option);
                    if(new_option=='1'){
                        //search by serial number
                        printf("Enter the serial number of the patient\n");
                        int serial_number;
                        scanf("%d",&serial_number);
                      // remove_newline(serial_number);
                       print_single_patient(patients,serial_number-1);
                       if(option=='4'){
                        update_array_content(patients,serial_number-1,7);
                        print_patient(patients,patient_size);
                        copy_write_file(patienttxt,patient_filename,patients,patient_size);
                       }  
                          if(option=='5'){
                            delete_specific_index_array(patients,serial_number-1,&patient_size,7);
                            print_patient(patients,patient_size);
                            copy_write_file(patienttxt,patient_filename,patients,patient_size);
                          }
                    }
                    if(new_option=='2'){
                        //search by name
                        printf("Enter the name or sub name of the patient\n");
                        char name[40];
                        clear_input_buffer();
                        fgets(name, sizeof(name),stdin);
                        remove_newline(name);
                        search_patient_by_name(patients,name,patient_size);
                    
                    if(option=='4'||option=='5'){
                        //update a patient 
                        printf("Enter the serial number of the patient\n");
                        int serial_number;
                        scanf("%d",&serial_number);
                        if(option=='4'){

                        update_array_content(patients,serial_number-1,7);
                        print_patient(patients,patient_size);
                        copy_write_file(patienttxt,patient_filename,patients,patient_size);
                    }
                        if(option=='5'){
                            delete_specific_index_array(patients,serial_number-1,&patient_size,7);
                            print_patient(patients,patient_size);
                            copy_write_file(patienttxt,patient_filename,patients,patient_size);
                        }
                    }
                    }
                    //search_patient_by_serialnumber(patients,serial_number);
                }
               }

             }
            /* else{
                exit(0);
             }*/
        }
}

