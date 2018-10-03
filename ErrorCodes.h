#ifndef RADIO_ERROR_CODES_H
#define RADIO_ERROR_CODES_H
// info on error codes http://blog.think-async.com/2010/04/system-error-support-in-c0x-part-4.html
#include <system_error>  


enum class encoding_error
{
    OK = 0,
    NOT_OK
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
            case static_cast<int>( encoding_error::NOT_OK):
                return "Not ok";

            default:
                return "Unknown Radio error";
        }
    };

};


    


#endif //RADIO_ERROR_CODES_H
