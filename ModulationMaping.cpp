#include"ModulationMaping.h"
#include <limits>
	
	/**
	 * C++ version 0.4 char* style "itoa":
	 * Written by Lukás Chmela
	 * Released under GPLv3.

	 */
	char* itoa(int value, char* result, int base) {
		// check that the base if valid
		if (base < 2 || base > 36) { *result = '\0'; return result; }

		char* ptr = result, *ptr1 = result, tmp_char;
		int tmp_value;

		do {
			tmp_value = value;
			value /= base;
			*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
		} while ( value );

		// Apply negative sign
		if (tmp_value < 0) *ptr++ = '-';
		*ptr-- = '\0';
		while(ptr1 < ptr) {
			tmp_char = *ptr;
			*ptr--= *ptr1;
			*ptr1++ = tmp_char;
		}
		return result;
	}
	

namespace radio {

    ModulationMaping::ModulationMaping()
    {
    }

    ModulationMaping::~ModulationMaping()
    {
    }



    //special case for when modulation size small is needed, bsk ect - maybe something more effiecent- a mini distance ect
    deModValueAndDistance ModulationMaping::DemodulateValue(const cmplx &InputVal) const
    {
        float smallestDistance 
        = std::numeric_limits<float>::max();
        uint8_t iReturnValue =0; 

        for(uint8_t i = 0 ; i < m_ConstalationDiagram.ConstalationSize ; ++i)
        {
            float diss = ModulationMaping::absDiff(m_ConstalationDiagram.m_aConstalationMapping[i],InputVal); //no need to test invariant
            if(diss < smallestDistance)
            {
                smallestDistance = diss;
                iReturnValue = i;
            }
        }
        return {iReturnValue,smallestDistance};

    }










    void printBinaray(uint8_t number)
    {
          char buffer [33];
            itoa (number,buffer,2);
            
    }


    std::error_code ModulationMaping::DemodulateBuffer(cmplx * pInputBuffer,uint32_t uiSizeOfInputBuffer, uint8_t * pOutbuffer,uint32_t uiSizeOfOutputBuffer )
    {
        



        static_assert(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 2 || MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 4 || MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 16,"Modulation mapping does not yet support support all constalation sizes, byte allignment");
        
        const uint8_t bitsPerOutput = sizeof (uint8_t) * 8;

        const uint8_t SymbolsPerOutput = (bitsPerOutput/ m_ConstalationDiagram.BitsPerSymbol) ;
        
        const uint32_t minSizeRequiredForOutBuff = uiSizeOfInputBuffer / SymbolsPerOutput;

        if(uiSizeOfOutputBuffer < minSizeRequiredForOutBuff)
        {
           
          return encoding_error::MODULATION_BUFFER_SMALL;
        }
        uint32_t outBuffTracker = 0;
        uint8_t outValue = 0;
        uint8_t ValuespackedInCurrentOutVal = 0;

        for(size_t i = 0 ; i < minSizeRequiredForOutBuff ; i++) //little strange as the symbolls are packed lsf
        {
            int8_t inputBufStart = ((i + 1) * SymbolsPerOutput) -1;
            int8_t inputBufEnd =  (i) * SymbolsPerOutput;
            

            
            uint8_t outValue = 0;
            while(inputBufStart >= inputBufEnd)
            {
                deModValueAndDistance val = DemodulateValue(pInputBuffer[inputBufStart]);
                outValue = outValue << m_ConstalationDiagram.BitsPerSymbol; // unnecesary shift on zero each time;
                outValue = outValue | val.val;
                inputBufStart--;
                
                printBinaray(outValue);
            }
            pOutbuffer[i] = outValue;
        }

                
        // for(size_t i = 0; i < uiSizeOfInputBuffer; i++)
        // {
          

        //   deModValueAndDistance val = DemodulateValue(pInputBuffer[i]);
        //   outValue = outValue << m_ConstalationDiagram.BitsPerSymbol; // unnecesary shift on zero each time;
        //   outValue = outValue | val.val;
        //   printBinaray(outValue);
        //   ++ValuespackedInCurrentOutVal;

        //   if(ValuespackedInCurrentOutVal == SymbolsPerOutput)
        //   {
        //       ValuespackedInCurrentOutVal = 0;
        //       pOutbuffer[outBuffTracker] = outValue;
        //       outBuffTracker++;
        //       outValue = 0;
        //   }



        // } 
        
 

        
        return encoding_error::OK;

        
        
    }

    valueAndError<cmplx> ModulationMaping::ModulateValue(uint8_t val)
    {
        
        
        //think return value optimasation will prevent coppies, not sure if it works with optimasations off -- will benchmark in future
        valueAndError<cmplx> returnValue;
        if(val > m_ConstalationDiagram.ConstalationMaxIndex)
        {
            returnValue.err = encoding_error::CONSTALATION_INVALID_INDEX;
            return returnValue;
            
        }
       
        returnValue.err = encoding_error::OK;
        returnValue.value = m_ConstalationDiagram.m_aConstalationMapping[val];
        return returnValue;
    }


}