#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>

char *patient_print_string[7]={"","name","cabin room","doctor","disease","drug name","recovery time"};
char *doctor_print_string[6]={"","name","expertise","checking day","contact info","visit fee"};
char *hospital_print_string[10]={"hospital name","hospital address","hospital owner","max patient capacity","total doctor","total employee","hospital phone number","hospital email","hospital website","hospital year of establishment"};                    

struct hospitalinfo {
    char hospital_name[40];
    char hospital_address[40];
    char hospital_owner[40];
    char max_patient_capacity[40];
    char total_doctor[40];
    char total_employee[40]; 
    char hospital_phone_number[40];
    char hospital_email[40];
    char hospital_website[40];
    char hospital_year_of_establishment[40];
};

struct patient {
    char serial_number[20];
    char name[20];
    char cabinroom[20];
    char doctor[20];
    char disease[20];
    char drugname[20];
    char recovery_time[20];
};

struct doctor {
    char serial_number[20];
    char name[20];
    char expertise[20];
    char checking_day[20];
    char contactinfo[20];
    char visit_fee[20];
};

char *str_to_lower(char str[]) {
    //this function is used to convert the string to lower case
    //it returns the lower case string
    int length=strlen(str);
    char *newstr=(char*)malloc((length+1)*sizeof(char));
    for(int i=0;i<strlen(str);i++) {
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

void print_single_patient(char patients[][10][40],int index) {
    printf("Serial number: %s\n", patients[index][0]);
    printf("Name: %s\n", patients[index][1]);
    printf("Cabin room: %s\n", patients[index][2]);
    printf("Doctor: %s\n", patients[index][3]);
    printf("Disease: %s\n", patients[index][4]);
    printf("Drug name: %s\n", patients[index][5]);
    printf("Recovery time: %s\n", patients[index][6]);
}

void print_single_doctor(char doctors[][10][40],int index) {
    printf("Serial number: %s\n", doctors[index][0]);
    printf("Name: %s\n", doctors[index][1]);
    printf("Expertise: %s\n", doctors[index][2]);
    printf("Checking day: %s\n", doctors[index][3]);
    printf("Contact info: %s\n", doctors[index][4]);
    printf("Visit fee: %s\n", doctors[index][5]);
}

void print_single_appointment(char appoint[][10][40],int index) {
    printf("Serial number: %s\n", appoint[index][0]);
    printf("Patient name: %s\n", appoint[index][1]);
    printf("Doctor name: %s\n", appoint[index][2]);
    printf("Cabin room: %s\n", appoint[index][3]);
    printf("Appointment day: %s\n", appoint[index][4]);
}

void print_hospital_info(char hospital[][10][40]) {
    printf("Hospital name: %s\n", hospital[0][0]);
    printf("Hospital address: %s\n", hospital[0][1]);
    printf("Hospital owner: %s\n", hospital[0][2]);
    printf("Max patient capacity: %s\n", hospital[0][3]);
    printf("Total doctor: %s\n", hospital[0][4]);
    printf("Total employee: %s\n", hospital[0][5]);
    printf("Hospital phone number: %s\n", hospital[0][6]);
    printf("Hospital email: %s\n", hospital[0][7]);
    printf("Hospital website: %s\n", hospital[0][8]);
    printf("Hospital year of establishment: %s\n", hospital[0][9]);
}

void print_patient(char patients[][10][40],int count) {
    for (int i=0;i<count;i++) {
        print_single_patient(patients,i);
        printf("\n");
    }
}

void print_doctor(char doctors[][10][40],int count) {
    for (int i=0;i<count;i++) {
        print_single_doctor(doctors,i);
        printf("\n");
    }
}

void print_appointment(char appoint[][10][40],int count) {
    for (int i=0;i<count;i++) {
        print_single_appointment(appoint,i);
        printf("\n");
    }
}

int split(char *str,char arr[][40],char *splitby) {
    //strtok is used to split the string into tokens based on the delimiter
    //in this case the delimiter is "-"
    //token takes the string each time it is called and then it changes to next string
    //at the end it returns the value size of the array
    char *token;
    token = strtok(str, splitby);
    int i=0;
    while(token != NULL) {
        strcpy(arr[i],token);
        token = strtok(NULL, splitby);
        i++;
    }
    return i;
}

int verifyadmin(FILE *passkeytxt) {
    //actualpassword and actualusername are the paword and username that are stored in the file
    char *actualpassword, *actualusername;
    actualusername=(char*)malloc(20*sizeof(char));
    actualpassword=(char*)malloc(20*sizeof(char));
    //checking if the memory allocation was successful or not
    if(actualusername==NULL || actualpassword==NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }
    fgets(actualusername, 20, passkeytxt);
    remove_newline(actualusername);
    actualusername= realloc(actualusername, (strlen(actualusername)+1)*sizeof(char));
    fgets(actualpassword, 20, passkeytxt);
    remove_newline(actualpassword);
    actualpassword= realloc(actualpassword, (strlen(actualpassword)+1)*sizeof(char));
  
    char *username, *password;
    username=(char*)malloc(20*sizeof(char));
    password=(char*)malloc(20*sizeof(char));
    //checking if the memory allocation was successful or not
    if(username==NULL || password==NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }
    int counter=0;
    int maxattempts=3;
    while(1) {
        //I will use malloc to allocate memory for the username and password
        printf("Enter your admin username ");
        fgets(username, 20, stdin);
        remove_newline(username);
        printf("Enter your admin password ");
        fgets(password, 20, stdin);
        remove_newline(password);
        printf("%s and %s \n", actualusername,username);
        printf("%s and %s \n", actualpassword,password);
        if(strcmp(username, actualusername)==0 && strcmp(password, actualpassword)==0) {
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
        else {
            printf("Invalid username or password\n");
            printf("Try again\n");
            counter++;
            printf("You have %d attempts left\n", maxattempts-counter);
        }
        if(counter==maxattempts) {
            printf("You have exceeded the maximum number of attempts\n");
            return 0;
        }
    }
}

int read_file_with_initializing(FILE *fp,char *filename,char arr[][10][40]) {
    char str[200];
    //this function is used to read the file and initialize the array with the values from the file
    //it returns the count of the patients/doctors but if if the file is not found it returns 0 too since theres no info about the patients anyways
    fp=fopen(filename,"r");
    int count=0;
    if(fp==NULL) {
        printf("File not found\n");
        return 0;
    }
    while(fgets(str, sizeof(str), fp) != NULL) {
        remove_newline(str);
        split(str, arr[count],"-");
        count++;
    }
    return count;
}

int get_total_contentby_filename(char *filename) {
    int total_content;
    if(strcmp(filename,"patientinfo.txt")==0) {
        total_content=7;
    }
    else if(strcmp(filename,"doctorinfo.txt")==0) {
        //printf("This is the doctor file\n");
        total_content=6;
    }
    else if(strcmp(filename,"appointment_info.txt")==0) {
        total_content=5;
    }
    else if(strcmp(filename,"hospitalinfo.txt")==0) {
        total_content=10;
    }
    else {
        printf("Invalid file name\n");
        return -1;
    }
    return total_content;
}

int search_patient_by_name(char arr[][10][40],char *name,int total_size) {
    int store_serial[100];
    int count=0;
    printf("Possible patients");
    for(int i=0;i<total_size;i++) {
        if(strstr(str_to_lower(arr[i][1]),str_to_lower(name))) {
            store_serial[count]=i+1;
            count++;
            print_single_patient(arr,i);
            printf("\n");
        }
    }
    return 0;
}

int search_doctor_by_name(char arr[][10][40],char *name,int total_size) {
    int store_serial[100];
    int count=0;
    printf("Possible doctors");
    for(int i=0;i<total_size;i++) {
        if(strstr(str_to_lower(arr[i][1]),str_to_lower(name))) {
            store_serial[count]=i+1;
            count++;
            print_single_doctor(arr,i);
            printf("\n");
        }
    }
    return 0;
}

int search_appointment_by_name(char arr[][10][40],char *name,int total_size) {
    int store_serial[100];
    int count=0;
    printf("Possible appointments");
    for(int i=0;i<total_size;i++) {
        if(strstr(str_to_lower(arr[i][1]),str_to_lower(name))) {
            store_serial[count]=i+1;
            count++;
            print_single_appointment(arr,i);
            printf("\n");
        }
    }
    return count;
}

int update_array_content(char arr[][10][40],int index,int content_size) {
    printf("What do you want to update?\n");
    int option;
    if(content_size==7) {
        printf("Press 1 to update the name\n");
        printf("Press 2 to update the cabin room\n");
        printf("Press 3 to update the doctor\n");
        printf("Press 4 to update the disease\n");
        printf("Press 5 to update the drug name\n");
        printf("Press 6 to update the recovery time\n");
        scanf("%d",&option);
        if(!(option>=1&&option<=6)) {
            printf("Invalid option\n");
            return -1;
        }
        getchar();
        printf("Enter the new %s of the patient\n",patient_print_string[option]);
        fgets(arr[index][option], sizeof(arr[index][option]),stdin);
        remove_newline(arr[index][option]);
    }
    else if(content_size==6) {
        printf("Press 1 to update the name\n");
        printf("Press 2 to update the expertise\n");
        printf("Press 3 to update the checking day\n");
        printf("Press 4 to update the contact info\n");
        printf("Press 5 to update the visit fee\n");
        scanf("%d",&option);
        if(!(option>=1&&option<=5)) {
            printf("Invalid option\n");
            return -1;
        }
        getchar();
        printf("Enter the new %s of the doctor\n",doctor_print_string[option]);
        fgets(arr[index][option], sizeof(arr[index][option]),stdin);
        remove_newline(arr[index][option]);
    }
    else if(content_size==10) {
        printf("Press 1 to update the hospital name\n");
        printf("Press 2 to update the hospital address\n");
        printf("Press 3 to update the hospital owner\n");
        printf("Press 4 to update the max patient capacity\n");
        printf("Press 5 to update the total doctor\n");
        printf("Press 6 to update the total employee\n");
        printf("Press 7 to update the hospital phone number\n");
        printf("Press 8 to update the hospital email\n");
        printf("Press 9 to update the hospital website\n");
        printf("Press 10 to update the hospital year of establishment\n");
        scanf("%d",&option);
        if(!(option>=1&&option<=10)) {
            printf("Invalid option\n");
            return -1;
        }
        getchar();
        printf("Enter the new %s of the hospital\n",hospital_print_string[option-1]);
        fgets(arr[index][option-1], sizeof(arr[index][option-1]),stdin);
        remove_newline(arr[index][option-1]);
    }
    else {
        printf("Invalid option\n");
        return -1;
    }
    return 0;
}

int add_any_specific_index(char arr[][10][40],int index,int content_size) {
    char str[40];
    sprintf(arr[index][0],"%d",index+1);
    int j;
    for (int i=1;i<content_size;i++) {
        j=i;
        if(content_size==7) {
            printf("Enter the %s of the patient\n",patient_print_string[j]);
        }
        else if(content_size==6) {
            printf("Enter the %s of the Doctor\n",doctor_print_string[j]);
        }
        else if(content_size==10) {
            j=i-1;
            printf("Enter the %s of the hospital\n",hospital_print_string[j]);
        }
        fgets(str, sizeof(str),stdin);
        remove_newline(str);
        strcpy(arr[index][j],str);
    }
    if(content_size==10) {
        printf("Enter the hospital year of establishment\n");
        fgets(str, sizeof(str),stdin);
        remove_newline(str);
        strcpy(arr[index][9],str);
    }
    return 0;
}

int append_file_update_array(char arr[][10][40],int *total_size,char *filename) {
    int content_size=get_total_contentby_filename(filename);
    add_any_specific_index(arr,*total_size,content_size);
    *total_size=*total_size+1;
    return 0;
}

int update_file_add_newinfo_onindex_array(char arr[][10][40],int *total_size) {
    return 0;
}

int update_file_change_info_onindex_array(char arr[][10][40],int *total_size) {
    return 0;
}

int copy_write_file(FILE *fp,char *filename,char arr[][10][40],int total_size) {
    int total_content;
    total_content=get_total_contentby_filename(filename);

    fp=fopen(filename,"w");
    if(fp==NULL||total_content==-1) {
        printf("File not found\n");
        return -1;
    }
    for(int i=0;i<total_size;i++) {
        for(int j=0;j<total_content;j++) {
            fprintf(fp,"%s",arr[i][j]);
            if(j!=total_content-1) {
                fprintf(fp,"-");
            }
        }
        if(i!=total_size-1) {
            fprintf(fp,"\n");
        }
    }
    fclose(fp);
    return 1;
}

int delete_specific_index_array(char arr[][10][40],int index,int *total_size,int content_size) {
    for(int i=index;i<*total_size-1;i++) {
        for(int j=1;j<content_size;j++) {
            strcpy(arr[i][j],arr[i+1][j]);
        }
    }
    *total_size=*total_size-1;
    return 1;
}

int appoint_doctor_by_serialnumber(char doctorarr[][10][40],int doctor_serial_number,char appointarr[][10][40],int *appoint_size) {
    char patient_name[40];
    printf("Enter the name of the patient\n");
    clear_input_buffer();
    fgets(patient_name, sizeof(patient_name),stdin);
    remove_newline(patient_name);
    sprintf(appointarr[*appoint_size][0],"%d",*appoint_size+1);
    strcpy(appointarr[*appoint_size][1],patient_name);
    strcpy(appointarr[*appoint_size][2],doctorarr[doctor_serial_number-1][1]);
    strcpy(appointarr[*appoint_size][3],doctorarr[doctor_serial_number-1][2]);
    printf("Which day do you want to appoint the doctor?\n");
    char appoint_day[20][40];
    int length=split(doctorarr[doctor_serial_number-1][3],appoint_day,",");
    for(int i=0;i<length;i++) {
        printf("Press %d. for %s\n",i+1,appoint_day[i]);
    }
    int option;
    scanf("%d",&option);
    if(option<1||option>length) {
        printf("Invalid option\n");
        return -1;
    }
    strcpy(appointarr[*appoint_size][4],appoint_day[option-1]);
    (*appoint_size)++;
    printf("You have successfully appointed the doctor\n");
    return 0;
}

int main() {
    char arr[20][40];
    int count=0;//this is the count of the patients
    char patients[100][10][40];
    char doctors[100][10][40];
    char appoint[100][10][40];
    char hospital[1][10][40];
    char total_single_line_string[100];
    char input[] = "hello-My name Samsil Arefeen-How are you-so u are working-right"; 
    int length=split(input,arr,"-");
    for(int i=0;i<length;i++) {
        printf("%s\n",arr[i]);
    }
    FILE *adminpass=fopen("admin passkey.txt","r");
    printf("Welcome to VitalPro Hospital yoyoyo\n");
    printf("Are you Admin or Customer ? Press a if you are admin and press c if you are Customer");
    char customer_or_admin;
    char option;
    scanf(" %c",&customer_or_admin);
    getchar();
    customer_or_admin=tolower(customer_or_admin);
    
    if(customer_or_admin=='a') {
        if(verifyadmin(adminpass)) {
            //something to do with admin
            printf("What do you want to do?\n");
            printf("Press p for if related patient info\n");
            printf("Press d for if related doctor info\n");
            printf("Press h for if related hospital info\n");
            scanf(" %c",&option);
            
            if(option=='p') {  
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
                if(option=='1') {
                    //add a new patient
                    clear_input_buffer();
                    append_file_update_array(patients,&patient_size,patient_filename);
                    print_patient(patients,patient_size);
                    printf("%d\n",patient_size );
                    copy_write_file(patienttxt,patient_filename,patients,patient_size);
                }
                
                if(option=='2') {
                    //view all patients
                    print_patient(patients,patient_size);
                }
                
                if(option=='3'||option=='4'||option=='5') {
                    //search for a patient
                    if(option=='4') { 
                        printf("To update a patient you need to search for the patient first\n");
                    }
                    char new_option;
                    char printoption[3][10]={"search","update","delete"};
                    
                    printf("How do you want to %s\n",printoption[option-'3']);
                    printf("Press 1 to %s by serial number\n",printoption[option-'3']);
                    printf("Press 2 to %s by name\n",printoption[option-'3']);
                    scanf(" %c",&new_option);
                    
                    if(new_option=='1') {
                        //search by serial number
                        printf("Enter the serial number of the patient\n");
                        int serial_number;
                        scanf("%d",&serial_number);
                        print_single_patient(patients,serial_number-1);
                        
                        if(option=='4') {
                            update_array_content(patients,serial_number-1,7);
                            print_patient(patients,patient_size);
                            copy_write_file(patienttxt,patient_filename,patients,patient_size);
                        }  
                        
                        if(option=='5') {
                            delete_specific_index_array(patients,serial_number-1,&patient_size,7);
                            print_patient(patients,patient_size);
                            copy_write_file(patienttxt,patient_filename,patients,patient_size);
                        }
                    }
                    
                    if(new_option=='2') {
                        //search by name
                        printf("Enter the name or sub name of the patient\n");
                        char name[40];
                        clear_input_buffer();
                        fgets(name, sizeof(name),stdin);
                        remove_newline(name);
                        search_patient_by_name(patients,name,patient_size);
                    
                        if(option=='4'||option=='5') {
                            //update a patient 
                            printf("Enter the serial number of the patient\n");
                            int serial_number;
                            scanf("%d",&serial_number);
                            
                            if(option=='4') {
                                update_array_content(patients,serial_number-1,7);
                                print_patient(patients,patient_size);
                                copy_write_file(patienttxt,patient_filename,patients,patient_size);
                            }
                            
                            if(option=='5') {
                                delete_specific_index_array(patients,serial_number-1,&patient_size,7);
                                print_patient(patients,patient_size);
                                copy_write_file(patienttxt,patient_filename,patients,patient_size);
                            }
                        }
                    }
                }
            }
            else if (option=='d') {
                //something to do with doctor
                FILE *doctortxt;
                char *doctor_filename="doctorinfo.txt";
                printf("Here are serveral options for you\n");
                printf("Press 1 to add a new doctor\n");
                printf("Press 2 to view all doctors\n");
                printf("Press 3 to search for a doctor\n");
                printf("Press 4 to update a doctor\n");
                printf("Press 5 to delete a doctor\n");
                printf("Press 6 to exit\n");
                int doctor_size=read_file_with_initializing(doctortxt,doctor_filename,doctors);
                
                scanf(" %c",&option);
                if(option=='1') {
                    //add a new doctor
                    clear_input_buffer();
                    append_file_update_array(doctors,&doctor_size,doctor_filename);
                    print_doctor(doctors,doctor_size);
                    copy_write_file(doctortxt,doctor_filename,doctors,doctor_size);
                }
                
                if(option=='2') {
                    //view all doctors
                    print_doctor(doctors,doctor_size);
                }
                
                if(option=='3'||option=='4'||option=='5') {
                    //search for a doctor
                    if(option=='4') { 
                        printf("To update a doctor you need to search for the doctor first\n");
                    }
                    char new_option;
                    char printoption[3][10]={"search","update","delete"};
                    
                    printf("How do you want to %s\n",printoption[option-'3']);
                    printf("Press 1 to %s by serial number\n",printoption[option-'3']);
                    printf("Press 2 to %s by name\n",printoption[option-'3']);
                    scanf(" %c",&new_option);
                    
                    if(new_option=='1') {
                        //search by serial number
                        printf("Enter the serial number of the doctor\n");
                        int serial_number;
                        scanf("%d",&serial_number);
                        print_single_doctor(doctors,serial_number-1);
                        
                        if(option=='4') {
                            update_array_content(doctors,serial_number-1,6);
                            print_doctor(doctors,doctor_size);
                            copy_write_file(doctortxt,doctor_filename,doctors,doctor_size);
                        }  
                        
                        if(option=='5') {
                            delete_specific_index_array(doctors,serial_number-1,&doctor_size,6);
                            print_doctor(doctors,doctor_size);
                            copy_write_file(doctortxt,doctor_filename,doctors,doctor_size);
                        }
                    }
                    
                    if(new_option=='2') {
                        //search by name
                        printf("Enter the name or sub name of the doctor\n");
                        char name[40];
                        clear_input_buffer();
                        fgets(name, sizeof(name),stdin);
                        remove_newline(name);
                        search_doctor_by_name(doctors,name,doctor_size);
                    
                        if(option=='4'||option=='5') {
                            //update a doctor 
                            printf("Enter the serial number of the doctor\n");
                            int serial_number;
                            scanf("%d",&serial_number);
                            
                            if(option=='4') {
                                update_array_content(doctors,serial_number-1,6);
                                print_doctor(doctors,doctor_size);
                                copy_write_file(doctortxt,doctor_filename,doctors,doctor_size);
                            }
                            
                            if(option=='5') {
                                delete_specific_index_array(doctors,serial_number-1,&doctor_size,6);
                                print_doctor(doctors,doctor_size);
                                copy_write_file(doctortxt,doctor_filename,doctors,doctor_size);
                            }
                        }
                    }
                }
            }
            else if (option=='h') {
                //something to do with hospital
                FILE *hospitaltxt;
                char *hospital_filename="hospitalinfo.txt";
                printf("Here are serveral options for you\n");
                printf("Press 1 to view all hospital info\n");
                printf("Press 2 to change all hospital info\n");
                printf("Press 3 to update hospital info\n");
                printf("Press 4 to exit\n");
                int hospital_size=read_file_with_initializing(hospitaltxt,hospital_filename,hospital);
                scanf(" %c",&option);
                
                if(option=='1') {
                    //view all hospital info
                    if(hospital_size!=0) {
                        print_hospital_info(hospital);
                    }
                    else {
                        printf("No hospital info found\n");
                    }
                }
                
                if(option=='2') {
                    //change all hospital info
                    clear_input_buffer();
                    add_any_specific_index(hospital,0,10);
                    copy_write_file(hospitaltxt,hospital_filename,hospital,1);
                }
                
                if(option=='3') {
                    update_array_content(hospital,0,10);
                    print_hospital_info(hospital);
                    copy_write_file(hospitaltxt,hospital_filename,hospital,1);
                }
            }
        }
    }
    else if(customer_or_admin=='c') {
        //something to do with customer
        printf("Welcome how can we help you?\n");
        printf("Press 1 to view all doctors\n");
        printf("Press 2 to search for a doctor\n");
        printf("Press 3 to appoint a doctor\n");
        printf("Press 4 to find your appointment\n");
        printf("Press 5 to delete your appointment\n");
        FILE *doctortxt,*appointxt;
        char *apointment_filename="appointment_info.txt";
        char *doctor_filename="doctorinfo.txt";

        int doctor_size=read_file_with_initializing(doctortxt,doctor_filename,doctors);
        int appoint_size=read_file_with_initializing(appointxt,apointment_filename,appoint);
        scanf(" %c",&option);
        
        if(option=='1') {
            //view all doctors
            print_doctor(doctors,doctor_size);
        }
        
        if(option=='2') {
            //search for a doctor
            char new_option;
            printf("Press 1 to search by serial number\n");
            printf("Press 2 to search by name\n");
            printf("Press 4 to exit\n");
            scanf(" %c",&new_option);
            
            if(new_option=='1') {
                //search by serial number
                printf("Enter the serial number of the doctor\n");
                int serial_number;
                scanf("%d",&serial_number);
                print_single_doctor(doctors,serial_number-1);
            }
            
            if(new_option=='2') {
                //search by name
                printf("Enter the name or sub name of the doctor\n");
                char name[40];
                clear_input_buffer();
                fgets(name, sizeof(name),stdin);
                remove_newline(name);
                search_doctor_by_name(doctors,name,doctor_size);
            }
        }
        
        if(option=='3') {
            char new_option;
            printf("Press 1 to appoint by serial number\n");
            printf("Press 2 to appoint by name\n");
            scanf(" %c",&new_option);
            
            //appoint a doctor
            //search by doctor name
            if(new_option=='2') {
                //search by name
                printf("Enter the name or sub name of the doctor\n");
                char name[40];
                clear_input_buffer();
                fgets(name, sizeof(name),stdin);
                remove_newline(name);
                search_doctor_by_name(doctors,name,doctor_size);
            }
            
            if(new_option=='1'||new_option=='2') {
                printf("Enter the serial number of the doctor\n");
                int serial_number;
                scanf("%d",&serial_number);
                appoint_doctor_by_serialnumber(doctors,serial_number,appoint,&appoint_size);
                copy_write_file(appointxt,apointment_filename,appoint,appoint_size);
            }
        }
        
        if(option=='4'||option=='5') {
            int new_option;
            if(appoint_size==0) {
                printf("You have no appointment\n");
                exit(0);
            }
            
            char printoption[3][10]={"search","delete"};
            printf("Press 1 to %s by serial number\n",printoption[option-'4']);
            printf("Press 2 to %s by name\n",printoption[option-'4']);
            scanf(" %d",&new_option);
            
            if(new_option==2) {
                //search by name
                printf("Enter the name or sub name of the patient\n");
                char name[40];
                clear_input_buffer();
                fgets(name, sizeof(name),stdin);
                remove_newline(name);
                search_appointment_by_name(appoint,name,appoint_size);
            }
            
            if(new_option==1||new_option==2) {
                //search by serial number
                printf("Enter the serial number of the appointment\n");
                int serial_number;
                scanf("%d",&serial_number);
                print_single_appointment(appoint,serial_number-1);
                
                if(option=='5') {
                    delete_specific_index_array(appoint,serial_number-1,&appoint_size,5);
                    print_appointment(appoint,appoint_size);
                    copy_write_file(appointxt,apointment_filename,appoint,appoint_size);
                }
            }
        }
    }
    else {
        exit(0);
    }
    
    return 0;
}