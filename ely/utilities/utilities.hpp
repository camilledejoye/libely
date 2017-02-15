#ifndef UTILS_H
#define UTILS_H

#include "ely/config.hpp"


namespace ely
{
namespace utilities
{


template < template< typename ... > class Predicate, typename ... Args >
ELY_CONSTEXPR_OR_INLINE bool verify( Args && ... args )
{
    return Predicate<   typename std::remove_const<
                            typename std::remove_reference< Args >::type >::type ... >() ( std::forward< Args >( args ) ... );
}


} // namespace ::ely::utilities
} // namespace ::ely

#endif // UTILS_H
