#ifndef DATE_EXCEPTION_H
#define DATE_EXCEPTION_H

#include "DateTimeException.hpp"

namespace ely
{
namespace date
{
namespace exceptions
{


class DateException : public DateTimeException
{
public:
    DateException( std::string const & message_ = "La date est invalide." ) noexcept :
        DateTimeException( message_ ) {}
};


} // namespace ::ely::date::exceptions
} // namespace ::ely::date
} // namespace ::ely

#endif // DATE_EXCEPTION_H
