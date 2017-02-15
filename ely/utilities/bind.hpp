/*!
 * \file bind.hpp
 *
 * \author Ely
 *
 * \brief Header file for the bind function.
 *
 * Provides a function \c bind which can bound a function with
 * automatic placeholders.
 */

#ifndef BIND_HPP
#define BIND_HPP

#include <functional>


#include "ely/utilities/IntegerSequence.hpp"


namespace ely
{
namespace utilities
{


namespace detail
{


/// Some placeholders to use with variadic templates.
template < ::std::size_t N > struct PlaceHolders {};


template< ::std::size_t ... Indices,
          typename Function,
          typename ... BindArgs >
/// \c bind function using an integer sequence to create as many
/// placeholders as needed.
auto bind( utilities::IntegerSequence< Indices ... >,
           const Function &function,
           BindArgs && ... bindArgs )
->decltype( ::std::bind( function,
                         ::std::forward< BindArgs >( bindArgs ) ...,
                         PlaceHolders< Indices >{} ... ) )
{
    return ::std::bind( function,
                        ::std::forward< BindArgs >( bindArgs ) ...,
                        PlaceHolders< Indices >{} ... );
}


/// Helper used to get the number of arguments waited by a function.
struct FunctionArgs
{
    template < typename Return, typename ... Args >
    /// Overload for a non-member function.
    static constexpr ::std::size_t size( Return ( * )( Args ... ) )
    {
        return sizeof ... ( Args );
    }

    template < typename Return, typename Object, typename ... Args >
    /// Overload for a non-constant member function.
    static constexpr ::std::size_t size( Return ( Object::* )( Args ... ) )
    {
        return sizeof ... ( Args );
    }

    template < typename Return, typename Object, typename ... Args >
    /// Overload for a constant member function.
    static constexpr ::std::size_t size( Return ( Object::* )( Args ... ) const )
    {
        return sizeof ... ( Args );
    }

};


template < typename Function, typename ... BindArgs >
/*!
 * \brief Helper used to get the number of arguments to automatically bind.
 *
 * Compute the number of arguments by subtracting the number of arguments
 * waiting by the function of type \p Function from the number of arguments
 * provided in \p BindArgs.\n
 * If the function is a member function, the result of the subtraction is
 * incremented by 1.
 *
 * \tparam Function The type of the function to bind.
 * \tparam BindArgs All the arguments to bind to the function.
 */
struct NumberOfPlaceHolders
{
    /// The number of arguments to automatically bind.
    static constexpr ::std::size_t value = ( ::std::is_member_function_pointer< Function >::value ) ?
                                           FunctionArgs::size( Function() ) + 1 - sizeof ... ( BindArgs ) :
                                           FunctionArgs::size( Function() ) - sizeof ... ( BindArgs );
};


} // namespace ::ely::detail


template< typename Function,
          typename ... BindArgs,
          ::std::size_t diffArgs = detail::NumberOfPlaceHolders< Function, BindArgs ... >::value >
/*!
 * \brief Binds a function with automatic placeholders.
 *
 * Binds the function \p function with the arguments \p bindArgs and
 * as many placeholders as needed to respect the function's signature.\n\n
 * Basically it's just a function which call ::std::bin and provides
 * the right number of arguments, including placeholders.
 *
 * \tparam Function The type of the function to bind.
 * \tparam BindArgs The types of the arguments to bind to the function.
 *
 * \param function The function to bind.
 * \param bindArgs The arguments to bind to the function.
 *
 * \return A function object of unspecified type T, as the return
 * value of ::std::bind
 *
 * \note The arguments to bind are copied or moved by the function
 * \c ::std::bind.
 * The only way to pass them by reference is to wrappe them whith
 * ::std::ref or ::std::cref.\n\n
 * In the case of a non-member or static member function, the
 * address-of  operator ( \c & ) must be use, ex. :
 * <em>bind( &nonMemberFunction, ... )</em>
 *
 * \example bind.cpp
 * This is an exemple of how to use the \c bind function.
 *
 * \sa ::std::bind
 */
auto bind( const Function &function,
           BindArgs && ... bindArgs )
->decltype( detail::bind( utilities::makeIntegerSequence< 1, diffArgs >{},
                          function,
                          ::std::forward< BindArgs >( bindArgs ) ... ) )
{
    return detail::bind( utilities::makeIntegerSequence< 1, diffArgs >{},
                         function,
                         ::std::forward< BindArgs >( bindArgs ) ... );
}


} // namespace ::ely::utilities
} // namespace ::ely


namespace std
{


template < ::std::size_t N >
/*!
 * \brief Specialization of is_placeholder
 *
 * Specialize is_placeholder for PlaceHolders< 0 >, PlaceHolders< 1 >, PlaceHolders< ... >, PlaceHolders< N >.
 */
struct is_placeholder< ::ely::utilities::detail::PlaceHolders< N > >
    : integral_constant< int, N >
{};


} // namespace ::std


#endif // BIND_HPP
