/*!
 * \file FilePath.hpp
 *
 * \author Ely
 *
 * \brief A class for manage files' path.
 */
#ifndef FILE_PATH_HPP
#define FILE_PATH_HPP


#include "ely/file_system/Path.hpp"


namespace ely
{
namespace file_system
{


/*!
 * \brief The FilePath class
 *
 * Represents the path of a file which is a real file, not a directory.\n\n
 *
 * This class allow to use a path idependently of the operating system.\n
 * This is done by using the character \e / as directory seprator whatever the platform.\n\n
 *
 * A path is composed of its access path (the path to the directory containing the file) and its name (the filename).\n
 * Exemple : \e /home/ely/script.sh\n
 * \e /home/ely is the access path.\n
 * \e script.sh is the name.
 */
class FilePath : public Path
{
public:
    static std::string extractExtension( const std::string & filename, const char separator = extensionSeparator() );


    FilePath( const std::string & pathString );
    FilePath( const FilePath & path ) noexcept;
    FilePath( FilePath && path ) noexcept;

    FilePath & operator =( const std::string & pathString ) noexcept;
    FilePath & operator =( const FilePath & path ) noexcept;
    FilePath & operator =( FilePath && path ) noexcept;


    virtual std::string const & getName() const noexcept override;
    virtual FilePath & setName( ::std::string const & aName ) override;

    std::string getExtension() const noexcept;
    void setExtension( const std::string & extension = std::string() ) noexcept;
    
    
    CLONE( FilePath )

private:
    static constexpr char extensionSeparator() noexcept;


    FilePath() = delete;

    ::std::string myFullName;
    std::string myExtension;
};


//
// Accessors
//

/*!
 * \brief Accessor
 *
 * \return The extension of the file.
 */
inline std::string FilePath::getExtension() const noexcept
{
    return myExtension;
}
/*!
 * \brief Accessor
 *
 * Replace the actual extenion with \p extension
 *
 * \param extension The new extension of the file, whithout the separator.
 */
inline void FilePath::setExtension( const std::string & extension ) noexcept
{
    myExtension = extension;
    
    if ( myExtension.empty() )
    {
        myFullName = myName;
    }
    else
    {
        myFullName = myName + extensionSeparator() + myExtension;
    }
}


//
// Private static functions
//

/*!
 * \brief Constant accessor
 *
 * \return The character separating the filename and its extension.
 */
constexpr char FilePath::extensionSeparator() noexcept
{
    return '.';
}


} // namespace ::ely::file_system
} // namespace ::ely

#endif // FILE_PATH_HPP
