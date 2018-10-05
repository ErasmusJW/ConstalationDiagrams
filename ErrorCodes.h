#ifndef RADIO_ERROR_CODES_H
#define RADIO_ERROR_CODES_H
// info on error codes http://blog.think-async.com/2010/04/system-error-support-in-c0x-part-4.html
#include <system_error>  


//proposed error codes regions
//No error 0
//No error but log 0-9 result
//Warning 10 - 19
//Errror 20 -29
enum class encoding_error
{
    OK = 0,
    CONSTALATION_INVALID_INDEX = 20,
    MODULATION_BUFFER_SMALL 

};

namespace std //std namespace is legal here don't worry
{
  template <>
  struct is_error_code_enum<encoding_error>
    : public true_type {};
}

class Radio_Catagory_impl
    : public std::error_category
{
    public:
    virtual const char* name() const noexcept { return "Radio Encoding";};
    virtual std::string message(int ev) const noexcept
    {
        switch (ev)
        {
            case static_cast<int>(encoding_error::OK):
                return "OK";
            case static_cast<int>( encoding_error::CONSTALATION_INVALID_INDEX):
                return "Tried to look up a constalation value with invalid index";
            case static_cast<int>( encoding_error::MODULATION_BUFFER_SMALL):
                return "Output buffer for modulation ConvertBuffer is to small";



            default:
                return "Unknown Radio error";
        }
    };

};

const std::error_category& Radio_Catagory();
std::error_condition make_error_condition(encoding_error e);
std::error_code make_error_code(encoding_error e);
    


#endif //RADIO_ERROR_CODES_H
