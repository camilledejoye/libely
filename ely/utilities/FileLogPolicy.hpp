#ifndef FILE_LOG_POLICY_HPP
#define FILE_LOG_POLICY_HPP


#include <fstream>


namespace ely
{
namespace utilities
{


class FileLogPolicy : public std::ofstream
{
protected:
    FileLogPolicy() = default;
};


} // namespace ::ely::utilities
} // namespace ::ely

#endif // FILE_LOG_POLICY_HPP
