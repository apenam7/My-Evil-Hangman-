#include <stdio.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
  MY_STRING hString = NULL;

  hString = my_string_init_default();

  if(hString == NULL)
    {
      strncpy(buffer, "test_init_default_returns_nonNULL\n"
	      "my_string_init_default returns NULL", length);
      return FAILURE;
    }
  else
    {
      my_string_destroy(&hString);
      strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
      return SUCCESS;
    }
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  
  hString = my_string_init_default();
  
  if(my_string_get_size(hString) != 0)
    {
      status = FAILURE;
      printf("Expected a size of 0 but got %d\n"
	     , my_string_get_size(hString));
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
	     "Did not receive 0 from get_size after init_default\n", length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
    }
  my_string_destroy(&hString);
  return status;
}

Status test_jcalles_get_capacity_on_init_default_returns_7(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;

  hString = my_string_init_default();

  if (my_string_get_capacity(hString) != 7)
    {
      status = FAILURE;
      printf("Expected a capacity of 7 but got %d\n",
	 my_string_get_size(hString));
      strncpy(buffer,
	      "test_get_capacity_on_init_default_returns_7\n"
	      "Did not receive 7 from get_capacity after init_default\n"
	      , length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer,
	      "test_get_capacity_on_init_default_returns_7\n"
	      , length);
    }
  my_string_destroy(&hString);
  return status;
}

Status test_jcalles_init_c_string_returns_nonNULL(char* buffer, int length)
{
  MY_STRING hString = NULL;
  hString = my_string_init_c_string("StarLight");

  if(hString == NULL)
    {
      strncpy(buffer,
	      "test_jcalles_init_c_string_returns_nonNULL\n"
	      "my_string_init_c_string returns NULL"
	      , length);
      return FAILURE;
    }
  else
    {
      my_string_destroy(&hString);
      strncpy(buffer
	      , "test_jcalles_init_c_string_returns_nonNULL\n"
	      , length);
      return SUCCESS;
    }
}

Status test_jcalles_destroy_changes_handle_to_NULL(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  int* x;
  hString = my_string_init_c_string("StarLight");
  my_string_destroy(&hString);

  x = (int*)hString;

  if (x != NULL)
    {
      strncpy(buffer,
	      "test_jcalles_destroy_changes_handle_to_NULL\n"
	      "my_string_destroy does not return NULL"
	      , length);
      status = FAILURE;
    }
  else
    {
      strncpy(buffer
	      , "test_jcalles_destroy_changes_handle_to_NULL\n"
	      , length);
      status = SUCCESS;
    }
  return status;
}


Status test_jcalles_compare_works_with_non_alphanumeric_characters(char* buffer, int length)
{
  MY_STRING hRstring = NULL;
  MY_STRING hLstring = NULL;
  int result = 0;
  Status status = FAILURE;

  hRstring = my_string_init_c_string("+-&^ *"); // R is smaller
  hLstring = my_string_init_c_string("+-&^ *?");

  result = my_string_compare(hLstring, hRstring);

  if (result <= 0)
    {
      strncpy(buffer,
	      "test_jcalles_compare_works_with_non_alphanumeric_characters\n"
	      "my_string_compare returned incorrect value"
	      , length);
      status = FAILURE;
    }
  else
    {
      strncpy(buffer,
	      "test_jcalles_compare_works_with_non_alphanumeric_characters\n"
	      , length);
      status = SUCCESS;
    }
  my_string_destroy(&hRstring);
  my_string_destroy(&hLstring);
  return status;
}

Status test_jcalles_my_string_c_str_returns_address_of_data(char* buffer, int length)
{
  MY_STRING hMy_string = NULL;
  char* c;
  int i = 0;
  Status status = SUCCESS; // initially assume the best of people
  char actual_string[9] = "StarLight";
  
  hMy_string = my_string_init_c_string(actual_string);
  c = my_string_c_str(hMy_string);
  
  for (i = 0; i < 9; i++, c++) // loop through c-string
    {
      if (*c != actual_string[i])
	{
	  status = FAILURE;
	}
    }

  if (status == FAILURE)
    {
      strncpy(buffer,
	      "test_jcalles_my_string_c_str_returns_address_of_data\n"
	      "Address returned by my_string_c_str did not align."
	      , length);
    }
  else
    {
      strncpy(buffer,
	      "test_jcalles_my_string_c_str_returns_address_of_data\n"
	      , length);
    }

  my_string_destroy(&hMy_string);
  return status;
}

