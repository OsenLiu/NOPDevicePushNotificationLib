#ifndef NIGHTOWL_NOP_HTTP_SENDER_H
#define NIGHTOWL_NOP_HTTP_SENDER_H

#include <vector>

namespace nightowl 
{
namespace NOP_Push_Notification
{
// Http sender interface. The push notification will use the sender to send push URL.
// Example:
//    sender->send("https://example.com");
class IHttpSender
{
public:
	enum class ParameterType {
		kContent,
		kFile
	};

	struct PostInfo {
		std::string key;
		std::string value;
		ParameterType type;
	};

	struct Response {
		int responseCode;
		std::string text;
	};

public:
	virtual ~IHttpSender() = default;

	//send url with https.
	//return the result code with the http library. The result code is depending on what library you use.
	virtual int send(const std::string& url) = 0;

	//post with https
	//return the result code and response text. The result code is depending on what library you use.
	virtual NOP_Push_Notification::IHttpSender::Response post(const std::string& url, const std::vector<NOP_Push_Notification::IHttpSender::PostInfo> parameters) = 0;
};
} //NOP_Push_Notification
} //nightowl

#endif //NIGHTOWL_NOP_HTTP_SENDER_H