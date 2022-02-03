#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>


#ifdef _WIN32
    #define clear_screen "cls"

#elif __linux__
    #define clear_screen "clear"

#endif



int add_contact();
int list_contacts();
int search_contact();
int edit_contact();
int delete_contact();
int exit_contacts();

int display_menu();
void save_contact();
void extract_from_tag();
int get_contact();
int find_contact();
int copy_lines();
int jump_lines();
int delete_con();


int main(void) {
    
    int (*func_arr[6])(void) = {exit_contacts, add_contact, list_contacts, search_contact, edit_contact, delete_contact};
    int status = 0;

    while (status == 0){
        status = (*func_arr[display_menu()])();
    }


    fprintf(stderr, "Unknown error encounterd, exiting program...");
    exit(EXIT_FAILURE);
}

int display_menu() {

    printf("*** CONTACT MANAGEMENT SYSTEM ***\n\n\n");
    printf("            MAIN MENU            \n");
    printf("=================================\n");
    printf("[1] Add a new Contact            \n");
    printf("[2] List all Contacts            \n");
    printf("[3] Search for a Contact         \n");
    printf("[4] Edit a Contact               \n");
    printf("[5] Delete a Contact             \n");
    printf("[0] Exit                         \n");
    printf("=================================\n");
    printf("Enter a choice: ");
    
    int choice;
    char buffer[100];

    fgets(buffer, 100, stdin);
    sscanf(buffer, "%d", &choice);

    if (choice < 0 || choice > 5){
    
        printf("\nUnrecognized response, valid values are 0-5");
        printf("\nExiting program...");
        exit(EXIT_FAILURE);
    
    }

    system(cleare_screen);
    return choice;


}

int add_contact() {

    printf("*** CONTACT MANAGEMENT SYSTEM ***\n\n\n");
    printf("           ADD CONTACT           \n");
    printf("=================================\n");

    char buffer[100];
    char name[100], tel_num[100];

    printf("Enter contacts name: ");
    fgets(buffer, 100, stdin);
    sscanf(buffer,"%s", name);

    printf("\nEnter contacts telephone number: ");
    fgets(buffer, 100, stdin);
    sscanf(buffer,"%s", tel_num);

    save_contact(name, tel_num);



    return 0;
}

int list_contacts(){ 

    printf("*** CONTACT MANAGEMENT SYSTEM ***\n\n\n");
    printf("          LIST CONTACTS           \n");
    printf("=================================\n");

    FILE* fptr_database;

    fptr_database = fopen("contacts.txt", "r");

    if (fptr_database == NULL) {
        perror("Error::");
        exit(EXIT_FAILURE);
    }

    char line[150];

    char name[100], tel_num[100];
    int i = 0;

    while ( fgets(line, 150, fptr_database) != NULL ) {

        if (strcmp("<contact>\n", line) == 0) {
        
            fgets(line, 150, fptr_database);
            extract_from_tag(line, "\t<name>", name);
        
            fgets(line, 150, fptr_database);
            extract_from_tag(line, "\t<tel>", tel_num);
        
            fgets(line, 150, fptr_database);

            printf("\nContact:\n\tName: %s\n\tTelephone number: %s\n", name, tel_num);
        }

    }

    fclose(fptr_database);

     printf("\n\n\tPress ENTER to exit");

    getc(stdin);
    system(cleare_screen);
    return 0;
}

int search_contact(){ 

    printf("*** CONTACT MANAGEMENT SYSTEM ***\n\n\n");
    printf("           SEARCH CONTACT           \n");
    printf("=================================\n");
    
    char line[150];
    char s_name[100], tel_num[100];
    printf("Enter contacts name: ");
    fgets(line, 150, stdin);
    sscanf(line, "%s", s_name);

    int found = get_contact(s_name, tel_num);

    if (!found) {
        printf("You do not have contact '%s' ", s_name);
    } else {
        printf("\nContact:\n\tName: %s\n\tTelephone number: %s\n", s_name, tel_num);
    }

    printf("\n\n\tPress ENTER to exit");

    getc(stdin);
    system(cleare_screen);
    return 0;
}

int delete_contact(){

    printf("*** CONTACT MANAGEMENT SYSTEM ***\n\n\n");
    printf("          DELETE CONTACT           \n");
    printf("=================================\n");
 
    char line[150], s_name[100];

    printf("Enter contacts name: ");
    fgets(line, 150, stdin);
    sscanf(line, "%s", s_name);

    if (delete_con(s_name) != 0) {
        return 0;
    }

    printf("\nContact sucessfully deleted...\n\n\tPress ENTER to exit");

    getc(stdin);
    system(cleare_screen);

    return 0;

}

