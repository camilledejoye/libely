#ifndef NULL_VALUE_H
#define NULL_VALUE_H


namespace ely
{
namespace traits
{


// TODO : voir pour ::value plutôt que ::value()
//      Pour : standardisation vis à vis de la STL
//      Contre : Problèmes avec constexpr et mieux comme ça
template < typename T >     struct NullValue { static constexpr T                value() {
                                                   return T();
                                               }
};
template < typename T >     struct NullValue< T * >     { static constexpr std::nullptr_t   value() {
                                                              return nullptr;
                                                          }
};
template < >                struct NullValue< int >     { static constexpr int              value() {
                                                              return 0;
                                                          }
};
template < >                struct NullValue< char >    { static constexpr char             value() {
                                                              return char( 0 );
                                                          }
};
template < >                struct NullValue< float >   { static constexpr float            value() {
                                                              return 0.0f;
                                                          }
};
template < >                struct NullValue< double >  { static constexpr double           value() {
                                                              return 0.0d;
                                                          }
};
template < >                struct NullValue< char * >  { static constexpr char const    *  value() {
                                                              return "";
                                                          }
};
template < std::size_t N >  struct NullValue< char[ N ] > { static constexpr char const    *  value() {
                                                                return "";
                                                            }
};


} // namespace ::ely::traits
} // namespace ::ely


#endif // NULL_VALUE_H
