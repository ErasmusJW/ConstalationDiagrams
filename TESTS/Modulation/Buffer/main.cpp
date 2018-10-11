#include "mbed.h"
#include "greentea-client/test_env.h"
#include "unity.h"
#include "utest.h"
#include "rtos.h"

#include "ModulationMaping.h"
#include "ErrorCodes.h"
#include <limits>
#include <vector>

#include <random>

#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"

using namespace utest::v1;

#define FREEMEM_CELL 100
struct elem { /* Definition of a structure that is FREEMEM_CELL bytes  in size.) */
    struct elem *next;
    char dummy[FREEMEM_CELL-2];
};
int FreeMem(void) {
    int counter;
    struct elem *head, *current, *nextone;
    current = head = (struct elem*) malloc(sizeof(struct elem));
    if (head == NULL)
        return 0;      /*No memory available.*/
    counter = 0;
   // __disable_irq();
    do {
        counter++;
        current->next = (struct elem*) malloc(sizeof(struct elem));
        current = current->next;
    } while (current != NULL);
    /* Now counter holds the number of type elem
       structures we were able to allocate. We
       must free them all before returning. */
    current = head;
    do {
        nextone = current->next;
        free(current);
        current = nextone;
    } while (nextone != NULL);
   // __enable_irq();
 
    return counter*FREEMEM_CELL;
}



// Test coverage not wide enough
void test_Out_Of_Range() 
{
	radio::ModulationMaping myModulationMaping;
    
    std::error_code er;
    uint32_t valInOutBuf = 0;

    uint8_t inBuffer[10];

    radio::cmplx pOutbuffer[1];

    std::tie(er,valInOutBuf) = myModulationMaping.ModulateBuffer(inBuffer,10,pOutbuffer,1);
    TEST_ASSERT_MESSAGE(er == encoding_error::MODULATION_BUFFER_SMALL,"Out of range value not handled correctly");


}

// Test coverage not wide enough
void test_In_Range() 
{
	radio::ModulationMaping myModulationMaping;
    
    std::error_code er;
    uint32_t valInOutBuf = 0;

    uint8_t inBuffer[10];

    radio::cmplx pOutbuffer[80];

    std::tie(er,valInOutBuf) = myModulationMaping.ModulateBuffer(inBuffer,10,pOutbuffer,80);
    TEST_ASSERT_MESSAGE(er == encoding_error::OK,"not handled correctly");
    
}

