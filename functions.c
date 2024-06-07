/* File contains the definitions of functions for carrying out various operations */

#include<stdio.h>
#include<string.h>
#include "address_book.h"
#include "functions.h"
#include "add_contact.h"
#include "search_contact.h"
#include "edit_contact.h"
#include "delete_contact.h"
#include "list_book.h"

/* Function to create and open the .csv file for storing the data */
Status create_and_open_file( AddressBook *address_book )
{

	address_book->fptr = fopen( DEFAULT_FILE, "w+");

	if( address_book->fptr == NULL ) 
	{
		//Checks if the file has been opened properly
		return e_fail;
	}

	return e_success;
}

/* Function to print the feature menu of the program */
void main_menu( void )
{

	printf("\n############### Address Book ###############\n");
	printf("Features:\n");
	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("\n");
	printf("Please select an option: ");
}

/* Function to get the option from the user and call the 
   required function to do the required operation */
Status menu(AddressBook *address_book)
{

	int option;

	do
	{
		main_menu(); //Displays the menu

		scanf("%d", &option ); //Obtains the option based on user input

		if ( (address_book->count == 0) && (option != 1 ))
		{
			//To prevent other functions from being called in case the file is empty
			printf("ERROR: File is empty\n");
			continue;
		}

		switch (option)
		{
			case 1: //Operation to add contact to the file
				add_contacts(address_book);
				break;
			case 2: //Operation to search the file for the details of a contact
				search_file( address_book );
				break;
			case 3: //Calls the function to edit the details of a contact
				edit_contact(address_book);
				break;
			case 4: //Calls the function to delete the details of a contact
				delete_entry(address_book);
				break;
			case 5: //Calles the function to print the details of all contacts saved in then file
				display_data( address_book );
				break;
			case 0:
				break;
			default:
				printf("ERROR: Invalid Option\n");
				break;
		}
	} while ( option != 0 );

	return e_success;
}


/* Function checks if the name passed by the user is a valid name */
Status validate_name( const char *name )
{
	while( *name != '\0' )
	{
		//Checking if only alphabets and space is passed
		if( (*name >= 97 && *name <= 122) || (*name >= 65 && *name <= 90) )
		{
			*name++;
		}
		else if( *name == 32 )
		{
			*name++;
		}
		else
		{
			return e_fail;
		}
	}
	return e_success;
}

/* Function validates the phone number eneterd by the user */
Status validate_phone_number( const char *phone )
{
	// Checking if 10 digits are passed
	if( strlen( phone ) != 10 )
	{
		return e_no_match;
	}

	//Checking if digits are only passed
	while( *phone != '\0' )
	{
		if( *phone >= 48 && *phone <= 57 )
		{
			*phone++;
		}
		else
		{
			return e_fail;
		}
	}

	return e_success;
}

/* Function validates if the email passed by the user is a valid one */
Status validate_email( const char *email)
{
	// Checking if the email id has a .com / .in signature and @ is present
	if( strchr( email, '@' ) == NULL )
	{
		return e_fail;
	}

	if( strstr( email, ".com") != NULL )
	{
		return e_success;
	}
	else if( strstr( email, ".in") != NULL )
	{
		return e_success;
	}

		return e_fail;
}

/* Function writes the fields at the bginning of an empty file */
void write_field_to_file( AddressBook *address_book)
{

	fprintf(address_book->fptr, "%s", "Index");
	fprintf(address_book->fptr, "%c", DELIMITER );
	fprintf(address_book->fptr, "%s", "Name");
	fprintf(address_book->fptr, "%c", DELIMITER );
	fprintf(address_book->fptr, "%s", "Phone");
	fprintf(address_book->fptr, "%c", DELIMITER );
	fprintf(address_book->fptr, "%s", "Email");
	fprintf(address_book->fptr, "%c", DELIMITER );
	fprintf(address_book->fptr, "%s", "State");
	fprintf(address_book->fptr, "%c", DELIMITER );
	fprintf(address_book->fptr, "%c", NEXT_ENTRY );
}


/* Function to convert and integer number to a string. */
void itoa( int num, char *str )
{
	if( num == 0 )
	{
		*str = '0';
		return;
	}
	int d, flag = 0, l=0;
	unsigned char temp;
	if( num < 0 )
	{
		flag++;
		num = -num;
	}
	while( num > 0 )
	{
		d = num%10;
		*str = d+48;
		num = num/10;
		str++;
		l++;
	}
	if( flag == 1 )
	{
		*str = '-';
		str++;
		l++;
	}
	*str = '\0';
	str = str-l;
	for( int i = 0; i < l/2 ; i++ )
	{
		temp = str[i];
		str[i] = str[l-i-1];
		str[l-i-1] = temp;
	}
}

/* Function to initalize the structure variable */
 void initalize_structre( AddressBook *address_book )
{

	address_book->list->name[0] = '\0';
	address_book->list->phone_numbers[0] = '\0';
	address_book->list->email_addresses[0] = '\0';
	address_book->list->state[0] = '\0';
}

/* Function to print a header to display data */
void print_header( void )
{

	printf("************************************************************************************************************************************************************\n");
	printf("%-5s\t%-32s\t%-32s\t%-32s\t%-32s\n", "Index", "Name", "Phone Number", "Email", "Location");
	printf("************************************************************************************************************************************************************\n");
}

void print_footer(void)
{
	/* Function to print a footer to display data */

	printf("************************************************************************************************************************************************************\n");
}

/* Function will copy data from source file to destination file 
   character by character */
void copy_file_data( FILE *source, FILE *destination )
{

	char character; //Temporary character to store the data read from the file
	while( fread(&character, 1, 1, source ) != 0 )
	{
		fwrite(&character, 1, 1, destination );
	}
	fseek( destination, 0, SEEK_SET );
}
