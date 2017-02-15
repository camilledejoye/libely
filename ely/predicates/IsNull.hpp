#ifndef IS_NULL_H
#define IS_NULL_H

#include <memory>

#include "ely/config.hpp"
#include "ely/traits/Type.hpp"
#include "ely/traits/NullValue.hpp"

namespace ely
{
namespace predicates
{


template < typename T >
struct IsNull : public std::unary_function< T, bool >
{
    // TODO : utiliser type traits is_primitive pour savoir si passer par référence ou non
    // C++11 permet de faire la spécialisation dans les paramètres templates
    constexpr bool operator ()( typename traits::Type< const T >::Ref t ) const noexcept
    {
        typedef typename std::remove_reference< T >::type WithoutRefType;
        typedef typename std::remove_const< WithoutRefType >::type WithoutConstAndRefType;

        return traits::NullValue< WithoutConstAndRefType >::value() == t;
    }
};

template < typename T >
struct IsNull< std::weak_ptr< T > > : public std::unary_function< std::weak_ptr< T >, bool >
{
    constexpr bool operator ()( typename traits::Type< const std::weak_ptr< T > >::Ref t )
    {
        return t.expired();
    }
};


} // namespace ::ely::predicates


namespace utilities
{


template < typename T >
ELY_CONSTEXPR_OR_INLINE bool isNull( T && t )
{
    typedef typename std::remove_reference< T >::type WithoutRefType;
    typedef typename std::remove_const< WithoutRefType >::type WithoutConstAndRefType;

    return predicates::IsNull< WithoutConstAndRefType >() ( std::forward< T >( t ) );
}


} // namespace ::ely::utilities
} // namespace ::ely
#endif // IS_NULL_H
