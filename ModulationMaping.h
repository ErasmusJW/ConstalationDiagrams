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

class ModulationMaping
{
  public:
    ModulationMaping();

    //sorry mate, not going to do a malloc for you
    template<typename T>
    std::error_code ConvertBuffer(T * pInputBuffer,uint32_t uiSizeOfInputBuffer, std::complex<float> * pOutbuffer,uint32_t uiSizeOfOutputBuffer )
    {
        // use std::numeric limits maybe
        static_assert(MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 2 || MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 4 || MBED_CONF_CONSTALATIONDIAGRAMS_NUMBEROFPOINTS == 16,"Modulation mapping does not yet support support all donstalation sizes, byte allignment");

        const uint8_t SymbolsPerIntput = sizeof (T) * 8 / m_ConstalationDiagram.BitsPerSymbol ;
        const uint32_t minSizeRequiredForAutupBuff = uiSizeOfInputBuffer * SymbolsPerIntput;

        if(uiSizeOfOutputBuffer < minSizeRequiredForAutupBuff)
          return encoding_error::MODULATION_BUFFER_SMALL;

        size_t outBufTracker = 0;  
        
        for(size_t i = 0; i < uiSizeOfInputBuffer; i++)
        {
          T copyOfVal = pInputBuffer[i];
          for (size_t j = 0; j < SymbolsPerIntput; j++)
          {
              T
              //bit shift nonsense here 
              pOutbuffer[outBufTracker] = getMappedValue[]
          }
        }
         
          

        int idebug = 0;
        
        return encoding_error::OK;
    }


    // implication of using a uint8_t is 256 id the highest number of points in constalation diagram
    valueAndError<cmplx> getMappedValue(uint8_t);



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