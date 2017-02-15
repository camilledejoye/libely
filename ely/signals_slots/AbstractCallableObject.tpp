/*!
 * \file AbstractCallableObject.tpp
 * 
 * \author Ely
 * 
 * \brief Source file of the AbstractCallableObject class.
*/
#include <algorithm>


//#include "ely/signals_slots/Signal.hpp"


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
/*!
 * \brief Destructor
 * 
 * When a callable object is destroyed it tells to every connected callable object to remove it.
 */
AbstractCallableObject< Args ... >::~AbstractCallableObject()
{
    for ( auto caller : myCallerObjects )
    {
        caller->removeCalled( *this );
    }
}


//------------------------------------------//
//                                          //
//             Private functions            //
//                                          //
//------------------------------------------//

template < typename ... Args >
/*!
 * \brief Add a callable object to the list of connected callable objects.
 * 
 * \param callableObject The callable object to add.
 */
void AbstractCallableObject< Args ... >::addCaller( Signal< Args ... > & caller )
{
    if ( myCallerObjects.end() == ::std::find( myCallerObjects.begin(), myCallerObjects.end(), &caller ) )
    {
        myCallerObjects.push_back( &caller );
    }
}

template < typename ... Args >
/*!
 * \brief Remove a callable object from the list of connected callable objects.
 * 
 * \param callableObject The callable object to remove.
 */
void AbstractCallableObject< Args ... >::removeCaller( Signal< Args ... > & caller )
{
    auto it = ::std::find( myCallerObjects.begin(),
                           myCallerObjects.end(),
                           &caller );
    
    if ( myCallerObjects.end() != it )
    {
        myCallerObjects.erase( it );
    }
}


} // namespace ::ely::signals_slots
} // namespace ::ely
