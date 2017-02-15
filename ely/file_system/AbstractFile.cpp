#include "AbstractFile.hpp"


namespace ely
{
namespace file_system
{


//
// Constructors && operators =
//

/*!
 * \brief Constructor
 *
 * Default constructor : Create a file representing the one target
 * by \p pathor the current directory if \p path is not provided.
 *
 * \param path  The path to the file to manage.
 */
AbstractFile::AbstractFile( const Path & path )
    : myPath( std::move( path.clone() ) ) // TODO : try with unique_ptr => myPath ( std::move( path.clone().get() ) )
{}


} // namespace ::ely::file_system
} // namespace ::ely
