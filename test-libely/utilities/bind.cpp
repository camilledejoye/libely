/*!
 * \file bind.cpp
 *
 * \brief Tests program.
 *
 * \author Ely
 *
 * Test program for the bind function.
 */

#include <boost/test/unit_test.hpp>


#include <iostream>


#include "ely/utilities/bind.hpp"


bool greater( int a, int b ) {
    return a > b;
}

struct Struct
{
    Struct() {
        ::std::cout << "constructed" << ::std::endl;
    }
    Struct( const Struct & ) {
        ::std::cout << "copy constructed" << ::std::endl;
    }
    Struct( Struct && ) {
        ::std::cout << "move constructed" << ::std::endl;
    }

    void method( int ) const
    {
        ::std::cout << "Struct::method( int ) ; " << n << ::std::endl;
    }

    int n = 1;
};

BOOST_AUTO_TEST_SUITE( bind )


BOOST_AUTO_TEST_CASE( global )
{
    int n = 5;
    auto lessThanN = ::ely::utilities::bind( &greater,
                                             ::std::ref( n ) );
    // test with : Object &, Object *, Object {}
    Struct s;
    const Struct cs;
    Struct * ps = &s;

    s.method( 2 );

    auto t = ::ely::utilities::bind( &Struct::method, ps );
//    ::std::function< void( int ) > t = ::ely::utilities::bind( ::std::function< void( Struct &, int ) >{ &Struct::method }, cs );
//    auto t = bindMacro( &Struct::method, cs );
    s.n = 8;
//    auto t = ::std::bind( &Struct::method,
//                          ::std::ref( cs ), ::std::placeholders::_1 );
    t( 5 );

    ::std::cout << ::std::boolalpha <<
    lessThanN( 2 ) << ::std::endl;                // Print : true

    n = 1;
    ::std::cout << lessThanN( 2 ) << ::std::endl; // Print : false
}


BOOST_AUTO_TEST_SUITE_END()
