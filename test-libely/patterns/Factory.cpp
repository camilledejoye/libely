#include <boost/test/unit_test.hpp>

#include <ely/patterns/Factory.hpp>
#include <ely/patterns/Cloneable.hpp>

using ::std::string;
using ::std::unique_ptr;

BOOST_AUTO_TEST_SUITE( patterns )

class Base : public ely::patterns::AbstractCloneable< Base >
{
public:
    virtual ~Base() {}

    virtual string toString() const
    {
        return "Base";
    }
};

class Derived_1 : public Base // : public ely::patterns::Cloneable< Base, Derived_1 >
{
public:
    string toString() const
    {
        return Base::toString() + " <- Derived_1";
    }

    CLONE( Derived_1 )
};

class Derived_2 : public Derived_1 // : public ely::patterns::Cloneable< Derived_1, Derived_2 >
{
public:
    string toString() const
    {
        return Derived_1::toString() + " <- Derived_2";
    }

    CLONE( Derived_2 )
};

class A
{
public:
    virtual std::unique_ptr< A > clone() const = 0;

    virtual ~A() {}

    virtual string toString() const
    {
        return "A";
    }
};

class Component : public A
{
public:
    std::unique_ptr< A > clone() const override
    {
        return std::unique_ptr< Component >( new Component( *this ) );
    }


    string toString() const
    {
        return A::toString() + " <- B";
    }
};

class Composite : public Component
{
public:
    std::unique_ptr< A > clone() const override
    {
        return std::unique_ptr< Composite >( new Composite( *this ) );
    }


    string toString() const
    {
        return Component::toString() + " <- C";
    }
};

BOOST_AUTO_TEST_CASE( factory )
{
    typedef ely::patterns::Factory< Base > BaseFactory;

    BOOST_CHECK_EQUAL( BaseFactory::add( "Derived_1", unique_ptr< Derived_1 >( new Derived_1() ) ), true );
    BOOST_CHECK_EQUAL( BaseFactory::add( "Derived_2", BaseFactory::CreatedObject( new Derived_2() ) ), true );

    BOOST_CHECK_EQUAL( BaseFactory::add( "Derived_1", unique_ptr< Derived_1 >( new Derived_1() ) ), false );

    BOOST_CHECK_EQUAL( BaseFactory::create( "Derived_1" )->toString(), "Base <- Derived_1" );
    BOOST_CHECK_EQUAL( BaseFactory::create( "Derived_2" )->toString(), "Base <- Derived_1 <- Derived_2" );

    typedef ely::patterns::Factory< Derived_1 > Derived_1Factory;

    BOOST_CHECK_EQUAL( Derived_1Factory::add( "Derived_1", unique_ptr< Derived_1 >( new Derived_1() ) ), true );
    BOOST_CHECK_EQUAL( Derived_1Factory::add( "Derived_2", unique_ptr< Derived_2 >( new Derived_2() ) ), true );
    BOOST_CHECK_EQUAL( Derived_1Factory::add( "Derived_2", unique_ptr< Derived_2 >( new Derived_2() ) ), false );

    typedef ely::patterns::Factory< A > AFactory;
    BOOST_CHECK_EQUAL( AFactory::add( "B", unique_ptr< Component >( new Component() ) ), true );
    BOOST_CHECK_EQUAL( AFactory::add( "C", unique_ptr< Composite >( new Composite() ) ), true );

    BOOST_CHECK_EQUAL( AFactory::add( "B", unique_ptr< Component >( new Component() ) ), false );

    BOOST_CHECK_EQUAL( AFactory::create( "B" )->toString(), "A <- B" );
    BOOST_CHECK_EQUAL( AFactory::create( "C" )->toString(), "A <- B <- C" );
}

BOOST_AUTO_TEST_SUITE_END()
