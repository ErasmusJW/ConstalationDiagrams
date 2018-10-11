#include "mbed.h"
#include "greentea-client/test_env.h"
#include "unity.h"
#include "utest.h"
#include "rtos.h"

#include "ModulationMaping.h"
#include "ErrorCodes.h"
#include <limits>
#include <vector>

using namespace utest::v1;

// A test that returns successfully is considered successful
void test_Out_Of_Range() {
	radio::ModulationMaping myModulationMaping;
    

    for(uint8_t i = MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS ; i < std::numeric_limits<uint8_t>::max(); ++i )
    {
        radio::valueAndError<radio::cmplx> val= myModulationMaping.ModulateValue(i);
        TEST_ASSERT_MESSAGE(val.err == encoding_error::CONSTALATION_INVALID_INDEX,"Out of range value not handled correctly");
    }
     

    


}
// Tests that assert are considered failing
void test_In_Range() 
{
    radio::ModulationMaping myModulationMaping;
    for(uint8_t i = 0 ; i < MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS; ++i )
    {
        radio::valueAndError<radio::cmplx> val= myModulationMaping.ModulateValue(i);
        TEST_ASSERT_MESSAGE(val.err == encoding_error::OK,"In range value not handled correctly");
    }
    
}

void test_Range_uniqueness() 
{

    radio::ModulationMaping myModulationMaping;
    std::vector<radio::cmplx> valsLookedUp;


    for(uint8_t i = 0 ; i < MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS; ++i )
    {
        radio::valueAndError<radio::cmplx> val = myModulationMaping.ModulateValue(i);

        TEST_ASSERT_MESSAGE(val.err == encoding_error::OK,"uniqueness modulating incorrectly");
        auto it = std::find(valsLookedUp.begin(),valsLookedUp.end(),val.value);
        TEST_ASSERT_MESSAGE(it == valsLookedUp.end(),"Values modulated are not unique");
        valsLookedUp.push_back(val.value);

    }



}


void test_Demodulation() 
{
    

    
    radio::ModulationMaping myModulationMaping;
    for(uint8_t i = 0 ; i < MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS; ++i )
    {
        radio::valueAndError<radio::cmplx> val= myModulationMaping.ModulateValue(i);
        TEST_ASSERT_MESSAGE(val.err == encoding_error::OK,"test_Demodulation fails to look up value");
        radio::deModValueAndDistance demod =  myModulationMaping.DemodulateValue(val.value);
        TEST_ASSERT_MESSAGE(demod.val == i,"test_Demodulation demodulates incorrectly");
    }
     

}

utest::v1::status_t test_setup(const size_t number_of_cases) {
    // Setup Greentea using a reasonable timeout in seconds
    GREENTEA_SETUP(40, "default_auto");
    return verbose_test_setup_handler(number_of_cases);
}

// Test cases
Case cases[] = {
    Case("Out Of Range", test_Out_Of_Range),
    Case("In range", test_In_Range),
    Case("test Range uniqueness", test_Range_uniqueness),
    Case("test Demodulation", test_Demodulation)

    
};

Specification specification(test_setup, cases);

// Entry point into the tests
int main() {
    return !Harness::run(specification);
}