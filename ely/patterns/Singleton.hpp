/*!
 * \file Singleton.h
 *
 * \author Ely
 *
 * \brief A generic implementation of the Singleton deisgn pattern.
 */
#ifndef SINGLETON_H
#define SINGLETON_H


#include <memory>

#include "ely/predicates/IsNull.hpp"


namespace ely
{
namespace patterns
{


template < class Object >
/*!
 * \brief The Singleton class
 *
 * The basic implementation needed by any objects which have to be a singleton.\n\n
 *
 * Implement it as follow :\n
 * \code
 * class MySingleton : ely::patterns::Singleton< MySingleton >
 * {
 *     friend class ely::patterns::Singleton< MySingleton >;
 *
 *     // Implementation
 * };
 *
 * MySingleton::getInstance().myMethod();
 *
 * \endcode
 */
class Singleton
{
public:
    static Object & getInstance() noexcept( noexcept( Object() ) );

    static void destroy() noexcept;

protected:
    /// Default constructor.
    constexpr Singleton() noexcept = default;

private:
    typedef std::unique_ptr< Object > Instance;


    static Instance myInstance;


    Singleton( Singleton< Object > & ) = delete;
    void operator =( Singleton< Object > & ) = delete;
};

#include "ely/patterns/Singleton.tpp"


} // namespace ::ely::patterns
} // namespace ::ely

#endif // SINGLETON_H
