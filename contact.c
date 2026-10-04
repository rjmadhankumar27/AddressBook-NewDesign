/*Name        : Madhan Kumar R
  Description : "contact.c" file of AddressBook Project
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define ORANGE "\033[38;5;208m"
#define RESET   "\033[0m"

int by_name(AddressBook* addressBook);
int by_phonenumber(AddressBook* addressBook);
int by_mail(AddressBook* addressBook);
void create_name(char* name);
void create_number(char* phone,AddressBook* addressBook);
void create_mail(char* mail,AddressBook* addressBook);
void edit_name(AddressBook* addressBook,int index);
void edit_phonenumber(AddressBook* addressBook,int index);
void edit_mail(AddressBook* addressBook,int index);
void separatingline();
void display(AddressBook* addressBook,int i);

static int indicator;

//Function for the  listing all the contacts
void listContacts(AddressBook *addressBook) 
{
   if(addressBook->contactCount==0) //To print "No Contacts present",if there are no contacts 
   {
    printf(RED"There is no Contacts present!!"RESET);
   }

   separatingline();//Printing separating line
   printf(ORANGE"%-5s %-25s %-15s %-30s\n"RESET,"S.No","Name","Number","E-mail");//To print header for listing 
   
   separatingline();//Printing separating line

   int z=0;
   for(int i=0;i<addressBook->contactCount;i++)//To list all the members
   {
       z++;
       printf(YELLOW"%-5d %-25s %-15s %-30s\n"RESET,z,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
   }

   separatingline();//Printing separating line

   printf(GREEN"These all are the contacts present!!\n"RESET);

  separatingline();//Printing separating line
   return;
}

//To load contacts from the File 
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook); 
}

//To Save the structure and to Exit the program  
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//Fucntion for the Create Contact
void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[50];
    char phone[20];
    char mail[50];
    name[0]='\0';
    phone[0]='\0';
    mail[0]='\0';

    create_name(name);//calling the function "create_name"-->To create name 

    if(name[0]!='\0')
    {
        create_number(phone,addressBook);//calling the function "create_number"-->To create number
    }

    if(phone[0]!='\0')
    {
       create_mail(mail,addressBook);//calling the function "create_mail"-->To create E-mail
    }
    
    /*To update to structures if all three are valid*/

    if(mail[0]!='\0')
    {
      strcpy(addressBook->contacts[addressBook->contactCount].name,name);
      strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
      strcpy(addressBook->contacts[addressBook->contactCount].email,mail);
      addressBook->contactCount++;
    }
    else
    {
        printf(GREEN"Please Try Again!!"RESET);
    }
    return;
}

//Function for the Search Contact
int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int flag=1;
    int index=-1;
    int error_count=0;
    do
    {
        int option;
        printf(YELLOW"Do you want to search by \n"RESET);

        //Asking about options they want to search by
        printf(ORANGE"1.Name\n2.Phone Number\n3.E-mail\n4.Exit\n"RESET);
        printf(YELLOW"Enter the option : "RESET);

        if(scanf("%d",&option) != 1)//To check the entered input
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
        switch(option)
        {
            case 1:
              index=by_name(addressBook);//Calling the function "To search by name"
              flag=0;
              break;
            case 2:
              index=by_phonenumber(addressBook);//Calling the function "To search by number"
              flag=0;
              break;
            case 3:
              index=by_mail(addressBook);//Calling the function "To search by E-mail"
              flag=0;
              break;
            case 4:
              flag=0;
              break;
            default:
              printf(RED"Invalid option!!\n"RESET);//To print "Invalid option"-->if user entered Invalid Option
              if(error_count<3)
              printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count));//To print remaining attempts
             break;

        }
        if(error_count==3)
        {
            printf(RED"Your attempts are finished!!\n"RESET);
            return -1;
        }

    } while (flag);

    return index;
    
}

