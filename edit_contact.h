/* File contains the prototype of functions required to
   carryout the process of editing contact details saved
   in the .csv file and write it back
*/

#include "address_book.h"

#ifndef EDIT_CONTACT_H 
#define EDIT_CONTACT_H 

/* Function to fetch the key using which the contact is to be searched and validates it */
void edit_contact( AddressBook *address_book );

/* Function to modify the details of the contact in the .csv file */
Status modify_entry( AddressBook *address_book, int pointer );

#endif
