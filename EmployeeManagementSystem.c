#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct emp {
    int id;
    char name[100];
    char desgn[10];
    float sal;
    char jdate[9]; 
    char gender[10];
    char branch[50];
    char psaddr[200];
    char prtaddr[200];
    char phone[15];
    char mail[20];
};

typedef struct emp Employee;

void printChar(char ch, int n);
void printHead();
void welcome();
void add(Employee e, FILE *fp);
void del(int id, FILE *fp);
void modify(int id, FILE *fp);
void displayList(FILE *fp);
void searchRecord(int id, FILE *fp);
void displayBasic(FILE *fp);
void basicContact(FILE *fp);
void maleEmp(FILE *fp);
void femaleEmp(FILE *fp);
void fromDhaka(FILE *fp);
void fromOthers(FILE *fp);
void mainBranch(FILE *fp);
void otherBranch(FILE *fp);

/**
 * Function to clear the screen based on the operating system.
 * On Windows systems, it uses the "cls" command to clear the console.
 * On Unix-like systems (Linux, macOS), it uses the "clear" command.
 */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    FILE *fp;
    Employee e;
    int option;
    char username[10], password[10];

    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL) {
        if ((fp = fopen("employeeInfo.txt", "wb+")) == NULL) {
              perror("Can't open or create file");
            return 1;
        }
    }

    printHead();
    welcome();
    printHead();

    printf("\n\t\t\t\t  Login Screen");
    printf("\n\t\t\t      Enter Your Credential");
    printf("\n\n\n\t\tUsername: ");
    scanf("%s", username);
    getchar();  // Consume the newline character in the input buffer

   printf("\n\t\tPassword: ");
	// Read the password without echoing to the screen
	int i = 0;
	while (i < 9) {  // Limiting password length to 9 characters
	    char ch = getch(); // Use getch() to read characters without echoing
	    if (ch == '\n' || ch == '\r') {
	        password[i] = '\0';  // Null-terminate the password array
	        break;
	    } else if (ch == 127 || ch == 8) { // Backspace key
	        if (i > 0) {
	            i--;
	            printf("\b \b");  // Erase the character from the screen
	        }
	    } else {
	        password[i] = ch;
	        printf("*");  // Print asterisk instead of the actual character
	        i++;
	    }
	}

    // Verify the username and password
    if ((strcasecmp(username, "admin") == 0) && (strcasecmp(password, "pass") == 0)) {
        // Authentication successful, proceed to the main menu
        printf("\nAuthentication successful!\n");
        while (1) {
            printHead();
            printf("\n\t\t\t\tMain Menu");
            printf("\n\n\n");

            // Display the menu options
            printf("\n\n\t\t\t1. Add Employee");
            printf("\n\n\t\t\t2. Delete Employee");
            printf("\n\n\t\t\t3. Modify Employee");
            printf("\n\n\t\t\t4. Display Employee List");
            printf("\n\n\t\t\t5. Search Record");
            printf("\n\n\t\t\t6. Display Basic Info");
            printf("\n\n\t\t\t7. Display Basic Contact Info");
            printf("\n\n\t\t\t8. List of Male Employee");
            printf("\n\n\t\t\t9. List of Female Employee");
            printf("\n\n\t\t\t10. List of Employee From Dhaka");
            printf("\n\n\t\t\t11. List of Employee From Others District");
            printf("\n\n\t\t\t12. List of Employee of Main Branch");
            printf("\n\n\t\t\t13. List of Employee of Others Branch");
            printf("\n\n\t\t\t0. EXIT");

            printf("\n\n\t\tEnter Your Option :--> ");
            scanf("%d", &option);

            // Handle user selection
            switch (option) {
                case 0: 
                    fclose(fp); // Close the file before exiting
                    return 0;
                case 1: 
                    add(e, fp); 
                    break;
                case 2: 
                    printf("\n\n\t\tEnter ID to search: ");
					    scanf("%d", &e.id);
					    del(e.id, fp);
					    break;
                case 3:
			    // Prompt user to enter the ID of the employee to modify
			    printf("\n\n\t\tEnter the ID of the employee to modify: ");
			    scanf("%d", &e.id);
			    modify(e.id, fp);
			    break;

                case 4: 
                    displayList(fp); 
                    break;
                case 5:
					    printf("\n\n\t\tEnter ID to search: ");
					    scanf("%d", &e.id);
					    searchRecord(e.id, fp);
					    break;
                case 6: 
                    displayBasic(fp); 
                    break;
                case 7: 
                    basicContact(fp); 
                    break;
                case 8: 
                    maleEmp(fp); 
                    break;
                case 9: 
                    femaleEmp(fp); 
                    break;
                case 10: 
                    fromDhaka(fp); 
                    break;
                case 11: 
                    fromOthers(fp); 
                    break;
                case 12: 
                    mainBranch(fp); 
                    break;
                case 13: 
                    otherBranch(fp); 
                    break;
                default:
                    printf("\n\t\tYou pressed the wrong key");
                    printf("\n\t\tPlease enter a valid option.\n");
            }
        }
    } else {
        printf("\n\t\tLogin Failed");
    }

    fclose(fp); // Close the file before exiting in case of login failure
    return 0;
}

