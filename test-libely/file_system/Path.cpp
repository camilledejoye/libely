/*!
 * \file Path.cpp
 *
 * \brief Tests program.
 *
 * \author Ely
 *
 * Test program for the Path class.
 */

#include <boost/test/unit_test.hpp>

#include <string>
#include <sstream>

#include <ely/config.hpp>
#include <ely/file_system/Path.hpp>


using ::std::string;
using ::std::stringstream;

using namespace ely::file_system;


struct PathFixture
{
    PathFixture()
        : unixPath( "/home/ely/my directory/" ),
        winPath( "D:\\home\\ely\\my directory\\" ),
        pathName( "my script.sh" ),

    #if ! defined ( ELY_USING_WIN32_API )

        standardDirectoryPath( unixPath ),
        standardFilePath( standardDirectoryPath + pathName ),
        systemDirectoryPath( standardDirectoryPath ),
        systemFilePath( standardFilePath ),

    #else

        standardDirectoryPath( string( "D:" ) + unixPath ),
        standardFilePath( standardDirectoryPath + pathName ),
        systemDirectoryPath( winPath ),
        systemFilePath( systemDirectoryPath + pathName ),

    #endif
        standardDirectoryPathWithoutLastSeparator( standardDirectoryPath, 0, standardDirectoryPath.size() - 1 ),
        systemDirectoryPathWithoutLastSeparator( systemDirectoryPath, 0, systemDirectoryPath.size() - 1 )
    {}

    const string unixPath;
    const string winPath;
    const string pathName;

    const string standardDirectoryPath;
    const string standardFilePath;

    const string systemDirectoryPath;
    const string systemFilePath;

    const string standardDirectoryPathWithoutLastSeparator;
    const string systemDirectoryPathWithoutLastSeparator;
};

BOOST_FIXTURE_TEST_SUITE( path, PathFixture )

