#ifndef EQUAL_TO_H
#define EQUAL_TO_H

#include <memory>

#include "ely/config.hpp"
#include "ely/traits/Type.hpp"
#include "ely/predicates/IsNull.hpp"

namespace ely
{
namespace predicates
{


template < typename T, typename U = T >
struct EqualTo : public std::binary_function< T, U, bool >
{
    ELY_CONSTEXPR_OR_INLINE bool operator ()( typename traits::Type< const T >::Ref first,
                                              typename traits::Type< const U >::Ref second ) const
    {
        return first == second;
    }
};

template < typename T, typename U >
struct EqualTo< T *, U * > : public std::binary_function< T *, U *, bool >
{
    ELY_CONSTEXPR_OR_INLINE bool operator ()( typename traits::Type< const T >::Ptr first,
                                              typename traits::Type< const U >::Ptr second ) const
    {
        return ( utilities::isNull( first ) || utilities::isNull( second ) ) ? false : EqualTo< T, U >() ( *first, *second );
    }
};

template < typename T, typename U >
struct EqualTo< std::unique_ptr< T >, std::unique_ptr< U > > : public std::binary_function< std::unique_ptr< T >, std::unique_ptr< U >, bool >
{
    ELY_CONSTEXPR_OR_INLINE bool operator ()( typename traits::Type< const std::unique_ptr< T > >::Ref first,
                                              typename traits::Type< const std::unique_ptr< U > >::Ref second ) const
    {
        return EqualTo< T *, U * >() ( first.get(), second.get() );
    }
};

template < typename T, typename U >
struct EqualTo< std::weak_ptr< T >, std::weak_ptr< U > > : public std::binary_function< std::weak_ptr< T >, std::weak_ptr< U >, bool >
{
    ELY_CONSTEXPR_OR_INLINE bool operator ()( typename traits::Type< const std::weak_ptr< T > >::Ref first,
                                              typename traits::Type< const std::weak_ptr< U > >::Ref second ) const
    {
        return EqualTo< std::shared_ptr< T >, std::shared_ptr< U > >() ( first.lock(), second.lock() );
    }
};

template < typename T, typename U >
struct EqualTo< std::shared_ptr< T >, std::shared_ptr< U > > : public std::binary_function< std::shared_ptr< T >, std::shared_ptr< U >, bool >
{
    ELY_CONSTEXPR_OR_INLINE bool operator ()( typename traits::Type< const std::shared_ptr< T > >::Ref first,
                                              typename traits::Type< const std::shared_ptr< U > >::Ref second ) const
    {
        return EqualTo< T *, U * >() ( first.get(), second.get() );
    }
};


} // namespace ::ely::predicates
} // namespace ::ely

#endif // EQUAL_TO_H
