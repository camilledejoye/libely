//------------------------------------------------------//
//                                                      //
//                  Component class                     //
//                                                      //
//------------------------------------------------------//
template < typename Object >
/*!
 * \brief Allow to know if the object has a parent.
 *
 * \return \c true if the object has a parent, \c false otherwise.
 */
ELY_CONSTEXPR_OR_INLINE bool Component< Object >::hasParent() const ELY_NOEXCEPT_OR_NOTHROW
{
    return ( ::ely::utilities::isNull( myParent ) ) ? true : false;
}

template < typename Object >
/*!
 * \brief Accessor
 *
 * You must call \sa Component< Object >::hasParent() before calling this method.\n
 * If you don't, it's behavior will be unpredictable.
 *
 * \return A reference to the parent object.
 */
typename Component< Object >::CompositeType & Component< Object >::getParent() const ELY_NOEXCEPT_OR_NOTHROW
{
    return *myParent;
}


template < typename Object >
/*!
 * \brief Accessor
 *
 * Defines the parent of the object.
 *
 * \param composite The new parent of the object.
 */
Component< Object > & Component< Object >::setParent( typename Component< Object >::CompositeType * aComposite ) ELY_NOEXCEPT_OR_NOTHROW
{
    myParent = aComposite;

    return *this;
}




//------------------------------------------------------//
//                                                      //
//                  Composite class                     //
//                                                      //
//------------------------------------------------------//
template < typename ComponentType >
template < typename ... Args >
/*!
 * \brief Constructor
 *
 * Use to call the constructor of \c ComponentType.
 *
 * \param args  The arguments to provide to the constructor of \c ComponentType.
 */
Composite< ComponentType >::Composite( Args && ... args )
    : ComponentType( std::forward< Args >( args ) ... ),
    myChildren()
{}


template < typename ComponentType >
template < typename AComponent >
/*!
 * \brief Add an object which derives from \c ComponentType as a child.
 *
 * \param component The new component to add, it can be a component or a composite.
 *
 * \return A reference on the component added.
 */
Composite< ComponentType > & Composite< ComponentType >::add( AComponent const & aComponent )
{
    ELY_ASSERT_MSG( ( ::std::is_base_of< CompositeType, AComponent >::value ),
                    "AComponent must be of type CompositeType" );
    ELY_ASSERT_MSG( ::std::is_move_constructible< AComponent >::value,
                    "AComponent must be move constructible" );

    AComponent * t = new AComponent( ::std::move( aComponent ) );
    //Child newChild( new AComponent( ::std::move( aComponent ) ) );

    //myChildren.emplace_back( newChild.release() );

    //myChildren.back()->setParent( this );

    return *this;
}

template < typename ComponentType >
template < typename AComponent >
/*!
 * \brief Remove a child from the composite.
 *
 * \param component The object to remove.
 *
 * \return \c true if any object has been removed, \c false otherwise.
 */
Composite< ComponentType > & Composite< ComponentType >::remove( typename ::ely::traits::Type< AComponent const > & aChildToRemove )
{
    ELY_ASSERT_MSG( ( ::std::is_base_of< CompositeType, AComponent >::value ),
                    "AComponent must be of type CompositeType" );

    myChildren.remove_if(   [ &aChildToRemove ] ( Child const & aChild )->bool
                            {
                                return *aChild == aChildToRemove;
                            } );

    return *this;
}


template < typename ComponentType >
/*!
 * \brief Accessor
 *
 * \return All the children of the object.
 */
ELY_CONSTEXPR_OR_INLINE typename Composite< ComponentType >::Children const & Composite< ComponentType >::getChildren() const ELY_NOEXCEPT_OR_NOTHROW
{
    return myChildren;
}