BOOST_AUTO_TEST_CASE( static_functions )
{
    // fromSystemSeparator
    // With const parameter
    string newPathString = Path::toStandardSeparator( systemFilePath );

    BOOST_CHECK_EQUAL( systemFilePath, systemFilePath );
    BOOST_CHECK_EQUAL( newPathString, standardFilePath );
        #if defined ( ELY_USING_WIN32_API )
    BOOST_CHECK_NE( newPathString, systemFilePath );
        #endif

    // With non-const parameter
    string nonConstPathString = systemFilePath;
    newPathString = Path::toStandardSeparator( nonConstPathString );

    BOOST_CHECK_EQUAL( newPathString, nonConstPathString );
    BOOST_CHECK_EQUAL( nonConstPathString, standardFilePath );
        #if defined ( ELY_USING_WIN32_API )
    BOOST_CHECK_NE( nonConstPathString, systemFilePath );
        #endif


    // toSystemSeparator
    // With const parameter
    newPathString = Path::toSystemSeparator( standardFilePath );

    BOOST_CHECK_EQUAL( standardFilePath, standardFilePath );
    BOOST_CHECK_EQUAL( newPathString, systemFilePath );
        #if defined ( ELY_USING_WIN32_API )
    BOOST_CHECK_NE( newPathString, standardFilePath );
        #endif

    // With non-const parameter
    nonConstPathString = standardFilePath;
    newPathString = Path::toSystemSeparator( nonConstPathString );

    BOOST_CHECK_EQUAL( newPathString, nonConstPathString );
    BOOST_CHECK_EQUAL( nonConstPathString, systemFilePath );
        #if defined ( ELY_USING_WIN32_API )
    BOOST_CHECK_NE( nonConstPathString, standardFilePath );
        #endif



    // dirName
    BOOST_CHECK_EQUAL( Path::dirName( "" ), "" );
    BOOST_CHECK_EQUAL( Path::dirName( "/" ), "/" );
    BOOST_CHECK_EQUAL( Path::dirName( "." ), "." );
    BOOST_CHECK_EQUAL( Path::dirName( "./" ), "." );
    BOOST_CHECK_EQUAL( Path::dirName( "file.sh" ), "." );
    BOOST_CHECK_EQUAL( Path::dirName( "/file.sh" ), "/" );
    BOOST_CHECK_EQUAL( Path::dirName( "./file.sh" ), "." );
    BOOST_CHECK_EQUAL( Path::dirName( "/home/ely/file.sh" ), "/home/ely" );
    BOOST_CHECK_EQUAL( Path::dirName( "/home/ely/" ), "/home" );
    BOOST_CHECK_EQUAL( Path::dirName( "/home/ely" ), "/home" );
#if defined ( ELY_USING_WIN32_API )
    BOOST_CHECK_EQUAL( Path::dirName( "C:\\uses\\ely\\" ), "C:/uses" );
    BOOST_CHECK_EQUAL( Path::dirName( "C:\\uses\\ely" ), "C:/uses" );
#endif


    // baseName
    BOOST_CHECK_EQUAL( Path::baseName( "" ), "" );
    BOOST_CHECK_EQUAL( Path::baseName( "/" ), "/" );
    BOOST_CHECK_EQUAL( Path::baseName( "." ), "." );
    BOOST_CHECK_EQUAL( Path::baseName( "./" ), "." );
    BOOST_CHECK_EQUAL( Path::baseName( "file.sh" ), "file.sh" );
    BOOST_CHECK_EQUAL( Path::baseName( "file.sh", ".sh" ), "file" );
    BOOST_CHECK_EQUAL( Path::baseName( "/file.sh" ), "file.sh" );
    BOOST_CHECK_EQUAL( Path::baseName( "./file.sh" ), "file.sh" );
    BOOST_CHECK_EQUAL( Path::baseName( "/home/ely/file.sh" ), "file.sh" );
    BOOST_CHECK_EQUAL( Path::baseName( "/home/ely/directory/" ), "directory" );
    BOOST_CHECK_EQUAL( Path::baseName( "/home/ely/directory" ), "directory" );
#if defined ( ELY_USING_WIN32_API )
    BOOST_CHECK_EQUAL( Path::baseName( "C:\\uses\\ely\\file.bat" ), "file.bat" );
#endif

    // stripLastSeparator
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "" ), "" );
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "/" ), "/" );
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "." ), "." );
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "./" ), "." );
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "file.sh" ), "file.sh" );
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "/file.sh" ), "/file.sh" );
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "/home/ely/directory/" ), "/home/ely/directory" );
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "/home/ely/directory" ), "/home/ely/directory" );
#if defined ( ELY_USING_WIN32_API )
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "C:\\uses\\ely\\" ), "C:/uses/ely" );
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( "C:\\uses\\ely" ), "C:/uses/ely" );
#endif

    // With const parameter
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( systemDirectoryPath ),  standardDirectoryPathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( systemDirectoryPath, systemDirectoryPath );

    // With non-const parameter
    nonConstPathString = systemDirectoryPath;
    BOOST_CHECK_EQUAL( Path::stripLastSeparator( nonConstPathString ),  standardDirectoryPathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( nonConstPathString, standardDirectoryPathWithoutLastSeparator );
}

