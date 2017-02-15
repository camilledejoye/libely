namespace ely
{
namespace signals_slots
{


template < typename ... Args >
void connect( Signal< Args ... > & aSignal, AbstractCallableObject< Args ... > & callableObject )
{
    aSignal.addCalled( callableObject );
    callableObject.addCaller( aSignal );
}

template < typename ... Args >
void disconnect( Signal< Args ... > & aSignal, AbstractCallableObject< Args ... > & callableObject )
{
    aSignal.removeCalled( callableObject );
    callableObject.removeCaller( aSignal );
}


} // namespace ::ely::signals_slots
} // namespace ::ely
