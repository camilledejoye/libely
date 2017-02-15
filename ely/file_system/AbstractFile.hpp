/*!
 * \file AbstractFile.hpp
 *
 * \author Ely
 *
 * \brief A class for manage path.
 */
#ifndef ABSTRACT_FILE_HPP
#define ABSTRACT_FILE_HPP


#include <memory>
#include <string>


#include "ely/file_system/Path.hpp"


namespace ely
{
namespace file_system
{


/*!
 * \brief The AbstractFile class
 *
 * Represents a file, whatever if it's a directory or a true file.
 */
class AbstractFile
{
public:
    AbstractFile( const Path & path = Path() );
    virtual ~AbstractFile() = default;

    std::string getPath() const;
    std::string getAccessPath() const noexcept;
    std::string getName() const noexcept;

private:
    /// The type of the path store by the object.
    typedef std::shared_ptr< Path > PathType;

    PathType myPath;
};


//
// Public inline functions
//

inline std::string AbstractFile::getPath() const
{
    return myPath->toString();
}

inline std::string AbstractFile::getAccessPath() const noexcept
{
    return myPath->getAccessPath();
}

inline std::string AbstractFile::getName() const noexcept
{
    return myPath->getName();
}


} // namespace ::ely::file_system
} // namespace ::ely

#endif // ABSTRACT_FILE_HPP