Status test_jcalles_my_string_pop_back_reduces_size(char* buffer, int length)
{
  MY_STRING hMy_string = NULL;
  Status status;
  hMy_string = my_string_init_c_string("StarLight");
  my_string_pop_back(hMy_string);
  if (my_string_get_size(hMy_string) != 8)
    {
      strncpy(buffer,
	      "test_jcalles_my_string_pop_back_reduces_size\n"
	      "my_string_pop_back did not properly reduce size of hMy_string"
	      , length);
      status = FAILURE;
    }
  else
    {
     strncpy(buffer,
	      "test_jcalles_my_string_pop_back_reduces_size\n"
	      , length);
      status = SUCCESS;
    }
  my_string_destroy(&hMy_string);
  return status;
}

Status test_jcalles_my_string_empty_confirms_on_popped_back_string(char* buffer, int length)
{
  MY_STRING hMy_string = NULL;
  Status status;
  hMy_string = my_string_init_c_string("StarLight");
  
  my_string_pop_back(hMy_string); // S
  my_string_pop_back(hMy_string); // t
  my_string_pop_back(hMy_string); // a
  my_string_pop_back(hMy_string); // r
  my_string_pop_back(hMy_string); // L
  my_string_pop_back(hMy_string); // i
  my_string_pop_back(hMy_string); // g
  my_string_pop_back(hMy_string); // h
  my_string_pop_back(hMy_string); // t

  if (!my_string_empty(hMy_string))
    {
      strncpy(buffer,
	      "test_jcalles_my_string_empty_confirms_on_popped_back_string\n"
	      "my_string_empty did not work when hMy_string is popped empty"
	      , length);
      status = FAILURE;
    }
  else
    {
     strncpy(buffer,
	      "test_jcalles_my_string_empty_confirms_on_popped_back_string\n"
	      , length);
      status = SUCCESS;
    }
  my_string_destroy(&hMy_string);
  return status;
}

Status test_jcalles_my_string_concat_properly_adjusts_size(char* buffer, int length)
{
  MY_STRING hFirstString = NULL;
  MY_STRING hSecondString = NULL;
  Status status;
  hFirstString = my_string_init_c_string("StarLight");
  hSecondString = my_string_init_c_string("Diamonds");
  my_string_concat(hFirstString, hSecondString);
  if (my_string_get_size(hFirstString) != 17)
    {
      strncpy(buffer,
	      "test_jcalles_my_string_concat_properly_adjusts_size\n"
	      "my_string_concat did not properly adjust size"
	      , length);
      status = FAILURE;
    }
  else
    {
     strncpy(buffer,
	      "test_jcalles_my_string_concat_properly_adjusts_size\n"
	      , length);
      status = SUCCESS;
    }

  my_string_destroy(&hFirstString);
  my_string_destroy(&hSecondString);
  return status;
}

Status test_jcalles_my_string_c_str_does_not_change_size(char* buffer, int length)
{
  MY_STRING hMy_string = NULL;
  Status status;
  hMy_string = my_string_init_c_string("StarLight");
  my_string_c_str(hMy_string);
  if (my_string_get_size(hMy_string) != 9)
    {
      strncpy(buffer,
	      "test_jcalles_my_string_c_str_does_not_change_size\n"
	      "my_string_c_string inappropriately altered the size of string"
	      , length);
      status = FAILURE;
    }
  else
    {
     strncpy(buffer,
	      "test_jcalles_my_string_c_str_does_not_change_size\n"
	      , length);
      status = SUCCESS;
    }
  my_string_destroy(&hMy_string);
  return status;
}

