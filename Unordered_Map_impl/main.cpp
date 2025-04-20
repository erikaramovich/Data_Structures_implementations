#include "tests.h"

int main() {
  test_operator_brackets_simple();
  test_operator_brackets_empty_string();
  test_operator_brackets_key_not_exist();
  test_operator_brackets_key_not_exist_const();

  test_contains_simple();
  test_contains_false();

  test_find();
  test_find_not_found();

  test_insert_false();
  test_insert_accessed();

  test_erase_simple();
  test_erase_returned_value();

  test_empty_simple();
  test_empty();

  test_size();
  test_size_empty_container();

  test_operator_equal_r_value();
  test_move_constructor();
  test_copy_constructor();
}