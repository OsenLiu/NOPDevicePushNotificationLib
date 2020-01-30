#ifndef NIGHTOWL_NOP_MOCKIHTTPSENDER_H
#define NIGHTOWL_NOP_MOCKIHTTPSENDER_H

#include <string>

#include <gmock/gmock.h>

#include <iHttpSender.h>

namespace nightowl
{
namespace NOP
{
class MockIHTTPSender : public NOP_Push_Notification::IHttpSender
{
public:
	MOCK_METHOD1(send, int(const std::string& url));
};
} //NOP
} //nightowl

#endif // NIGHTOWL_NOP_MOCKIHTTPSENDER_H