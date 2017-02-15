#ifndef INVALID_MONTH_EXCEPTION_H
#define INVALID_MONTH_EXCEPTION_H

#include "DateException.hpp"

namespace ely
{
namespace date
{
namespace exceptions
{


class InvalidMonthException : public DateException
{
public:
    InvalidMonthException() noexcept :
        DateException( "Le mois est invalide." ) {}
};


} // namespace ::ely::date::exceptions
} // namespace ::ely::date
} // namespace ::ely

#endif // INVALID_MONTH_EXCEPTION_H