Status test_jcalles_my_string_at_correctly_returns_address(char* buffer, int length)
{
  MY_STRING hMy_string = NULL;
  Status status = SUCCESS; // initially assume the best of people
  char actual_string[9] = "StarLight";
  int i = 0;
  hMy_string = my_string_init_c_string(actual_string);
  
  for (i = 0; i < 9; i++) // loop through c-string
    {
      if (*my_string_at(hMy_string, i) != actual_string[i])
	{
	  status = FAILURE;
	}
    }

  if (status == FAILURE)
    {
      strncpy(buffer,
	      "test_jcalles_my_string_at_correctly_returns_address\n"
	      "Address returned by my_string_at did not align."
	      , length);
    }
  else
    {
      strncpy(buffer,
	      "test_jcalles_my_string_at_correctly_returns_address\n"
	      , length);
    }

  my_string_destroy(&hMy_string);
  return status;
}

Status test_jcalles_extraction_returns_correct_size(char* buffer, int length)
{

  MY_STRING hMy_string = NULL;
  Status status;
  FILE* fp;
  
  hMy_string = my_string_init_default();
  
  fp = fopen("x01qIlnv7r.txt", "w");
  fprintf(fp, "  StarLight Diamonds  ");
  fclose(fp);
  
  fp = fopen("x01qIlnv7r.txt", "r");

  my_string_extraction(hMy_string, fp);
  if (my_string_get_size(hMy_string) != 9)
    {
      strncpy(buffer,
	      "test_jcalles_extraction_returns_correct_size\n"
	      "my_string_extraction set the wrong size or inlcuded spaces"
	      , length);
      status = FAILURE;
    }
  else
    {
      strncpy(buffer,
	      "test_jcalles_extraction_returns_correct_size\n"
	      , length);
      status = SUCCESS;
    }
  
  fclose(fp);
  remove("x01qIlnv7r.txt");
  my_string_destroy(&hMy_string);
  return status;
}

Status test_jcalles_insertion_prints_c_string_correctly(char* buffer, int length)
{
  MY_STRING hMy_string = NULL;
  char actual_string[9] = "StarLight";
  Status status = SUCCESS;
  int i = 0;
  FILE* fp;

  hMy_string = my_string_init_c_string(actual_string);
  
  fp = fopen("x01qIlnv7r.txt", "w");
  my_string_insertion(hMy_string, fp);
  fclose(fp);
  
  fp = fopen("x01qIlnv7r.txt", "r");

  for (i = 0; i < 9; i++) // loop through c-string
    {
      if (fgetc(fp) != actual_string[i])
	{
	  status = FAILURE;
	}
    }
  
  if (status == FAILURE)
    {
      strncpy(buffer,
	      "test_jcalles_insertion_prints_c_string_correctly\n"
	      "my_string_insertion did not copy to buffer correctly"
	      , length);
      status = FAILURE;
    }
  else
    {
      strncpy(buffer,
	      "test_jcalles_insertion_prints_c_string_correctly\n"
	      , length);
      status = SUCCESS;
    }
  
  fclose(fp);
  remove("x01qIlnv7r.txt");
  my_string_destroy(&hMy_string);
  return status;
}

Status test_jcalles_extraction_copies_correctly_from_file(char* buffer, int length)
{

  MY_STRING hMy_string = NULL;
  char actual_string[9] = "StarLight";
  Status status = SUCCESS;
  FILE* fp;
  int i = 0;
  
  hMy_string = my_string_init_default();
  
  fp = fopen("x01qIlnv7r.txt", "w");
  fprintf(fp, "  StarLight Diamonds  ");
  fclose(fp);
  
  fp = fopen("x01qIlnv7r.txt", "r");
  my_string_extraction(hMy_string, fp);
  fclose(fp);

  for (i = 0; i < 9; i++) // loop through c-string
    {
      if (*my_string_at(hMy_string, i) != actual_string[i])
	{
	  status = FAILURE;
	}
    }

  if (status == FAILURE)
    {
      strncpy(buffer,
	      "test_jcalles_extraction_copies_correctly_from_file\n"
	      "my_string_extraction did not copy correctly from file."
	      , length);
      status = FAILURE;
    }
  else
    {
      strncpy(buffer,
	      "test_jcalles_extraction_copies_correctly_from_file\n"
	      , length);
      status = SUCCESS;
    }
  
  remove("x01qIlnv7r.txt");
  my_string_destroy(&hMy_string);
  return status;
}

