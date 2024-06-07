/* File Contains the prototype of functions required to
   carryout the process of adding contact details to the 
   .csv file									
*/

#include "address_book.h"

#ifndef ADD_CONTACT_H
#define ADD_CONTACT_H

/* Function to fetch details from user and write data to the file */
void add_contacts( AddressBook *address_book );

/* Function to write the field names at the beginning of the file */
void write_field_to_file( AddressBook *address_book );

#endif
