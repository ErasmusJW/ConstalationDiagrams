#include"ModulationMaping.h"

namespace radio {

    ModulationMaping::ModulationMaping()
    {
    }

    ModulationMaping::~ModulationMaping()
    {
    }

    valueAndError<cmplx> ModulationMaping::getMappedValues(uint8_t val)
    {
        valueAndError<cmplx> returnValue;
        std::error_code ec;
        ec = encoding_error::NOT_OK;
        returnValue.err = ec;
        //returnValue.value = cmplx{2,1};
        return returnValue;
    }

}