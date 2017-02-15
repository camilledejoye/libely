#include "ely/file_system/File.hpp"

#include <cstdio>

#include "ely/config.hpp"

using std::string;

namespace ely
{
namespace file_system
{


//
// Objects creation operations
//
/*!
 * \brief Constructor
 *
 * Create a \c File to access the file representing by \p filePathString and try to open it.
 *
 * \param filePathString  A string representing the path to the file to manage.
 */
File::File( const string & filePathString )
    : myFilePath( filePathString ),
    myStream( ELY_NULLPTR ),
    myIsOpen( false )
{
    open();
}

/*!
 * \brief Constructor
 *
 * Create a \c File to access the file representing by \p filePath and try to open it.
 *
 * \param filePath  A \c FilePath object representing the path to the file to manage.
 */
File::File( const FilePath & filePath )
    : myFilePath( filePath ),
    myStream( ELY_NULLPTR ),
    myIsOpen( false )
{
    open();
}

/*!
 * \brief Constructor
 *
 * Move constructor : Constructs the object with the contents of \p file using the move semantics.\n
 * \p file is left valid but unspecified state.
 *
 * \param file The \c File object to move.
 */
File::File( File && file )
    : myFilePath( std::move( file.myFilePath ) ),
    myStream( std::move( file.myStream ) ),
    myIsOpen( std::move( file.myIsOpen ) )
{}


File & File::operator =( File && file )
{
    myFilePath = std::move( file.myFilePath );
    myStream = std::move( file.myStream );
    myIsOpen = std::move( file.myIsOpen );

    return *this;
}


void File::swap( File & file )
{
    std::swap( myFilePath, file.myFilePath );
    myStream.swap( file.myStream );
    std::swap( myIsOpen, file.myIsOpen );
}


File::~File()
{
    close();
}


//
// Public functions
//
bool File::open()
{
    if ( ! isOpen() )
    {
        myStream.reset( new FileStream( FilePath::toSystemSeparator( myFilePath.toString() ),
                                        std::ios_base::in | std::ios_base::out | std::ios_base::app ) );

        if ( false == ! getStream() )
        {
            myIsOpen = true;
        }
    }

    return myIsOpen;
}

bool File::open( const std::string & filePathString )
{
    open( FilePath( filePathString ) );

    return myIsOpen;
}

bool File::open( const FilePath & filePath )
{
    if ( filePath == myFilePath )
    {
        open();
    }
    else
    {
        close();

        myFilePath = filePath;

        open();
    }

    return myIsOpen;
}


void File::close()
{
    if ( isOpen() )
    {
        getStream().close();

        myIsOpen = false;
    }
}


/*!
 * \brief Rename the file
 *
 * Rename the file in \p filePathString .\n
 * After renaming the file is still in open state.
 *
 * \param filePathString    A string representing the new name of the file.
 *
 * \return \c true if the file was successfully renamed, \c false otherwise.
 */
bool File::rename( const std::string & filePathString )
{
    close();

    FilePath newFilePath( FilePath::baseName( filePathString ) );
    newFilePath.setAccessPath( myFilePath.getAccessPath() );

    // TODO : manage error :  when rename != 0 and why ?
    // new name already exists ? etc.
    // return exception for more infos to the user.
    int renameCode = std::rename( myFilePath.toString().c_str(), newFilePath.toString().c_str() );

    // If the file has been renamed
    if ( 0 == renameCode )
    {
        myFilePath = std::move( newFilePath );
    }

    open();

    return ( 0 == renameCode ) ? true : false;
}

/*!
 * \brief Rename the file
 *
 * Rename the file in \code filePath.getName()\endcode.\n
 * After renaming the file is still in open state.
 *
 * \param filePath    A \c FilePath object used to rename the file.
 *
 * \return \c true if the file was successfully renamed, \c false otherwise.
 */
bool File::rename( const FilePath & filePath )
{
    return rename( filePath.getName() );
}

bool File::erase()
{
    close();

    int removeCode = std::remove( FilePath::toSystemSeparator( myFilePath.toString() ).c_str() );

    return ( 0 == removeCode ) ? true : false;
}


} // namespace ::ely::file_system
} // namespace ::ely
