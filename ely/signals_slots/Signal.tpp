/*!
 * \file Signal.tpp
 * 
 * \author Ely
 * 
 * \brief Source file of the Signal class.
*/
#include <algorithm>


namespace ely
{
namespace signals_slots
{


//------------------------------------------//
//                                          //
//      Constructors & Destructors          //
//                                          //
//------------------------------------------//

template < typename ... Args >
Signal< Args ... >::~Signal()
{
    for ( auto called : myCalledObjects )
    {
        called->removeCaller( *this );
    }
}


//------------------------------------------//
//                                          //
//             Public functions             //
//                                          //
//------------------------------------------//

template < typename ... Args >
/*!
 * \brief operator ()
 * 
 * Call every connected signals/slots with the needed information.
 * 
 * \param args  The information to transmit to the signals/slots.
 */
void Signal< Args ... >::operator ()( Args ... args ) const
{
    for ( auto called : myCalledObjects )
    {
        (*called)( args ... );
    }
}


//------------------------------------------//
//                                          //
//             Private functions            //
//                                          //
//------------------------------------------//

template < typename ... Args >
void Signal< Args ... >::addCalled( AbstractCallableObject< Args ... > & called )
{
    if ( myCalledObjects.end() == ::std::find( myCalledObjects.begin(), myCalledObjects.end(), &called ) )
    {
        myCalledObjects.push_back( &called );
    }
}

template < typename ... Args >
void Signal< Args ... >::removeCalled( AbstractCallableObject< Args ... > & called )
{
    auto it = ::std::find( myCalledObjects.begin(),
                           myCalledObjects.end(),
                           &called );
    
    if ( myCalledObjects.end() != it )
    {
        myCalledObjects.erase( it );
    }
}


} // namespace ::ely::signals_slots
} // namespace ::ely
