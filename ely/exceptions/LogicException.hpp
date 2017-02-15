#ifndef LOGIC_EXCEPTION_H
#define LOGIC_EXCEPTION_H

#include <stdexcept>
#include <string>

#include "ely/config.hpp"

namespace ely
{
namespace exceptions
{


/*!
 * \class LogicException
 *
 * \brief Base class for logics exceptions.
 *
 * Provide a basic implementation for logics exceptions and allows
 * derived objects to modify the message show to the user.
 */
class LogicException : public std::logic_error
{
public:
    friend std::ostream & operator <<( std::ostream & os, const LogicException & exception );


    LogicException( const std::string & message ) ELY_NOEXCEPT_OR_NOTHROW;
    virtual ~LogicException() ELY_NOEXCEPT_OR_NOTHROW;


    virtual const char * what() const ELY_NOEXCEPT_OR_NOTHROW;
    // TODO : do not use std::string
    // Try to use std::string in a catch ( std::bas_alloc & ) is risky
    virtual const std::string toString() const ELY_NOEXCEPT_OR_NOTHROW;
    virtual void print( std::ostream & os ) const ELY_NOEXCEPT_OR_NOTHROW;

protected:
    std::string myMessage;
};

/*!
 * \brief Stream operator
 *
 * Write an exception's message in to a stream.
 *
 * \param os           The stream to print in the message.
 * \param exception    The object to print.
 *
 * \return A reference to the stream \p os.
 */
inline std::ostream & operator <<( std::ostream & os, const LogicException & exception )
{
    exception.print( os );

    return os;
}

inline void LogicException::print( std::ostream & os ) const ELY_NOEXCEPT_OR_NOTHROW
{
    os << toString();
}

inline const char * LogicException::what() const ELY_NOEXCEPT_OR_NOTHROW
{
    return toString().c_str();
}

inline const std::string LogicException::toString() const ELY_NOEXCEPT_OR_NOTHROW
{
    return myMessage;
}

} // namespace ::ely::exceptionss
} // namespace ::ely

#endif // LOGIC_EXCEPTION_H
