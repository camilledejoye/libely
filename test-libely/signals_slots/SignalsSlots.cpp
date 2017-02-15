#include <boost/test/unit_test.hpp>


#include <iostream>


#include <ely/signals_slots/Signal.hpp>
#include <ely/signals_slots/Slot.hpp>


using ::ely::signals_slots::Signal;
using ::ely::signals_slots::Slot;
using ::ely::signals_slots::connect;

class Server
{
public:
    void connect()
    {
        connected( true );
    }
    void disconnect()
    {
        connected( false );
        disconnected();
    }


    Signal< bool > connected;
    Signal< > disconnected;
};

class PeerManager
{
public:
    PeerManager()
    {
        serverConnected.bind( &PeerManager::slotServerConnected, *this );
        serverDisconnected.bind( &PeerManager::slotServerDisconnected, *this );
    }

    Slot< bool > serverConnected;
    Slot< > serverDisconnected;

private:
    void slotServerConnected( bool connected )
    {
        ::std::cout << ::std::boolalpha << "Server connected : " << connected << ::std::endl;

        myN = 1;
    }

    void slotServerDisconnected( void )
    {
        ::std::cout << "PeerManager : server disconnected" << ::std::endl;

        myN = 2;
    }

    int myN;
};

void slotNonMemberFunction()
{
    ::std::cout << "slotNonMemberFunction()" << ::std::endl;
}

struct Client
{
    Signal< > disconnected;
};

class ClientWindow
{
public:
    ClientWindow()
    {
        disconnected.bind( &ClientWindow::slotDisconnected, *this );
    }

    Slot< > disconnected;
    Slot< > unboundSlot;

private:
    void slotDisconnected()
    {
        ::std::cout << "You are now disconnected." << ::std::endl;
    }
};


BOOST_AUTO_TEST_SUITE( patterns )

BOOST_AUTO_TEST_CASE( signals_slots )
{
    Server server;
    Client client;
    ClientWindow clientWindow;

    {
        Slot< > nonMemberSlot;
        nonMemberSlot.bind( slotNonMemberFunction );

        PeerManager peerManager;

        connect( server.connected, peerManager.serverConnected );
        connect( server.connected, peerManager.serverConnected ); // Do nothing

        connect( server.disconnected, peerManager.serverDisconnected );

        connect( server.disconnected, client.disconnected );
        connect( client.disconnected, clientWindow.unboundSlot ); // Do nothing
        connect( client.disconnected, clientWindow.disconnected );
        connect( client.disconnected, nonMemberSlot );

        server.connect(); // Print : Server connected : true
        server.disconnect();    // Print :  Server connected : false
                                //          PeerManager : server disconnected
                                //          You are now disconnected.
                                //          slotNonMemberFunction()
    }

    server.connect(); // Print nothing
    server.disconnect(); // Print : You are now disconnected.
}

BOOST_AUTO_TEST_SUITE_END()
