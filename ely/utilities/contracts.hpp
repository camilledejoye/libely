#ifndef CONTRACTS_H
#define CONTRACTS_H

#include "ely/exceptions/ContractException.hpp"
#include "ely/config.hpp"

// Juste pour l'IDE, ces définitions seront prises en compte
#define REQUIRE( cond, text )
#define ENSURE( cond, text )
#define INVARIANT( cond, text )
#define PROTOTYPE_CHECK_INVARIANTS()
#define BEGIN_INVARIANT_BLOCK( className )
#define END_INVARIANT_BLOCK
#define CHECK_INVARIANTS()
#define CONTRACTS_CODE( inst )
#define BEGIN_INVARIANT_CRITICAL_SECTION( val )
#define END_INVARIANT_CRITICAL_SECTION

#ifdef CONTRACTS_USE_CLASSIC_ASSERT

#undef REQUIRE
#undef ENSURE
#undef INVARIANT

#define REQUIRE( cond, text )     ELY_ASSERT_MSG( ( cond ), text )
#define ENSURE( cond, text )      ELY_ASSERT_MSG( ( cond ), text )
#define INVARIANT( cond, text )   ELY_ASSERT_MSG( ( cond ), text )

#define CONTRACTS_ACTIVE

#endif // CONTRACT_USE_CLASSIC_ASSERT

#ifdef CONTRACTS_USE_ASSERT

#include <iostream>
#include <cstdlib>

#ifndef CONTRACTS_ASSERT_OSTREAM
#define CONTRACTS_ASSERT_OSTREAM std::cerr
#endif

namespace ely
{
namespace utilities
{
namespace contracts
{
inline void assert_failed( char const * contract_type_, char const * condition_, char const * contract_, char const * filename_, int const line_number_ )
{
    CONTRACTS_ASSERT_OSTREAM << "The following contract has been broken ( " << contract_type_ << " ) : " << contract_ << std::endl <<
    "File : " << filename_ << std::endl <<
    "Line : " << line_number_ << std::endl <<
    "Condition : " << condition_ << std::endl;

    std::abort();
}
} // namespace contracts
} // namespace ::ely::utilities
} // namespace ::ely

#undef REQUIRE
#undef ENSURE
#undef INVARIANT

#define REQUIRE( cond, text )     if ( ! ( cond ) ) ely::utilities::contracts::assert_failed( "pre-condition", # cond, text, __FILE__, __LINE__ )
#define ENSURE( cond, text )      if ( ! ( cond ) ) ely::utilities::contracts::assert_failed( "post-condition", # cond, text, __FILE__, __LINE__ )
#define INVARIANT( cond, text )   if ( ! ( cond ) ) ely::utilities::contracts::assert_failed( "invariant", # cond, text, file_, line_number_ )

#define CONTRACTS_ACTIVE

#endif // CONTRACT_USE_ASSERT

#ifdef CONTRACTS_USE_EXCEPTION

#undef REQUIRE
#undef ENSURE
#undef INVARIANT

#define REQUIRE( cond, text )     if ( ! ( cond ) ) throw ely::exceptions::ContractException( "pre-condition", # cond, text, __FILE__, __LINE__ )
#define ENSURE( cond, text )      if ( ! ( cond ) ) throw ely::exceptions::ContractException( "postcondition", # cond, text, __FILE__, __LINE__ )
#define INVARIANT( cond, text )   if ( ! ( cond ) ) throw ely::exceptions::ContractException( "invariant", # cond, text, file_, line_number_ )

#define CONTRACTS_ACTIVE

#endif //CONTRACTS_USE_EXCEPTION

#ifdef CONTRACTS_ACTIVE

#undef PROTOTYPE_CHECK_INVARIANTS
#undef BEGIN_INVARIANT_BLOCK
#undef END_INVARIANT_BLOCK
#undef CHECK_INVARIANTS
#undef CONTRACTS_CODE
#undef BEGIN_INVARIANT_CRITICAL_SECTION
#undef END_INVARIANT_CRITICAL_SECTION

#define PROTOTYPE_CHECK_INVARIANTS()            void ely_utilities_contracts_check_invariant( char const * file_, int const line_number_ ) const; \
    static bool ely_utilities_contracts_invariant_critical_section // 0 par défaut
#define BEGIN_INVARIANT_BLOCK( className )        bool className::ely_utilities_contracts_invariant_critical_section = false; \
    void className::ely_utilities_contracts_check_invariant( char const * file_, int const line_number_ ) const { ( void ) file_; ( void ) line_number_; \
                                                                                                                  if ( ! ely_utilities_contracts_invariant_critical_section ) {
#define END_INVARIANT_BLOCK                     } }

#define CHECK_INVARIANTS()                      ely_utilities_contracts_check_invariant( __FILE__, __LINE__ )

#define BEGIN_INVARIANT_CRITICAL_SECTION        this->ely_utilities_contracts_invariant_critical_section = true
#define END_INVARIANT_CRITICAL_SECTION          this->ely_utilities_contracts_invariant_critical_section = false

#define CONTRACTS_CODE( inst )                    inst

#endif // CONTRACTS_ACTIVE

#ifdef CONTRACTS_NO_PRECONDITIONS

#undef REQUIRE
#define REQUIRE( cond, text ) static_cast< void >( 0 )

#endif // CONTRACTS_NO_PRECONDITIONS

#ifdef CONTRACTS_NO_POSTCONDITIONS

#undef ENSURE
#define ENSURE( cond, text ) static_cast< void >( 0 )

#endif // CONTRACTS_NO_POSTCONDITIONS

#ifdef CONTRACTS_NO_INVARIANTS
#undef INVARIANT( cond, text )
#undef PROTOTYPE_CHECK_INVARIANTS
#undef BEGIN_INVARIANT_BLOCK
#undef END_INVARIANT_BLOCK
#undef CHECK_INVARIANTS

#define INVARIANT( cond, text )               static_cast< void >( 0 )
#define PROTOTYPE_CHECK_INVARIANTS()         static_cast< void >( 0 )
#define BEGIN_INVARIANT_BLOCK( className )
#define END_INVARIANT_BLOCK
#define CHECK_INVARIANTS()                  static_cast< void >( 0 )
#endif // CONTRACTS_NO_INVARIANTS

#endif // CONTRACTS_H
