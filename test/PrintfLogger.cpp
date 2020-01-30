#include <stdarg.h>
#include <cstdarg>
#include <cstdio>

#include "printfLogger.h"

namespace nightowl
{
namespace NOP
{
void PrintfLogger::log(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}
} //NOP
} //nightowl