Status test_apenamartinez_compare_returns_0(char* buffer, int length)
{
  MY_STRING hLeft_string = NULL;
  MY_STRING hRight_string = NULL;
  Status status;

  hLeft_string = my_string_init_c_string( "loremipsum" ) ;
  hRight_string = my_string_init_c_string( "loremipsum" ) ;

  if ( my_string_compare( hLeft_string, hRight_string ) == 0)
    {
      status = SUCCESS ;
      strncpy( buffer, "test_apenamartinez_compare_returns_0\n", length ) ;
    }
  else
    {
      status = FAILURE ;
      strncpy( buffer, "test_apenamartinez_compare_returns_0\n"
	       "my_string_compare returned a value greater or less than 0\n", length);
    
    }
  my_string_destroy( &hLeft_string ) ;
  my_string_destroy( &hRight_string ) ;
  return status ; 
}

Status test_apenamartinez_compare_returns_greater_than_0( char *buffer, int length )
{

  MY_STRING hLeft_string = NULL ;
  MY_STRING hRight_string = NULL ;
  Status status ;

  hLeft_string = my_string_init_c_string( "lorem" ) ;
  hRight_string = my_string_init_c_string( "ipsum" ) ;

  if ( my_string_compare( hLeft_string, hRight_string ) > 0 )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_compare_returns_greater_than_0\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_compare_returns_greater_than_0\n"
             "my_string_compare returned a value less than or equal to zero\n", length ) ;

    }

  my_string_destroy( &hLeft_string ) ;
  my_string_destroy( &hRight_string ) ;
  return status ;
}

Status test_apenamartinez_compare_returns_less_than_0( char *buffer, int length )
{

  MY_STRING hLeft_string = NULL ;
  MY_STRING hRight_string = NULL ;
  Status status ;

  hLeft_string = my_string_init_c_string( "lorem" ) ;
  hRight_string = my_string_init_c_string( "loremipsum" ) ;

  if ( my_string_compare( hLeft_string, hRight_string ) < 0 )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_compare_returns_less_than_0\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_compare_returns_less_than_0\n"
             "my_string_compare returned a value greater than or equal to zero\n", length ) ;

    }

  my_string_destroy( &hLeft_string ) ;
  my_string_destroy( &hRight_string ) ;
  return status ;
}

Status test_apenamartinez_concat_allocates_additional_memory( char *buffer, int length )
{

  MY_STRING lhString = NULL ;
  MY_STRING rhString = NULL ;
  Status status ;
  int capacity ;

  lhString = my_string_init_c_string( "lorem" ) ;
  rhString = my_string_init_c_string( "ipsum" ) ;
  capacity = my_string_get_capacity( lhString ) ;
  my_string_concat( lhString, rhString ) ;

  if ( capacity < my_string_get_size( lhString ) )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_concat_allocates_additional_memory\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_concat_allocates_additional_memory\n"
              "my_string_concat does not allocate additional memory\n", length ) ;

    }

  my_string_destroy( &lhString ) ;
  my_string_destroy( &rhString ) ;
  return status ;
}

Status test_apenamartinez_concat_returns_success( char *buffer, int length )
{

  MY_STRING lhString = NULL ;
  MY_STRING rhString = NULL ;
  Status status ;

  lhString = my_string_init_c_string( "lorem" ) ;
  rhString = my_string_init_c_string( "ipsum" ) ;

  if ( my_string_concat( lhString, rhString ) )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_concat_returns_success\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_concat_returns_success\n"
              "my_string_concat does not return success\n", length ) ;

    }

  my_string_destroy( &lhString ) ;
  my_string_destroy( &rhString ) ;
  return status ;
}

Status test_apenamartinez_concat_returns_success_with_empty_string( char *buffer, int length )
{

  MY_STRING lhString = NULL ;
  MY_STRING rhString = NULL ;
  Status status ;

  lhString = my_string_init_c_string( "lorem" ) ;
  rhString = my_string_init_default() ;

  if ( my_string_concat( lhString, rhString ) )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_concat_returns_success_with_empty_string\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_concat_returns_success_with_empty_string\n"
              "my_string_concat return success with empty string\n", length ) ;

    }

  my_string_destroy( &lhString ) ;
  my_string_destroy( &rhString ) ;
  return status ;
}

