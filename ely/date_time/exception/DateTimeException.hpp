#ifndef DATE_TIME_EXCEPTION_H
#define DATE_TIME_EXCEPTION_H

#include "ely/exception/LogicException.hpp"

namespace ely
{
namespace date
{
namespace exceptions
{


class DateTimeException : public ely::exceptions::LogicException
{
public:
    DateTimeException( std::string const & message_ = "La date est invalide." ) noexcept :
        LogicException( message_ ) {}
};


} // namespace ::ely::date::exceptions
} // namespace ::ely::date
} // namespace ::ely

#endif // DATE_TIME_EXCEPTION_H
