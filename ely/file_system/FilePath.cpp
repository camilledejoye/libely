#include "ely/file_system/FilePath.hpp"


using std::string;


namespace ely
{
namespace file_system
{

//
// Static public functions
//

/*!
 * \brief Extract the extension from a filename.
 *
 * Look for the last characrer \p separator in \p filename and trim from its
 * position to the end of the filename.
 *
 * \param filename  The name of the file from which the extension will be extracted.
 * \param separator The separator used to find the extension.
 *
 * \return The extension of \p filename without the separator.
 */
string FilePath::extractExtension( const string & filename, const char separator )
{
    string extension;

    if ( false == filename.empty() )
    {
        string::size_type separatorPsotion = filename.find_last_of( separator );

        if ( string::npos != separatorPsotion )
        {
            extension = filename.substr( ++separatorPsotion );
        }
    }

    return extension;
}


//
// Constructors && operators =
//

/*!
 * \brief Constructor
 *
 * Create a \c FilePath object wich refere to file given in \p filePathString.
 *
 * \param filePathString  The path to the file to manage.
 *
 * \sa FilePath()
 * \sa FilePath( const FilePath & )
 * \sa FilePath( FilePath && )
 */
FilePath::FilePath( const string & filePathString )
    : Path( filePathString ),
    myExtension( extractExtension( myName ) )
{
    myName = baseName( myName, extensionSeparator() + myExtension );
}

/*!
 * \brief Constructor
 *
 * Copy constructor : make a copy of \p FilePath.
 *
 * \param filePath  The \c FilePath object to copy.
 *
 * \sa FilePath()
 * \sa FilePath( const string & )
 * \sa FilePath( FilePath && )
 */
FilePath::FilePath( const FilePath & filePath ) noexcept
    : Path( filePath ),
    myExtension( filePath.myExtension )
{}

/*!
 * \brief Constructor
 *
 * Move constructor : Constructs the object with the contents of \p filePath
 * using the move semantics.\n
 * \p filePath is left valid but unspecified state.
 *
 * \param filePath  The \c FilePath object to move.
 *
 * \sa FilePath()
 * \sa FilePath( const string & )
 * \sa FilePath( FilePath && )
 */
FilePath::FilePath( FilePath && filePath ) noexcept
    : Path( std::forward< FilePath >( filePath ) ),
    myExtension( std::move( filePath.myExtension ) )
{}

/*!
 * \brief Assignment operator
 *
 * Replace the path of the file currently manage by the one reprenting by the string \p filePathString.
 *
 * \param filePathString  The path to the new file to manage.
 *
 * \return A reference on the current object.
 *
 * \sa operator =( const FilePath & )
 * \sa operator =( FilePath && )
 */
FilePath & FilePath::operator =( const string & filePathString ) noexcept
{
    Path::operator =( filePathString );
    myExtension = extractExtension( myName );
    myName = baseName( myName, extensionSeparator() + myExtension );

    return *this;
}

/*!
 * \brief Assignment operator
 *
 * Replace the path currently manage by the one contains in \p filePath
 *
 * \param filePath  The object wich contains the path to manage.
 *
 * \return A reference on the current object.
 *
 * \sa operator =( const string & )
 * \sa operator =( FilePath && )
 */
FilePath & FilePath::operator =( const FilePath & filePath ) noexcept
{
    Path::operator =( filePath );
    myExtension = filePath.myExtension;

    return *this;
}

/*!
 * \brief Assignment operator
 *
 * Move the contents of \p filePath using the move semantics.
 *
 * \param filePath  The \c FilePath object to move.
 *
 * \return A Reference on the current object.
 *
 * \sa operator =( const string & )
 * \sa operator =( const FilePath & )
 */
FilePath & FilePath::operator =( FilePath && filePath ) noexcept
{
    Path::operator =( filePath );
    myExtension = std::move( filePath.myExtension );

    return *this;
}


//
// Private functions
//

/*!
 * \brief Clone the current object.
 *
 * \return A dynamic copy of the current object.
 */
FilePath::Clone FilePath::doClone() const
{
    return Clone( new FilePath( *this ) );
}


} // namespace ::ely::file_system
} // namespace ::ely
