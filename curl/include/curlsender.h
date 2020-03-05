#ifndef NIGHTOWL_NOP_CURL_SENDER_H
#define NIGHTOWL_NOP_CURL_SENDER_H

#include <string>
#include <vector>

#include <iHttpSender.h>

#include "curlsender.h"

namespace nightowl 
{
namespace NOP 
{
class CurlSender : public NOP_Push_Notification::IHttpSender
{
public:
	virtual ~CurlSender() = default;

	int send(const std::string& url);

	NOP_Push_Notification::IHttpSender::Response post(const std::string& url, const std::vector<NOP_Push_Notification::IHttpSender::PostInfo> parameters);
};
} //NOP
} //nightowl
#endif //NIGHTOWL_NOP_CURL_SENDER_H