void welcome() {
    printf("\n\n\n\n\n\t\t[ [ [ WELCOME TO OUR EMPLOYEE MANAGEMENT SYSTEM ] ] ]\n\n\n\n\n\n\n\t");
    printf("Press Enter to continue...");
    getchar(); // Wait for user input
}

void printChar(char ch, int n) {
    while (n--) {
        putchar(ch);
    }
}

void printHead() {	
    clearScreen();
    printf("\t");
    printChar('=', 65);
    printf("\n\t");
    printChar('=', 16);
    printf("[EMPLOYEE] [MANAGEMENT] [SYSTEM]");
    printChar('=', 16);
    printf("\n\t");
    printChar('=', 65);
}

void add(Employee e, FILE *fp) {
    printHead();
    printf("\n\t\t\tAdd Employee");
    char another = 'y';

    fseek(fp, 0, SEEK_END);
    while (another == 'y' || another == 'Y') {
        printf("\n\n\t\tEnter ID number: ");
        scanf("%d", &e.id);

        printf("\n\n\t\tEnter Full Name of Employee [John Doe]: ");
        getchar(); // Consume the newline left in the input buffer
        fgets(e.name, sizeof(e.name), stdin);
        e.name[strcspn(e.name, "\n")] = '\0'; // Remove newline if present
        if (strlen(e.name) == 0) {
            strcpy(e.name, "John Doe");
        }

        printf("\n\n\t\tEnter Designation [Manager]: ");
        fgets(e.desgn, sizeof(e.desgn), stdin);
        e.desgn[strcspn(e.desgn, "\n")] = '\0'; // Remove newline if present
        if (strlen(e.desgn) == 0) {
            strcpy(e.desgn, "Manager");
        }

        printf("\n\n\t\tEnter Gender [Male]: ");
        fgets(e.gender, sizeof(e.gender), stdin);
        e.gender[strcspn(e.gender, "\n")] = '\0'; // Remove newline if present
        if (strlen(e.gender) == 0) {
            strcpy(e.gender, "Male");
        }

        printf("\n\n\t\tEnter Branch [Dhaka]: ");
        fgets(e.branch, sizeof(e.branch), stdin);
        e.branch[strcspn(e.branch, "\n")] = '\0'; // Remove newline if present
        if (strlen(e.branch) == 0) {
            strcpy(e.branch, "Dhaka");
        }

        printf("\n\n\t\tEnter Salary [50000.00]: ");
        scanf("%f", &e.sal);
        if (e.sal == 0) {
            e.sal = 50000.00;
        }

        printf("\n\n\t\tEnter Joining Date (YYYYMMDD) [20240101]: ");
        scanf("%8s", e.jdate); // Read the date directly into the jdate field
        if (strlen(e.jdate) == 0) {
            strcpy(e.jdate, "20240101");
        }

        printf("\n\n\t\tEnter Present Address: ");
        getchar(); // Consume the newline left in the input buffer
        fgets(e.psaddr, sizeof(e.psaddr), stdin);
        e.psaddr[strcspn(e.psaddr, "\n")] = '\0'; // Remove newline if present

        printf("\n\n\t\tEnter Permanent Address: ");
        fgets(e.prtaddr, sizeof(e.prtaddr), stdin);
        e.prtaddr[strcspn(e.prtaddr, "\n")] = '\0'; // Remove newline if present

        printf("\n\n\t\tEnter Phone: ");
        fgets(e.phone, sizeof(e.phone), stdin);
        e.phone[strcspn(e.phone, "\n")] = '\0'; // Remove newline if present

        printf("\n\n\t\tEnter E-mail: ");
        fgets(e.mail, sizeof(e.mail), stdin);
        e.mail[strcspn(e.mail, "\n")] = '\0'; // Remove newline if present

        fwrite(&e, sizeof(e), 1, fp);

        printf("\n\n\t\tWant to enter another employee info (Y/N): ");
        getchar(); // Consume the newline left in the input buffer
        another = getchar();
    }

    printf("\n\t\tEmployee(s) added successfully!");
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar(); // Wait for user input
}

