template < class Object, typename Key >
typename Factory< Object, Key >::Register Factory< Object, Key >::myRegister = Register();


template < class Object, typename Key >
/*!
 * \brief Register an object of base \c Object.
 * 
 * Register an object of base \c Object in order to be cloned later.\n
 * A key is unique, so if you try to add an object with an already used key,
 * the object will not be added and the function will return \c false.\n\n
 * 
 * The objects are created by copy using their \c clone() function.\n
 * So they must implement this a \c clone() function and it has to return
 * an object of type <em>std::unique_ptr< Object ></em>.
 * 
 * \param key       The key using to identify the object.
 * \param object    The object which will be clone to create a new instance.
 * 
 * \return \c true if the pair \c Key, \c Object was added, \c false otherwise.
 */
bool Factory< Object, Key >::add( const Key & key, CreatedObject object )
{
    // Create compile-time error if Object has no member clone
    // And abort if it's not a function
    static_assert( std::is_member_function_pointer< decltype( &Object::clone ) >::value,
                   "Object must have a clone function." );
    
    // NOTICE : can't do this on a pure virtual function
//    static_assert( std::is_same< typename std::result_of< decltype( &Object::clone )( Object ) >::type,
//                                 CreatedObject >::value,
//                   "The function Object::clone() must return an object of type : std::unique_ptr< Object > .");
    
    
    bool isAdded = false;

    if ( myRegister.end() == myRegister.find( key ) )
    {
        isAdded = myRegister.emplace( key, move( object ) ).second;
    }

    return isAdded;
}

template < class Object, typename Key >
/*!
 * \brief Create a new instance of an object.
 * 
 * Create a new instance of the object corresponding to \c key.\n
 * If the key is invalid, a null \c CreatedObject will be returned.
 * 
 * \param key   The key corresponding to the object to create.
 * 
 * \return An object of type \c CreatedObject pointing to the new
 * created object or \c nullptr if the key doesn't exist.
 */
typename Factory< Object, Key >::CreatedObject Factory< Object, Key >::create( const Key & key )
{
    CreatedObject newObject;

    typename Register::const_iterator it = myRegister.find( key );

    if ( myRegister.end() != it )
    {
        // No need to move, a function return value is a rvalue
        newObject = it->second->clone();
    }

    return newObject;
}
