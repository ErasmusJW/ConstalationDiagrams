#ifndef MODULATION_MAPPING_H
#define MODULATION_MAPPING_H
#include "ConstalationDiagrams/ConstalationDiagrams.h"
#include "ConstalationDiagrams/ErrorCodes.h"
#include "TempGlobals.h"


namespace radio
{
template <typename T> //move to globals or something
struct valueAndError
{
    T value;
    std::error_code err;
};

//currently only return a byte, thus will fail BitsPerSymbol > 8 
struct deModValueAndDistance
{
    const uint8_t val;
    float fDistance;
};

class ModulationMaping
{
  public:
    ModulationMaping();

    //sorry mate, not going to do a malloc for you
    template<typename T>
    std::error_code ModulateBuffer(T * pInputBuffer,uint32_t uiSizeOfInputBuffer, cmplx * pOutbuffer,uint32_t uiSizeOfOutputBuffer )
    {
        //pc.printf("\n\rModulateBuffer-------------entered \n\r");
        
        // use std::numeric limits maybe
        static_assert(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 2 || MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 4 || MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 16,"Modulation mapping does not yet support support all donstalation sizes, byte allignment");

        const uint8_t SymbolsPerIntput = (sizeof (T) * 8) / m_ConstalationDiagram.BitsPerSymbol ;

        //pc.printf("\t SymbolsPerIntput %i \n\r",SymbolsPerIntput);
        const uint32_t minSizeRequiredForAutupBuff = uiSizeOfInputBuffer * SymbolsPerIntput;
        //pc.printf("\t minSizeRequiredForAutupBuff %i \n\r",minSizeRequiredForAutupBuff);

        if(uiSizeOfOutputBuffer < minSizeRequiredForAutupBuff)
        {
          //pc.printf("ModulateBuffer-------------leave Error \n\r");
          return encoding_error::MODULATION_BUFFER_SMALL;
        }
        size_t outBufTracker = 0;  
        
        for(size_t i = 0; i < uiSizeOfInputBuffer; i++)
        {
          T copyOfVal = pInputBuffer[i];
          for (size_t j = 0; j < SymbolsPerIntput; j++)
          {
              uint8_t uiLookupVal = (copyOfVal >> (j * m_ConstalationDiagram.BitsPerSymbol)) & m_ConstalationDiagram.SetBitsMask ;
              valueAndError<cmplx>  Val = ModulateValue(uiLookupVal);
              if(Val.err !=  encoding_error::OK)
                return Val.err;
              pOutbuffer[outBufTracker] = Val.value;
              outBufTracker++;
              
          }
        }
         
        //pc.printf("ModulateBuffer-------------leave normal \n\r \n\r");
        return encoding_error::OK;
    }

    //notice outputbuffer lockert to uint8_t thus locking BitsPerSymbol <= 8 - check buffer constness
    std::error_code DemodulateBuffer(cmplx * pInputBuffer,uint32_t uiSizeOfInputBuffer, uint8_t * pOutbuffer,uint32_t uiSizeOfOutputBuffer );


    // implication of using a uint8_t is 256 id the highest number of points in constalation diagram
    valueAndError<cmplx> ModulateValue(uint8_t val);


    //Returns the smallest distance, always returns - loops
    deModValueAndDistance DemodulateValue(const cmplx &val) const;

    //ass far as I can tell distance between points
    static float absDiff(const cmplx &a,const cmplx &b)
    {
      return std::abs(b - a);
    }

    ModulationMaping(ModulationMaping &&) = default;
    ModulationMaping(const ModulationMaping &) = default;
    ModulationMaping &operator=(ModulationMaping &&) = default;
    ModulationMaping &operator=(const ModulationMaping &) = default;
    ~ModulationMaping();

  private:
    //Constalation Diagram specified in compile time macros
    ConstalationDiagram m_ConstalationDiagram;
};
} // namespace radio

#endif //MODULATION_MAPPING_H