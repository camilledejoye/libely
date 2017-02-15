/*!
 * \file IntegerSequence.cpp
 *
 * \brief Tests program.
 *
 * \author Ely
 *
 * Test program for the IntegerSequence struct.
 */

#include <boost/test/unit_test.hpp>


#include <sstream>


#include <ely/utilities/IntegerSequence.hpp>


using namespace ely::utilities;


template < ::std::size_t ... Indices >
void printIntegerSequence( ::std::ostream & os, IntegerSequence< Indices ... > )
{
    [] (...) {} ( ( ( ( os << Indices ), 0 ) ) ...);
}

template < typename ... Args >
void makeIntegerSequenceForVariadic( ::std::ostream & os )
{
    printIntegerSequence( os, makeIntegerSequenceFor< Args ... >{} );
}

BOOST_AUTO_TEST_SUITE( integer_sequence )

BOOST_AUTO_TEST_CASE( global )
{
    ::std::stringstream ss;

// TODO : corriger car bug, faut remplacer
// : MakeIntegerSequence< From + 1, Count - 1, From, Indices ... > // Concat From and Indices ...
// par
// : MakeIntegerSequence< From + 1, Count - 1, Count - 1, Indices ... > // Concat From and Indices ...
// Afficher à l'envers mais c'est ce que l'on veux... je crois :
/*
   // Example program
   #include <iostream>
   #include <string>
   #include <tuple>
   #include <cstddef>


   namespace utilities
   {


   /// A sequence of integer values.
   template < ::std::size_t ... Indices >
   struct IntegerSequence
   {
    /// The type of each indice.
    typedef ::std::size_t Type;

   /*!
 * \brief Returns the number of elements in \c Indicies.
 *
 * \return The number of element in \c Indices.
 *//*
    static constexpr Type size()
    {
        return sizeof ... ( Indices );
    }
   };

   namespace detail
   {


   template < ::std::size_t From,
           ::std::size_t Count,
           ::std::size_t ... Indices >
   /// Make a sequence of integer from \c From to <em>From + Count - 1</em>.
   struct MakeIntegerSequence
    : MakeIntegerSequence< From + 1, Count - 1, Count - 1, Indices ... > // Concat From and Indices ...
   {};
   template < ::std::size_t From,
           ::std::size_t ... Indices >
   struct MakeIntegerSequence< From, 0, Indices ... >
    : IntegerSequence< Indices ... >
   {};


   } // namespace ::utilities::detail


   template < ::std::size_t From, ::std::size_t Count >
   /// Helper to make a sequence of integer from \c From to <em>From + Count - 1</em>.
   using makeIntegerSequence = detail::MakeIntegerSequence< From, Count >;

   template < ::std::size_t N >
   /// Helper to make a sequence of integer from \c 0 to \c N .
   using makeIntegerSequenceTo = makeIntegerSequence< 0, N >;

   template < typename ... Args >
   /// Helper to make a sequence of integer from \c 0 to <em>sizeof...( Args )</em>.
   using makeIntegerSequenceFor = makeIntegerSequence< 0, sizeof ... ( Args ) >;



   } // namespace ::utilities


   void sum( int a, int b )
   {
    ::std::cout << ( a - b ) << '\n';
   }

   template < typename Tuple, ::std::size_t ... Indices >
   void foo_detail( Tuple & tuple, ::utilities::IntegerSequence< Indices ... >)
   {
    sum( ::std::get< Indices >( tuple ) ... );
   }

   template < typename ... Args >
   void foo( const Args & ... args )
   {
    ::std::tuple< const Args & ... > tuple_args( args ... );
    sum( ::std::get< 0 >( tuple_args ), ::std::get< 1 >( tuple_args ) );
    foo_detail( tuple_args, ::utilities::makeIntegerSequenceTo< sizeof ... ( Args ) >{} );
   }

   template < ::std::size_t ... Indices >
   void print( ::utilities::IntegerSequence< Indices ... > )
   {
    [] (...) {} ( ( ( ( ::std::cout << Indices ), 0 ) ) ...);
   }

   int main()
   {
    foo( 2, 3 );
    ::std::cout << "test\n";

    print( ::utilities::makeIntegerSequence< 0, 6 >{} );
    ::std::cout << '\n';
    print( ::utilities::makeIntegerSequenceTo< 6 >{} );
   }

   //*/

    printIntegerSequence( ss, makeIntegerSequenceTo< 5 >{} );
    BOOST_CHECK_EQUAL( ss.str(), "01234" );

    ss.str( "" );
    printIntegerSequence( ss, makeIntegerSequence< 2, 0 >{} );
    BOOST_CHECK_EQUAL( ss.str().empty(), true );

    ss.str( "" );
    printIntegerSequence( ss, makeIntegerSequence< 2, 1 >{} );
    BOOST_CHECK_EQUAL( ss.str(), "2" );

    ss.str( "" );
    printIntegerSequence( ss, makeIntegerSequence< 2, 4 >{} );
    BOOST_CHECK_EQUAL( ss.str(), "2345" );

    ss.str( "" );
    makeIntegerSequenceForVariadic< int, int, int >( ss );
    BOOST_CHECK_EQUAL( ss.str(), "012" );
}

BOOST_AUTO_TEST_SUITE_END()
