#include<stdio.h>
#include<string.h>
#include "address_book.h"
#include "functions.h"
#include "search_contact.h"

/* Function to obtain the type of data to be searched in the .csv file and obtain the key 
   to be searched for. Based on his it will call other function to search the file. */
void search_file( AddressBook *address_book )
{
	/* Variable to get the option from the user */
	int option;
   	int file_pointer_position; //Variable to store the file offset location
	char key[KEY_STRING]; //Array to store the data to be searched from the file based on user input
	int index[INDEX_LEN]; //Array to store file offset in case of multiple entries
	printf("\n################ Search Contact ################\n\n");
	do
	{
		printf("0. Back\n");
		printf("1. Search by Name\n");
		printf("2. Search by Phone Number\n");
		printf("3. Search by Email\n");
		printf("4. Search by Place\n");
		printf("Enter your choice : ");
		scanf("%d", &option );
		getchar();

		switch(option)
		{
			case 1: 
				//To search by name of contact
search_name:
				printf("Enter the name : ");
				scanf("%32[^\n]", key );
				getchar();
				
				/* Validating the name entered by the user */
				if( validate_name( key ) == e_fail )
				{
					printf("WARNING: Name can only have alphabets\n");
					goto search_name;
				}
				if( search_by_name( address_book->fptr, key , SEARCH , index) != e_success)
				{
					printf("No entries found for %s\n", key);
				}
				break;	
			case 2:
				//To search for contact by phone number
search_phone:
				printf("Enter the phone number : ");
				scanf("%32[^\n]", key );
				getchar();

				/* Validating the phone number entered by the user */
				if( validate_phone_number( key ) == e_fail )
				{
					printf("WARNING: Invalid Phone Number\n");
					goto search_phone;
				}
				if( search_by_phone( address_book->fptr, key, SEARCH , &file_pointer_position) != e_success)
				{
					printf("No entries found for %s\n", key);
				}
				break;	
			case 3:
				//To search for contact by email address
search_email:
				printf("Enter the email : ");
				scanf("%32[^\n]", key );
				getchar();

				/* Validating the email entered by the user */
				if( validate_email(key) == e_fail )
				{
					printf("EARNING: Invalid email address\n");
					goto search_email;
				}
				if( search_by_email( address_book->fptr, key, SEARCH, &file_pointer_position) != e_success)
				{
					printf("No entries found for %s\n", key);
				}
				break;	
			case 4:
				//To search for contact by location
				printf("Enter the location : ");
				scanf("%32[^\n]", key );
				getchar();
				if( search_by_location( address_book->fptr, key, SEARCH ) != e_success)
				{
					printf("No entries found for %s\n", key);
				}
				break;	
			case 0:
				//Exit
				break;
			default:
				printf("Enter a valid option\n");
				break;
		}
	}while( option != 0 );
}

/* Function to search the file for contact with required name */
Status search_by_name( FILE *file_pointer, const char *key , char mode, int *pointer_position)
{

	int print_flag=0, i=0;

	/* Sets the file pointer to the beginning of the file */
	fseek(file_pointer, 0, SEEK_SET );

	char line[LINE_LEN], name[NAME_LEN], index[INDEX_LEN], phone[NUMBER_LEN], email[EMAIL_ID_LEN], location[STATE_LEN];

	/* Running a loop till the required name is found */
	while( fscanf( file_pointer, "%[^\n]\n", line ) != EOF )
	{
		strcpy( index, strtok(line, ",") );
		strcpy( name, strtok(NULL, ",") );
		if( strncmp( name, key , strlen(key)) != 0 ) //Checking if the obtained 
		{
			pointer_position[i] = ftell(file_pointer);
			continue;
		}
		print_flag++; //Increments print flag if data was found
		if( mode == SEARCH || mode == EDIT || mode == DELETE)
		{
			//Print the data in search, edit and delete mode only
			strcpy( phone, strtok(NULL, ",") );
			strcpy( email, strtok(NULL, ",") );
			strcpy( location, strtok(NULL, ",") );
			if( print_flag == 1 )
			{
				//To print the header and message stating that entry has been found
				printf("\nEntry found for %s\n\n", key);
				print_header();
			}
			printf("%-5s\t%-32s\t%-32s\t%-32s\t%-32s\n", index, name, phone, email, location);

		}
		i++;
	}
	pointer_position[i] = 0; //Clears the last file pointer location, since it contains the index of last line

	fseek(file_pointer, 0, SEEK_END ); //Resets the file pointer to the end
	if( print_flag )
	{
		print_footer();
		return e_success;
	}
	else
	{
		return e_no_match;
	}
}

