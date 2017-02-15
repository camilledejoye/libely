/*!
 * \file IntegerSequence.hpp
 *
 * \author ely
 *
 * \brief Header file for the IntegerSequence struc.
 *
 * Implement an equivalent of integer_sequence for c++11.
 */

#ifndef INTEGER_SEQUENCE_HPP
#define INTEGER_SEQUENCE_HPP


#include <cstddef>


namespace ely
{
namespace utilities
{


/// A sequence of integer values.
template < ::std::size_t ... Indices >
struct IntegerSequence
{
    /// The type of each indice.
    typedef ::std::size_t Type;


    /*!
     * \brief Returns the number of elements in \c Indicies.
     *
     * \return The number of element in \c Indices.
     */
    static constexpr Type size()
    {
        return sizeof ... ( Indices );
    }
};

namespace detail
{


template < ::std::size_t From,
           ::std::size_t Count,
           ::std::size_t ... Indices >
/// Make a sequence of integer from \c From to <em>From + Count - 1</em>.
struct MakeIntegerSequence
    : MakeIntegerSequence< From + 1, Count - 1, From, Indices ... > // Concat From and Indices ...
{};
template < ::std::size_t From,
           ::std::size_t ... Indices >
struct MakeIntegerSequence< From, 0, Indices ... >
    : IntegerSequence< Indices ... >
{};


} // namespace ::ely::utilities::detail


template < ::std::size_t From, ::std::size_t Count >
/// Helper to make a sequence of integer from \c From to <em>From + Count - 1</em>.
using makeIntegerSequence = detail::MakeIntegerSequence< From, Count >;

template < ::std::size_t N >
/// Helper to make a sequence of integer from \c 0 to \c N .
using makeIntegerSequenceTo = makeIntegerSequence< 0, N >;

template < typename ... Args >
/// Helper to make a sequence of integer from \c 0 to <em>sizeof...( Args )</em>.
using makeIntegerSequenceFor = makeIntegerSequence< 0, sizeof ... ( Args ) >;



} // namespace ::ely::utilities
} // namespace ::ely


#endif // INTEGER_SEQUENCE_HPP
