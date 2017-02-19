/*!
 * \file Cloneable.h
 *
 * \author Ely
 *
 * \brief A generic implementation of the Prototype design pattern.
 */
#ifndef CLONEABLE_H
#define CLONEABLE_H


#include <memory>

#include "ely/traits/Type.hpp"


namespace ely
{
namespace patterns
{


template < class Object >
/*!
 * \brief The AbstractCloneable class
 *
 * The basic implementation needed by any polymorphic objects which need to be copy and is a base class.\n
 * The class of type \c Object becomes abstract.\n\n
 *
 * Implement it as follow :\n
 * \code
 * class MyClass : public ely::patterns::AbstractCloneable< MyClass >
 * {
 *     // Implementation
 * };
 * \endcode
 */
class AbstractCloneable
{
public:
    /// The type return by the \c clone() function.
    using Clone = ::std::unique_ptr< typename ::ely::traits::Type< Object >::Base >;

    /// Virtual destructor, for a polymorphic usage of the object.
    virtual ~AbstractCloneable() noexcept = default;

    /*!
     * \brief Create a polymorphic copy of the object.
     *
     * \return A pointer, of type \c Clone, to a polymorphic copy of the object.
     */
    virtual Clone clone() const = 0;
};

#define CLONE( Type )   virtual Clone clone() const override { return ::std::make_unique< Type >( *this ); }


} // namespace ::ely::patterns
} // namespace ::ely

#endif // CLONEABLE_H
