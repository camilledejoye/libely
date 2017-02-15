#include "ely/utilities/DebugLogPolicy.hpp"


#include <iostream>


namespace ely
{
namespace utilities
{


DebugLogPolicy::DebugLogPolicy()
    : std::ostream( std::clog.rdbuf() )
{}


} // namespace ::ely::utilities
} // namespace ::ely
