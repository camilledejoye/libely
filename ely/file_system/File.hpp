#ifndef FILE_H
#define FILE_H

#include <string>
#include <memory>
#include <fstream>

#include "ely/file_system/FilePath.hpp"

namespace ely
{
namespace file_system
{


/*!
 * \class File
 *
 * \brief Read and write in to a file.
 *
 * This class allows to manage files with TODO : end this
 */
class File
{
public:
    typedef std::fstream FileStream;


    File( const std::string & filePathString );
    File( const FilePath & filePath );
    File( File && file );

    File & operator =( File && file );

    void swap( File & file );

    virtual ~File();


    bool open();
    bool open( const std::string & filePathString );
    bool open( const FilePath & filePath );
    void close();


    bool rename( const std::string & filePathString );
    bool rename( const FilePath & filePath );
    bool erase();


    const FilePath & getPath() const;

    FileStream & getStream() const;


    bool isOpen() const;

    bool operator !() const;
    explicit operator bool() const;

    template < typename T >
    File & operator <<( T && t );
    template < typename T >
    File & operator >>( T && t );

private:
    FilePath myFilePath;
    std::unique_ptr< FileStream > myStream;
    bool myIsOpen;
};


/*!
 * \brief Check if the file is open.
 *
 * \return \c true if the file is open, \c false otherwise.
 *
 * \sa open()
 * \sa open( const std::string & )
 * \sa open( const FilePath & )
 */
inline bool File::isOpen() const
{
    return myIsOpen;
}


/*!
 * \brief Accessor
 *
 * \return A constant reference on \c FilePath representing the path of the file.
 */
inline const FilePath & File::getPath() const
{
    return myFilePath;
}

/*!
 * \brief Accessor
 *
 * \return A stream \c FileStream corresonding to the file.
 */
inline File::FileStream & File::getStream() const
{
    return *myStream;
}


/*!
 * \brief Check if the file is open.
 *
 * \return \c false if the file is open, \c true otherwise.
 *
 * \sa isOpen()
 * \sa operator bool()
 * \sa open()
 * \sa open( const std::string & )
 * \sa open( const FilePath & )
 */
inline bool File::operator !() const
{
    return ! isOpen();
}

/*!
 * \brief Check if the file is open.
 *
 * \return \c true if the file is open, \c false otherwise.
 *
 * \sa isOpen()
 * \sa operator !()
 * \sa open()
 * \sa open( const std::string & )
 * \sa open( const FilePath & )
 */
inline File::operator bool() const
{
    return isOpen();
}


template < typename T >
/*!
 * \brief Stream operator
 *
 * Write the value of \p t in to the file.
 *
 * \param t The value to write.
 *
 * \return A reference on the current object.
 */
File & File::operator <<( T && t )
{
    // TODO : gestion erreurs
    if ( isOpen() )
    {
        getStream() << std::forward< T >( t );
    }

    return *this;
}

template < typename T >
/*!
 * \brief Stream operator
 *
 * Write the value of \p t in to the file.
 *
 * \param t Reference to a variable to store the extracted value to.
 *
 * \return A reference on the current object.
 */
File & File::operator >>( T && t )
{
    // TODO : gestion erreurs
    if ( isOpen() )
    {
        getStream() >> std::forward< T >( t );
    }

    return *this;
}


} // namespace ::ely::file_system
} // namespace ::ely
#endif // FILE_H
