#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "my_string.h"
#include "generic_vector.h"
#include "avl_tree.h"

#define MAX_SIZE 30

GENERIC_VECTOR *init_dictionary( void ) ;
Boolean prompt_continue_game( void ) ;
Boolean prompt_running_total( void ) ;
int prompt_word_length( void ) ;
int prompt_number_of_guesses( void ) ;
char get_character( void ) ;
void clear_keyboard_buffer( void ) ;
void clear_screen( void ) ;
void hangman_driver( void ) ;

int main( int argc, char *argv[] ) {

    do {
        // game loop
        hangman_driver() ;

    } while ( prompt_continue_game() ) ;

    return 0 ;

}

GENERIC_VECTOR *init_dictionary( void ) {

    GENERIC_VECTOR *hgVector = ( GENERIC_VECTOR * ) malloc( MAX_SIZE * sizeof( GENERIC_VECTOR ) ) ;
    MY_STRING hString = NULL ;
    FILE *fp ;
    int i ;

    fp = fopen( "dictionary.txt", "r" ) ;

    if ( fp == NULL ) exit( 1 ) ;

    for ( i = 0; i < MAX_SIZE; i++ ) {

        hgVector[i] = generic_vector_init_default( my_string_assignment, my_string_destroy ) ;

        if ( hgVector[i] == NULL ) exit( 1 ) ;
 
    }
      
    hString = my_string_init_default() ;

    if ( hString == NULL ) exit( 1 ) ;

    while ( my_string_extraction( hString, fp ) ) {

        if ( my_string_get_size( hString ) < 30 ) {

            if ( !generic_vector_push_back( hgVector[my_string_get_size( hString )], ( Item ) hString ) ) exit( 1 ) ;
    
        }

    }

    my_string_destroy( &hString ) ;
    fclose( fp ) ;

    return hgVector ;
}

Boolean prompt_continue_game( void ) {

    char c ;

    printf( "Would you like to play again? (y/n) " ) ;
    scanf( "%c", &c ) ;
    clear_keyboard_buffer() ;

    c = tolower( c ) ;

    if ( !isalpha( c ) || ( isalpha( c ) && c != 121 && c != 110 ) ) {

        return prompt_continue_game() ;

    }

    if ( c == 121 ) return TRUE ;
    if ( c == 110 ) return FALSE ;

    return FALSE ;

}

Boolean prompt_running_total( void ) {

    char c ;

    printf( "Would you like a running total of the number of words remaining? (y/n) " ) ;
    scanf( "%c", &c ) ;
    clear_keyboard_buffer() ;

    c = tolower( c ) ;

    if ( !isalpha( c ) || ( isalpha( c ) && c != 121 && c != 110 ) ) {

        return prompt_running_total() ;

    }

    if ( c == 121 ) return TRUE ;
    if ( c == 110 ) return FALSE ;

    return FALSE ;

}


int prompt_word_length( void ) {

    int d ;

    do {

        printf( "How many characters do you want the word to be? " ) ;
        scanf( "%d", &d ) ;
        clear_keyboard_buffer() ;

    } while ( d <= 2 || d >= MAX_SIZE ) ; 

    return d ;

}

int prompt_number_of_guesses( void ) {

    int d ;

    do {

        printf( "How many guesses do you want? " ) ;
        scanf( "%d", &d ) ;
        clear_keyboard_buffer() ;

    } while ( d <= 0 || d > 26 ) ; 

    return d ;

}

char get_character( void ) {

    char c ;

    printf( "\nGuess a character: " ) ;
    scanf( "%c", &c ) ;
    clear_keyboard_buffer() ;

    if ( isalpha( c ) ) {

        c = tolower( c ) ;
    
    } else {

        return get_character() ;

    }

    return c ;

}

void clear_keyboard_buffer( void ) {
    
    char c ;

    do {

        scanf( "%c", &c) ;

    } while ( c != '\n' ) ;
    
    return ;
}

void clear_screen( void ) {

    #ifdef _WIN32
        system( "cls" ) ;
    #elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
        system( "clear" ) ;
    #else
        #error "OS not supported"
    #endif

}

