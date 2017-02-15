/*!
 * \file Slot.tpp
 * 
 * \author Ely
 * 
 * \brief Source file of the Slot class.
*/


namespace ely
{
namespace signals_slots
{


//------------------------------------------//
//                                          //
//             Public functions             //
//                                          //
//------------------------------------------//

template < typename ... Args >
template < class Object, typename ... FArgs >
/*!
 * \brief Bind a slot to a member function.
 * 
 * \param object The instance of the object owning the member function
 * \param slotFunction The function pointer pointing to the member function to call
 * when a signal is emit.
 */
void Slot< Args ... >::bind( void( Object::*slotFunction )( FArgs ... ), Object & object )
{
//    mySlotFunction = detail::bindAutoPlaceholders( ::std::function< void( Object &, FArgs ... ) >{ slotFunction },
//                                                  object );
}

template < typename ... Args >
void Slot< Args ... >::bind( ::std::function< void( Args ... ) > slotFunction )
{
    mySlotFunction = ::std::move( slotFunction );
}


template < typename ... Args >
/*!
 * \brief operator ()
 * 
 * Call the function bound to the slot.
 * 
 * \param args The information to forward to the bound function.
 */
inline void Slot< Args ... >::operator ()( Args ... args ) const
{
    if ( mySlotFunction )
    {
        mySlotFunction( args ... );
    }
}


} // namespace ::ely::signals_slots
} // namespace ::ely
