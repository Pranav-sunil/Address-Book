/* File contains the prototypes of all general functions required */

#include "address_book.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* Function to create and open the .csv file */
Status create_and_open_file( AddressBook *address_book );

/* Function to select the operation type */
Status menu( AddressBook *address_book );

/* Function to print the menu options */
void main_menu( void );

/* Function to check if the name passed by the user is a valid name */
Status validate_name( const char *name);

/* Function to check if the phone number passed by the user is a valid number */
Status validate_phone_number( const char *phone );

/* Function to check if the email address passed by the user is a valid email */
Status validate_email( const char *email );

/* Function to convert an integer number to a string */
void itoa( int num, char *str );

/* Function to initalize the structre for reading data */
void initalize_structre( AddressBook *address_book );

/* Function to copy the contents of the source file to the destination file */
void copy_file_data( FILE *source, FILE *destination );

/* Function to print the header for displaying contact details */
void print_header(void);

/* Function to print the footer for displaying contact details */
void print_footer(void);

#endif