//Function for Editing the contact
void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int flag1=1;
    int error_count=0;
    int index;
    indicator=1;
    index=searchContact(addressBook);//Calling "searchcontact" function-->to find the index of the desired contact
    indicator=0;
    
    //It is for the any error occur in searchcontact
    if(index==-1)
    {
       return;
    }

    do
    {
        printf(YELLOW"What do you want edit :\n"RESET);
        printf(ORANGE"1.Edit the Name\n2.Edit the phone number\n3.Edit the E-mail\n4.Exit\n"RESET);//Asking what he want to edit
        printf(YELLOW"Enter the option : "RESET);
        int option;
        if(scanf("%d",&option) != 1)//To check the enetred input
        {
            while(getchar() != '\n');//To clear the inputbuffer

            printf(RED"Invalid option!!\n"RESET);//To print "Invalid option"-->if user entered Invalid Option
            error_count++;
            
            if(error_count < 3)
               printf(RED"Only %d attempts is remaining!!\n"RESET,3-error_count);//To print remaining attempts

            if(error_count == 3)
            {
               printf(RED"Your attempts are finished!!\n"RESET);//To print "Attempt for this is finished"
               return;
            }
             continue;
        }
        switch (option)
        {
        case 1:
            edit_name(addressBook,index);//Calling the function "edit_name"
            flag1=0;
            break;
        
        case 2:
            edit_phonenumber(addressBook,index);//Calling the function "edit_phonenumber"
            flag1=0;
            break;
        case 3:
            edit_mail(addressBook,index);//Calling the function "edit_mail"
            flag1=0;
            break;
        case 4:
            flag1=0;
            break;
        default:
            printf(RED"Invalid option!!\n"RESET);//To print "Invalid option"-->if user entered Invalid Option
            error_count++;
            if(error_count<3)
            printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count));//To print remaining attempts
            break;
        }
         if(error_count==3)
        {
            printf(RED"Your attempts are finished!!\n"RESET);//To print "Attempt for this is finished"
            return;
        }

    } while (flag1);


    


    
}

//Function for Deleting the contact
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int index;
    indicator=1;
    index=searchContact(addressBook);//Calling "searchcontact" function-->to find the index of the desired contact
    indicator=0;

    //It is for the any error occur in searchcontact
    if(index==-1)
   {
      return;
   }

   //It will delete contact of the desired contact
   for(int i=index;i<((addressBook->contactCount)-1);i++)
   {
      strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
      strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
      strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
   }
   addressBook->contactCount--;
   printf(GREEN"The contact is deleted successfully!!\n"RESET);//To print that the contact deleted successfully
   return;

   
}

//Function for Search by name
int by_name(AddressBook* addressBook)
{
   char name[50];
   int flag_find=0;
   int index;
   int error_count=0;
   printf(ORANGE"Enter the name : "RESET);
   scanf(" %[^\n]",name);
   int m=0;
   int z=1;
   
   //Finding the contacts index by Entered name
   for(int i=0;i<addressBook->contactCount;i++)
   {
     
      if(strcmp(addressBook->contacts[i].name,name)==0)
      {
         if(m==0)
        {
          separatingline();//Printing separating line
          printf(ORANGE"%-5s %-25s %-15s %-30s\n","S.No","Name","Number","E-mail"RESET);
          separatingline();//Printing separating line
          m++;
        }
        printf(YELLOW"%-5d %-25s %-15s %-30s\n"RESET,z,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
        flag_find++;
        z++;
        index=i;
      }
   }

   //This is for if there are same name available 
   if(indicator==1)
   {
      if(flag_find>1)
      {
         int flag=1;
         printf(BLUE"There are same name are available!!\n"RESET);
         do
         {
           int option;
           
           //Asking about other options to enter "number" or "E-mail"
           printf(YELLOW"Search with \n1.Phone number\n2.E-mail\n3.Exit\n"RESET);
           printf(ORANGE"Enter the option\n"RESET);

           if(scanf("%d",&option) != 1)//To check the entered input
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
           switch (option)
           {
             case 1:
                 index=by_phonenumber(addressBook);//calling the function "by_phonenumber"-->to search by number
                 flag=0;
                 break;
             case 2:
                 index=by_mail(addressBook);//calling the function "by_mail"-->to search by mail
                 flag=0;
                 break;
             case 3:
                 flag=0;
                 break;
             default:
                 printf(RED"Invalid option!!\n"RESET);//To print "Invalid option"-->if user entered Invalid Option
                 error_count++;
                 if(error_count<3)
                 printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count));//To print remaining attempts
                 break;
            }
             if(error_count==3)
            {
               printf(RED"Your attempts are finished!!\n"RESET);//To print "Attempt for this is finished"
               return -1;
            }

          } while (flag);     
       
       }

    }
   if(flag_find==0)
   {
     printf(BLUE"There is no such name!!\n"RESET);//To print there are no name-->if there are no name
     return -1;
   }
   return index;
}

