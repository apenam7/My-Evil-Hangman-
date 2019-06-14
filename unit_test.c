#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
  Status (*tests[])(char*, int) =
    {
      test_init_default_returns_nonNULL,
      test_get_size_on_init_default_returns_0,
      test_jcalles_get_capacity_on_init_default_returns_7,
      test_jcalles_init_c_string_returns_nonNULL,
      test_jcalles_destroy_changes_handle_to_NULL,
      test_jcalles_compare_works_with_non_alphanumeric_characters,
      test_jcalles_my_string_c_str_returns_address_of_data,
      test_jcalles_my_string_pop_back_reduces_size,
      test_jcalles_my_string_empty_confirms_on_popped_back_string,
      test_jcalles_my_string_concat_properly_adjusts_size,
      test_jcalles_my_string_c_str_does_not_change_size,
      test_jcalles_my_string_at_correctly_returns_address,
      test_jcalles_extraction_returns_correct_size,
      test_jcalles_insertion_prints_c_string_correctly,
      test_jcalles_extraction_copies_correctly_from_file,
      test_apenamartinez_compare_returns_0,
      test_apenamartinez_compare_returns_greater_than_0,
      test_apenamartinez_compare_returns_less_than_0,
      test_apenamartinez_concat_allocates_additional_memory,
      test_apenamartinez_concat_returns_success,
      test_apenamartinez_concat_returns_success_with_empty_string,
      test_apenamartinez_empty_returns_false_on_a_nonempty_string,
      test_apenamartinez_empty_returns_true_on_an_empty_string,
      test_apenamartinez_pop_back_decrements_size,
      test_apenamartinez_pop_back_returns_success_on_a_nonempty_string,
      test_apenamartinez_pop_back_returns_failure_on_an_empty_string,
      test_apenamartinez_push_back_allocates_additional_memory,
      test_apenamartinez_push_back_returns_success,
      
      //write more functions
    };
  int number_of_functions = sizeof(tests)/sizeof(tests[0]);
  int i;
  char buffer[500];
  int success_count = 0;
  int failure_count = 0;

  for(i=0; i<number_of_functions; i++)
    {
      if(tests[i](buffer, 500) == FAILURE)
	{
	  printf("FAILED: Test %d failed miserably\n", i);
	  printf("\t%s\n", buffer);
	  failure_count++;
	}
      else
	{
	  printf("PASS: Test %d passed\n", i);
	  printf("\t%s\n", buffer);
	  success_count++;
	}
    }
  printf("Total number of tests: %d\n", number_of_functions);
  printf("%d/%d Pass, %d/%d Failure\n", success_count, number_of_functions,
	 failure_count, number_of_functions);
  return 0;
 

  /*const int SIZE = 100;
  MY_STRING array[SIZE];
  int i;
  for(i=0; i< SIZE; i++)
    {
      array[i] = NULL;
    }
  array[0] = my_string_init_c_string("COPY ME!");
  for(i=1; i<SIZE; i++)
    {
      my_string_assignment(&(array[i]),array[0]);
    }
  for(i=0; i<SIZE; i++)
    {
      my_string_insertion(array[i],stdout);
      printf("\n");
      my_string_destroy(&array[i]);
      }*/
}
