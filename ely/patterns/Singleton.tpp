template < typename Object >
typename Singleton< Object >::Instance Singleton< Object >::myInstance = nullptr;

template < typename Object >
/*!
 * \brief Acces to the object.
 * 
 * If the object isn't instantiated yet, it's instantiated and returned.
 * 
 * \return A reference on the object.
 */
Object & Singleton< Object >::getInstance() noexcept( noexcept( Object() ) )
{
    if ( utilities::isNull( myInstance ) )
    {
        myInstance = Instance( new Object );
    }
    
    return *myInstance;
}


template < typename Object >
/*!
 * \brief Destroy the object.
 * 
 * Destroy the current instance of the object in order to rebuild it in the next call of \c getInstance().
 */
void Singleton< Object >::destroy() noexcept
{
    if ( !utilities::isNull( myInstance ) )
    {
        myInstance.reset( nullptr );
    }
}
