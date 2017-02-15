#include <boost/test/unit_test.hpp>

#include <ely/utilities/log.hpp>

using ely::debug;

BOOST_AUTO_TEST_SUITE( ely_log )

BOOST_AUTO_TEST_CASE( global )
{
    ely::log << "To log\n";

    debug << "To debug\n";
}

BOOST_AUTO_TEST_SUITE_END()
