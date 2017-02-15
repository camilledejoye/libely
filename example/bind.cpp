/*!
 * \file bind.cpp
 *
 * \author Ely
 *
 * \brief Example file for the bind function.
 *
 * Show how to use the function \c bind .
 */
#include <iostream>

#include "ely/utilities/bind.hpp"


using ::ely::utilities::bind;


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

    void constMethod( int ) const
    {
        ::std::cout << "Struct::constMethod( int ) : " << n << ::std::endl;
    }
    void nonConstMethod( int, char )
    {
        ::std::cout << "Struct::nonConstMethod( int, char ) : " << n << ::std::endl;
    }

    int n = 1;
};


int main()
{
    Struct s; // Print : constructed
    Struct * ps = &s;
    const Struct * cps = &s;

    // Need to call bind as ::bind, because if we use a type of std namespace
    // ::std::bind could still be find by argument dependent lookup.

    auto f_10 = ::bind( &Struct::nonConstMethod, s ); // ::std::bind call copy constructor
                                                      // Print : copy constructed
    auto f_11 = ::bind( &Struct::nonConstMethod, ::std::ref( s ) );
    /* auto f_12 = */ ::bind( &Struct::nonConstMethod, ::std::cref( s ) ); // Works but call it will fail
    auto f_13 = ::bind( &Struct::nonConstMethod, ps );
    /* auto f_14 = */ ::bind( &Struct::nonConstMethod, cps ); // Works but call it will fail
    auto f_15 = ::bind( &Struct::nonConstMethod, Struct {} ); // ::std::bind call move constructor
                                                              // Print : constructed
                                                              // Print : move constructed

    auto f_20 = ::bind( &Struct::constMethod, s ); // ::std::bind call copy constructor
                                                   // Print : copy constructed
    auto f_21 = ::bind( &Struct::constMethod, ::std::ref( s ) );
    auto f_22 = ::bind( &Struct::constMethod, ::std::cref( s ) );
    auto f_23 = ::bind( &Struct::constMethod, ps );
    auto f_24 = ::bind( &Struct::constMethod, cps );
    auto f_25 = ::bind( &Struct::constMethod, Struct {} ); // ::std::bind call move constructor
                                                           // Print : constructed
                                                           // Print : move constructed

    s.n = 8;

    f_10( 0, 0 ); // Print : 1
    f_11( 0, 0 ); // Print : 8
//    f_12( 0, 0 ); // Can't call a non-const function from a const instance
    f_13( 0, 0 ); // Print : 8
//    f_14( 0, 0 ); // Can't call a non-const function from a const instance
    f_15( 0, 0 ); // Print : 1

    f_20( 0 ); // Print : 1
    f_21( 0 ); // Print : 8
    f_22( 0 ); // Print : 8
    f_23( 0 ); // Print : 8
    f_24( 0 ); // Print : 8
    f_25( 0 ); // Print : 1

    int n = 5;
    auto lessThan = ::bind( &greater, ::std::ref( n ) );

    ::std::cout << ::std::boolalpha <<
    lessThan( 2 ) << ::std::endl;                // Print : true

    n = 1;
    ::std::cout << lessThan( 2 ) << ::std::endl; // Print : false

    return 0;
}
