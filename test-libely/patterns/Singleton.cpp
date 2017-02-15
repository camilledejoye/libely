#include <boost/test/unit_test.hpp>

#include <string>

#include <ely/patterns/Singleton.hpp>


BOOST_AUTO_TEST_SUITE( patterns )

class S : public ely::patterns::Singleton< S >
{
    friend class ely::patterns::Singleton< S >;

public:
    static int getCounter() {
        return myCounter;
    }

    std::string getS() {
        return myString;
    }
    void setS( std::string const & s_ ) {
        myString = s_;
    }


protected:
    S() : myString( "test" ) {
        ++myCounter;
    }

private:
    static int myCounter;
    std::string myString;
};
int S::myCounter = 0;

BOOST_AUTO_TEST_CASE( singleton )
{
    BOOST_CHECK_EQUAL( S::getInstance().getS(), "test" );

    S::getInstance().setS( "blabla" );

    BOOST_CHECK_EQUAL( S::getInstance().getS(), "blabla" );
    BOOST_CHECK_EQUAL( &S::getInstance(), &S::getInstance() );
    BOOST_CHECK_EQUAL( &S::getInstance() != nullptr, true );
    BOOST_CHECK_EQUAL( S::getCounter(), 1 );

    S * oldAddress = &S::getInstance();
    S::getInstance().destroy();
    BOOST_CHECK_EQUAL( oldAddress, &S::getInstance() ); // Because the unique_ptr is the same
    BOOST_CHECK_EQUAL( S::getInstance().getS(), "test" );
    BOOST_CHECK_EQUAL( S::getCounter(), 2 );
}

BOOST_AUTO_TEST_SUITE_END()
