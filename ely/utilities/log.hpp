#ifndef LOG_H
#define LOG_H

#include "ely/utilities/ElyLog.hpp"
#include "ely/utilities/LogPolicies.hpp"

typedef ely::utilities::ElyLog< ely::utilities::DebugLogPolicy >    DebugLogger;
typedef ely::utilities::ElyLog< ely::utilities::FileLogPolicy >     FileLogger;
typedef ely::utilities::ElyLog< ely::utilities::NoLogPolicy >       NoLogger;

#if defined ( NDEBUG )
typedef NoLogger Logger;
typedef NoLogger DebugOutput;
#elif defined ( FILE_LOGGER )
typedef FileLogger Logger;
typedef DebugLogger DebugOutput;
#else
typedef DebugLogger Logger;
typedef DebugLogger DebugOutput;
#endif


namespace ely
{


extern Logger & log;            // To log information
extern DebugOutput & debug;     // To debug


} // namespace ::ely

#endif // LOG_H
