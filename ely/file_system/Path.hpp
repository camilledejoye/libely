/*!
 * \file Path.hpp
 *
 * \author Ely
 *
 * \brief A class for manage path.
 */
#ifndef PATH_H
#define PATH_H


#include <string>


#include "ely/config.hpp"
#include "ely/patterns/Cloneable.hpp"


namespace ely
{
namespace file_system
{


/*!
 * \brief The Path class
 *
 * Represents a path, whatever if the target is a directory or a file.\n\n
 *
 * This class allow to use a path idependently of the operating system.\n
 * This is done by using the character \e / as directory seprator whatever the platform.\n\n
 *
 * A path is composed of its access path (its location) and its name.\n
 * Exemple : \e /home/ely/script.sh\n
 * \e /home/ely is the access path.\n
 * \e script.sh is the name.
 */
class Path : public patterns::AbstractCloneable< Path >
{
public:
    enum Separator { Standard, System };
    
    static ::std::string dirName( ::std::string aStringPath );
    static ::std::string baseName( ::std::string aStringPath, ::std::string const & aSuffix = ::std::string() );
    static ::std::string & stripLastSeparator( ::std::string & aStringPath );
    static ::std::string stripLastSeparator( ::std::string const & aStringPath );
    static ::std::string & stripFirstSeparator( ::std::string & aStringPath );
    static ::std::string stripFirstSeparator( ::std::string const & aStringPath );
    static ::std::string & toStandardSeparator( ::std::string & aStringPath );
    static ::std::string toStandardSeparator( ::std::string const & aStringPath );
    static ::std::string & toSystemSeparator( ::std::string & aStringPath );
    static ::std::string toSystemSeparator( ::std::string const & aStringPath );
    
    
    Path() noexcept;
    Path( ::std::string const & aStringPath );
    Path( Path const & path ) noexcept;
    Path( Path && path ) noexcept;
    /// The default virtual destructor for a polymorphic usage.
    virtual ~Path() noexcept = default;
    
    Path & operator =( ::std::string const & aStringPath );
    Path & operator =( Path const & path ) noexcept;
    Path & operator =( Path && path ) noexcept;
    
    
    Path & add( Path const & aPath );
    Path & add( ::std::string const & aString );
    
    
    ::std::ostream & print( ::std::ostream & os ) const;
    ::std::string toString( Separator aType = Standard ) const;
    
    
    Path & set( ::std::string const & aStringPath );
    
    ::std::string const & getAccessPath() const noexcept;
    
    virtual ::std::string const & getName() const noexcept;
    virtual Path & setName( ::std::string const & aName );
    
    
    CLONE( Path )
    
protected:
#if defined ( ELY_USING_WIN32_API )
    static constexpr char systemSeparator   = '\\';
#else
    static constexpr char systemSeparator   = '/';
#endif
    static constexpr char standardSeparator = '/';
    static constexpr auto currentDirectory  = ".";
    static constexpr auto parentDirectory   = "..";


    ::std::string myAccessPath;
    ::std::string myName;
};

//
// External functions
//

// Overload the stl's streams operator <<
/*!
 * \brief Stream operator
 *
 * Print the obejct \p aPath to the stream \p os.\n
 * Call \e print( \p os \e )
 *
 * \param os The stream to print in.
 * \param abstractPath The \c Path object to print.
 *
 * \return A reference on the stream \p os.
 *
 * \sa Path::print( ::std::ostream & )
 */
inline ::std::ostream & operator <<( ::std::ostream & os, Path const & aPath )
{
    aPath.print( os );

    return os;
}

/*!
 * \brief operator ==
 *
 * Compare two objects of type \c Path.
 *
 * \param aPath The first object to compare to.
 * \param anotherPath The second object to compare with.
 *
 * \return \c true if they represent the same path, \c false otherwise.
 */
inline bool operator ==( Path const & aPath, Path const & anotherPath ) noexcept
{
    return aPath.getAccessPath() == anotherPath.getAccessPath() &&
           aPath.getName() == anotherPath.getName();
}

/*!
 * \brief operator ==
 * 
 * Compare an object of type \c Path with a string.
 * 
 * \param aPath The object to compare to.
 * \param aString The string to compare with.
 * 
 * \return \c true if they represent the same path, \c false otherwise.
 */
inline bool operator ==( Path const & aPath, ::std::string const & aString )
{
    return aPath == Path( aString );
}

inline Path operator +( Path const & aPath, Path const & anotherPath )
{
    Path newPath( aPath );
    
    newPath.add( anotherPath );
    
    return newPath;
}

//
// Public inline functions
//

/*!
 * \brief Print to a stream.
 *
 * Print the string representation of the current object to the stream \p os.\n
 * Call \e toString()
 *
 * \param os  The stream to print in.
 *
 * \sa toString()
 */
inline ::std::ostream & Path::print( ::std::ostream & os ) const
{
    os << toString();
    
    return os;
}


//
// Accessors
//

/*!
 * \brief Accessor
 *
 * \return The access path.
 */
inline std::string const & Path::getAccessPath() const noexcept
{
    return myAccessPath;
}

/*!
 * \brief Accessor
 *
 * Set a new access path and a new name based on \c aStringPath .
 *
 * \param aStringPath The new path.
 */
inline Path & Path::set( ::std::string const & aStringPath )
{
    myAccessPath = dirName( aStringPath );
    setName( baseName( aStringPath ) );
    
    return *this;
}


} // namespace ::ely::file_system
} // namespace ::ely

#endif // PATH_H
