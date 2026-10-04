# AddressBook-NewDesign
A C-based contact management system for creating, searching, editing, deleting, and viewing contacts, with data saved to a file.

I built this project to practice working with structures, functions, and file handling in C. It gives you a simple menu for managing contacts from the terminal.

You can add a contact, look one up, update or delete it, and list the contacts saved in the address book. When you exit, the program writes the contact data to `contacts.txt` so it can be loaded the next time you run it.

## What you can do

- Add a contact with a name, phone number, and email address
- Search for a contact
- Edit or delete a contact
- View the contact list
- Save and load contact data using a file

## Build

You need a C compiler such as GCC. In the project folder, run:

```sh
gcc -Wall -Wextra main.c contact.c file.c -o address_book
```

On Windows with MinGW GCC, you can use:

```sh
gcc -Wall -Wextra main.c contact.c file.c -o address_book.exe
```

## Run

On macOS or Linux:

```sh
./address_book
```

On Windows:

```powershell
.\address_book.exe
```

Use the numbered menu to manage contacts. Choose **6** to save and exit. The program reads and writes `contacts.txt` in its current working directory.

## Project files

- `main.c` — displays the menu and dispatches each choice
- `contact.c` and `contact.h` — contact operations and data structures
- `file.c` and `file.h` — loading and saving contact data

## A note about the sample data

The `contacts.txt` included with the project contains phone numbers and email addresses. I recommend leaving it out of a public GitHub repository, or replacing it with clearly fictional sample data before uploading. The program can create a new data file when you run it.

## Author

Madhan Kumar R
