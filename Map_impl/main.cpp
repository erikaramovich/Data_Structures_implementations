#include "tests.h"

int main() {

  test_operator_brackets_simple();
  test_operator_brackets_empty_string();
  test_operator_brackets_key_not_exist();
  test_operator_brackets_key_not_exist_const();

  test_contains();
  test_contains_key_not_exist();

  test_copy_constructor();
  test_move_constructor();
  test_operator_equal_r_value();

  test_size();

  test_clear();

  test_swap_with_empty_container();
  test_swap();

  test_erase_simple();
  test_erase_returned_value();

  test_lower_bound();
  test_lower_bound_equal();
}
