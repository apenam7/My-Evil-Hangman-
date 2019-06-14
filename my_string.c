#include <stdio.h> // include directive
#include <stdlib.h> // include directive
#include <ctype.h> // include directive
#include "my_string.h" // include header

struct my_string // declare known type of structure
{
  int size; // the number of characters currently in the object
  int capacity; // total capacity of the object
  char* data; // pointer to the object -malloc starts here
};
typedef struct my_string My_string; // define type

Boolean check_if_used( MY_STRING guess_list, char c ) {

    My_string* pMy_string = (My_string*)guess_list;
    int i ;

    for ( i = 0; i < my_string_get_size( guess_list ); i++ ) {

        if ( pMy_string -> data[i] == c ) {

            printf( "You have already guessed that letter! Try again...\n" ) ;
            return TRUE ;

        }

    }

    return FALSE ;

}

//Precondition: None
//Postcondition: Allocate space for a string object that represents the empty
//  string. The string will have capacity 7 and size 0 by default. A copy of
//  the address of the opaque object will be returned on success and NULL on
//  failure.
MY_STRING my_string_init_default(void)
{
  My_string* pString; // declare pointer to object
  pString = (My_string*)malloc(sizeof(My_string)); // allocate space for object
  if(pString != NULL) // if allocation was successful
  {
    pString->size = 0; // initalise size
    pString->capacity = 7; // initalise capacity
    pString->data = (char*)malloc(sizeof(char)*pString->capacity);
    // allocate space for capacity number of characters
  }
  else // if allocation was not successful
  {
    free(pString); // release the pointer
    pString = NULL; // and set it to NULL
  }
  return (MY_STRING)pString; // cast to handle type void* and return
}

//Precondition: phMy_string holds the address of a valid handle to a MY_STRING
//   object.
//Postcondition: The memory used for the MY_STRING object has be reclaimed by
//   the system and the handle referred to by the pointer phMy_string has been
//   set to NULL.
void my_string_destroy(Item* pItem)
{
  My_string* pMy_string = (My_string*) *pItem; // cast to the known type
  free(pMy_string->data); // release the data pointer within the object
  free(pMy_string); // release the pointer to the object itself
  *pItem = NULL; // and set it to NULL
  return; // return
}

//Precondtion: c_string is a valid null terminated c-string.
//Postcondition: Allocate space for a string object that represents a string
//   with the same value as the given c-string.  The capacity of the string
//   object will be set to be one greater than is required to hold the string.
//   As an example, the string "the" would set capacity at 4 instead of 3. A
//   copy of the address of the opaque object will be returned on success and
//   NULL on failure.
MY_STRING my_string_init_c_string(const char* c_string)
{
  int i = 0; // declare counter variable
  int capacity = 0; // declare holder variable
  int size = 0; // declare holder variable
  char c = 'd'; // declare holder variable

  for( i = 0; c != '\0'; i++) // measure the size of the given c-string
    {
      c = c_string[i];
    }
  size = i - 1; // correct one-off error 
  capacity = size; // capacity is equal to size for initial object
  
  My_string* pString; // declare pointer to object
  pString = (My_string*)malloc(sizeof(My_string)); // allocate space for object
  if(pString != NULL) // if allocation was successful
  {
    pString->size = size; // initalise size
    pString->capacity = capacity; // initalise capacity
    pString->data = (char*)malloc(sizeof(char)*pString->capacity);
    // allocate space for capacity number of characters
  }
  else // if allocation was not successful
  {
    free(pString); // release the pointer
    pString = NULL; // and set it to NULL
  }

  for (i = 0; i < capacity; i++) // copy contents of c_string onto pString
  {
    pString->data[i] = c_string[i];
  }

  return (MY_STRING)pString; // cast to handle tpye void* and return
}

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's capacity.
int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string; // cast to the known type
  return pString->capacity; // return the capacity
}