void hangman_driver( void ) {

    GENERIC_VECTOR *dictionary = init_dictionary() ;
    GENERIC_VECTOR largest_family = NULL ;
    TREE hTree = avl_tree_init_default() ;
    MY_STRING word_key = my_string_init_default() ;
    MY_STRING guess_list = my_string_init_c_string( " " ) ;
    MY_STRING word_family = my_string_init_default() ;
    int word_length, number_of_guesses, running_total, i ;
    char current_guess ;

    clear_screen() ;
    word_length = prompt_word_length() ;
    number_of_guesses = prompt_number_of_guesses() ;
    running_total = prompt_running_total() ;


    for ( i = 0; i < word_length; i++ ) my_string_push_back( word_key, '-' ) ;

    // logic loop
    clear_screen() ;

    do {
        
        printf( "You have %d guess(es) remaining\nLetters used: ", number_of_guesses ) ;
        my_string_insertion( guess_list, stdout ) ;
        
        printf( "\nCurrent word: ") ;
        my_string_insertion( word_key, stdout ) ;

        do {

            current_guess = get_character() ;

        } while ( check_if_used( guess_list, current_guess ) ) ;

        my_string_push_back( guess_list, current_guess) ;
        my_string_push_back( guess_list, ',' ) ;
        my_string_push_back( guess_list, ' ' ) ;

        // ISSUE MIGHT BE WITH PUSHBACK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        clear_screen() ;

        if ( running_total ) printf( "Running total of the number of words remaining:\n" ) ;

        for ( i = 0; i < generic_vector_get_size( dictionary[word_length] ); i++ ) {
   
            get_word_key_value( word_key, word_family, generic_vector_at( dictionary[word_length], i ), current_guess ) ;
            avl_tree_push( hTree, word_family, generic_vector_at( dictionary[word_length], i ) ) ;
   
        }

        largest_family = avl_tree_get_largest_family( hTree, running_total ) ;
        generic_vector_destroy( &( dictionary[word_length] ) ) ;
        dictionary[word_length] = generic_vector_init_default( my_string_assignment, my_string_destroy ) ;
        
        for ( i = 0; i < generic_vector_get_size( largest_family ); i++ ) {

            generic_vector_push_back( dictionary[word_length], generic_vector_at( largest_family, i ) ) ;

        }

        get_word_key_value( word_key, word_family, generic_vector_at( dictionary[word_length], 0 ), current_guess ) ;

        if ( my_string_compare( word_key, word_family ) == 0 ) {
            
            printf( "\nIncorrect. The word does not include any %c's\n\n", current_guess ) ;
            number_of_guesses-- ;
        
        }

        my_string_assignment( &word_key, word_family ) ;

        generic_vector_destroy( &largest_family ) ;
        avl_tree_destroy( &hTree ) ;
        my_string_destroy( &word_family ) ;
        word_family = my_string_init_default();
        hTree = avl_tree_init_default() ;

        if ( number_of_guesses == 0 ) {
            
            printf( "You lose!\nThe word was: " ) ;
            my_string_insertion( generic_vector_at( dictionary[word_length], 0), stdout ) ;
            printf( "\n\n" ) ;
            break ;

        }

        if ( my_string_compare( generic_vector_at( dictionary[word_length], 0 ), word_key ) == 0 ) {
            
            if ( generic_vector_get_size( dictionary[word_length] ) == 1) {
            
                printf( "You win!\nThe word was: ");
                my_string_insertion( generic_vector_at( dictionary[word_length], 0), stdout ) ;
                printf( "\n\n" ) ;
                break ;
            
            }

        }

    } while ( number_of_guesses > 0 ) ;

    // free data
    avl_tree_destroy( &hTree ) ;
    my_string_destroy( &word_key ) ;
    my_string_destroy( &guess_list ) ;
    my_string_destroy( &word_family ) ;
    for ( i = 0; i < MAX_SIZE; i++ ) generic_vector_destroy( &dictionary[i] ) ;
    free( dictionary ) ;

}