//Function for Search by Phonenumber 
int by_phonenumber(AddressBook* addressBook)
{
   char number[20];
   int flag_find=0;
   printf(ORANGE"Enter the phone number : "RESET);
   scanf(" %[^\n]",number);

   //To search index by phonenumber
   for(int i=0;i<addressBook->contactCount;i++)
   {
      
      if(strcmp(addressBook->contacts[i].phone,number)==0)
      {
          
         display(addressBook,i);
         flag_find=1;
         return i;
      }
   }
   if(flag_find==0)
   {
     //To print if there is no such number
     printf(BLUE"There is no such Phone number!!\n"RESET);
     return -1;
   }
   return 0;
}

//Function for Search by E-mail
int by_mail(AddressBook* addressBook)
{
   char mail[50];
   int flag_find=0;
   printf(ORANGE"Enter the E-mail Id : "RESET);
   scanf(" %[^\n]",mail);

   //To search index by E-mail
   for(int i=0;i<addressBook->contactCount;i++)
   {
      if(strcmp(addressBook->contacts[i].email,mail)==0)
      {
         display(addressBook,i);
         flag_find=1;
         return i;
      }
   }
   if(flag_find==0)
   {
     //To print there is no such E-mail
     printf(BLUE"There is no such E-mail Id!!\n"RESET);
     return -1;
   }
   return 0;
}

//Function for creating name
void create_name(char* name)


{
    char name_temp[50];
    int error_count_name=0;
     while(1)
    {
       int flag_error=0;
       if(error_count_name>=3)
       {
         printf(RED"Your attempts are finished\n"RESET);//To print "Attempt for this is finished"
         return;
       }
       printf(ORANGE"Enter the Name : "RESET);
       scanf(" %[^\n]",name_temp);
       getchar();
       int i,len=strlen(name_temp);
       int count_dot_name=0;
       if(len>=3)
       {
           for(i=0;i<len;i++)
           {
              if(isalpha(name_temp[i])!=0 || name_temp[i]==' ' || name_temp[i]=='.')
              {
                 if(name_temp[i]=='.')
                 {
                     count_dot_name++;
                 }
              }
              else
              {
                //To print Error Message about Creating name
                 printf(RED"Error Message : Name should contain only alphabets\n"RESET);
                 error_count_name++;
                 if(error_count_name<3)
                 printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_name));//To print remaining attempts
                 flag_error=1;
                 break;
              }
            }
            if(flag_error==1)
            {
                continue;
            }
            if (count_dot_name>1)
            {
                //To print Error Message about Creating name
                printf(RED"Error Message : Name should contain only atmost one dot\n"RESET);
                error_count_name++;
                if(error_count_name<3)
                printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_name));//To print remaining attempts
                continue;
            }
            else
            {
                strcpy(name,name_temp);
                //Printing that Name is successfully saved
                printf(GREEN"Your name is successfully saved!!\n"RESET);
                return;
            }
        
        }
        else
        {
           printf(RED"Error Message : Name must contain atleast 3 characters\n"RESET);//To print Error Message about Creating name
           error_count_name++;
           if(error_count_name<3)
           printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_name));//To print remaining attempts
           continue;
        }
    }

}

//Function for Creating phonenumber
void create_number(char* phone,AddressBook* addressBook)