int edit_contact(){

    printf("*** CONTACT MANAGEMENT SYSTEM ***\n\n\n");
    printf("           EDIT CONTACT           \n");
    printf("=================================\n");
  
    char line[150], s_name[100];
    int fpos;

    printf("Enter contacts name: ");
    fgets(line, 150, stdin);
    sscanf(line, "%s", s_name);

    int status = find_contact(s_name, &fpos);

    if (!status) {
        printf("Contact '%s' does not exist...", s_name);
    } else {

        char name[100], tel_num[100];

        printf("\nEnter contacts NEW name: ");
        fgets(line, 150, stdin);
        sscanf(line, "%s", name);

        printf("\nEnter contacts NEW telephone number: ");
        fgets(line, 150, stdin);
        sscanf(line, "%s", tel_num);

        delete_con(s_name);
        save_contact(name, tel_num);

        printf("\nSuccessfully edited the contact...");

    }

    printf("\n\n\tPress ENTER to exit");

    getc(stdin);
    system(cleare_screen);

    return 0;

}

int exit_contacts(){
    system(cleare_screen);
    printf("Exiting the application...");
    exit(EXIT_SUCCESS);
}

void save_contact(char* name, char* tel_num) {

    FILE *fptr_database;

    fptr_database = fopen("contacts.txt", "a");

    if (fptr_database == NULL) {
        perror("Error::");
        exit(EXIT_FAILURE);
    }

    fprintf(fptr_database, "<contact>\n\t<name>%s</name>\n\t<tel>%s</tel>\n</contact>\n",name, tel_num);

    fclose(fptr_database);

}

int get_contact(char *s_name, char *tel_num) {

    FILE* fptr_database;
    char line[150], name[100];
    int found = 0;

    fptr_database = fopen("contacts.txt", "r");

    if (fptr_database == NULL) {
        perror("Error::");
        exit(EXIT_FAILURE);
    }


    while ( fgets(line, 150, fptr_database) != NULL ) {

        if (strcmp("<contact>\n", line) == 0) {
        
            fgets(line, 150, fptr_database);
            extract_from_tag(line, "\t<name>", name);

            if (strcmp(s_name, name) == 0) {

                fgets(line, 150, fptr_database);
                extract_from_tag(line, "\t<tel>", tel_num);
            
                fclose(fptr_database);
                return 1;
            }
        }

    }

    fclose(fptr_database);
    return 0;
}

int find_contact(char *s_name, int *fpos) {

    FILE* fptr_database;

    fptr_database = fopen("contacts.txt", "r");

    if (fptr_database == NULL) {
        perror("Error::");
        exit(EXIT_FAILURE);
    }

    char line[150];

    char name[100], tel_num[100];

    while ( fgets(line, 150, fptr_database) != NULL ) {
        *fpos = ftell(fptr_database) - strlen(line) - 1;
        if (strcmp("<contact>\n", line) == 0) {
        
            fgets(line, 150, fptr_database);
            extract_from_tag(line, "\t<name>", name);

            if (strcmp(s_name, name) == 0) {
                fclose(fptr_database);
                return 1;
            }
        }

    }

    fclose(fptr_database);
    *fpos = -1;
    return 0;


}

void extract_from_tag(char *line, char *tag, char *val) {

    int offset = strlen(tag);
    int tag_len = strlen(tag);
    int line_len = strlen(line);

    while (offset != line_len - tag_len - 1) {
        val[offset - tag_len] = line[offset];
        offset++;
    }
    val[offset - tag_len] = '\0';
}

// Copy n_lines from src file to dst file
int copy_lines(int n_lines, FILE *src, FILE *dst) {

    char line[150];

    while (n_lines > 0) {

        if ( fgets(line, 150, src) == NULL){ return -1; }
        fputs(line, dst);
        n_lines--;
    }

    return 0;

}

// Jump n_lines in file, must make sure n_lines is <= number of remaining lines
int jump_lines(int n_lines, FILE *fptr) {

    char line[150];

    while( n_lines > 0) {
        if (fgets(line, 150, fptr) == NULL) {
            fprintf(stderr, "EOF encounterd when not expected at %d. %s", __LINE__ - 1, __func__);
            exit(EXIT_FAILURE);
        }
        n_lines--;
    }
    
    return 0;
}

int delete_con(char *s_name){

    int fpos;
    find_contact(s_name, &fpos);

    if (fpos == -1) {
        printf("Contact '%s' does not exist...", s_name);
        printf("\n\n\tPress ENTER to exit");

        getc(stdin);
        system(cleare_screen);

        return -1;
    }

    FILE *fptr_database;
    
    fptr_database = fopen("contacts.txt", "r");

    if (fptr_database == NULL) {
        perror("Error::");
        exit(EXIT_FAILURE);
    }

    FILE *copy_file;

    copy_file = fopen("copy.txt", "w");

    if (copy_file == NULL) {
        perror("Error::");
        exit(EXIT_FAILURE);
    }

    do {

        if (fpos == ftell(fptr_database)) {
            jump_lines(4, fptr_database); // skip entire contact entry
        }
    
     } while ( copy_lines(4, fptr_database, copy_file) != -1 ); // copy entire contact entry

    fclose(fptr_database);
    fclose(copy_file);

    remove("contacts.txt");
    rename("copy.txt", "contacts.txt");

    return 0;
}

