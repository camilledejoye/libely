#include "ely/file_system/Path.hpp"


#include <algorithm>


namespace ely
{
namespace file_system
{


//
// Static public functions
//

/*!
 * \brief Get the access path.
 *
 * Gets the access path of the path given in \p pathString.\n
 * If \p pathString contains no standard separators (\e / ), return \c currentDirectory() .
 *
 * \param pathString  The access path to the target.
 *
 * \return The path of the target pointed by \p path.\n
 * Or the value of \c currentDirectory() if \p pathString contains no standard separators.
 */
std::string Path::dirName( std::string pathString )
{
    if ( ! pathString.empty() )
    {
        stripLastSeparator( pathString );

        std::string::size_type lastSeparatorPosition = pathString.find_last_of( standardSeparator() );

        if ( std::string::npos != lastSeparatorPosition ) // last separator found
        {
            if ( 0 == lastSeparatorPosition )
            {
                pathString = standardSeparator();
            }
            else
            {
                pathString = pathString.substr( 0, lastSeparatorPosition );
            }
        }
        else if ( parentDirectory() != pathString )
        {
            pathString = currentDirectory();
        }
    }

    return pathString;
}

/*!
 * \brief Strip directory and suffix from a path.
 *
 * Keeps only the name without neither it's access path or the
 * \p suffix if it ends the name.
 *
 * \param pathString  The full path.
 * \param suffix    The suffix to remove.
 *
 * \return The name without it's access path and the \p suffix if it's provide.
 */
std::string Path::baseName( std::string pathString, const std::string & suffix )
{
    std::string baseNameReturned;

    if ( ! pathString.empty() )
    {
        stripLastSeparator( pathString );

        std::string::size_type from = pathString.find_last_of( standardSeparator() );

        if ( std::string::npos != from && pathString.size() > 1 ) // last separator found
        {
            ++from;
        }
        else // If there is no access path or it's the unix root directory '/'
        {
            from = 0;
        }

        std::string::size_type to = pathString.length();

        if ( ! suffix.empty() )
        {
            if ( suffix == pathString.substr( pathString.length() - suffix.length() ) ) // pathString ends with suffix
            {
                to -= suffix.length();
            }
        }

        baseNameReturned = std::string( pathString, from, to - from );
    }

    return baseNameReturned;
}

/*!
 * \brief Removes the last separator if it ends the path \p pathString.
 *
 * \param pathString The path in which the separator will be look for.
 *
 * \return \c pathString without the last separator if it was at the end of the path.
 */
std::string & Path::stripLastSeparator( std::string & pathString )
{
    if ( 1 < pathString.size() )
    {
        fromSystemSeparator( pathString );

        std::string::iterator lastCharIterator = --pathString.end();

        if ( standardSeparator() == *lastCharIterator )
        {
            pathString.erase( lastCharIterator );
        }
    }

    return pathString;
}


/*!
 * \brief Removes the last separator if it ends the path \p pathString.
 *
 * \param pathString The path in which the separator will be look for.
 *
 * \return \c pathString without the last separator if it was at the end of the path.
 */
std::string Path::stripLastSeparator( const std::string & pathString )
{
    std::string pathStringWithoutLastSeparator( pathString );

    return stripLastSeparator( pathStringWithoutLastSeparator );
}


/*!
 * \brief Convert a path to the standard format.
 *
 * Convert a path to the standard format by replacing
 * the system directory separator by \c '/' .
 *
 * \param pathString  The path to convert.
 *
 * \return The path \p pathString in the standard format.
 */
std::string & Path::fromSystemSeparator( std::string & pathString )
{
    if ( systemSeparator() != standardSeparator() )
    {
        std::replace( pathString.begin(), pathString.end(), systemSeparator(), standardSeparator() );
    }

    return pathString;
}

/*!
 * \brief Convert a path to the standard format.
 *
 * Convert a path to the standard format by replacing
 * the system directory separator by \c '/' .
 *
 * \param pathString  The path to convert.
 *
 * \return A new string containing the path \p pathString in the standard format.
 */
std::string Path::fromSystemSeparator( const std::string & pathString )
{
    std::string standardFilePath( pathString );

    return fromSystemSeparator( standardFilePath );
}

/*!
 * \brief Convert a path to the system format.
 *
 * Convert a path to the system format by replacing
 * the standard directory separator by \c '/' the one use
 * by the system.
 *
 * \param pathString  The path to convert.
 *
 * \return The path \p pathString in the system format.
 */
std::string & Path::toSystemSeparator( std::string & pathString )
{
    if ( systemSeparator() != standardSeparator() )
    {
        std::replace( pathString.begin(), pathString.end(), standardSeparator(), systemSeparator() );
    }

    return pathString;
}
/*!
 * \brief Convert a path to the system format.
 *
 * Convert a path to the system format by replacing
 * the standard directory separator by \c '/' the one use
 * by the system.
 *
 * \param pathString  The path to convert.
 *
 * \return A new string containing the path \p pathString in the system format.
 */
std::string Path::toSystemSeparator( const std::string & pathString )
{
    std::string systemFilePath( pathString );

    return toSystemSeparator( systemFilePath );
}


//
// Constructors && operators =
//

/**
 * \brief Constructor
 *
 * Default constructor : create a path targeting the current directory.
 *
 * \sa Path( const std::string & )
 * \sa Path( const Path & )
 * \sa Path( Path && )
 */
Path::Path() noexcept
    : myAccessPath( currentDirectory() ),
    myName( currentDirectory() )
{}

/*!
 * \brief Constructor
 *
 * Create a \c Path object wich refere to the path to file given in \p pathString.
 *
 * \param pathString  The access path to manage.
 *
 * \sa Path()
 * \sa Path( const Path & )
 * \sa Path( Path && )
 */
Path::Path( const std::string & pathString )
    : myAccessPath( dirName( pathString ) ),
    myName( baseName( pathString ) )
{}

/*!
 * \brief Constructor
 *
 * Copy constructor : make a copy of \p Path.
 *
 * \param path  The \c Path object to copy.
 *
 * \sa Path()
 * \sa Path( const std::string & )
 * \sa Path( Path && )
 */
Path::Path( const Path & path ) noexcept
    : myAccessPath( path.myAccessPath ),
    myName( path.myName )
{}

/*!
 * \brief Constructor
 *
 * Move constructor : Constructs the object with the contents of \p path
 * using the move semantics.\n
 * \p path is left valid but unspecified state.
 *
 * \param path  The \c Path object to move.
 *
 * \sa Path()
 * \sa Path( const std::string & )
 * \sa Path( Path && )
 */
Path::Path( Path && path ) noexcept
    : myAccessPath( std::move( path.myAccessPath ) ),
    myName( std::move( path.myName ) )
{}

/*!
 * \brief Assignment operator
 *
 * Replace the path currently manage by \p pathString.
 *
 * \param pathString  The new path to manage.
 *
 * \return A reference on the current object.
 *
 * \sa operator =( const Path & )
 * \sa operator =( Path && )
 */
Path & Path::operator =( const std::string & pathString ) noexcept
{
    try
    {
        myAccessPath = dirName( pathString );
        myName = baseName( pathString );
    }
    catch ( ... )
    {
        // TODO : print debug infos ?
        static_cast< void >( 0 );
    }

    return *this;
}

/*!
 * \brief Assignment operator
 *
 * Replace the path currently manage by the one contains in \p path
 *
 * \param path  The object wich contains the path to manage.
 *
 * \return A reference on the current object.
 *
 * \sa operator =( const std::string & )
 * \sa operator =( Path && )
 */
Path & Path::operator =( const Path & path ) noexcept
{
    myAccessPath = path.myAccessPath;
    myName = path.myName;

    return *this;
}

/*!
 * \brief Assignment operator
 *
 * Move the contents of \p path using the move semantics.
 *
 * \param path  The \c Path object to move.
 *
 * \return A Reference on the current object.
 *
 * \sa operator =( const std::string & )
 * \sa operator =( const Path & )
 */
Path & Path::operator =( Path && path ) noexcept
{
    myAccessPath = std::move( path.myAccessPath );
    myName = std::move( path.myName );

    return *this;
}


//
// Public functions
//

/*!
 * \brief Convert an \c Path object to a string
 *
 * \return The path to the file manage by the object.
 */
std::string Path::toString() const
{
    return ( getAccessPath() == getName() ) ? getAccessPath() : getAccessPath() + standardSeparator() + getName();
}


//
// Accessors
//

/*!
 * \brief Accessor
 *
 * \return The name of the path's target.
 */
std::string Path::getName() const noexcept
{
    return myName;
}


//
// Protected functions
//

/*!
 * \brief Clone the current object.
 *
 * \return A dynamic copy of the current object.
 */
Path::Clone Path::doClone() const
{
    return Clone( new Path( *this ) );
}


} // namespace ::ely::file_system
} // namespace ::ely
