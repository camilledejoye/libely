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
    static std::string dirName( std::string pathString );
    static std::string baseName( std::string pathString, const std::string & suffix = std::string() );
    static std::string & stripLastSeparator( std::string & pathString );
    static std::string stripLastSeparator( const std::string & pathString );
    static std::string & fromSystemSeparator( std::string & pathString );
    // TODO : try with std::string to let the compiler do the copy but i think there is a signature problem with the previous declaration
    static std::string fromSystemSeparator( const std::string & pathString );
    static std::string & toSystemSeparator( std::string & pathString );
    // TODO : the same as above
    static std::string toSystemSeparator( const std::string & pathString );


    Path() noexcept;
    Path( const std::string & pathString );
    Path( const Path & path ) noexcept;
    Path( Path && path ) noexcept;
    /// The default virtual destructor for a polymorphic usage.
    virtual ~Path() noexcept = default;

    Path & operator =( const std::string & pathString ) noexcept;
    Path & operator =( const Path & path ) noexcept;
    Path & operator =( Path && path ) noexcept;


    void print( std::ostream & os ) const;
    virtual std::string toString() const;


    std::string getAccessPath() const noexcept;
    void setAccessPath( const std::string & accessPath );

    virtual std::string getName() const noexcept;
    void setName( const std::string & name );


    // TODO : add operator +(Path, string) => Path + separator + string
    //                      (Path, Path) => Path + separator + Path ?

protected:
    static constexpr char systemSeparator() noexcept;
    static constexpr char standardSeparator() noexcept;
    static const std::string currentDirectory() noexcept;
    static const std::string parentDirectory() noexcept;


    Clone doClone() const override;


    std::string myAccessPath;
    std::string myName;
};

//
// External functions
//

// Overload the stl's streams operator <<
/*!
 * \brief Stream operator
 *
 * Print the obejct \p abstractPath to the stream \p os.\n
 * Call \e print( \p os \e )
 *
 * \param os        The stream to print in.
 * \param abstractPath  The \c Path object to print.
 *
 * \return A reference on the stream \p os.
 *
 * \sa Path::print( std::ostream & )
 */
inline std::ostream & operator <<( std::ostream & os, const Path & abstractPath )
{
    abstractPath.print( os );

    return os;
}

/*!
 * \brief Operator <em>equal to</em>
 *
 * Compare two objects of type \c Path.
 *
 * \param first     The first object to compare.
 * \param second    The second object to compare with.
 *
 * \return \c true if they represent the same file, \c false otherwise.
 */
inline bool operator ==( const Path & first, const Path & second ) noexcept
{
    return first.getAccessPath() == second.getAccessPath() &&
           first.getName() == second.getName();
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
inline void Path::print( std::ostream & os ) const
{
    os << toString();
}


//
// Accessors
//

/*!
 * \brief Accessor
 *
 * \return The access path.
 */
inline std::string Path::getAccessPath() const noexcept
{
    return myAccessPath;
}
/*!
 * \brief Accessor
 *
 * Replace the actual access path with \p accessPath.\n
 * Remove the dir separator at the end of the new path if there is one.\n
 * \n
 * Convert the new path in the standard format.
 *
 * \param path The new access path.
 *
 * \sa fromSystemSeparator( const std::string & )
 */
inline void Path::setAccessPath( const std::string & accessPath )
{
    myAccessPath = stripLastSeparator( accessPath );
}

/*!
 * \brief Accessor
 *
 * Replace the actual name with \p name.\n
 *
 * \param name The new name of the path's target.
 */
inline void Path::setName( const std::string & name )
{
    myName = stripLastSeparator( name );
}


//
// Protected static functions
//

/*!
 * \brief Constant accessor
 *
 * \return The separator used by the operating system.
 *
 * \sa fromSystemSeparator( std::string & )
 * \sa fromSystemSeparator( const std::string & )
 * \sa toSystemSeparator( std::string & )
 * \sa toSystemSeparator( const std::string & )
 */
constexpr char Path::systemSeparator() noexcept
{
#if defined ( ELY_USING_WIN32_API )
    return '\\';
#else
    return '/';
#endif
}

/*!
 * \brief Constant accessor
 *
 * \return The standard separator used by the class.
 *
 * \sa fromSystemSeparator( std::string & )
 * \sa fromSystemSeparator( const std::string & )
 * \sa toSystemSeparator( std::string & )
 * \sa toSystemSeparator( const std::string & )
 */
constexpr char Path::standardSeparator() noexcept
{
    return '/';
}

/*!
 * \brief Constant accessor
 *
 * \return The string representing the current directory.
 */
inline const std::string Path::currentDirectory() noexcept
{
    return std::string( "." );
}

/*!
 * \brief Constant accessor
 *
 * \return The string representing the parent directory.
 */
inline const std::string Path::parentDirectory() noexcept
{
    return std::string( ".." );
}


} // namespace ::ely::file_system
} // namespace ::ely

#endif // PATH_H
