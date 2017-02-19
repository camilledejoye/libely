#include "ely/file_system/Path.hpp"


#include <algorithm>
#include <functional>


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
 * Gets the access path of the path given in \p aStringPath.\n
 * If \p aStringPath contains no standard separators (\e / ), return \c currentDirectory .
 *
 * \param aStringPath  A string representing the access path to the target.
 *
 * \return The access path of the target pointed by \p aStringPath.\n
 * Or an empty string if \p aStringPath is empty.
 */
std::string Path::dirName( ::std::string aStringPath )
{
    if ( ! aStringPath.empty() )
    {
        stripLastSeparator( aStringPath );

        ::std::string::size_type lastSeparatorPosition = aStringPath.find_last_of( standardSeparator );

        if ( ::std::string::npos != lastSeparatorPosition ) // last separator found
        {
            if ( 0 == lastSeparatorPosition )
            {
                aStringPath = standardSeparator;
            }
            else
            {
                aStringPath = aStringPath.substr( 0, lastSeparatorPosition );
            }
        }
        else if ( parentDirectory  != aStringPath &&
                  currentDirectory != aStringPath )
        {
            aStringPath = currentDirectory;
        }
    }

    return aStringPath;
}

/*!
 * \brief Strip directory and suffix from a path.
 *
 * Keeps only the name without neither it's access path or the
 * \p aSuffix if it ends the name.
 *
 * \param aStringPath  The full path.
 * \param aSuffix    The suffix to remove.
 *
 * \return The name without it's access path and \p aSuffix if it's provided.n
 * Or an empty string if \p aStringPath is empty.
 */
std::string Path::baseName(::std::string aStringPath, ::std::string const & aSuffix )
{
    if ( ! aStringPath.empty() )
    {
        stripLastSeparator( aStringPath );

        ::std::string::size_type from = aStringPath.find_last_of( standardSeparator );

        if ( ::std::string::npos != from && aStringPath.size() > 1 ) // last separator found
        {
            ++from;
        }
        else // If there is no access path or it's the unix root directory '/'
        {
            from = 0;
        }

        ::std::string::size_type length = aStringPath.length() - from;

        if ( ! aSuffix.empty() )
        {
            if ( aSuffix == aStringPath.substr( aStringPath.length() - aSuffix.length() ) ) // aStringPath ends with suffix
            {
                length -= aSuffix.length();
            }
        }

        aStringPath = aStringPath.substr( from, length );
    }

    return aStringPath;
}

/*!
 * \brief Removes the last separator if it ends the path \p aStringPath.
 *
 * \param aStringPath The path in which the separator will be look for.
 *
 * \return \c aStringPath without the last separator if it was at the end of the path.
 */
std::string & Path::stripLastSeparator(::std::string & aStringPath )
{
    if ( 1 < aStringPath.size() ) // If it's not the unix root directory '/'
    {
        toStandardSeparator( aStringPath );

        if ( standardSeparator == aStringPath.back() )
        {
            aStringPath.pop_back();
        }
    }

    return aStringPath;
}


/*!
 * \brief Removes the last separator if it ends the path \p aStringPath.
 *
 * \param aStringPath The path in which the separator will be look for.
 *
 * \return \c aStringPath without the last separator if it was at the end of the path.
 */
std::string Path::stripLastSeparator( ::std::string const & aStringPath )
{
    ::std::string aStringPathWithoutLastSeparator( aStringPath );

    return stripLastSeparator( aStringPathWithoutLastSeparator );
}

/*!
 * \brief Removes the first separator if it begins the path \p aStringPath.
 *
 * \param aStringPath The path in which the separator will be look for.
 *
 * \return \c aStringPath without the first separator if it was at the begin of the path.
 */
std::string & Path::stripFirstSeparator(::std::string & aStringPath )
{
    if ( 1 < aStringPath.size() ) // If it's not the unix root directory '/'
    {
        toStandardSeparator( aStringPath );

        if ( standardSeparator == aStringPath.front() )
        {
            aStringPath.erase( aStringPath.cbegin() );
        }
    }

    return aStringPath;
}


/*!
 * \brief Removes the first separator if it begins the path \p aStringPath.
 *
 * \param aStringPath The path in which the separator will be look for.
 *
 * \return \c aStringPath without the first separator if it was at the begin of the path.
 */
std::string Path::stripFirstSeparator( ::std::string const & aStringPath )
{
    ::std::string aStringPathWithoutFirstSeparator( aStringPath );

    return stripFirstSeparator( aStringPathWithoutFirstSeparator );
}


/*!
 * \brief Convert a path to the standard format.
 *
 * Convert a path to the standard format by replacing
 * the system directory separator by \c '/' .
 *
 * \param aStringPath  The path to convert.
 *
 * \return The path \p aStringPath in the standard format.
 */
std::string & Path::toStandardSeparator( ::std::string & aStringPath )
{
    if ( systemSeparator != standardSeparator )
    {
        ::std::replace( aStringPath.begin(), aStringPath.end(), systemSeparator, standardSeparator );
    }

    return aStringPath;
}

/*!
 * \brief Convert a path to the standard format.
 *
 * Convert a path to the standard format by replacing
 * the system directory separator by \c '/' .
 *
 * \param aStringPath  The path to convert.
 *
 * \return A new string containing the path \p aStringPath in the standard format.
 */