Status test_apenamartinez_empty_returns_false_on_a_nonempty_string( char *buffer, int length )
{

  MY_STRING hString = NULL ;
  Status status ;

  hString = my_string_init_c_string("loremipsum") ;

  if ( !( my_string_empty( hString ) ) )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_empty_returns_false_on_a_nonempty_string\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_empty_returns_false_on_a_nonempty_string\n"
              "my_string_empty returned true\n", length ) ;

    }

  my_string_destroy( &hString ) ;
  return status ;

}

Status test_apenamartinez_empty_returns_true_on_an_empty_string( char *buffer, int length )
{

  MY_STRING hString = NULL ;
  Status status ;

  hString = my_string_init_default() ;

  if ( my_string_empty( hString ) )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_empty_returns_true_on_an_empty_string\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_empty_returns_true_on_an_empty_string\n"
              "my_string_empty returned false\n", length ) ;

    }

  my_string_destroy( &hString ) ;
  return status ;

}

Status test_apenamartinez_pop_back_decrements_size( char *buffer, int length )
{

  MY_STRING hString = NULL ;
  Status status ;
  int size_0, size_1 ;

  hString = my_string_init_c_string("loremipsum") ;
  size_0 = my_string_get_size( hString ) ;
  my_string_pop_back( hString ) ;
  size_1 = my_string_get_size( hString ) ;

  if ( size_0 - 1 == size_1  )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_pop_back_decrements_size\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_pop_back_decrements_size\n"
              "my_string_pop_back did not decrement size\n", length ) ;

    }

  my_string_destroy( &hString ) ;
  return status ;

}

Status test_apenamartinez_pop_back_returns_success_on_a_nonempty_string( char *buffer, int length )
{

  MY_STRING hString = NULL ;
  Status status ;

  hString = my_string_init_c_string("loremipsum") ;

  if ( my_string_pop_back( hString ) )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_pop_back_returns_success_on_a_nonempty_string\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_pop_back_returns_success_on_a_nonempty_string\n"
              "my_string_pop_back returned failure\n", length ) ;

    }

  my_string_destroy( &hString ) ;
  return status ;

}

Status test_apenamartinez_pop_back_returns_failure_on_an_empty_string( char *buffer, int length )
{

  MY_STRING hString = NULL ;
  Status status ;

  hString = my_string_init_default() ;

  if ( !( my_string_pop_back( hString ) ) )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_pop_back_returns_failure_on_an_empty_string\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_pop_back_returns_failure_on_an_empty_string\n"
              "my_string_pop_back did not return failure\n", length ) ;

    }

  my_string_destroy( &hString ) ;
  return status ;

}

Status test_apenamartinez_push_back_allocates_additional_memory( char *buffer, int length )
{

  MY_STRING hString = NULL ;
  Status status ;
  int capacity ;

  hString = my_string_init_c_string( "lorem" ) ;
  capacity = my_string_get_capacity( hString ) ;

  my_string_push_back( hString, ' ' ) ;

  if ( capacity < my_string_get_capacity( hString ) )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_push_back_allocates_additional_memory\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_push_back_allocates_additional_memory\n"
              "my_string_push_back does not allocate additional memory\n", length ) ;

    }

  my_string_destroy( &hString ) ;
  return status ;

}

Status test_apenamartinez_push_back_returns_success( char *buffer, int length )
{

  MY_STRING hString = NULL ;
  Status status ;

  hString = my_string_init_c_string( "lorem ipsum" ) ;

  if ( my_string_push_back( hString, '.' ) )
    {

    status = SUCCESS ;
    strncpy( buffer, "test_apenamartinez_push_back_returns_success\n", length ) ;

    }
  else
    {

    status = FAILURE ;
    strncpy( buffer, "test_apenamartinez_push_back_returns_success\n"
              "my_string_push_back does not return success\n", length ) ;

    }

  my_string_destroy( &hString ) ;
  return status ;

}
