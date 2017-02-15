/*!
 * \file FilePath.cpp
 *
 * \brief Tests program.
 *
 * \author Ely
 *
 * Test program for the AbstractFilePath and FilePath class.
 */

#include <boost/test/unit_test.hpp>

#include <string>
#include <sstream>

#include <ely/config.hpp>
#include <ely/file_system/FilePath.hpp>


using ::std::string;

using namespace ely::file_system;


struct FilePathFixture
{
    FilePathFixture()
        : unixFilePath( "/home/ely/my directory/" ),
        winFilePath( "D:\\home\\ely\\my directory\\" ),
        extension( "sh" ),
        filename( string( "my script" ) + "." + extension ),

    #if ! defined ( ELY_USING_WIN32_API )

        standardDirectoryFilePath( unixFilePath ),
        standardFilePath( standardDirectoryFilePath + filename ),
        systemDirectoryFilePath( standardDirectoryFilePath ),
        systemFilePath( standardFilePath ),

    #else

        standardDirectoryFilePath( string( "D:" ) + unixFilePath ),
        standardFilePath( standardDirectoryFilePath + filename ),
        systemDirectoryFilePath( winFilePath ),
        systemFilePath( systemDirectoryFilePath + filename ),

    #endif
        standardDirectoryFilePathWithoutLastSeparator( standardDirectoryFilePath, 0, standardDirectoryFilePath.size() - 1 ),
        systemDirectoryFilePathWithoutLastSeparator( systemFilePath, 0, systemFilePath.size() - 1 )
    {}

    const string unixFilePath;
    const string winFilePath;
    const string extension;
    const string filename;

    const string standardDirectoryFilePath;
    const string standardFilePath;

    const string systemDirectoryFilePath;
    const string systemFilePath;

    const string standardDirectoryFilePathWithoutLastSeparator;
    const string systemDirectoryFilePathWithoutLastSeparator;
};

BOOST_FIXTURE_TEST_SUITE( file_path, FilePathFixture )


BOOST_AUTO_TEST_CASE( constructors )
{
    // FilePath( const std::string & )
    FilePath stringFilePath( systemFilePath );

    BOOST_CHECK_EQUAL( stringFilePath.getAccessPath(), standardDirectoryFilePathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( stringFilePath.getName(), filename );
    BOOST_CHECK_EQUAL( stringFilePath.getExtension(), extension );

    FilePath withoutAccessPathFilePath( "test.ext" );

    BOOST_CHECK_EQUAL( withoutAccessPathFilePath.getAccessPath(), "." );
    BOOST_CHECK_EQUAL( withoutAccessPathFilePath.getName(), "test.ext" );
    BOOST_CHECK_EQUAL( withoutAccessPathFilePath.getExtension(), "ext" );

    FilePath withoutExtensionFilePath( "test" );

    BOOST_CHECK_EQUAL( withoutExtensionFilePath.getAccessPath(), "." );
    BOOST_CHECK_EQUAL( withoutExtensionFilePath.getName(), "test" );
    BOOST_CHECK_EQUAL( withoutExtensionFilePath.getExtension().empty(), true );

    // FilePath( const FilePath & )
    FilePath copyFilePath( stringFilePath );

    BOOST_CHECK_EQUAL( copyFilePath.getAccessPath(), standardDirectoryFilePathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( copyFilePath.getName(), filename );
    BOOST_CHECK_EQUAL( copyFilePath.getExtension(), extension );

    // FilePath( FilePath && )
    FilePath moveFilePath( std::move( stringFilePath ) );

    BOOST_CHECK_EQUAL( moveFilePath.getAccessPath(), standardDirectoryFilePathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( moveFilePath.getName(), filename );
    BOOST_CHECK_EQUAL( moveFilePath.getExtension(), extension );
}

BOOST_AUTO_TEST_CASE( assignment_operators )
{
    // FilePath & operator =( const std::string & )
    FilePath stringFilePath( "temp" );
    stringFilePath = systemFilePath;

    BOOST_CHECK_EQUAL( stringFilePath.getAccessPath(), standardDirectoryFilePathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( stringFilePath.getName(), filename );
    BOOST_CHECK_EQUAL( stringFilePath.getExtension(), extension );

    // FilePath & operator =( const FilePath & )
    FilePath copyFilePath( "temp" );
    copyFilePath = stringFilePath;

    BOOST_CHECK_EQUAL( copyFilePath.getAccessPath(), standardDirectoryFilePathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( copyFilePath.getName(), filename );
    BOOST_CHECK_EQUAL( copyFilePath.getExtension(), extension );

    // FilePath & operator =( FilePath && )
    FilePath moveFilePath( "temp" );
    moveFilePath = std::move( stringFilePath );

    BOOST_CHECK_EQUAL( moveFilePath.getAccessPath(), standardDirectoryFilePathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( moveFilePath.getName(), filename );
    BOOST_CHECK_EQUAL( moveFilePath.getExtension(), extension );
}

BOOST_AUTO_TEST_CASE( accessors )
{
    FilePath filePath( systemFilePath );

#if ! defined ( ELY_USING_WIN32_API )
    string newFilePath = "/new/path/";
#else
    string newFilePath = "F:\\new\\FilePath\\";
#endif
    string newName = "newName";
    string newExtension = "newExtension";

    filePath.setAccessPath( newFilePath );
    filePath.setName( newName );
    filePath.setExtension( newExtension );


    BOOST_CHECK_EQUAL( filePath.getAccessPath(), FilePath::stripLastSeparator( newFilePath ) );
    BOOST_CHECK_EQUAL( filePath.getName(), newName + "." + newExtension );
    BOOST_CHECK_EQUAL( filePath.getExtension(), newExtension );

    filePath.setExtension();
    BOOST_CHECK_EQUAL( filePath.getName(), newName );
    BOOST_CHECK_EQUAL( filePath.getExtension().empty(), true );

    filePath.setExtension( newExtension );
    BOOST_CHECK_EQUAL( filePath.getName(), newName + "." + newExtension );
    BOOST_CHECK_EQUAL( filePath.getExtension(), newExtension );
}

BOOST_AUTO_TEST_CASE( other_functions )
{
    FilePath filePath( systemFilePath );

    BOOST_CHECK_EQUAL( filePath.toString(), standardFilePath );
}

BOOST_AUTO_TEST_SUITE_END()
