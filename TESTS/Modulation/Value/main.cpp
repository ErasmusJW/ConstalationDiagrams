#include "mbed.h"
#include "greentea-client/test_env.h"
#include "unity.h"
#include "utest.h"
#include "rtos.h"

#include "ModulationMaping.h"
#include "ErrorCodes.h"

using namespace utest::v1;

// A test that returns successfully is considered successful
void test_Out_Of_Range() {
	radio::ModulationMaping myModulationMaping;
    radio::valueAndError<radio::cmplx> val= myModulationMaping.ModulateValue(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS);


    
    TEST_ASSERT_MESSAGE(val.err == encoding_error::CONSTALATION_INVALID_INDEX,"Out of range value not handled correctly");

}
// Tests that assert are considered failing
void test_failure() {
    TEST_ASSERT(true);
}

utest::v1::status_t test_setup(const size_t number_of_cases) {
    // Setup Greentea using a reasonable timeout in seconds
    GREENTEA_SETUP(40, "default_auto");
    return verbose_test_setup_handler(number_of_cases);
}

// Test cases
Case cases[] = {
    Case("Out Of Range", test_Out_Of_Range),
    Case("Testing failure test", test_failure),
};

Specification specification(test_setup, cases);

// Entry point into the tests
int main() {
    return !Harness::run(specification);
}