{
    char phone_temp[20];
    int error_count_phone=0;
    while(1)
    {
       int flag_error=0;
   
       if(error_count_phone==3)
       {
         printf(RED"Your attempts are finished\n"RESET);//To print "Attempt for this is finished"
         return;
       }
       printf(ORANGE"Enter the Number : "RESET);
       scanf(" %[^\n]",phone_temp);
       int len=strlen(phone_temp);

       if(len==10)
       {
            if(((phone_temp[0])>='6') && ((phone_temp[0])<='9'))
            {
               for(int i=0;i<len;i++)
               {
                  if(isdigit(phone_temp[i])==0)
                  {
                      printf(RED"Error Message : Other than Digits any other Character not allowed in phone number\n"RESET);//To print Error Message about Creating name
                      error_count_phone++;
                      if(error_count_phone<3)
                      printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_phone));//To print remaining attempts
                      flag_error=1;
                      break;
                  }
               }
               if(flag_error==0)
               {
                  int flag_unique=0;
                  for(int i=0;i<addressBook->contactCount;i++)
                  {
                      if(strcmp(addressBook->contacts[i].phone,phone_temp)==0)
                      {
                          flag_unique=1;
                          break;
                      }
                  }
                  if(flag_unique==1)
                  {
                    printf(RED"Error Message : Phone number is already exist!!\n"RESET);//To print Error Message about Creating phone number
                    error_count_phone++;
                    if(error_count_phone<3)
                    printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_phone));//To print remaining attempts
                    continue;
                  }
                  else
                  {
                    strcpy(phone,phone_temp);
                    //Printing that the Phone number is successfully saved
                    printf(GREEN"Your number is saved!!\n"RESET);
                    return;
                  }
               }
               else
               {
                  continue;
               }
            } 
            else
            {
               printf(RED"Error Message : First digit must be between 6 and 9\n"RESET);//To print Error Message about Creating phone number
               error_count_phone++;
               if(error_count_phone<3)
               printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_phone));//To print remaining attempts
               continue;
            }
        }
        else
        {
           printf(RED"Error Message : Phone number must contain exactly 10 digits\n"RESET);//To print Error Message about Creating phone number
           error_count_phone++;
           if(error_count_phone<3)
           printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_phone));//To print remaining attempts
           continue;
        }
    }
}

//Function for Creating E-mail
void create_mail(char* mail,AddressBook* addressBook)

