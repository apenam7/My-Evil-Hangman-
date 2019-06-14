#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_apenamar_blah(char* buffer, int length);
Status test_apenamar_bleh(char* buffer, int length);
Status test_jcalles_get_capacity_on_init_default_returns_7(char* buffer, int length);
Status test_jcalles_init_c_string_returns_nonNULL(char* buffer, int length);
Status test_jcalles_destroy_changes_handle_to_NULL(char* buffer, int length);
Status test_jcalles_compare_works_with_non_alphanumeric_characters(char* buffer, int length);
Status test_jcalles_my_string_c_str_returns_address_of_data(char* buffer, int length);
Status test_jcalles_my_string_pop_back_reduces_size(char* buffer, int length);
Status test_jcalles_my_string_empty_confirms_on_popped_back_string(char* buffer, int length);
Status test_jcalles_my_string_concat_properly_adjusts_size(char* buffer, int length);
Status test_jcalles_my_string_c_str_does_not_change_size(char* buffer, int length);
Status test_jcalles_my_string_at_correctly_returns_address(char* buffer, int length);
Status test_jcalles_extraction_returns_correct_size(char* buffer, int length);
Status test_jcalles_insertion_prints_c_string_correctly(char* buffer, int length);
Status test_jcalles_extraction_copies_correctly_from_file(char* buffer, int length);
Status test_apenamartinez_compare_returns_0(char* buffer, int length);
Status test_apenamartinez_compare_returns_greater_than_0( char *buffer, int length );
Status test_apenamartinez_compare_returns_less_than_0( char *buffer, int length );
Status test_apenamartinez_concat_allocates_additional_memory( char *buffer, int length);
Status test_apenamartinez_concat_returns_success( char *buffer, int length);
Status test_apenamartinez_concat_returns_success_with_empty_string( char *buffer, int length);
Status test_apenamartinez_empty_returns_false_on_a_nonempty_string( char *buffer, int length);
Status test_apenamartinez_empty_returns_true_on_an_empty_string( char *buffer, int length);
Status test_apenamartinez_pop_back_decrements_size( char *buffer, int length);
Status test_apenamartinez_pop_back_returns_success_on_a_nonempty_string( char *buffer, int length);
Status test_apenamartinez_pop_back_returns_failure_on_an_empty_string( char *buffer, int length);
Status test_apenamartinez_push_back_allocates_additional_memory( char *buffer, int length);
Status test_apenamartinez_push_back_returns_success( char *buffer, int length);




#endif
