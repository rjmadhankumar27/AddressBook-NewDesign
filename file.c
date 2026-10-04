/*Name        : Madhan Kumar R
  Description : "file.c" file of AddressBook Project
*/

#include <stdio.h>
#include "file.h"


#define RED     "\033[31m"
#define RESET   "\033[0m"

//To save the contacts that are present in 'Structure' to file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE* fp=fopen("contacts.txt","w");

    //To write the contacts to the file
    fwrite(addressBook,sizeof(AddressBook),1,fp);
    fclose(fp);
}

//To load the contact from 'File' to structure
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE* fp=fopen("contacts.txt","r");

    //To print if there are no such file
    if(fp == NULL)
    {
        printf(RED"There is no such file\n"RESET);
        return;
    }

    //To read the contacts from the file
    while(fread(&addressBook->contacts[addressBook->contactCount],sizeof(Contact),1,fp)==1)
    {
        addressBook->contactCount++;
    }
    fclose(fp);
}
