/* ######################################## ADDRESS BOOK ######################################## 
Name : Pranav S
Project Name : Address Book
Description : Program to create and use an address book. Details such as name, phone, email address
and place can be stored in a .csv file. The entries made can be modified, viewed, 
searched and also be deleted
*/

#include<stdio.h>
#include<stdlib.h>
#include "address_book.h"
#include "functions.h"

int main()
{
	/* Declaring the strcture variable and allocating memory for it */
	AddressBook address_book; 
	address_book.list = malloc( sizeof( ContactInfo ));
	address_book.count = 0; //Initalizes the count to 0

	/* Creating the .csv file to store the contact information */
	if( create_and_open_file( &address_book ) == e_fail )
	{
		printf("ERROR: Unable to Create the .CSV File\n");
		return 0;
	}

	/* Calling menu function to do the required operation
	   on the .csv file */
	menu( &address_book );

	free(address_book.list); //Frees the memory allocated for the structure 
	address_book.list = NULL;

	if( fclose(address_book.fptr) != 0 )	//Closes the .csv file
	{
		printf("ERROR: Unable to close the file\n");
	}
	return 0;
}

