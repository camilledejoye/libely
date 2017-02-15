#include "ely/utilities/NoLogPolicy.hpp"


namespace ely
{
namespace utilities
{


NoLogPolicy::NullStreambuf::int_type NoLogPolicy::NullStreambuf::overflow( int_type character )
{
    return traits_type::not_eof( character );
}


NoLogPolicy::NoLogPolicy()
    : std::ostream(), nullStreambuf( new NullStreambuf )
{
    rdbuf( nullStreambuf.get() );
}


} // namespace ::ely::utilities
} // namespace ::ely
