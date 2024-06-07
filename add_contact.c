#include<stdio.h>
#include<string.h>
#include "address_book.h"
#include "functions.h"
#include "add_contact.h"
#include "search_contact.h"

/* Function to add contacts to the address book */
void add_contacts( AddressBook *address_book )
{

	/* Declaring variables to read option from the user 
	   and a variable to store the file offset */
	int option, file_position;

	/* Array to store file offsets in case of multiple entries with same
	   first name */
	char index_val[INDEX_LEN];

	//Initalizes the structre( and clears old data )
	initalize_structre( address_book );

	printf("\n###############  Add Contact ###############\n\n");
	do
	{
		printf("0. Back \n");
		printf("1. Name          :      %s\n" ,address_book->list->name);
		printf("2. Phone No      :      %s\n", address_book->list->phone_numbers);
		printf("3. Email ID      :      %s\n", address_book->list->email_addresses);
		printf("4. Place         :      %s\n\n", address_book->list->state);
		printf("please select an option: ");
		scanf("%d", &option);
		getchar();

		switch(option)
		{
			case 1:
				//Add name of the contact
re_name:
				printf("Enter the name : ");
				scanf("%32[^\n]", address_book->list->name);
				getchar();

				//Validating name entered by the user
				if( validate_name( address_book->list->name ) == e_fail )
				{
					printf("ERROR : Name can only have Alphabets\n");
					goto re_name;
				}
				break;

			case 2:
				//Add Phone number of the contact
re_phone:		
				printf("Enter phone number : ");
				scanf("%32[^\n]", address_book->list->phone_numbers);
				getchar();

				//Validating Phone Number entered by the user
				if( validate_phone_number( address_book->list->phone_numbers ) == e_no_match )
				{
					printf("ERROR : Phone number should have 10 Digits\n");
					goto re_phone;
				}
				else if( validate_phone_number( address_book->list->phone_numbers ) == e_fail )
				{
					printf("ERROR : Phone number should have only digits\n");
					goto re_phone;
				}

				//Checking if the phone number already exists in the data base
				if( search_by_phone( address_book->fptr, address_book->list->phone_numbers, ADD, &file_position ) == e_success )
				{
					printf("ERROR : Phone Number already exists in the database\n");
					address_book->list->phone_numbers[0] = '\0';
					goto re_phone;
				}	

				break;
			case 3:
				//Adding the mail address of the contact
re_mail:
				printf("Enter the email : ");
				scanf("%32[^\n]", address_book->list->email_addresses);
				getchar();

				//Validating Email address entered by the user
				if( validate_email( address_book->list->email_addresses) == e_fail )
				{
					printf("ERROR : Email address is not valid\n");
					goto re_mail;
				}

				if( search_by_email( address_book->fptr, address_book->list->email_addresses, ADD, &file_position ) == e_success )
				{
					//Checking if the email address is present in the data base
					printf("ERROR : Email already exists in the database\n");
					address_book->list->email_addresses[0] = '\n';
					goto re_mail;
				}	
				break;
			case 4:
				//Adding the place of the contact
				printf("Enter the Place : ");
				scanf("%32[^\n]", address_book->list->state);
				getchar();
			default:
				//invalid option, restart loop
		}
	}while( option != 0 );

	//Checking if this is the first entry
	if( address_book->count == 0 )
	{
		write_field_to_file( address_book);
	   //If yes, then writes the filed names to the file	
	}
	
	//updating the count value in the structure
	address_book->count++;

	/* Converting the integer value of index to character to write to the file */
	itoa( address_book->count, index_val );

	//write obtained data to the file
	fprintf(address_book->fptr, "%s", index_val);
	fprintf(address_book->fptr, "%c", DELIMITER);
	fprintf(address_book->fptr, "%s", address_book->list->name);
	fprintf(address_book->fptr, "%c", DELIMITER);
	fprintf(address_book->fptr, "%s", address_book->list->phone_numbers);
	fprintf(address_book->fptr, "%c", DELIMITER);
	fprintf(address_book->fptr, "%s", address_book->list->email_addresses);
	fprintf(address_book->fptr, "%c", DELIMITER);
	fprintf(address_book->fptr, "%s", address_book->list->state);
	fprintf(address_book->fptr, "%c", DELIMITER);
	fprintf(address_book->fptr, "%c", NEXT_ENTRY);
}
