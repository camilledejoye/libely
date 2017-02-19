/*!
 * \file Composite.h
 *
 * \author Ely
 *
 * \brief A generic implementation of the composite design pattern.
 */
#ifndef COMPOSITE_H
#define COMPOSITE_H


#include <memory>
#include <list>

#include "ely/config.hpp"
#include "ely/predicates/IsNull.hpp"


/*
 * Bad idea to make this one in a generic form.
 */

namespace ely
{
namespace patterns
{

template < class > class Composite;


template < class Object >
/*!
 * \brief The Component class
 *
 * The basic implementation needed by any objects which are components.\n\n
 *
 * Implement it as follow :\n
 * \code
 * class MyComponent : public ely::patterns::Component< MyComponent >
 * {
 *     // Implementation
 * };
 * \endcode
 */
class Component
{
public:
    /// The type of a composite object of type \c Object.
    using CompositeType = Composite< Object >;
    
    Component() ELY_NOEXCEPT_OR_NOTHROW;
    /// A default virtual destructor for polymorphic uses.
    virtual ~Component() ELY_NOEXCEPT_OR_NOTHROW = default;


    ELY_CONSTEXPR_OR_INLINE bool hasParent() const ELY_NOEXCEPT_OR_NOTHROW;


    CompositeType * getParent() const ELY_NOEXCEPT_OR_NOTHROW;

protected:
    Component< Object > & setParent( CompositeType * aComposite ) ELY_NOEXCEPT_OR_NOTHROW;


private:
    friend class Composite< Object >;
    
    /// The parent of the component.
    CompositeType * myParent;
};



template < class ComponentType >
/*!
 * \brief The Composite class
 *
 * The basic implementation needed by any objects which are composits.\n
 * Example of use :\n
 * \code
 * class AbstractFile : public ::ely::patterns::Component< AbstractFile > {
 *      // Implementation
 * };
 *
 * class Directory : public ::ely::patterns::Composite< AbstractFile > {
 *     Directory( ... )
 *         : ::ely::patterns::Composite< Path >( ... )
 *     {}
 *
 *     // Implementation
 * };
 *
 * class File : public ::ely::patterns::Component< Directory > {
 *     File( ... )
 *         : ::ely::patterns::Composite< Path >( ... )
 *     {}
 *
 *     // Implementation
 * };
 * \endcode
 */
class Composite : public::ely::traits::Type< ComponentType >::Base
{
public:
    /// The type of a child.
    using Child = ::std::unique_ptr<  typename ::ely::traits::Type< ComponentType >::Base >;
    /// The type of the children list.
    using Children = ::std::list< Child >;


    template < typename ... Args >
    Composite( Args && ... someArgs );
    
    /// A default virtual destructor for polymorphic uses.
    virtual ~Composite() ELY_NOEXCEPT_OR_NOTHROW = default;
    
    
    Composite< ComponentType > & add( Child aChild );
    template < typename AComponent, typename ... Args >
    AComponent * create( Args && ... someArgs );


    ELY_CONSTEXPR_OR_INLINE Children const & getChildren() const ELY_NOEXCEPT_OR_NOTHROW;

private:
    Children myChildren;
};

#include "ely/patterns/Composite.tpp"


} // namespace ::ely::patterns
} // namespace ::ely

#endif // COMPOSITE_H
