#ifndef DEBUG_LOG_POLICY_HPP
#define DEBUG_LOG_POLICY_HPP


#include <ostream>


namespace ely
{
namespace utilities
{


class DebugLogPolicy : public std::ostream
{
protected:
    DebugLogPolicy();
};


} // namespace ::ely::utilities
} // namespace ::ely

#endif // DEBUG_LOG_POLICY_HPP
