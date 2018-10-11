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

// A test that returns successfully is considered successful
void creationLeak() {
	
    int freeMemBefore = FreeMem();


    for(uint16_t i = 0 ; i < 10 ;  ++i )
    {
        radio::ModulationMaping myModulationMaping;
        
    }

    int freeAfter = FreeMem();

    int memoryLeak = freeMemBefore-freeAfter;

    printf("\n\r Free memory befor : %i \t Free mem After: %i \t leek: %i \n\r",freeMemBefore,freeAfter,freeMemBefore-freeAfter);

    TEST_ASSERT_MESSAGE(memoryLeak == 0,"leaking memory");
     

    





}

utest::v1::status_t test_setup(const size_t number_of_cases) {
    // Setup Greentea using a reasonable timeout in seconds
    GREENTEA_SETUP(120, "default_auto");
    return verbose_test_setup_handler(number_of_cases);
}

// Test cases
Case cases[] = {
    Case("Creation memory Leak", creationLeak),


    
};

Specification specification(test_setup, cases);

// Entry point into the tests
int main() {
    return !Harness::run(specification);
}