std::string Path::toStandardSeparator( ::std::string const & aStringPath )
{
    ::std::string standardFilePath( aStringPath );

    return toStandardSeparator( standardFilePath );
}

/*!
 * \brief Convert a path to the system format.
 *
 * Convert a path to the system format by replacing
 * the standard directory separator by \c '/' the one use
 * by the system.
 *
 * \param aStringPath  The path to convert.
 *
 * \return The path \p aStringPath in the system format.
 */
std::string & Path::toSystemSeparator( ::std::string & aStringPath )
{
    if ( systemSeparator != standardSeparator )
    {
        ::std::replace( aStringPath.begin(), aStringPath.end(), standardSeparator, systemSeparator );
    }

    return aStringPath;
}
/*!
 * \brief Convert a path to the system format.
 *
 * Convert a path to the system format by replacing
 * the standard directory separator by \c '/' the one use
 * by the system.
 *
 * \param aStringPath  The path to convert.
 *
 * \return A new string containing the path \p aStringPath in the system format.
 */
std::string Path::toSystemSeparator( ::std::string const & aStringPath )
{
    ::std::string systemFilePath( aStringPath );

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
 * \sa Path( ::std::string const & )
 * \sa Path( Path const & )
 * \sa Path( Path && )
 */
Path::Path() noexcept
    : myAccessPath( currentDirectory ),
    myName( currentDirectory )
{}

/*!
 * \brief Constructor
 *
 * Create a \c Path object wich refere to the path to file given in \p aStringPath.
 *
 * \param aStringPath  The access path to manage.
 *
 * \sa Path()
 * \sa Path( Path const & )
 * \sa Path( Path && )
 */
Path::Path( ::std::string const & aStringPath )
    : myAccessPath( dirName( aStringPath ) ),
    myName( baseName( aStringPath ) )
{}

/*!
 * \brief Constructor
 *
 * Copy constructor : make a copy of \p Path.
 *
 * \param path  The \c Path object to copy.
 *
 * \sa Path()
 * \sa Path( ::std::string const & )
 * \sa Path( Path && )
 */
Path::Path( Path const & path ) noexcept
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
 * \sa Path( ::std::string const & )
 * \sa Path( Path && )
 */
Path::Path( Path && path ) noexcept
    : myAccessPath( ::std::move( path.myAccessPath ) ),
    myName( ::std::move( path.myName ) )
{}

/*!
 * \brief Assignment operator
 *
 * Replace the path currently manage by \p aStringPath.
 *
 * \param aStringPath  The new path to manage.
 *
 * \return A reference on the current object.
 *
 * \sa operator =( Path const & )
 * \sa operator =( Path && )
 */
Path & Path::operator =( ::std::string const & aStringPath )
{
    myAccessPath = dirName( aStringPath );
    myName = baseName( aStringPath );

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
 * \sa operator =( ::std::string const & )
 * \sa operator =( Path && )
 */
Path & Path::operator =( Path const & path ) noexcept
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
 * \sa operator =( ::std::string const & )
 * \sa operator =( Path const & )
 */
Path & Path::operator =( Path && path ) noexcept
{
    myAccessPath = ::std::move( path.myAccessPath );
    myName = ::std::move( path.myName );

    return *this;
}

//
// Accessors
//

/*!
 * \brief Accessor
 *
 * \return The name of the path's target.
 */
std::string const & Path::getName() const noexcept
{
    return myName;
}

/*!
 * \brief Accessor
 *
 * Set a new access path and a new name based on \c aStringPath .
 *
 * \param aStringPath The new path.
 */
Path & Path::setName( ::std::string const & aName )
{
    myName = aName;
    
    return *this;
}


//
// Public functions
//

/*!
 * \brief Concatenate two pathes.
 * 
 * 
 * 
 * \param aPath The path to concatenate with.
 * \return 
 */
Path & Path::add( Path const & aPath )
{
    return add( aPath.toString() );
}

Path & Path::add( std::string const & aString )
{
    if ( ! aString.empty() )
    {
        if ( parentDirectory == aString.substr( 0, 2 ) )
        {
            set( myAccessPath +
                 standardSeparator +
                 stripFirstSeparator( aString.substr( 2 ) ) );
        }
        else if ( currentDirectory[ 0 ] == aString.front() )
        {
            set( toString() +
                 standardSeparator +
                 stripFirstSeparator( aString.substr( 1 ) ) );
        }
        else if ( standardSeparator == aString.front() )
        {
            set( toString() +
                 aString );
        }
        else
        {
            set( toString() +
                 standardSeparator +
                 aString );
        }
    }
    
    return *this;
}

/*!
 * \brief Convert an \c Path object to a string
 * 
 * \param aType The desired type of separator.
 *
 * \return The path to the file manage by the object.
 */
std::string Path::toString( Separator aType ) const
{
    ::std::string stringPath = ( getAccessPath() == getName() )
                               ? getAccessPath()
                               : getAccessPath() + standardSeparator + getName();
    
    if ( System == aType )
    {
        toSystemSeparator( stringPath );
    }
    
    return stringPath;
}


} // namespace ::ely::file_system
} // namespace ::ely
