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

    virtual ::std::string getPath() const = 0;


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
    File( ::std::string const & name )
        : AbstractFile( name )
    {}

    virtual ::std::string getPath() const override
    {
        ::std::string path;

        if ( hasParent() ) {
            path += getParent()->getPath();
        }
        
        path += getName();

        return path;
    }
};


class Directory : public Composite< AbstractFile >
{
public:
    Directory( ::std::string const & name )
        : Composite< AbstractFile >( name )
    {}

    virtual ::std::string getPath() const override
    {
        ::std::string path;

        if ( hasParent() ) {
            path += getParent()->getPath();
        }
        
        path += getName();
        
        if ( '/' != path.back() )
        {
            path += "/";
        }

        return path;
    }
};


BOOST_AUTO_TEST_SUITE( composite )

BOOST_AUTO_TEST_CASE( global )
{
    Directory root( "/" );

    root.add( ::std::make_unique< Directory >( "test" ) )
        .add( ::std::make_unique< File >( "aFile" ) );
    
    Directory * ely = root.create< Directory >( "home" )->create< Directory >( "ely" );
    File * file = ely->create< File >( "myFile" );
    
   BOOST_CHECK_EQUAL( root.getName(), "/" );

   BOOST_CHECK_EQUAL( ely->getName(), "ely" );
   BOOST_CHECK_EQUAL( file->getName(), "myFile" );
   BOOST_CHECK_EQUAL( root.hasParent(), false );
   BOOST_CHECK_EQUAL( ely->hasParent(), true );
   BOOST_CHECK_EQUAL( file->hasParent(), true );
   BOOST_CHECK_EQUAL( file->getPath(), "/home/ely/myFile" );
}

BOOST_AUTO_TEST_SUITE_END()

//*/
