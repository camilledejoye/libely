/*!
 * \file Slot.hpp
 *
 * \author Ely
 *
 * \brief Header file of the Slot class.
 */
#ifndef SLOT_HPP
#define SLOT_HPP


#include <functional>


#include "ely/signals_slots/AbstractCallableObject.hpp"


namespace ely
{
namespace signals_slots
{


template < typename ... Args >
/*!
 * \brief The Slot class
 *
 * Part of the signal/slot system that represent a signal.\n\n
 * A slot is a template object defined by its template parameters.\n
 * It can be connected to any signal with the same template parameters.\n
 * Each time a signal connected to a slot is emit, the function bound to
 * the corresponding slot is called.
 */
class Slot final : public AbstractCallableObject< Args ... >
{
public:
    template < class Object, typename ... FArgs >
    void bind( void ( Object::* slotFunction )( FArgs ... ), Object & object );
    void bind( ::std::function< void( Args ... ) > slotFunction );


    void operator ()( Args ... args ) const override;

private:
    ::std::function< void( Args ... ) > mySlotFunction;
};


} // namespace ::ely::signals_slots
} // namespace ::ely


#include "ely/signals_slots/Slot.tpp"


#endif // SLOT_HPP
