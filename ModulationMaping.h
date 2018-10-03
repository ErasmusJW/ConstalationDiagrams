#ifndef MODULATION_MAPPING_H
#define MODULATION_MAPPING_H
#include "ConstalationDiagrams/ConstalationDiagrams.h"
#include "ConstalationDiagrams/ErrorCodes.h"

namespace radio
{
template <class T> //move to globals or something
struct valueAndError
{
    T value;
    std::error_code err;
};

class ModulationMaping
{
  public:
    ModulationMaping();

    valueAndError<cmplx> getMappedValues(uint8_t val);
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