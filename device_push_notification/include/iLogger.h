#ifndef NIGHTOWL_NOP_Push_Notification_ILOGGER_H
#define NIGHTOWL_NOP_Push_Notification_ILOGGER_H

#include <initializer_list>

namespace nightowl
{
namespace NOP_Push_Notification
{
class ILogger
{
public:
	virtual ~ILogger() = default;

	//log message
	virtual void log(const char* format, ...) = 0;

};
} //NOP_Push_Notification
} //nightowl

#endif //NIGHTOWL_NOP_Push_Notification_ILOGGER_H