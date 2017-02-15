/*!
 * \file AbstractFile.cpp
 *
 * \brief Tests program.
 *
 * \author Ely
 *
 * Test program for the AbstractFile class.
 */

#include <boost/test/unit_test.hpp>


#include <ely/file_system/AbstractFile.hpp>


using namespace ely::file_system;


BOOST_AUTO_TEST_SUITE( abstract_file )


BOOST_AUTO_TEST_CASE( constructors )
{
    // AbstractFile( const Path & ) with call of Path's default constructor
    AbstractFile currentDirectory;

    BOOST_CHECK_EQUAL( currentDirectory.getPath(), "." );
    BOOST_CHECK_EQUAL( currentDirectory.getAccessPath(), "." );
    BOOST_CHECK_EQUAL( currentDirectory.getName(), "." );


    // AbstractFile( const Path & ) convert the given string in a Path
    std::string stringPath( "/home/ely/my directory/my file.ext" );
    AbstractFile stringDirectory( stringPath );

    BOOST_CHECK_EQUAL( stringDirectory.getPath(), "/home/ely/my directory/my file.ext" );
    BOOST_CHECK_EQUAL( stringDirectory.getAccessPath(), "/home/ely/my directory" );
    BOOST_CHECK_EQUAL( stringDirectory.getName(), "my file.ext" );


    // AbstractFile( const Path & )
    AbstractFile pathDirectory { Path( stringPath ) };    // Use uniform initialization syntax to avoir C++ most vexing parse !

    BOOST_CHECK_EQUAL( pathDirectory.getPath(), "/home/ely/my directory/my file.ext" );
    BOOST_CHECK_EQUAL( pathDirectory.getAccessPath(), "/home/ely/my directory" );
    BOOST_CHECK_EQUAL( pathDirectory.getName(), "my file.ext" );
}


BOOST_AUTO_TEST_SUITE_END()
