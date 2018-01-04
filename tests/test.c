#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "test_root.h"
#include "test_integration.h"
#include "test_bits.h"

//Import your test functions here


void test_test() //This function should be placed in another file.
{
  
  CU_ASSERT_EQUAL(strcmp("hej", "hej"), 0);
}

int main(int argc, char **argv) {
  
  CU_initialize_registry(); //Boilerplate

  //New test suit begins
  CU_pSuite tests = CU_add_suite("Unit tests sample", NULL, NULL); //Creats a bundle of tests (test suit) called tests.
  CU_add_test(tests, "First unit test", test_test); // Adds a test to tests
  CU_add_test(tests, "testing safe pointer check", test_is_pointer_to_heap);
  //CU_add_test(tests, "Integration test", test_gc);
  //Add your test suits and unit tests here.
  //The test functions should be placed in separate file the best thing would be one per module. Each module can have a seperate test suit to ease debugging.

  CU_pSuite bit_tests = CU_add_suite("Bit module", NULL, NULL); //Creats a bundle of tests (test suit) called tests.
  CU_add_test(bit_tests, "Test set a bit to at a certain index", test_set_bit);
  CU_add_test(bit_tests, "Test get least significant bits", test_get_lsbs);
  CU_add_test(bit_tests, "Test set least significant bits", test_set_lsbs);
  CU_add_test(bit_tests, "Test lsbs are zero", test_lsbs_are_zero);
  CU_add_test(bit_tests, "Test lsbs to zero", test_lsbs_to_zero);
  CU_add_test(bit_tests, "Test set most significant bit", test_set_msb);
  CU_add_test(bit_tests, "Test get most significant bit", test_get_msb);
  
  CU_basic_run_tests();//Run the tests
}
