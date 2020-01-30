#ifndef NIGHTOWL_NOP_PRINTF_LOGGER_H
#define NIGHTOWL_NOP_PRINTF_LOGGER_H

#include <iLogger.h>

namespace nightowl
{
namespace NOP
{
class PrintfLogger : public NOP_Push_Notification::ILogger
{
public:
	void log(const char* format, ...) override;
};
} //NOP
} //nightowl
#endif //NIGHTOWL_NOP_PRINTF_LOGGER_H