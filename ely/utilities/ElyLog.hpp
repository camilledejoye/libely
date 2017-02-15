#ifndef ELY_LOG_H
#define ELY_LOG_H


#include "ely/patterns/Singleton.hpp"


namespace ely
{
namespace utilities
{


template < typename LogPolicy >
class ElyLog final : public patterns::Singleton< ElyLog< LogPolicy > >, public LogPolicy
{
public:
    friend class patterns::Singleton< ElyLog< LogPolicy > >;

protected:
    ElyLog() = default;
};


} // namespace ::ely::utilities
} // namespace ::ely

#endif // ELY_LOG_H
