#include <boost/test/unit_test.hpp>

#include <string>

#include <ely/patterns/Cloneable.hpp>


class Base : public ely::patterns::AbstractCloneable< Base >
{
public:
    virtual ~Base() {}

    virtual std::string toString() const
    {
        return "Base";
    }
};

class Derived_1 : public Base // : public ely::patterns::Cloneable< Base, Derived_1 >
{
public:
    std::string toString() const
    {
        return Base::toString() + " <- Derived_1";
    }

    CLONE( Derived_1 )
};


class Derived_2 : public Derived_1 // : public ely::patterns::Cloneable< Derived_1, Derived_2 >
{
public:
    std::string toString() const
    {
        return Derived_1::toString() + " <- Derived_2";
    }

    CLONE( Derived_2 )
};
BOOST_AUTO_TEST_SUITE( patterns )

BOOST_AUTO_TEST_CASE( cloneable )
{
    Base * base_1 = new Derived_1;
    Base * base_2 = new Derived_2;

    std::unique_ptr< Base > copy_b1 = base_1->clone();
    Base::Clone copy_b21 = base_2->clone();
    //std::unique_ptr< Derived_2 > copy_b22 = std::dynamic_pointer_cast< Derived_2 >( base_2->clone() );

    BOOST_CHECK_EQUAL( copy_b1->toString(), "Base <- Derived_1" );
    BOOST_CHECK_EQUAL( copy_b21->toString(), "Base <- Derived_1 <- Derived_2" );
    //BOOST_CHECK_EQUAL( copy_b22->toString(), "Base <- Derived_1 <- Derived_2" );

    delete base_1;
    delete base_2;
}

BOOST_AUTO_TEST_SUITE_END()
