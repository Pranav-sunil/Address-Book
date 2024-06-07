/* File contains the prototype of functions rquired to
   carryout the process of deleting a contact details based
   on user input from the .csv file */

#include "address_book.h"

#ifndef DELETE_CONTACT_H
#define DELETE_CONTACT_H

/* Function to fetch required key based on which the contact details must be removed */
void delete_entry( AddressBook *address_book );

/* Function to delete and update the index in the file */
Status delete_contact( AddressBook *address_book, int pointer );

#endif