//Test for Lab 4
/*int main(int argc, char* argv[])
{
  MY_STRING hMy_string = NULL;
  MY_STRING hMy_new_string = NULL;
  MY_STRING hEmpty_string_test = NULL;
  char* c = NULL;
  char* x = NULL;
  char i = '\0';
  int k = 0;
  hMy_string = my_string_init_c_string("StarLight");
  hMy_new_string = my_string_init_c_string("Diamonds");
  hEmpty_string_test = my_string_init_default();
  //--------------------------

  // test of my_string_at
  c = my_string_at(hMy_string, 4); // retrieve character at index-4
  printf("my_string_at INDEX-4: %c\n", *c);

  // tests of my_string_pushback
  printf("PUSHBACK '!': ");
  my_string_push_back(hMy_string, '!'); // add !
  my_string_insertion(hMy_string, stdout);
  printf("\n");

  printf("PUSHBACK 'T': ");
  my_string_push_back(hMy_string, 'T'); // add T
  my_string_insertion(hMy_string, stdout);
  printf("\n");

  // test of my_string_popback
  printf("POPBACK: ");
  my_string_pop_back(hMy_string); // remove last character 'T'
  my_string_insertion(hMy_string, stdout);
  printf("\n");
  
  printf("hMy_new_string: ");
  my_string_insertion(hMy_new_string, stdout);
  printf("\n");

  // test of my_string_c_str
  x = my_string_c_str(hMy_string);
  printf("ADDRESS of first character in hMy_string: %p\n", (void*)(x));
  printf("DE-REFERENCE: %c\n", *(x));

  // print-out string by deferencing until NULL terminator is found
  printf("PRINT OUT BY DE-REFERENCE: ");
  i = *(x+k);
  while (i != '\0')
    {
      printf("%c", i);
      k++;
      i = *(x+k);
    }
  printf("\n");
  
  // tests of my_string_concat
  my_string_concat(hMy_string, hMy_new_string);
  printf("CONCAT: ");
  my_string_insertion(hMy_string, stdout);
  printf("\n");

  printf("hMy_new_string: ");
  my_string_insertion(hMy_new_string, stdout);
  printf("\n");

  printf("hMy_string: ");
  my_string_insertion(hMy_string, stdout);
  printf("\n");
 


  // test if hMy_string is empty
  if(my_string_empty(hMy_string))
    {
      printf("hMy_String is: EMPTY\n");
    }
  else
    {
      printf("hMy_String is: NOT EMPTY\n");
    }

  // test if hMy_new_string is empty 
  if(my_string_empty(hMy_new_string))
    {
      printf("hMy_new_string is: EMPTY\n");
    }
  else
    {
      printf("hMy_new_string is: NOT EMPTY\n");
    }

  // test if hEmpty_string_test is empty
  if(my_string_empty(hEmpty_string_test))
    {
      printf("hEmpty_string_test is: EMPTY\n");
    }
  else
    {
      printf("hEmpty_string_test is: NOT EMPTY\n");
    }
    
  
  //--------------------------
  my_string_destroy(&hMy_string);
  my_string_destroy(&hMy_new_string);
  my_string_destroy(&hEmpty_string_test);
  
  return 0;
}

*/



/*

 "In your experience, I am sure, you have seen many a sudent practice
    floccinaucinihilipilification in regards to assignments such as this
    --I assure you that I am not different than they."

 */


/*
int main(int argc, char* argv[])
{
  MY_STRING hMy_string = NULL;
  FILE* fp;
  hMy_string = my_string_init_default();
  fp = fopen("simple.txt", "r");

  while(my_string_extraction(hMy_string, fp))
    {
      my_string_insertion(hMy_string, stdout);
      printf("\n");
      if(fgetc(fp)== ' ')
	{
	  printf("Found a space after the string\n");
	}
    }
  
  my_string_destroy(&hMy_string);
  fclose(fp);
  return 0;
}


int main(int argc, char* argv[])
{
  int compare = 2;
  MY_STRING hLeft_string = NULL;
  MY_STRING hRight_string = NULL;
  MY_STRING hMy_string = NULL;
  hMy_string = my_string_init_default();
  hLeft_string = my_string_init_c_string("StarLight");
  hRight_string = my_string_init_c_string("Courage");
  printf("SIZE OF MY STRING: %d\n", my_string_get_size(hMy_string));
  printf("SIZE OF LEFT STRING: %d\n", my_string_get_size(hLeft_string));
  printf("SIZE OF RIGHT STRING: %d\n", my_string_get_size(hRight_string));
  printf("CAPACITY OF MY STRING: %d\n", my_string_get_capacity(hMy_string));
  printf("CAPACITY OF LEFT STRING: %d\n", my_string_get_capacity(hLeft_string));
  printf("CAPACITY OF RIGHT STRING: %d\n", my_string_get_capacity(hRight_string));
  compare = my_string_compare(hLeft_string, hRight_string);
  printf("OUTPUT OF COMPARE: %d\n", compare);
  my_string_destroy(&hMy_string);
  my_string_destroy(&hLeft_string);
  my_string_destroy(&hRight_string);
  return 0;
}



{
  int i = 0;
  int x = 0;
  int y = 0;
  int rows = 20;
  int columns = 30;

  int* array[rows]; // declaration of array

  printf("Hello world! I have created a dynamic 2D-Array of 20x30 integers!\n");

  // allocate first "bookends" at each point in the array
  for(i = 0; i < rows; i++)
    {
       array[i] = (int*) malloc(sizeof(int)*columns);//First "bookend" allocates space
    }
  
  // insert numbers one-at-a-time
  for(x = 0; x < rows; x++)
    {
      for(y = 0; y < columns; y++)
	{
	  array[x][y] = x+y;
	}
    }

  // print numbers one-at-a-time
  for(x = 0; x < rows; x++)
    {                                                                                                        
      for(y = 0; y < columns; y++)                                                                           
        {                                                                                                    
          printf("%2d ", array[x][y]);
        }
      printf("\n"); // newline after each y-cycle
    }   

  // free every alloated location in memory that was used in the Array
  for (i = 0; i < rows; i++)
    {
      free(array[i]);//Second "bookend" cleans up the space
    }
  
  return 0;
}
*/