Status search_by_phone( FILE *file_pointer, const char *key , char mode, int *pointer_position )
{

	/* Function to search the file for contact with required phone number */

	int print_flag=0;

	/* Sets the file pointer to the beginning of the file */
	fseek(file_pointer, 0, SEEK_SET );

	char line[LINE_LEN], name[NAME_LEN], index[INDEX_LEN], phone[NUMBER_LEN], email[EMAIL_ID_LEN], location[STATE_LEN];

	/* Running a loop till the required phone number is found */
	while( fscanf( file_pointer, "%[^\n]\n", line ) != EOF )
	{
		strcpy( index, strtok(line, ",") );
		strcpy( name, strtok(NULL, ",") );
		strcpy( phone, strtok(NULL, ",") );
		if( strcmp( phone, key ) != 0 ) // Checking if the required number was found
		{
			*pointer_position = ftell(file_pointer);
			continue;
		}
		print_flag++;
		if( mode == SEARCH )
		{
			strcpy( email, strtok(NULL, ",") );
			strcpy( location, strtok(NULL, ",") );
			if( print_flag == 1 )
			{
				printf("\nEntry found for %s\n\n", key);
				print_header();
			}
			printf("%-5s\t%-32s\t%-32s\t%-32s\t%-32s\n", index, name, phone, email, location);

		}
	}

	fseek(file_pointer, 0, SEEK_END ); //Resets the file pointer to the end of the file
	fseek(file_pointer, 0, SEEK_END ); //Resets the file pointer to the end of the file
	if( print_flag )
	{
		print_footer();
		return e_success;
	}
	else
	{
		return e_no_match;
	}
}

Status search_by_email( FILE *file_pointer, const char *key , char mode, int *pointer_position)
{
	/* Function to search the file for contact with required name */

	int print_flag=0;
	fseek(file_pointer, 0, SEEK_SET );
	char line[LINE_LEN], name[NAME_LEN], index[INDEX_LEN], phone[NUMBER_LEN], email[EMAIL_ID_LEN], location[STATE_LEN];
	while( fscanf( file_pointer, "%[^\n]\n", line) != EOF )
	{
		strcpy( index, strtok(line, ",") );
		strcpy( name, strtok(NULL, ",") );
		strcpy( phone, strtok(NULL, ",") );
		strcpy( email, strtok(NULL, ",") );
		if( strcmp( email, key ) != 0 )
		{
			*pointer_position = ftell(file_pointer);
			continue;
		}
		print_flag++;
		if( mode == SEARCH )
		{
			strcpy( location, strtok(NULL, ",") );
			if( print_flag == 1 )
			{
				printf("\nEntry found for %s\n\n", key);
				print_header();
			}
			printf("%-5s\t%-32s\t%-32s\t%-32s\t%-32s\n", index, name, phone, email, location);

		}
	}
	fseek(file_pointer, 0, SEEK_END ); //Resets the file pointer to the end of the file
	if( print_flag ) 
	{
		print_footer();
		return e_success;
	}
	else
	{
		return e_no_match;
	}
	return e_success;
}

Status search_by_location( FILE *file_pointer, const char *key , char mode)
{
	/* Function to search the file for contact with required name */

	int print_flag=0;
	fseek(file_pointer, 0, SEEK_SET );
	char line[LINE_LEN], name[NAME_LEN], index[INDEX_LEN], phone[NUMBER_LEN], email[EMAIL_ID_LEN], location[STATE_LEN];

	/* Running a loop till the contacts with required location is found */
	while( fscanf( file_pointer, "%[^\n]\n", line ) != EOF )
	{
		strcpy( index, strtok(line, ",") );
		strcpy( name, strtok(NULL, ",") );
		strcpy( phone, strtok(NULL, ",") );
		strcpy( email, strtok(NULL, ",") );
		strcpy( location, strtok(NULL, ",") );
		if( strcmp( location, key ) != 0 )
		{
			//Checking if the required location was found
			continue;
		}
		print_flag++;
		if( mode == SEARCH )
		{
			if( print_flag == 1 )
			{
				printf("\nEntry found for %s\n\n", key);
				print_header();
			}
			printf("%-5s\t%-32s\t%-32s\t%-32s\t%-32s\n", index, name, phone, email, location);

		}
	}
	fseek(file_pointer, 0, SEEK_END ); //Resets the file pointer back to the end
	if( print_flag ) 
	{
		print_footer();
		return e_success;
	}
	else
	{
		return e_no_match;
	}
}
