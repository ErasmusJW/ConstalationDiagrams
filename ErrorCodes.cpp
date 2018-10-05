#include "ConstalationDiagrams/ErrorCodes.h"


const std::error_category& Radio_Catagory()
{
  static Radio_Catagory_impl instance;
  return instance;
}

std::error_condition make_error_condition(encoding_error e)
{
  return std::error_condition(
      static_cast<int>(e),
      Radio_Catagory());
}

std::error_code make_error_code(encoding_error e)
{
  return std::error_code(
      static_cast<int>(e),
      Radio_Catagory());
}
