/*Name        : Madhan Kumar R
  Description : "main.c" file of AddressBook Project
*/

#include <stdio.h>
#include "contact.h"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define ORANGE "\033[38;5;208m"
#define RESET   "\033[0m"

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    int error_count=0;
    do {
        printf(BLUE"\nAddress Book Menu:\n"RESET);
        printf(YELLOW"1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Exit\n"RESET);
        printf(ORANGE"Enter your choice: "RESET);

        if(scanf("%d",&choice) != 1)
        {
            while(getchar() != '\n');//To clear the inputbuffer 
                         
            printf(RED"Invalid option!!\n"RESET);//To print "Invalid option"-->if user entered Invalid Option
            error_count++;
            
            if(error_count < 3)
               printf(RED"Only %d attempts is remaining!!\n"RESET,3-error_count);//To print remaining attempts

            if(error_count == 3)
            {
               printf(RED"Your attempts are finished!!\n"RESET);//To print "Attempt for this is finished"
               return -1;
            }
             continue;
        }
        
        switch (choice) {
            case 1:
                createContact(&addressBook);//Calling the function "createContact"-->To create contact
                break;
            case 2:
                searchContact(&addressBook);//Calling the function "searchContact"-->To search contact
                break;
            case 3:
                editContact(&addressBook);//Calling the function "editContact"-->To edit contact
                break;
            case 4:
                deleteContact(&addressBook);//Calling the function "deleteContact"-->To delete contact
                break;
            case 5:
                listContacts(&addressBook);//Calling the function "listContacts"-->To list all the contacts
                break;
            case 6:
                printf(GREEN"Saving and Exiting...\n"RESET);
                saveContactsToFile(&addressBook);//Calling the function "saveContactsToFile"-->To save the contacts to the file
                break;
            default:
                printf(RED"Invalid choice. Please try again.\n"RESET);//To print "Invalid option"-->if user entered Invalid Option
                error_count++;
                if(error_count<3)
                printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count));//To print remaining attempts
                break;
        }
         if(error_count==3)
        {
            printf(RED"Your attempts are finished!!\n"RESET);//To print "Attempt for this is finished"
            return 0;
        } 
    } while (choice != 6);

       return 0;
}
