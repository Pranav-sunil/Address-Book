#include<stdio.h>
#include<string.h>
#include "address_book.h"
#include "functions.h"
#include "list_book.h"

/* Function to fetch the details of all contacts present in the file */
void display_data( AddressBook *address_book )
{

	/* Sets the file pointer to the beginning of the data in the file */
	fseek(address_book->fptr, 30, SEEK_SET );

	/* CHaracter array to fetch and store the data from the file */
	char line[LINE_LEN], name[NAME_LEN], index[INDEX_LEN], phone[NUMBER_LEN], email[EMAIL_ID_LEN], location[STATE_LEN], *reciever;

	printf("\n");
	print_header(); //Prints the header field

	/* Running a loop to fetch the data in each line and print it */
	while( fscanf( address_book->fptr, "%[^\n]\n", line) != EOF )
	{
		/* Setting the arrays to NULL , to prevent old data from being printed
		   in case the current field is empty */
		name[0] = '\0';
		index[0] = '\0';
		phone[0] = '\0';
		email[0] = '\0';
		location[0] = '\0';
		/* Reads the index from the buffer line */

		reciever = strtok( line, ",");

		//Checks if the line is empty
		if( reciever == NULL )
		{
			//If true, skip the line
			//continue;
		}
		else
		{
			strcpy( index, reciever );
		}

		/* Reads the name from the buffer line */
		reciever = strtok( NULL, ",");

		//Checks if no address was recieved for name
		if( reciever == NULL )
		{
			name[0] = '\0';
		}
		else
		{
			//Checks if the data obtained is name
			if( validate_name( reciever ) != e_success )
			{
				name[0] = '\0';
				goto check_phone;
			}
			strcpy( name, reciever );
		}

		//Checks if no address was recieved for phone number
		reciever = strtok( NULL, ",");
		if( reciever == NULL )
		{
			phone[0] = '\0';
		}
		else
		{
check_phone:
			//Checks if the data obtained is a phone number
			if( validate_phone_number( reciever ) != e_success )
			{
				phone[0] = '\0';
				goto check_email;
			}
			strcpy( phone, reciever );
		}

		//Checks if no address was recieved for email address
		reciever = strtok( NULL, ",");
		if( reciever == NULL )
		{
			email[0] = '\0';
		}
		else
		{
check_email:
			//Checks if the data obtained is an email address
			if( validate_email( reciever ) != e_success )
			{
				email[0] = '\0';
				goto store_location;
			}
			strcpy( email, reciever );
		}

		// Checks if no address was recieved for location
		reciever = strtok( NULL, ",");
		if( reciever == NULL )
		{
			location[0] = '\0';
		}
		else
		{
store_location:
			strcpy( location, reciever );
		}

		/* Printing the data from the file */
		printf("%-5s\t%-32s\t%-32s\t%-32s\t%-32s\n", index, name, phone, email, location);

	}

	//At the end, print the footer
	print_footer();
	//Reset the file pointer to back to the beginning of the file */
	fseek(address_book->fptr, 0, SEEK_END );
}
