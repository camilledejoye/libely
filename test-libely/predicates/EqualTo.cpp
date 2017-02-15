#include <boost/test/unit_test.hpp>

#include <ely/predicates/EqualTo.hpp>
#include <ely/utilities/utilities.hpp>

using ::std::unique_ptr;
using ::std::shared_ptr;
using ::std::weak_ptr;
using ::std::string;
using ::std::ostream;

using namespace ely::predicates;
using namespace ely::utilities;

BOOST_AUTO_TEST_SUITE( predicates )

class A
{
public:
    A( string const & a_ = "a" )
        : a( a_ )
    {}
    bool operator ==( A const & object_ ) const
    {
        return a == object_.a;
    }

    string toString() const
    {
        return a;
    }

private:
    string a;
};

ostream & operator <<( ostream & os, const A & a )
{
    os << a.toString();

    return os;
}

BOOST_AUTO_TEST_CASE( equal_to )
{
    A a;
    A b( "b" );
    A * aPtr = new A();
    A * bPtr = new A( "b" );
    unique_ptr< A > upa1( new A() );
    unique_ptr< A > upa2( new A( "b" ) );
    shared_ptr< A > spa1( aPtr );
    shared_ptr< A > spa2( bPtr );
    weak_ptr< A > wpa1( spa1 );
    weak_ptr< A > wpa2( spa2 );

    bool test = EqualTo< A, A >() ( a, a );

    BOOST_CHECK_EQUAL( test, true );
    BOOST_CHECK_EQUAL( EqualTo< A >() ( a, b ), false );

    test = EqualTo< A *, A * >() ( aPtr, aPtr );

    BOOST_CHECK_EQUAL( test, true );
    BOOST_CHECK_EQUAL( EqualTo< A * >() ( aPtr, bPtr ), false );

    BOOST_CHECK_EQUAL( EqualTo< A * >() ( aPtr, &a ), true );
    BOOST_CHECK_EQUAL( EqualTo< A * >() ( &b, aPtr ), false );

    BOOST_CHECK_EQUAL( EqualTo< unique_ptr< A > >() ( upa1, upa1 ), true );
    BOOST_CHECK_EQUAL( EqualTo< unique_ptr< A > >() ( upa1, upa2 ), false );

    BOOST_CHECK_EQUAL( EqualTo< shared_ptr< A > >() ( spa1, spa1 ), true );
    BOOST_CHECK_EQUAL( EqualTo< shared_ptr< A > >() ( spa1, spa2 ), false );

    BOOST_CHECK_EQUAL( EqualTo< weak_ptr< A > >() ( wpa1, wpa1 ), true );
    BOOST_CHECK_EQUAL( EqualTo< weak_ptr< A > >() ( wpa1, wpa2 ), false );

    BOOST_CHECK_EQUAL( verify< EqualTo >( wpa1, wpa1 ), true );
    BOOST_CHECK_EQUAL( verify< EqualTo >( wpa1, wpa2 ), false );
}

BOOST_AUTO_TEST_SUITE_END()
