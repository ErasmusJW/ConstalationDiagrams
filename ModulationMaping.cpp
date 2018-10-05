#include"ModulationMaping.h"

namespace radio {

    ModulationMaping::ModulationMaping()
    {
    }

    ModulationMaping::~ModulationMaping()
    {
    }

    
   
    valueAndError<cmplx> ModulationMaping::getMappedValue(uint8_t val)
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