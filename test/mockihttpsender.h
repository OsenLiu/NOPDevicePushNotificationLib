#ifndef NIGHTOWL_NOP_MOCKIHTTPSENDER_H
#define NIGHTOWL_NOP_MOCKIHTTPSENDER_H

#include <string>
#include <vector>

#include <gmock/gmock.h>

#include <iHttpSender.h>

namespace nightowl
{
namespace NOP
{
class MockIHTTPSender : public NOP_Push_Notification::IHttpSender
{
public:
	MOCK_METHOD(int, send, (const std::string& url), (override));

	MOCK_METHOD(NOP_Push_Notification::IHttpSender::Response, post,
		(const std::string& url, const std::vector<NOP_Push_Notification::IHttpSender::PostInfo> parameters), 
		(override));
};
} //NOP
} //nightowl

#endif // NIGHTOWL_NOP_MOCKIHTTPSENDER_H