{
    
    char mail_temp[50];
    int error_count_mail=0;
  
    while(1)
    {
        if(error_count_mail==3)
        {
            printf(RED"Your attempts are finished!!\n"RESET);//To print "Attempt for this is finished"
            return;
        }
        int symbol_count=0,dot_count=0;
        int differnce;
        int index;
        char str[50];
        printf(ORANGE"Enter the mail Id : "RESET);
        scanf(" %[^\n]",mail_temp);
        int len=strlen(mail_temp);
        for(int i=0;i<len;i++)
        {
            if(mail_temp[i]=='@')
            {
                index=i;
                symbol_count++;
                for(int j=i;j<len;j++)
                {
                    if(mail_temp[j]=='.')
                    {
                       int m=0;
                       dot_count++;
                       differnce=j-i;
                       for(int k=j+1;k<len;k++)
                       {
                          str[m]=mail_temp[k];
                          m++;
                       }
                       str[m]='\0';
                    }
                }
            }
        }
        if(symbol_count==0)
        {
            printf(RED"Error Message : Missing @\n"RESET);//To print Error Message about Creating E-mail
            error_count_mail++;
            if(error_count_mail<3)
            printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_mail));//To print remaining attempts
            continue;
        }

        if(symbol_count==1)
        {
            if(dot_count==1)
            {
                if(differnce>1)
                {     
                   if(strcmp(str,"com")==0)
                   {
                        int flag_unique=0;
                     for(int i=0;i<addressBook->contactCount;i++)
                     {
                         if(strcmp(addressBook->contacts[i].email,mail_temp)==0)
                         {
                             flag_unique=1;
                             break;
                         }
                     }
                     if(flag_unique==1)
                     {
                         printf(RED"Error Message : E-mail is already exist\n"RESET);//To print Error Message about Creating E-mail
                         error_count_mail++;
                         if(error_count_mail<3)
                         printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_mail));//To print remaining attempts
                         continue;
                     }
                     else
                     {
                        if(index<3)
                        {
                            printf(RED"Error Message : Before @ there atleast 3 characters!!\n"RESET);//To print Error Message about Creating E-mail
                            error_count_mail++;
                            if(error_count_mail<3)
                            printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_mail));//To print remaining attempts
                            continue;
                        }
                        else
                        {
                          strcpy(mail,mail_temp);
                          //Printing that E-mail is successfully saved
                          printf(GREEN"Your E-mail Id is saved!!\n"RESET);
                          return ;
                        }
                     }
                   }
                   else
                   {
                       printf(RED"Error Message : After .(dot) ,there have to be only one com\n"RESET);//To print Error Message about Creating E-mail
                       error_count_mail++;
                       if(error_count_mail<3)
                       printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_mail));//To print remaining attempts
                       continue;
                   }

                }
                else
                {
                    printf(RED"Error Message : There must be atleast one character between @ and .(dot)\n"RESET);//To print Error Message about Creating E-mail
                    error_count_mail++;
                    if(error_count_mail<3)
                    printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_mail));//To print remaining attempts
                    continue;
                }
            }
            else
            {
                printf(RED"Error Message : After @ there should be exactly one dot\n"RESET);//To print Error Message about Creating E-mail
                error_count_mail++;
                if(error_count_mail<3)
                printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_mail));//To print remaining attempts
                continue;
            }
        }
        else
        {
            printf(RED"Error Message : Multiple @ symbols are not allowed\n"RESET);//To print Error Message about Creating E-mail
            error_count_mail++;
            if(error_count_mail<3)
            printf(RED"Only %d attempts is remaining!!\n"RESET,(3-error_count_mail));//To print remaining attempts
            continue;
        }

        
    }
}

//Function for Editing name
void edit_name(AddressBook* addressBook,int index)
{
    char name[50]={0};
    create_name(name);//Calling the function "create_name"-->to check validation
    if(name[0]!='\0')
    {
        strcpy(addressBook->contacts[index].name,name);
        printf(GREEN"Your contact has been edited successfully!!\n"RESET);//Printing that the contact edited successfully
    }
    else
    {
       printf(BLUE"Please Try Again!!\n"RESET);//Asking to try again if validation goes wrong
    }
    return;
}

//Function for Editing Phonenumber
void edit_phonenumber(AddressBook* addressBook,int index)
{
    char number[50]={0};
    create_number(number,addressBook);//Calling the function "create_number"-->to check validation
    if(number[0]!='\0')
    {
        strcpy(addressBook->contacts[index].phone,number);
        printf(GREEN"Your contact has been edited successfully!!\n"RESET);//Printing that the contact edited successfully
    }
    else
    {
       printf(BLUE"Please Try Again!!\n"RESET);//Asking to try again if validation goes wrong
    }
    return;
}

//Function for Editing E-mail
void edit_mail(AddressBook* addressBook,int index)
{
    char email[50]={0};
    create_mail(email,addressBook);//Calling the function "create_mail"-->to check validation
    if(email[0]!='\0')
    {
        strcpy(addressBook->contacts[index].email,email);
        printf(GREEN"Your contact has been edited successfully!!\n"RESET);//Printing that the contact edited successfully
    }
    else
    {
       printf(BLUE"Please Try Again!!\n"RESET);//Asking to try again if validation goes wrong
    }
    return;
}

//Function for printing Separating line
void separatingline()
{
   for(int j=0;j<75;j++)
   {
    printf("=");
   }
   printf("\n");
}

//To display the names
void display(AddressBook* addressBook,int i)
{
    separatingline();//Printing separating line
    printf(ORANGE"%-5s %-25s %-15s %-30s\n","S.No","Name","Number","E-mail"RESET);
    separatingline();//Printing separating line
    printf(YELLOW"%-5d %-25s %-15s %-30s\n"RESET,1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
}