/* File contains the prototype of functions required to
   carryout the process of searching the details of required
   contact from the saved .csv file
*/

#include "address_book.h"

#ifndef SEARCH_CONTACT_H
#define SEARCH_CONTACT_H

/* Function to select the data to be searched and validate it */
void search_file( AddressBook *address_book );

/* Function to search the file for the required name and display details */
Status search_by_name( FILE *file_pointer, const char *key, char mode, int *pointer_position );

/* Function to search the file for the required phone number and display details */
Status search_by_phone( FILE *file_pointer, const char *key, char mode, int *pointer_position );

/* Function to search the file for the required email address and display details*/
Status search_by_email( FILE *file_pointer, const char *key, char mode, int *pointer_position );

/* Function to search the file for the required location and display details */
Status search_by_location( FILE *file_pointer, const char *key, char mode );

#endif
