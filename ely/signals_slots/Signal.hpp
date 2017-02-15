/*!
 * \file Signal.hpp
 *
 * \author Ely
 *
 * \brief Header file of the Signal class.
 */
#ifndef SIGNAL_HPP
#define SIGNAL_HPP


#include <vector>


#include "ely/signals_slots/AbstractCallableObject.hpp"
#include "ely/signals_slots/connect.hpp"


namespace ely
{
namespace signals_slots
{


template < typename ... Args >
/*!
 * \brief The Signal class
 *
 * Part of the signal/slot system that represents a signal.\n\n
 * A signal is a template object defined by its template parameters.\n
 * It can be connected to any slot with the same template parameters.\n
 * Each time a signal is emit, with the function <em>operator ()</em>,
 *      every slot connected are called.
 */
class Signal final : public AbstractCallableObject< Args ... >
{
public:
    friend AbstractCallableObject< Args ... >::~AbstractCallableObject();
    friend void connect< Args ... >( Signal< Args ... > &, AbstractCallableObject< Args ... > & );
    friend void disconnect< Args ... >( Signal< Args ... > &, AbstractCallableObject< Args ... > & );


    ~Signal();


    void operator ()( Args ... args ) const override;

private:
    void addCalled( AbstractCallableObject< Args ... > & called );
    void removeCalled( AbstractCallableObject< Args ... > & called );


    ::std::vector< AbstractCallableObject< Args ... > * > myCalledObjects;
};


} // namespace ::ely::signals_slots
} // namespace ::ely


#include "ely/signals_slots/Signal.tpp"


#endif // SIGNAL_HPP
