#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "address_book.h"
#include "functions.h"
#include "search_contact.h"
#include "delete_contact.h"

/* Function gives the user the option to search the database based on data type (name, phone number or email )
   and searches if the data is present in the file. If present, it will call the delete_contact function and 
   deletes the entry requested by the user */
void delete_entry( AddressBook *address_book )
{

	/* Variable and and array for storing file offsets */
	int pointer=0, index[INDEX_LEN] = {0};
	int option; //Variable to store the option selected by the user
	int i; //Variable for running loops
	int count = 0; //Variable to count the number of entires 

	char key[KEY_STRING]; //Array to store the data to be searched from the file

	do
	{
		printf("\n############### Delete Contact ###############\n\n");
		printf("0. Go Back\n");
		printf("1. Search by Name\n");
		printf("2. Search by Phone Number\n");
		printf("3. Search by email\n");
		printf("Enter option : ");
		scanf("%d", &option);
		getchar();

		switch(option)
		{
			case 1:
				//Search and delete by name
delete_name:
				printf("Enter the Name : ");
				scanf("%32[^\n]", key);
				getchar();

				//Validates the name enetered by the user
				if( validate_name( key ) == e_fail )
				{
					printf("WARNING : Name can only have alphabets\n");
					goto delete_name;
				}

				/* Searches the file for the name */
				if( search_by_name( address_book->fptr, key, DELETE, index) == e_no_match )
				{
					printf("No entry found for %s\n", key);
					break;
				}

				/* Checks if there is more than one entry with the same name */
				//printf("Index values : ");
				for( i = 0 ; i < 3 ; i++ )
				{
					//printf("%d ", index[i] );
					if( index[i] != 0 )
					{
						count++;
					}
				}
				//printf("\n");
				if( count == 1 )
				{
					pointer = index[0];
				}
				else
				{
					/* Prompts the user to select the entry to be deleted in case of multiple entries */
					printf("More than 1 entry found for %s\n", key);
select_index:
					printf("Enter the Sl.No of entry to delete : ");
					scanf("%d", &i );
					if( i <= 0 && i > count )
					{
						printf("Error : Please choose correct option\n");
						goto select_index;
					}
					pointer = index[i-1];
				}

				/* Calls function to delete the data if found */
				if( delete_contact( address_book, pointer ) != e_success )
				{
					printf("ERROR: Unable to delete the entry\n");
				}
				break;
			case 2:
				//Search and delete by phone number
delete_phone:
				printf("Enter the Phone Number : ");
				scanf("%32[^\n]", key);
				getchar();

				//Validates the name enetered by the user
				if( validate_phone_number(key) == e_fail )
				{
					printf("WARNING : Invalid Phone Number\n");
					goto delete_phone;
				}

				/* Searches the file for the phone number */
				if( search_by_phone( address_book->fptr, key, DELETE, &pointer) == e_no_match )
				{
					printf("No entry found for %s\n", key);
					break;
				}

				/* Calls function to delete the data if found */
				if( delete_contact( address_book, pointer ) != e_success )
				{
					printf("ERROR: Unable to delete the entry\n");
				}
				break;
			case 3:
				//Search and delete by email
delete_email:
				printf("Enter the Email : ");
				scanf("%32[^\n]", key);
				getchar();

				//Validates the name enetered by the user
				if( validate_email(key) == e_fail )
				{
					printf("WARNING : Invalid Email ID\n");
					goto delete_email;
				}

				/* Searches the file for the email address */
				if( search_by_email( address_book->fptr, key, DELETE, &pointer) == e_no_match )
				{
					printf("No entry found for %s\n", key);
					break;
				}

				/* Calls function to delete the data if found */
				if( delete_contact( address_book, pointer ) != e_success )
				{
					printf("ERROR: Unable to delete the entry\n");
				}
				break;
			case 0:
				//To go back
				break;
			default:
				printf("Invalid Option\n");
				break;
		}

	}while( option != 0);
}


/* Function to copy the data to a temporary file, delete the required index and update
   index of the remaining entries */
Status delete_contact( AddressBook *address_book, int pointer )
{
	/* Declaring arrays to store the data fetched from the file */
	char line[LINE_LEN], index[INDEX_LEN], name[NUMBER_LEN], phone[NUMBER_LEN], email[EMAIL_ID_LEN], location[STATE_LEN];

	/* Variable to store the index of the contact */
	int index_val;

	/* Opens a temporary file to store the data */
	FILE *temporary_file = fopen(TEMPORARY_FILE, "w+" );

	/* Validate if file has been opened correctly */
	if( temporary_file == NULL )
	{
		printf("ERROR: Unable to Open Temporary File\n");
		return e_fail;
	}

	/* Sets the file pointer to where the data to be deleted is */
	fseek( address_book->fptr, pointer, SEEK_SET );

	/* Reads the data to be deleted and obtains the index */
	fscanf(address_book->fptr, "%[^\n]\n", line);

	strcpy( index, strtok( line, ",") ); //Obtains the index of the entry to be deleted
	index_val = atoi( index ); //Obtains the integer value of the index

	/* Copies the data in the csv file to the temporary file */
	copy_file_data( address_book->fptr, temporary_file );

	/* Resets the file pointer before the entry to be deleted */
	fseek( address_book->fptr, pointer, SEEK_SET );

	/* Loop to update and write data back to the original file */
	while( fscanf(temporary_file, "%[^\n]\n", line ) != EOF )
	{
		strcpy( index, strtok(line, "," ) );
		itoa( index_val, index ); //Obtains the string of index
		index_val++; //Updates the index 
		strcpy( name, strtok( NULL, "," ) );
		strcpy( phone, strtok( NULL, "," ) );
		strcpy( email, strtok( NULL, "," ) );
		strcpy( location, strtok( NULL, "," ) );

		fprintf(address_book->fptr, "%s", index);
		fprintf(address_book->fptr, "%c", DELIMITER);
		fprintf(address_book->fptr, "%s", name);
		fprintf(address_book->fptr, "%c", DELIMITER);
		fprintf(address_book->fptr, "%s", phone);
		fprintf(address_book->fptr, "%c", DELIMITER);
		fprintf(address_book->fptr, "%s", email);
		fprintf(address_book->fptr, "%c", DELIMITER);
		fprintf(address_book->fptr, "%s", location);
		fprintf(address_book->fptr, "%c", DELIMITER);
		fprintf(address_book->fptr, "%c", NEXT_ENTRY);

	}
	//To clear the last line
	line[0] = ' ';
	pointer = ftell(address_book->fptr);
	fprintf(address_book->fptr, "%-80s", line );
	fseek( address_book->fptr, pointer, SEEK_SET ); //Resets the file pointer back to last line

	(address_book->count)--; //Updates the count in the structre variable
	if( fclose( temporary_file ) != 0 )	//Closes the temporary file
	{
		printf("ERROR: Unabble to close the temporary file\n");
		return e_fail;
	}
	if( remove(TEMPORARY_FILE) != 0 )	//Removes the temporary file
	{
		printf("ERROR: Unable to remove temporary file\n");
		return e_fail;
	}
	return e_success;
}