BOOST_AUTO_TEST_CASE( constructors )
{
    // Path()
    Path emptyPath;

    BOOST_CHECK_EQUAL( emptyPath.getAccessPath(), "." );
    BOOST_CHECK_EQUAL( emptyPath.getName(), "." );

    // TODO : isRoot ? for windows : E:
    Path rootPath( "/" );

    BOOST_CHECK_EQUAL( rootPath.getAccessPath(), "/" );
    BOOST_CHECK_EQUAL( rootPath.getName(), "/" );

    Path currentPath( "." );

    BOOST_CHECK_EQUAL( currentPath.getAccessPath(), "." );
    BOOST_CHECK_EQUAL( currentPath.getName(), "." );

    Path parentPath( ".." );

    BOOST_CHECK_EQUAL( parentPath.getAccessPath(), ".." );
    BOOST_CHECK_EQUAL( parentPath.getName(), ".." );

    // Path( const std::string & )
    Path stringPath( systemFilePath );

    BOOST_CHECK_EQUAL( stringPath.getAccessPath(), standardDirectoryPathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( stringPath.getName(), pathName );

    Path directoryPath( systemDirectoryPath );

    BOOST_CHECK_EQUAL( directoryPath.getAccessPath(), Path::dirName( standardDirectoryPathWithoutLastSeparator ) );
    BOOST_CHECK_EQUAL( directoryPath.getName(), Path::baseName( systemDirectoryPath ) );

    Path directoryWithoutLastSeparatorPath( systemDirectoryPathWithoutLastSeparator );

    BOOST_CHECK_EQUAL( directoryWithoutLastSeparatorPath.getAccessPath(), Path::dirName( standardDirectoryPathWithoutLastSeparator ) );
    BOOST_CHECK_EQUAL( directoryWithoutLastSeparatorPath.getName(), Path::baseName( systemDirectoryPathWithoutLastSeparator ) );

    // Path( const Path & )
    Path copyPath( stringPath );

    BOOST_CHECK_EQUAL( copyPath.getAccessPath(), standardDirectoryPathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( copyPath.getName(), pathName );

    // Path( Path && )
    Path movePath( std::move( stringPath ) );

    BOOST_CHECK_EQUAL( movePath.getAccessPath(), standardDirectoryPathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( movePath.getName(), pathName );
}

BOOST_AUTO_TEST_CASE( assignment_operators )
{
    // Path & operator =( const std::string & )
    Path stringPath;
    stringPath = systemFilePath;

    BOOST_CHECK_EQUAL( stringPath.getAccessPath(), standardDirectoryPathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( stringPath.getName(), pathName );

    Path directoryPath;
    directoryPath = systemDirectoryPath;

    BOOST_CHECK_EQUAL( directoryPath.getAccessPath(), Path::dirName( standardDirectoryPathWithoutLastSeparator ) );
    BOOST_CHECK_EQUAL( directoryPath.getName(), Path::baseName( systemDirectoryPath ) );

    Path directoryWithoutLastSeparatorPath;
    directoryWithoutLastSeparatorPath = systemDirectoryPathWithoutLastSeparator;

    BOOST_CHECK_EQUAL( directoryWithoutLastSeparatorPath.getAccessPath(), Path::dirName( standardDirectoryPathWithoutLastSeparator ) );
    BOOST_CHECK_EQUAL( directoryWithoutLastSeparatorPath.getName(), Path::baseName( systemDirectoryPathWithoutLastSeparator ) );

    // Path & operator =( const Path & )
    Path copyPath;
    copyPath = stringPath;

    BOOST_CHECK_EQUAL( copyPath.getAccessPath(), standardDirectoryPathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( copyPath.getName(), pathName );

    // Path & operator =( Path && )
    Path movePath;
    movePath = std::move( stringPath );

    BOOST_CHECK_EQUAL( movePath.getAccessPath(), standardDirectoryPathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( movePath.getName(), pathName );
}

BOOST_AUTO_TEST_CASE( accessors )
{
    Path path( systemFilePath );

#if ! defined ( ELY_USING_WIN32_API )
    string const newPath = "/new/path/";
#else
    string newPath = "F:\\new\\Path\\";
#endif
    string const newName = "newName/";

    path.set( newPath +
              newName );

    BOOST_CHECK_EQUAL( path.getAccessPath(), Path::stripLastSeparator( newPath ) );
    BOOST_CHECK_EQUAL( path.getName(), Path::stripLastSeparator( newName ) );

    path.set( Path::stripLastSeparator( newPath +
                                        newName ) );
    
    BOOST_CHECK_EQUAL( path.getAccessPath(), Path::stripLastSeparator( newPath ) );
    BOOST_CHECK_EQUAL( path.getName(), Path::stripLastSeparator( newName ) );
}

BOOST_AUTO_TEST_CASE( other_functions )
{
    Path path( systemFilePath );

    BOOST_CHECK_EQUAL( path.toString(), standardFilePath );

    Path currentPath;

    BOOST_CHECK_EQUAL( currentPath.toString(), "." );

    Path parentPath( ".." );

    BOOST_CHECK_EQUAL( parentPath.toString(), ".." );

    Path rootPath( "/" );

    BOOST_CHECK_EQUAL( rootPath.toString(), "/" );


    stringstream ss;
    path.print( ss );

    BOOST_CHECK_EQUAL( ss.str(), standardFilePath );


    Path::Clone clonePath = path.clone();

    BOOST_CHECK_EQUAL( clonePath->getAccessPath(), standardDirectoryPathWithoutLastSeparator );
    BOOST_CHECK_EQUAL( clonePath->getName(), pathName );
}

BOOST_AUTO_TEST_CASE( other_operators )
{
    Path firstPath( systemFilePath );

    stringstream ss;
    ss << firstPath;

    BOOST_CHECK_EQUAL( ss.str(), standardFilePath );


    Path secondPath( firstPath );

    BOOST_CHECK_EQUAL( firstPath, secondPath );


    Path thirdPath( "/usr/bin/gcc" );

    BOOST_CHECK_NE( firstPath, thirdPath );
}


BOOST_AUTO_TEST_SUITE_END()
