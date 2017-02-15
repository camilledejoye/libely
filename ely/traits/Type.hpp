#ifndef TYPE_H
#define TYPE_H

namespace ely
{
namespace traits
{


template < typename T >
struct Type
{
    typedef T Base;
    typedef T   &   Ref;
    typedef T   &&  Rval;
    typedef T   *   Ptr;
};

template < typename T >
struct Type< T & >
{
    typedef T Base;
    typedef T   &   Ref;
    typedef T   &&  Rval;
    typedef T   *   Ptr;
};

template < typename T >
struct Type< T && >
{
    typedef T Base;
    typedef T   &   Ref;
    typedef T   &&  Rval;
    typedef T   *   Ptr;
};

template < typename T >
struct Type< T * >
{
    typedef T Base;
    typedef T   &   Ref;
    typedef T   &&  Rval;
    typedef T   *   Ptr;
};


} // namespace ::ely::traits
} // namespace ::ely

#endif // TYPE_H
