/* File contains the enum definitions for return type of functions,
   mode, structure definitions for storing contact details for
   writing and holding the file pointer							*/

#ifndef ADDRESS_BOOK_H
#define ADDRESS_BOOK_H

/* Name of file to which data is to be saved */
#define DEFAULT_FILE				"address_book.csv"
/* Name of temporary file to store the data */
#define TEMPORARY_FILE				"temporary_file.csv"

/* Length of index string */
#define INDEX_LEN					5
/* Length of a contact name  */
#define NAME_LEN					32
/* Length of a phone number */
#define NUMBER_LEN					32
/* Length of an email address */
#define EMAIL_ID_LEN				32
/* Length of state name */
#define STATE_LEN					32
/* Length of key, for searching */
#define KEY_STRING					32
/* Length of line string to store each line from file */
#define LINE_LEN					145

#define DELIMITER					','
#define NEXT_ENTRY					'\n'

/* Macro for search mode */
#define SEARCH						'S'
/* Macro for edit mode */
#define EDIT						'E'
/* Macro for add mode */
#define ADD							'A'
/* Macro for delete mode */
#define DELETE						'D'

/* Enum for return status of functions */
typedef enum
{
	e_fail = -10,
	e_back,
	e_success,
	e_no_match,
	e_new_line,
} Status;

/* Structure to store the details temporarily */
typedef struct
{
	char name[NAME_LEN];
	char phone_numbers[NUMBER_LEN];
	char email_addresses[EMAIL_ID_LEN];
	char state[STATE_LEN];
} ContactInfo;

/* Structure to store the file pointers ,
   contactinfo structure and number of entries */
typedef struct
{
	FILE *fptr;
	ContactInfo *list;
	int count;	
} AddressBook;

#endif