void del(int id, FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tDelete Employee");

    // Declare variables
    Employee e;
    int flag = 0, siz = sizeof(e);
    FILE *ft;

    // Open a temporary file for writing
    if ((ft = fopen("temp.txt", "wb+")) == NULL) {
        perror("temp.txt");
        return;
    }

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Read through the file and copy all records except the one to delete
    while (fread(&e, siz, 1, fp) == 1) {
        if (e.id == id) {
            flag = 1;
            printf("\n\tRecord Deleted for");
            printf("\n\t\t%s\n", e.name);
            continue;
        }
        fwrite(&e, siz, 1, ft);
    }

    // Close the files
    fclose(fp);
    fclose(ft);

    // Remove the original file and rename the temporary file
    remove("employeeInfo.txt");
    rename("temp.txt", "employeeInfo.txt");

    // Reopen the file in read-write mode
    if ((fp = fopen("employeeInfo.txt", "rb+")) == NULL) {
        perror("Can't open file");
        return;
    }

    // Print message if record not found
    if (!flag) {
        printf("\n\n\t\tNo record found with the given ID.");
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void modify(int id, FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tModify Employee");

    // Declare variables
    Employee e;
    int flag = 0, siz = sizeof(e);
    long int recsize = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Read through the file and modify the record with the given ID
    while (fread(&e, recsize, 1, fp) == 1) {
        if (e.id == id) {
            flag = 1;
            printf("\n\n\t\tEnter new details for Employee ID %d:", id);

            printf("\n\n\t\tEnter Full Name of Employee: ");
            getchar(); // Consume the newline left in the input buffer
            fgets(e.name, sizeof(e.name), stdin);
            e.name[strcspn(e.name, "\n")] = '\0'; // Remove newline if present

            printf("\n\n\t\tEnter Designation: ");
            fgets(e.desgn, sizeof(e.desgn), stdin);
            e.desgn[strcspn(e.desgn, "\n")] = '\0'; // Remove newline if present

            printf("\n\n\t\tEnter Gender: ");
            fgets(e.gender, sizeof(e.gender), stdin);
            e.gender[strcspn(e.gender, "\n")] = '\0'; // Remove newline if present

            printf("\n\n\t\tEnter Branch: ");
            fgets(e.branch, sizeof(e.branch), stdin);
            e.branch[strcspn(e.branch, "\n")] = '\0'; // Remove newline if present

            printf("\n\n\t\tEnter Salary: ");
            scanf("%f", &e.sal);

            printf("\n\n\t\tEnter Joining Date (YYYYMMDD): ");
            scanf("%8s", e.jdate); // Read the date directly into the jdate field

            printf("\n\n\t\tEnter Present Address: ");
            getchar(); // Consume the newline left in the input buffer
            fgets(e.psaddr, sizeof(e.psaddr), stdin);
            e.psaddr[strcspn(e.psaddr, "\n")] = '\0'; // Remove newline if present

            printf("\n\n\t\tEnter Permanent Address: ");
            fgets(e.prtaddr, sizeof(e.prtaddr), stdin);
            e.prtaddr[strcspn(e.prtaddr, "\n")] = '\0'; // Remove newline if present

            printf("\n\n\t\tEnter Phone: ");
            fgets(e.phone, sizeof(e.phone), stdin);
            e.phone[strcspn(e.phone, "\n")] = '\0'; // Remove newline if present

            printf("\n\n\t\tEnter E-mail: ");
            fgets(e.mail, sizeof(e.mail), stdin);
            e.mail[strcspn(e.mail, "\n")] = '\0'; // Remove newline if present

            fseek(fp, -recsize, SEEK_CUR); // Move the file pointer to the beginning of the current record
            fwrite(&e, recsize, 1, fp); // Overwrite the current record with the modified one
            break; // Exit the loop since the modification is done
        }
    }

    // Print message if record not found
    if (!flag) {
        printf("\n\n\t\tNo record found with the given ID.");
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar(); // Wait for user input
}

void displayList(FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tEmployee List");

    // Declare variables
    Employee e;
    int i, siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Print table header
    printf("\n\n\t\tID\tName\t\tDesignation\tSalary\t\tJoining Date\tGender\t\tBranch\t\tPhone\t\tEmail");

    // Read through the file and display each record
    while (fread(&e, siz, 1, fp) == 1) {
        printf("\n\t\t%d\t%s\t\t%s\t%.2f\t\t%s\t%s\t\t%s\t\t%s\t\t%s", e.id, e.name, e.desgn, e.sal, e.jdate, e.gender, e.branch, e.phone, e.mail);
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void searchRecord(int id, FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tSearch Employee Record");

    // Declare variables
    Employee e;
    int flag = 0, siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Read through the file and search for the record with the given ID
    while (fread(&e, siz, 1, fp) == 1) {
        if (e.id == id) {
            flag = 1;
            printf("\n\n\t\tID: %d", e.id);
            printf("\n\t\tName: %s", e.name);
            printf("\n\t\tDesignation: %s", e.desgn);
            printf("\n\t\tSalary: %.2f", e.sal);
            printf("\n\t\tJoining Date: %s", e.jdate);
            printf("\n\t\tGender: %s", e.gender);
            printf("\n\t\tBranch: %s", e.branch);
            printf("\n\t\tPresent Address: %s", e.psaddr);
            printf("\n\t\tPermanent Address: %s", e.prtaddr);
            printf("\n\t\tPhone: %s", e.phone);
            printf("\n\t\tEmail: %s", e.mail);
            break;
        }
    }

    // Print message if record not found
    if (!flag) {
        printf("\n\n\t\tNo record found with the given ID.");
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void displayBasic(FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tBasic Employee Info");

    // Declare variables
    Employee e;
    int siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Print table header
    printf("\n\n\t\tID\tName\t\tDesignation\tBranch");

    // Read through the file and display basic info for each record
    while (fread(&e, siz, 1, fp) == 1) {
        printf("\n\t\t%d\t%s\t\t%s\t%s", e.id, e.name, e.desgn, e.branch);
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void basicContact(FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tBasic Contact Info");

    // Declare variables
    Employee e;
    int siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Print table header
    printf("\n\n\t\tID\tName\t\tPhone\t\tEmail");

    // Read through the file and display contact info for each record
    while (fread(&e, siz, 1, fp) == 1) {
        printf("\n\t\t%d\t%s\t\t%s\t\t%s", e.id, e.name, e.phone, e.mail);
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void maleEmp(FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tMale Employees");

    // Declare variables
    Employee e;
    int siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Print table header
    printf("\n\n\t\tID\tName\t\tGender");

    // Read through the file and display male employees
    while (fread(&e, siz, 1, fp) == 1) {
        if (strcasecmp(e.gender, "Male") == 0) {
            printf("\n\t\t%d\t%s\t\t%s", e.id, e.name, e.gender);
        }
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void femaleEmp(FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tFemale Employees");

    // Declare variables
    Employee e;
    int siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Print table header
    printf("\n\n\t\tID\tName\t\tGender");

    // Read through the file and display female employees
    while (fread(&e, siz, 1, fp) == 1) {
        if (strcasecmp(e.gender, "Female") == 0) {
            printf("\n\t\t%d\t%s\t\t%s", e.id, e.name, e.gender);
        }
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void fromDhaka(FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tEmployees from Dhaka");

    // Declare variables
    Employee e;
    int siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Print table header
    printf("\n\n\t\tID\tName\t\tBranch");

    // Read through the file and display employees from Dhaka
    while (fread(&e, siz, 1, fp) == 1) {
        if (strcasecmp(e.branch, "Dhaka") == 0) {
            printf("\n\t\t%d\t%s\t\t%s", e.id, e.name, e.branch);
        }
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void fromOthers(FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tEmployees from Other Branches");

    // Declare variables
    Employee e;
    int siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Print table header
    printf("\n\n\t\tID\tName\t\tBranch");

    // Read through the file and display employees from branches other than Dhaka
    while (fread(&e, siz, 1, fp) == 1) {
        if (strcasecmp(e.branch, "Dhaka") != 0) {
            printf("\n\t\t%d\t%s\t\t%s", e.id, e.name, e.branch);
        }
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void mainBranch(FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tEmployees from Main Branch");

    // Declare variables
    Employee e;
    int siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Print table header
    printf("\n\n\t\tID\tName\t\tBranch");

    // Read through the file and display employees from the main branch
    while (fread(&e, siz, 1, fp) == 1) {
        if (strcasecmp(e.branch, "Main Branch") == 0) {
            printf("\n\t\t%d\t%s\t\t%s", e.id, e.name, e.branch);
        }
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}

void otherBranch(FILE *fp) {
    // Print the header
    printHead();
    printf("\n\t\t\tEmployees from Other Branches");

    // Declare variables
    Employee e;
    int siz = sizeof(e);

    // Rewind the file pointer to the beginning of the file
    rewind(fp);

    // Print table header
    printf("\n\n\t\tID\tName\t\tBranch");

    // Read through the file and display employees from branches other than the main branch
    while (fread(&e, siz, 1, fp) == 1) {
        if (strcasecmp(e.branch, "Main Branch") != 0) {
            printf("\n\t\t%d\t%s\t\t%s", e.id, e.name, e.branch);
        }
    }

    // Prompt user to press Enter to continue
    printf("\n\n\t");
    printf("Press Enter to continue...");
    getchar();
    getchar(); // Wait for user input
}








