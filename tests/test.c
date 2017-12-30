#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <math.h>
#include <CUnit/CUnit.h>
#include <string.h>
#include "test_memorymap.h"
#include <string.h>
//Import your test functions here


void test_test() //This function should be placed in another file.
{
  
    CU_ASSERT_EQUAL(strcmp("hej", "hej"), 0);
}

int main(int argc, char** argv) {
  
    CU_initialize_registry(); //Boilerplate

  //New test suit begins
    CU_pSuite tests = CU_add_suite("Unit tests sample", NULL, NULL); //Creats a bundle of tests (test suit) called tests.
    CU_add_test(tests, "First unit test", test_test); // Adds a test to tests

  //Add your test suits and unit tests here.
  //The test functions should be placed in separate file the best thing would be one per module. Each module can have a seperate test suit to ease debugging.

    CU_pSuite memmap = CU_add_suite("Testing memmap", NULL, NULL);
    CU_add_test(memmap, "", test_memorymap);
  
  
    CU_basic_run_tests();//Run the tests
}
