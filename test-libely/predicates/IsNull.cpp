#include <boost/test/unit_test.hpp>

#include <string>

#include <ely/predicates/IsNull.hpp>
#include <ely/utilities/utilities.hpp>

using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using ely::predicates::IsNull;
using ely::utilities::isNull;
using ely::utilities::verify;

BOOST_AUTO_TEST_SUITE( predicates )

class A
{
public:
    A( string const & attribute = "attribute" )
        : myAttribute( attribute )
    {}
    bool operator ==( A const & a ) const
    {
        return myAttribute == a.myAttribute;
    }

private:
    string myAttribute;
};

BOOST_AUTO_TEST_CASE( is_null )
{
    BOOST_CHECK_EQUAL( IsNull< A >() ( A( "isNull" ) ), false );
    BOOST_CHECK_EQUAL( IsNull< A >() ( A() ), true );
    BOOST_CHECK_EQUAL( IsNull< int >() ( 1 ), false );
    BOOST_CHECK_EQUAL( IsNull< int >() ( 0 ), true );
    BOOST_CHECK_EQUAL( IsNull< float >() ( 18.54 ), false );
    BOOST_CHECK_EQUAL( IsNull< float >() ( 0.00 ), true );
    BOOST_CHECK_EQUAL( IsNull< double >() ( 1.12854 ), false );
    BOOST_CHECK_EQUAL( IsNull< double >() ( 0.00000 ), true );
    BOOST_CHECK_EQUAL( IsNull< char * >() ( const_cast< char * >( "rsdqqfsd" ) ), false );
    BOOST_CHECK_EQUAL( IsNull< char * >() ( const_cast< char * >( "" ) ), true );
    BOOST_CHECK_EQUAL( IsNull< string >() ( "rsdfdsf" ), false );
    BOOST_CHECK_EQUAL( IsNull< string >() ( "" ), true );

    A * aPtr = new A();
    BOOST_CHECK_EQUAL( IsNull< A * >() ( aPtr ), false );
    delete aPtr; aPtr = ELY_NULLPTR;
    BOOST_CHECK_EQUAL( IsNull< A * >() ( aPtr ), true );

    unique_ptr< A > upa( new A() );
    BOOST_CHECK_EQUAL( IsNull< unique_ptr< A > >() ( upa ), false );
    upa.reset( ELY_NULLPTR );
    BOOST_CHECK_EQUAL( IsNull< unique_ptr< A > >() ( upa ), true );

    shared_ptr< A > sp;
    BOOST_CHECK_EQUAL( IsNull< shared_ptr< A > >() ( sp ), true );
    sp.reset( new A() );
    BOOST_CHECK_EQUAL( IsNull< shared_ptr< A > >() ( sp ), false );

    weak_ptr< A > wp;
    BOOST_CHECK_EQUAL( IsNull< weak_ptr< A > >() ( wp ), true );
    weak_ptr< A > wp2( sp );
    BOOST_CHECK_EQUAL( IsNull< weak_ptr< A > >() ( wp2 ), false );

    weak_ptr< A > wp3;
    weak_ptr< A > & rwp = wp3;
    const weak_ptr< A > cwp;
    const weak_ptr< A > & crwp = wp3;

    BOOST_CHECK_EQUAL( IsNull< weak_ptr< A > >() ( wp3 ), true );
    BOOST_CHECK_EQUAL( IsNull< weak_ptr< A > >() ( rwp ), true );
    BOOST_CHECK_EQUAL( IsNull< weak_ptr< A > >() ( cwp ), true );
    BOOST_CHECK_EQUAL( IsNull< weak_ptr< A > >() ( crwp ), true );

    BOOST_CHECK_EQUAL( isNull( wp3 ), true );
    BOOST_CHECK_EQUAL( isNull( rwp ), true );
    BOOST_CHECK_EQUAL( isNull( cwp ), true );
    BOOST_CHECK_EQUAL( isNull( crwp ), true );

    BOOST_CHECK_EQUAL( verify< IsNull >( wp3 ), true );
    BOOST_CHECK_EQUAL( verify< IsNull >( rwp ), true );
    BOOST_CHECK_EQUAL( verify< IsNull >( cwp ), true );
    BOOST_CHECK_EQUAL( verify< IsNull >( crwp ), true );
}

BOOST_AUTO_TEST_SUITE_END()
