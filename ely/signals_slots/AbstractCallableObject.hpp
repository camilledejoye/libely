/*!
 * \file AbstractCallableObject.hpp
 *
 * \author Ely
 *
 * \brief Header file of the AbstractCallableObject class.
 */
#ifndef ABSTRACT_CALLABLE_OBJECT_HPP
#define ABSTRACT_CALLABLE_OBJECT_HPP


#include <vector>


#include "ely/signals_slots/connect.hpp"


namespace ely
{
namespace signals_slots
{


template < typename ... Args > class Signal;


template < typename ... Args >
/*!
 * \brief The AbstractCallableObject class
 *
 * The base implementation for a signal or a slot.\n
 * In this system a signal and a slot are callable objects.\n
 * Their purpose is to call the appropriate function when it is asked.\n\n
 *
 * A signal is an object with the responsibility to call every callable objects
 * which are connected to it.\n
 * A signal can be connected to slot or to another signal.\n\n
 *
 * A slot is an object with the responsibility to call a function to handle a signal.\n
 * To do that a slot must be bound to another function.\n
 * If a slot isn't bound, it does nothing.\n\n
 *
 * The signals/slots connected to a signal are called in the same order
 * as they were connected.
 *
 * Example of use :
 * \code
 * #include <iostream>
 *
 *
 * #include <ely/signals_slots/SignalsSlots.hpp>
 *
 *
 * using ::ely::signals_slots::Signal;
 * using ::ely::signals_slots::Slot;
 *
 *
 * struct Message
 * {
 *     ::std::string text;
 * };
 *
 * struct Server
 * {
 *     Signal<> connected;
 *     Signal< const Message & > newMessage;
 *
 *
 *     void connect()
 *     {
 *         // Implementation ...
 *
 *         connected();
 *     }
 *
 *     void send( const ::std::string & text )
 *     {
 *         // Implementation ...
 *
 *         newMessage( Message{ text } );
 *     }
 * };
 *
 * class Client
 * {
 * public :
 *     Client()
 *     {
 *         serverConnected.bind( &Client::slotServerConnected, *this );
 *         printMessage.bind( &Client::slotPrintMessage, *this );
 *     }
 *
 *
 *     Slot<> serverConnected;
 *     Slot< const Message & > printMessage;
 *
 * private :
 *     void slotServerConnected()
 *     {
 *         ::std::cout << "Server connected" << ::std::endl;
 *     }
 *
 *     void slotPrintMessage( const Message & message )
 *     {
 *         ::std::cout << message.text << ::std::endl;
 *     }
 * };
 *
 *
 * int main()
 * {
 *     Server server;
 *     Client client;
 *
 *     ely::connect( server.connected, client.serverConnected );
 *     ely::connect( server.newMessage, client.printMessage );
 *
 *     server.connect(); // Print : Server connected
 *     server.send( "Server message" ); // Print : Server message
 *     client.printMessage( Message{ "Other message" } ); // Print : Other message
 *
 *     return 0;
 * }
 * \endcode
 */
class AbstractCallableObject
{
public:
    friend class Signal< Args ... >;
    friend void connect< Args ... >( Signal< Args ... > &, AbstractCallableObject< Args ... > & );
    friend void disconnect< Args ... >( Signal< Args ... > &, AbstractCallableObject< Args ... > & );



    virtual ~AbstractCallableObject();


    /*!
     * \brief operator ()
     *
     * Call the appropriate function for the corresponding task.
     *
     * \param args
     */
    virtual void operator ()( Args ... args ) const = 0;

private:
    void addCaller( Signal< Args ... > & caller );
    void removeCaller( Signal< Args ... > & caller );


    ::std::vector< Signal< Args ... > * > myCallerObjects;
};


} // namespace ::ely::signals_slots
} // namespace ::ely


#include "ely/signals_slots/AbstractCallableObject.tpp"


#endif // ABSTRACT_CALLABLE_OBJECT_HPP
