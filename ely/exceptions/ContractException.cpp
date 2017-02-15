#include "ely/exceptions/ContractException.hpp"

namespace ely
{
namespace exceptions
{
ContractException::ContractException( char const * contract_type_, char const * condition_, char const * contract_, char const * filename_, const int line_number_ ) ELY_NOEXCEPT_OR_NOTHROW
    : LogicException( "a" )
{
    std::ostringstream oss;
    oss << "The following contract has been broken ( " << contract_type_ << " ) : " << contract_ << std::endl
        << "File : " << filename_ << std::endl
        << "Line : " << line_number_ << std::endl
        << "Condition : " << condition_;

    myMessage = oss.str();
}
} // namespace ::ely::exceptionss
} // namespace ::ely
