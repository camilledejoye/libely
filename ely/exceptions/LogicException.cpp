#include "ely/exceptions/LogicException.hpp"

using namespace ely::exceptions;

LogicException::LogicException( const std::string & message ) ELY_NOEXCEPT_OR_NOTHROW
    : std::logic_error( "" ),
    myMessage( message )
{}

LogicException::~LogicException() ELY_NOEXCEPT_OR_NOTHROW
{}
