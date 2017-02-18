#ifndef COFNIG_H
#define COFNIG_H

#include <boost/config.hpp>
#include <boost/system/api_config.hpp>


#if ( __cplusplus >= 201103L )

#   define ELY_USING_CXX11

#endif


#if defined ( ELY_USING_CXX11 )

#   define ELY_ASSERT_MSG( test, message )  static_assert( test, message )
#   define ELY_ASSERT( test )               ELY_ASSERT_MSG( test, #test )

#else

#   include <cassert>

#   define ELY_ASSERT( test )       assert( test )
#   define ELY_ASSERT_MSG( test )   ELY_ASSERT( test )
#endif


#if defined ( BOOST_WINDOWS_API )

#   define ELY_USING_WIN32_API

#else

#   define ELY_POSIX_API

#endif // windows API


#if ! defined ( BOOST_NO_CXX11_FINAL )

#   define ELY_FINAL    final
#   define ELY_OVERRIDE override

#else

#   define ELY_FINAL
#   define ELY_OVERRIDE

#endif // final && override


#if ! defined ( BOOST_NO_CXX11_CONSTEXPR )

#   define ELY_CONSTEXPR            constexpr
#   define ELY_CONSTEXPR_OR_CONST   ELY_CONSTEXPR
#   define ELY_CONSTEXPR_OR_INLINE  ELY_CONSTEXPR

#else

#   define ELY_CONSTEXPR
#   define ELY_CONSTEXPR_OR_CONST   const
#   define ELY_CONSTEXPR_OR_INLINE  inline

#endif // constexpr


#if ! defined ( BOOST_NO_CXX11_NOEXCEPT )

#   define ELY_NOEXCEPT                 noexcept
#   define ELY_NOEXCEPT_IF( cond )      noexcept( cond )
#   define ELY_IS_NOEXCEPT( expr )      noexcept( expr )
#   define ELY_NOEXCEPT_OR_NOTHROW      ELY_NOEXCEPT

#else

#   define ELY_NOEXCEPT
#   define ELY_NOEXCEPT_IF( expr )
#   define ELY_NOEXCEPT_EXPR( expr )
#   define ELY_NOEXCEPT_OR_NOTHROW      throw ()

#endif // noexcept


#if ! defined ( BOOST_NO_CXX11_DEFAULTED_FUNCTIONS )

#   define ELY_DEFAULTED_FUNCTION = default

#else

#   define ELY_DEFAULTED_FUNCTION

#endif // = default


#if ! defined ( BOOST_NO_CXX11_DELETED_FUNCTIONS )

#   define ELY_DELETED_FUNCTION = delete

#else

#   define ELY_DELETED_FUNCTION

#endif // = delete


#if ! defined ( BOOST_NO_CXX11_NULLPTR )

#   define ELY_USING_NULLPTR
#   define ELY_NULLPTR              nullptr
#   define ELY_NULLPTR_T            std::nullptr_t

#else

#   define ELY_NULLPTR              NULL
#   define ELY_NULLPTR_T            decltype( ELY_NULLPTR )

#endif // nullptr


#if ! defined ( BOOST_NO_CXX11_SMART_PTR )

#   define ELY_USING_SMART_POINTERS

#endif // smart pointers


//------------------------------------
//          Global macros
//------------------------------------
#define ELY_UNDEF_MACRO_PARAM   static_cast< void >( 0 )



#endif // CONFIG_H