// Test coverage not wide enough
void test_Buffer_Modulation() 
{

    radio::ModulationMaping myModulationMaping;

    const uint8_t numberOfVuluesToModulate = std::numeric_limits<uint8_t>::max();
    uint8_t values[numberOfVuluesToModulate];
    radio::cmplx modulatedBuffer[numberOfVuluesToModulate*8];
    uint8_t demodulatedValues[numberOfVuluesToModulate];

    uint32_t numValuesModulated = 0;
    uint32_t numValuesDeModulated = 0;

    std::error_code er;

   //printf("Assigning values \n\r");
    for(uint16_t i = 0 ; i < numberOfVuluesToModulate ; ++i)
    {
        values[i] = i;
    }

    //printf("Values assigned \n\r");
    //cant encode more than 8 symbyls per byte currently;

    //printf("ModulateBuffer size: %i \n\r", numberOfVuluesToModulate);
    std::tie(er,numValuesModulated) = myModulationMaping.ModulateBuffer(values,numberOfVuluesToModulate,modulatedBuffer,numberOfVuluesToModulate*8);
    //printf("Buffer Modulated  \n\r");
    TEST_ASSERT_MESSAGE(er == encoding_error::OK,"Modulation error");

    //printf("DemodulateBuffer size : %i  \n\r",numValuesModulated);
    std::tie(er,numValuesDeModulated) = myModulationMaping.DemodulateBuffer(modulatedBuffer,numValuesModulated,demodulatedValues,numberOfVuluesToModulate);
    //printf("Buffer demodulated  \n\r");
    TEST_ASSERT_MESSAGE(er == encoding_error::OK,"De Modulation error");
    TEST_ASSERT_MESSAGE(numValuesDeModulated == numberOfVuluesToModulate,"numValuesDeModulated error");

    //printf("Comapring values \n\r");
    for(uint16_t i = 0 ; i < numberOfVuluesToModulate ; ++i)
    {
        TEST_ASSERT_MESSAGE(values[i] == demodulatedValues[i],"Modulation demodulation error");
         
    }
     //printf("values  compared \n\r");







}
void test_Buffer_Modulation_random_Values() 
{
     printf(" \n\r test_Buffer_Modulation_random_Values \n\r");
    radio::ModulationMaping myModulationMaping;
    mbedtls_entropy_context entropy;
    mbedtls_entropy_init( &entropy );

    mbedtls_ctr_drbg_context ctr_drbg;
    const char *personalization = "A very specific String much wow";

    mbedtls_ctr_drbg_init( &ctr_drbg );


    auto ret = mbedtls_ctr_drbg_seed( &ctr_drbg , mbedtls_entropy_func, &entropy,
                     (const unsigned char *) personalization,
                     strlen( personalization ) );
    if( ret != 0 )
    {
        printf("Random inint failed \n\r");
    }
    
    

    printf(" \n\r Random init \n\r");
    for(uint8_t i = 0; i < 10; ++i)
    {
        int freeMem = FreeMem();
        
        
        const uint16_t bufferSize = 1000;
        uint8_t  * ValesToModulate  = new uint8_t[bufferSize];
                for(int j= 0 ; j < bufferSize ; ++j)
        {
            ValesToModulate[j] = 0;
        }


        uint8_t * demodulatedValues  = new uint8_t[bufferSize];
        radio::cmplx *  modulatedBuffer  = new  radio::cmplx[bufferSize*8];
        
        std::error_code er;
        uint32_t valuesModulated = 0;
        uint32_t valuesDeModulated = 0;



        auto ret2 = mbedtls_ctr_drbg_random(&ctr_drbg,ValesToModulate,bufferSize);

        
        std::tie(er,valuesModulated) = myModulationMaping.ModulateBuffer(ValesToModulate,bufferSize,modulatedBuffer,bufferSize*8);
        TEST_ASSERT_MESSAGE(er == encoding_error::OK,"Modulation error");
        std::tie(er,valuesDeModulated) = myModulationMaping.DemodulateBuffer(modulatedBuffer,valuesModulated,demodulatedValues,bufferSize);
        TEST_ASSERT_MESSAGE(er == encoding_error::OK,"Modulation error");
        TEST_ASSERT_MESSAGE(ret2 == 0 ,"Random Init Error");
        for(int j= 0 ; j < bufferSize ; ++j)
        {
            TEST_ASSERT_MESSAGE(ValesToModulate[j] == demodulatedValues[j],"De/Modulation error");
            
        }
        delete[] ValesToModulate;
        delete[] demodulatedValues;
        delete[] modulatedBuffer;

    }
    




    // auto ret2 = mbedtls_ctr_drbg_random(&ctr_drbg,randomVal,5);

    // if( ret2 != 0 )
    // {
    //     printf("Random inint failed");
    // }

    // // std::default_random_engine generator;
    // // std::uniform_int_distribution<int> distribution(1,6);
    // // int dice_roll1 = distribution(generator);
    // // int dice_roll2 = distribution(generator);
    // // int dice_roll3 = distribution(generator);
    // // int dice_roll4 = distribution(generator);
    // printf("\n\r random \t %i %i %i %i %i \n\r",randomVal[0],randomVal[1],randomVal[2],randomVal[3],randomVal[4]);

    // TEST_ASSERT_MESSAGE(true,"Modulation demodulation error");


}






utest::v1::status_t test_setup(const size_t number_of_cases) {
    // Setup Greentea using a reasonable timeout in seconds
    GREENTEA_SETUP(60, "default_auto");
    return verbose_test_setup_handler(number_of_cases);
}

// Test cases
Case cases[] = {
    Case("Out Of Range", test_Out_Of_Range),
    Case("InRange", test_In_Range),
    Case("Buffer modulation and demodulation",test_Buffer_Modulation),
    Case("test_Buffer_Modulation_random_Values",test_Buffer_Modulation_random_Values)
   
};

Specification specification(test_setup, cases);

// Entry point into the tests
int main() {
    return !Harness::run(specification);
}