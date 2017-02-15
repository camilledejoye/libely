/*!
 * \file Factory.h
 *
 * \author Ely
 *
 * \brief A generic implementation of the Factory deisgn pattern.
 */
#ifndef FACTORY_H
#define FACTORY_H


#include <map>
#include <string>
#include <memory>
#include <type_traits>


namespace ely
{
namespace patterns
{

template < class Object, typename Key = std::string >
/*!
 * \brief The Factory class
 *
 * A generic factory which can be use for any cloneable object.\n
 * This factory use the clone mechanism to create new instance of objects.
 * So it can only be used with objects which implements a function \c clone.\n\n
 *
 * Use it as follow :\n
 * \code
 * Class BaseClase : ely::patterns::AbstractCloneable< BaseClass >;
 * class DerivedClass : ely::patterns::Cloneable< BaseClass, DerivedClass >;
 *
 * typedef ely::patterns::Factory< BaseClass > BaseFactory;
 *
 * BaseFactory::add( "DerivedClass", new DerivedClass() );
 *
 * BaseFactory::CreatedObject newObjectOfBaseType = BaseFactory::create( "DerivedClass" );
 * std::shared_ptr< DerivedClass > newObjectOfDerivedType = std::dynamic_pointer_cast< DerivedClass >( BaseFactory::create( "DerivedClass" ) );
 * \endcode
 */
class Factory
{
public:
    /// The type of the object returned by \c create( const Key & ).
    typedef std::unique_ptr< Object > CreatedObject;


    static bool add( const Key & key, CreatedObject object );

    static CreatedObject create( const Key & key );

private:
    typedef typename std::map< Key, CreatedObject > Register;

    Factory() = delete;

    static Register myRegister;
};


#include "ely/patterns/Factory.tpp"


} // namespace ::ely::patterns
} // namespace ::ely


#endif // FACTORY_H