//Precondition: hMy_string is the handle of a valid My_string object.
//Postcondtion: Returns a copy of the integer value of the object's size.
int my_string_get_size(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string; // cast to the known type
  return pString->size; // return the size
}

//Precondition: hLeft_string and hRight_string are valid My_string objects.
//Postcondition: returns an integer less than zero if the string represented
//   by hLeft_string is lexicographically smaller than hRight_string.  If
//   one string is a prefix of the other string then the shorter string is
//   considered to be the smaller one. (app is less than apple).  Returns
//   0 if the strings are the same and returns a number greater than zero
//   if the string represented by hLeft_string is bigger than hRight_string.
/*int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  My_string* pLeft_string = (My_string*)hLeft_string;  // cast to the known type
  My_string* pRight_string = (My_string*)hRight_string;// cast to the known type
  char L = 'd'; // declare holder variable
  char R = 'd'; // declare holder variable
  int l = 0; // declare holder variable
  int r = 0; // declare holder variable
  int i = 0; // declare counter variable
  int Lsize = my_string_get_size(hLeft_string);
  int Rsize = my_string_get_size(hRight_string);
  
  i = 0; // initialise counter variable before entering loop
  while(1) // loop forever until return condition is met
    {
      if(i< Lsize)
	{
          L = pLeft_string->data[i]; // grab the character at index i
	}
      else
	{
	  L = '\0';
	}
      if(i< Rsize)
	{
	  R = pRight_string->data[i]; // grab the character ast index i
	}
      else
	{
	  R = '\0';
	}
      l = (int)L; // cast char L into its ASCII equvalent 
      r = (int)R; // cast char R into its ASCII equvalent 

      if (l < r || (l == 0 && r != 0)) // L is lexicographically smaller
	{
	  return -1; // return a negative number
	}
      else if (l > r || l != 0 && r == 0) // R is lexicographically smaller
	{
	  return 1; // return a positive number
	}

      if( l == 0 && r == 0) // both carry equal lexicographical weight
	{
	  return 0; // return zero
	}
      
      i++; // increment i each iteration
    }
  return 2; // return if error
  }*/

