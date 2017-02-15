#ifndef CONNECT_HPP
#define CONNECT_HPP


namespace ely
{
namespace signals_slots
{


template < typename ... Args > class Signal;
template < typename ... Args > class AbstractCallableObject;


template < typename ... SignalArgs, typename ... CallableArgs >
void connect( Signal< SignalArgs ... > & aSignal, AbstractCallableObject< CallableArgs ... > & callableObject );

template < typename ... SignalArgs, typename ... CallableArgs >
void disconnect( Signal< SignalArgs ... > & aSignal, AbstractCallableObject< CallableArgs ... > & callableObject );


} // namespace ::ely::signals_slots
} // namespace ::ely


#include "ely/signals_slots/connect.tpp"

#endif // CONNECT_HPP
