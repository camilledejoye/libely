//------------------------------------------------------//
//                                                      //
//                  Component class                     //
//                                                      //
//------------------------------------------------------//
template < typename Object >
/*!
 * \brief Default constructor
 */
Component< Object >::Component() ELY_NOEXCEPT_OR_NOTHROW
    : myParent( nullptr )
{}

template < typename Object >
/*!
 * \brief Allow to know if the object has a parent.
 *
 * \return \c true if the object has a parent, \c false otherwise.
 */
ELY_CONSTEXPR_OR_INLINE bool Component< Object >::hasParent() const ELY_NOEXCEPT_OR_NOTHROW
{
    return ( ::ely::utilities::isNull( myParent ) ) ? false : true;
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
typename Component< Object >::CompositeType * Component< Object >::getParent() const ELY_NOEXCEPT_OR_NOTHROW
{
    return myParent;
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
Composite< ComponentType >::Composite( Args && ... someArgs )
    : ComponentType( std::forward< Args >( someArgs ) ... ),
    myChildren()
{}


template < typename ComponentType >
/*!
 * \brief Add an object which derives from \c ComponentType as a child.
 *
 * \param aChild A child to add to the composite.
 *
 * \return A reference on the composite.
 */
Composite< ComponentType > & Composite< ComponentType >::add( Child aChild )
{
    myChildren.emplace_back( ::std::move( aChild ) );
    myChildren.back()->setParent( this );

    return *this;
}

template < typename ComponentType >
template < typename AComponent, typename ... Args >
/*!
 * \brief Create a component of type \c AComponent and add it as a child of the composite.
 *
 * \param someArgs The list of arguments to forward to the constructor of \c AComponent.
 *
 * \return A raw pointer to the newly created child.
 */
AComponent * Composite< ComponentType >::create( Args && ... someArgs )
{
    ELY_ASSERT_MSG( ( ::std::is_base_of< ComponentBase, AComponent >::value ),
                    "AComponent must be of type ComponentBase" );
    
    myChildren.emplace_back( ::std::make_unique< AComponent >( ::std::forward< Args >( someArgs ) ... ) );
    
    AComponent * createdChild = static_cast< AComponent * >( myChildren.back().get() );
    createdChild->setParent( this );
    
    return createdChild;
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