int my_string_compare( MY_STRING hLeft_string, MY_STRING hRight_string ) {

    My_string *pLeft_string = ( My_string * ) hLeft_string ;
    My_string *pRight_string = ( My_string * ) hRight_string ;
    int i ;

    for ( i = 0; i < pLeft_string -> size && i < pRight_string -> size; i++ )    {
        
        if ( pLeft_string -> data[i] < pRight_string -> data[i] )
	{
            return -1 ;
            //break;
        } else if ( pLeft_string -> data[i] > pRight_string -> data[i] ) {
            
            return 1 ;
            // break
        }

    }
    return 0;
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: hMy_string will be the handle of a string object that contains
//   the next string from the file stream fp according to the following rules.
//   1) Leading whitespace will be ignored.
//   2) All characters (after the first non-whitespace character is obtained
//      and included) will be added to the string until a stopping condition
//       is met.  The capacity of the string will continue to grow as needed
//       until all characters are stored.
//   3) A stopping condition is met if we read a whitespace character after
//      we have read at least one non-whitespace character or if we reach
//      the end of the file.
//   Function will return SUCCESS if a non-empty string is read successfully.
//   and failure otherwise.  Remember that the incoming string may aleady
//   contain some data and this function should replace the data but not
//   necessarily resize the array unless needed.
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
  My_string* pString = (My_string*)hMy_string;  // cast to the known type
  char c = 'd'; // declare holder variable
  int i = 0; // declare holder varible
  c = fgetc(fp); // assign the first charcter into char c
  while(isspace(c)) // passover whitespaces
    {
      c = fgetc(fp); // assign each following charcter into char c
	if(c == EOF) // check for end of file
	  {
	    return FAILURE; // return failure if end of file is reached
	  }
    }
  pString->size = 0; // reset size of pString for re-writing
  for(i = 0;!isspace(c); i++) // work with characters
    {
      if (pString->capacity > i+ 1) // if there is room in in pString
	{
	  pString->data[i] = c; // insert character into pSrting
	  pString->size = i + 1; // increment size
	}
      else // if there is not enough room for another character
	{
	  // reallocate twice the capacity as before resizing 
	  pString->data = (char*)realloc(pString->data, pString->capacity * 2);
	  if(pString->data == NULL)
	    {
	      return FAILURE;
	    }
	  pString->capacity *= 2; // set capacity
	  pString->data[i] = c; // insert character into pString
	  pString->size = i + 1; // increment size
	}
      c = fgetc(fp); // assign each following charcter into char c
      if(c == EOF) // check for end of file
	 {
	   return FAILURE; // return failure if end of file is reached
	 }
    }
  ungetc(c, fp); // after loop is completed, unget the final whitespace
  return SUCCESS; // return success
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Writes the characters contained in the string object indicated
//   by the handle hMy_string to the file stream fp.
//   Function will return SUCCESS if it successfully writes the string and
//   FAILURE otherwise.
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  My_string* pString = (My_string*)hMy_string; // cast to the known type
  char c = 'd'; // declare holder variable
  int i = 0; // declare holder variable
  if(pString == NULL) // check if pString is empty
    {
      return FAILURE; // if so, return failure
    }
  else // if pString actually holds something
    {
      for (i = 0; i < pString->size; i++) // loop to the end of pString
	{
	  c = pString->data[i]; // assign each following charcter into char c
	  fprintf(fp, "%c", c); // print each character one-by-one
	}
      return SUCCESS; // after loop is finished, return success
    }
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: If successful, places the character item at the end of the
//   string and returns SUCCESS.  If the string does not have enough room and
//   cannot resize to accomodate the new character then the operation fails
//   and FAILURE is returned.  The resize operation will attempt to amortize
//   the cost of a resize by making the string capacity somewhat larger than
//   it was before (up to 2 times bigger).
Status my_string_push_back(MY_STRING hMy_string, char item)
{
  My_string* pString = (My_string*)hMy_string; // cast to the known type
  if (pString->capacity > pString->size + 1) // if there is room in pString
    {
      pString->data[pString->size] = item; // insert character into pString
      pString->size = pString->size + 1; // increment size
    }
  else // if there is not enough room for another character
    {
      // reallocate twice the capacity as before resizing 
      pString->data = (char*)realloc(pString->data, pString->capacity * 2);
      if(pString->data == NULL) // if reallocation failed
	{
	  return FAILURE; // return failure
	}
      else // if reallocation succeeded
	{
	  pString->capacity *= 2; // re-set capacity
	  pString->data[pString->size] = item; // insert character into pString
	  pString->size = pString->size + 1; // increment size
	}
    }
  return SUCCESS; // return sucess
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Removes the last character of a string in constant time.
//  Guaranteed to not cause a resize operation of the internal data.  Returns
//  SUCCESS on success and FAILURE if the string is empty.
Status my_string_pop_back(MY_STRING hMy_string)
{
   My_string* pString = (My_string*)hMy_string; // cast to the known type
   if (pString->size > 0) // if pString is not empty
     {
       pString->size = pString->size - 1; // reduce size of pString
       return SUCCESS; // return sucess
     }
   else // if pString is empty
     {
       return FAILURE; // return failure
     }
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition:  Returns the address of the character located at the given
//   index if the index is in bounds but otherwise returns NULL.  This address
//   is not usable as a c-string since the data is not NULL terminated and is
//   intended to just provide access to the element at that index.
char* my_string_at(MY_STRING hMy_string, int index)
{
   My_string* pString = (My_string*)hMy_string; // cast to the known type

   if (index < pString->size && index >= 0) // if the index is within bounds
     {
       return (char*)&pString->data[index]; // return address
     }
   else // if the index is not within bounds
     {
       return NULL; // return NULL
     }
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns the address of the first element of the string object
//   for use as a c-string.  The resulting c-string is guaranteed to be NULL
//   terminated and the memory is still maintained by the string object though
//   the NULL is not actually counted as part of the string (in size).
char* my_string_c_str(MY_STRING hMy_string)
{
   My_string* pString = (My_string*)hMy_string; // cast to the known type
   my_string_push_back(hMy_string, '\0'); // insert a NULL character
   pString->size = pString->size - 1; // correct size increment 
   return (char*)&(pString->data[0]); // return address
}

//Precondition: hResult and hAppend are handles to valid My_string objects.
//Postcondition:  hResult is the handle of a string that contains the original
//   hResult object followed by the hAppend object concatenated together. This
//   function should guarantee no change to the hAppend object and return
//   SUCCESS if they operation is successful and FAILURE if the hResult object
//   is unable to accomodate the characters in the hAppend string perhaps
//   because of a failed resize operation.  On FAILURE, no change to either
//   string should be made.
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  My_string* pResult = (My_string*)hResult; // cast to the known type
  My_string* pAppend = (My_string*)hAppend; // cast to the known type
  int needed_size = (int)pResult->size + (int)pAppend->size; // find needed size
  int i= 0; // declare counter variable
  int continued_i = 0; // declare counter variable
  char* c = NULL; // declare character pointer
  char* pTemp = NULL; // declare temporary holder variable

  pTemp = (char*)malloc(sizeof(char) * needed_size); // allocate memory
  if (pTemp == NULL) // if allocation failed
    {
      return FAILURE; // return failure
    }
  
  c = my_string_c_str(hResult); // initialize character pointer
  for( i = 0; i < pResult->size; i++) // loop through first string
    {
      pTemp[i] = *(c + i); // insert one character at a time
    }

  continued_i = i; // maintain counter by saving its current value
  
  c = my_string_c_str(hAppend); // initialize character pointer
  for( i = 0; i < pAppend->size; i++) // loop through the second string
    {
      pTemp[continued_i] = *(c + i); // insert one character at a time
      continued_i++; // continue to increment the counter used above
    }

  free(pResult->data); // free old data handle
  pResult->data = pTemp; // insert new data handle
  pResult->size = needed_size; // adjust size
  pResult->capacity = needed_size; // adjust capacity
  
  return SUCCESS; // return success
}

//Precondition: hMy_string is the handle to a valid My_string object.
//Postcondition: Returns an enumerated type with value TRUE if the string
//   is empty and FALSE otherwise.
Boolean my_string_empty(MY_STRING hMy_string)
{
  My_string* pString = (My_string*)hMy_string; // cast to the known type
  if (pString->size <= 0) // if pString size is 0 (strong condition)
    {
      return TRUE; // return true (pString is empty)
    }
  else // if pString size is greater than 0
    {
      return FALSE; // return false (pString is not empty)
    }
}

void my_string_assignment(Item* pLeft, Item Right)
{
  My_string* pLeft_string = (My_string*)*pLeft;
  My_string* pRight_string = (My_string*)Right;
  int i;
  char* temp;
  temp = my_string_c_str((MY_STRING)Right);
  if(pLeft_string == NULL)
    {
      pLeft_string = my_string_init_c_string(temp);
    }
  else
    {
      pLeft_string->size = 0;
      for(i=0; i<pRight_string->size+1; i++)
	{
	  my_string_push_back(pLeft_string, pRight_string->data[i]);
	}
    }
  *pLeft = pLeft_string;
}

Status get_word_key_value( MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess ) {
    int i;
    while(!my_string_empty(new_key))
        my_string_pop_back(new_key);
    for(i = 0; i < my_string_get_size(word); i++)
        if(!my_string_push_back(new_key, *my_string_at(word, i) == guess ? guess : *my_string_at(current_word_family, i)))
            return FAILURE;
    return SUCCESS;   
}
