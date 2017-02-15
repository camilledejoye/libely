/*!
 * \file Composite.cpp
 *
 * \brief Tests program.
 *
 * \author Ely
 *
 * Test program for the Composite pattern.
 */

#include <boost/test/unit_test.hpp>

//*

#include <ely/patterns/Composite.hpp>

using ely::patterns::Component;
using ely::patterns::Composite;


class AbstractFile : public Component< AbstractFile >
{
public:
    AbstractFile( ::std::string const & aName )
        : myName( aName )
    {}

    virtual ::std::string toString() const = 0;


    AbstractFile & setName( ::std::string const & aName )
    {
        myName = aName;

        return *this;
    }

    virtual ::std::string const & getName() const
    {
        return myName;
    }


protected:
    ::std::string myName;
};


class File : public AbstractFile
{
public:
    static char const EXTENSION_SEPARATOR;

    File( ::std::string const & name )
        : AbstractFile( name ), myExtension()
    {}

    File( ::std::string const & name, ::std::string extension )
        : AbstractFile( name ), myExtension( ::std::move( extension ) )
    {}

    virtual ::std::string toString() const override
    {
        ::std::string completeFilename = getName();

        if ( false == getExtension().empty() )
        {
            completeFilename += EXTENSION_SEPARATOR + getExtension();
        }

        return completeFilename;
    }


    File & setExtension( ::std::string extension )
    {
        myExtension = ::std::move( extension );

        return *this;
    }

    ::std::string const & getExtension() const
    {
        return myExtension;
    }

protected:
    ::std::string myExtension;
};
char const File::EXTENSION_SEPARATOR = '.';


class Directory : public Composite< AbstractFile >
{
public:
    static char const SEPARATOR;

    Directory( ::std::string const & name )
        : Composite< AbstractFile >( name )
    {}

    virtual ::std::string toString() const override
    {
        ::std::string path;

        if ( hasParent() ) {
            path += getParent().toString();
        } else {
            path += SEPARATOR;
        }

        return path;
    }
};
char const Directory::SEPARATOR = '/';


BOOST_AUTO_TEST_SUITE( composite )

BOOST_AUTO_TEST_CASE( global )
{
    Directory root( "/" );
    Directory home( "home" );
    File logFile( "File", "log" );

    root.add( home );
    /*
       .add( Directory( "usr" ) )
       .add( File( ".test" ) );

       home.add( Directory( "ely" ) );
       home.getChildren().back()->add( logFile );

       BOOST_CHECK_EQUAL( root.toString(), "/home/ely/file.log" );

       Directory & homeDirectory = ( Directory & ) * root.getChildren().front();
       Directory & elyDirectory = ( Directory & ) * homeDirectory.getChildren().front();
       File & fileFile = ( File & ) * elyDirectory.getChildren().front();

       BOOST_CHECK_EQUAL( elyDirectory.toString(), "ely/file.log" );
       BOOST_CHECK_EQUAL( fileFile.getName(), "file" );
       BOOST_CHECK_EQUAL( fileFile.getExtension(), "log" );
       BOOST_CHECK_EQUAL( fileFile.toString(), "file.log" );
     */
}

BOOST_AUTO_TEST_SUITE_END()

//*/
