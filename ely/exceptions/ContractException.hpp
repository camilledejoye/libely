#ifndef CONTRACT_EXCEPTION_H
#define CONTRACT_EXCEPTION_H

#include <sstream>

#include "ely/exceptions/LogicException.hpp"

namespace ely
{
namespace exceptions
{


class ContractException : public LogicException
{
public:
    ContractException( char const * contract_type_, char const * condition_, char const * contract_, char const * filename_, int const line_number_ ) ELY_NOEXCEPT_OR_NOTHROW;
};


} // namespace ::ely::exceptions
} // namespace ::ely

#endif // CONTRACT_EXCEPTION_H
