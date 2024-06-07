#include<stdio.h>
#include<string.h>
#include "address_book.h"
#include "functions.h"
#include "search_contact.h"
#include "edit_contact.h"


/* Function to edit the contact. This function will then give the user the option to
   search for a data of a contact and calls the search function to check if the data
   is present in the file. If yes, it will call the modify function and edit the 
   details of the contact. */
void edit_contact( AddressBook *address_book )
{
	/* Variable and array to store the file offsets in case of multiple entries */
	int pointer = 0 , index[INDEX_LEN] = {0};
	int option; //Variable to store the option read from the user
	int count = 0; //Variable to count the number of entries found
	int i; //Variable to run the loop

	/* Array to store the data to be searched in the file */
	char key[KEY_STRING];

	do
	{
		printf("############### Edit Contact ###############\n\n");
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
				//Search and edit by name
edit_name:
				printf("Enter the Name : ");
				scanf("%32[^\n]", key);
				getchar();

				//Validates the name entered by the user
				if( validate_name( key ) == e_fail )
				{
					printf("WARNING : Name can only have alphabets\n");
					goto edit_name;
				}

				/* Searching the name in the databse */
				if( search_by_name( address_book->fptr, key, EDIT, index) == e_no_match )
				{
					printf("No entry found for %s\n", key);
					break;
				}

				//Checking if there are more than 1 entries with the same first name 
				for( i = 0 ; i < 3 ; i++ )
				{
					if( index[i] != 0 )
					{
						count++;
					}
				}
				if( count == 1 )
				{
					/* If there is only one entry, then assigning pointer with 
					   the offset in index 0 */
					pointer = index[0];
				}
				else
				{
					printf("More than 1 entry found for %s\n", key);
choose_index:
					printf("Enter the Sl.No of entry to edit : ");
					scanf("%d", &i );
					if( i <= 0 && i > count )
					{
						printf("Error : Please choose correct option\n");
						goto choose_index;
					}
					pointer = index[i-1];
				}
				if( modify_entry( address_book, pointer ) != e_success )
				{
					printf("ERROR: Data not edited correctly\n");
				}
				break;
			case 2:
				//Search and edit by phone number
edit_phone:
				printf("Enter the Phone Number : ");
				scanf("%32[^\n]", key);
				getchar();

				//Validates the phone number entered by the user
				if( validate_phone_number(key) == e_fail )
				{
					printf("WARNING : Invalid Phone Number\n");
					goto edit_phone;
				}

				/* Searching the phone in the databse */
				if( search_by_phone( address_book->fptr, key, EDIT, &pointer) == e_no_match )
				{
					printf("No entry found for %s\n", key);
					break;
				}

				if( modify_entry( address_book, pointer ) != e_success )
				{
					printf("ERROR: Data not edited correctly\n");
				}
				break;
			case 3:
				//Search and edit by email
edit_email:
				printf("Enter the Email : ");
				scanf("%32[^\n]", key);
				getchar();

				//Validates the email entered by the user
				if( validate_email(key) == e_fail )
				{
					printf("WARNING : Invalid Email ID\n");
					goto edit_email;
				}


				/* Searching the email in the databse */
				if( search_by_email( address_book->fptr, key, EDIT, &pointer) == e_no_match )
				{
					printf("\nNo entry found for %s\n", key);
					break;
				}
				if( modify_entry( address_book, pointer ) != e_success )
				{
					printf("ERROR: Data not edited correctly\n");
				}
				break;
			case 0:
				//To go back
				break;
			default:
				printf("Invalid Option\n");
				break;
		}

	}while( option != 0 );
}

/* Function to fetch the details from the user and edit the details. The function will
   copy the data after required index and store to a temporary variable and then it will 
   copy the data back after modifying the data */
Status modify_entry( AddressBook *address_book, int pointer )
{

	/* Char array to store the data fetched from the file, which is to be edited */
	char line[LINE_LEN], index[INDEX_LEN], name[NAME_LEN], phone[NUMBER_LEN], email[EMAIL_ID_LEN], location[STATE_LEN];
	int option; //Variable to store the option selected by the user

	/* Creates and opens the temporary file to store the data 
	   temporarily for editing */
	FILE *temp_file = fopen("TEMPORARY_FILE", "w+");
	if( temp_file == NULL )
	{
		printf("ERROR: Unable to Open Temporary File\n");
		return e_fail;
	}

	/* Sets the file pointer to the point just before the required data */
	fseek( address_book->fptr, pointer, SEEK_SET );

	/* Scans and stores the data to a temporary array called line */
	fscanf( address_book->fptr, "%[^\n]\n", line );

	/* Obtains each data from the line to modify */
	strcpy(index, strtok( line, ","));
	strcpy(name, strtok( NULL, ","));
	strcpy(phone, strtok( NULL, ","));
	strcpy(email, strtok( NULL, ","));
	strcpy(location, strtok( NULL, ","));
	
	/* Copying the data from the file to a temporary file */
	copy_file_data(address_book->fptr, temp_file );
	/* Resets the pointer just before the data to be edited */
	fseek( address_book->fptr, pointer, SEEK_SET );

	/* Loop to obtain the data to be updated by the user */
	do
	{
		printf("############### Modify Data ################\n\n");
		printf("0. Back\n");
		printf("1. Name         :          %s\n", name);
		printf("2. Phone No     :          %s\n", phone);
		printf("3. Email        :          %s\n", email);
		printf("4. Location     :          %s\n", location);

		printf("Enter option : ");
		scanf("%d", &option);
		getchar();
		switch(option)
		{
			case 1:
				//Reads new name for the contact from the user
edit_name:
				printf("Enter the name : ");
				scanf("%32[^\n]", name);
				getchar();

				//Validates the name entered by the user
				if( validate_name( name ) == e_fail )
				{
					printf("ERROR : Name can only have Alphabets\n");
					goto edit_name;
				}
				break;
			case 2:
				//Reads new phone number for the contact from the user
edit_phone:		
				printf("Enter phone number : ");
				scanf("%32[^\n]", phone);
				getchar();

				//Validates the phone number entered by the user
				if( validate_phone_number( phone ) == e_no_match )
				{
					printf("ERROR : Phone number should have 10 Digits\n");
					goto edit_phone;
				}
				else if( validate_phone_number( phone ) == e_fail )
				{
					printf("ERROR : Phone number should have only digits\n");
					goto edit_phone;
				}
				break;
			case 3:
				//Reads new email address for the contact from the user
edit_mail:
				printf("Enter the email : ");
				scanf("%32[^\n]", email);
				getchar();

				//Validates the email entered by the user
				if( validate_email( email) == e_fail )
				{
					printf("ERROR : Email address is not valid\n");
					goto edit_mail;
				}
				break;
			case 4:
				//Reads new place for the contact from the user
				printf("Enter the Place : ");
				scanf("%32[^\n]", location);
				getchar();
			default:
				//invalid option, restart loop
		}
	}while( option != 0 );

	//write obtained data to the file
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

	/* Copies the data back from the temporary file to the main file */
	copy_file_data( temp_file, address_book->fptr );
	
	/* Closes the temporary file stream */
	if( fclose( temp_file ) != 0 )
	{
		printf("ERROR: Unable to close the temporary file\n");
		return e_fail;
	}

	/* Removes the temporary file */
	if( remove("TEMPORARY_FILE") != 0 )
	{
		printf("ERROR: Unable to remove the temporary file\n");
		return e_fail;
	}

	return e_success;
}
