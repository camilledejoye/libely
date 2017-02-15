#ifndef NO_LOG_POLICY_HPP
#define NO_LOG_POLICY_HPP


#include <ostream>
#include <memory>


namespace ely
{
namespace utilities
{


/// The policy of the log system to not log.
class NoLogPolicy : public std::ostream
{
protected:
    NoLogPolicy();

private:
    class NullStreambuf;

    std::unique_ptr< NullStreambuf > nullStreambuf;
};


/// A stream buffer which doesn't print anything.
class NoLogPolicy::NullStreambuf : public std::basic_streambuf< char, std::char_traits< char > >
{
protected:
    virtual int_type overflow( int_type character );
};


} // namespace ::ely::utilities
} // namespace ::ely

#endif // NO_LOG_POLICY_HPP
