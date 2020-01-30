#ifndef NIGHTOWL_NOP_HTTP_SENDER_H
#define NIGHTOWL_NOP_HTTP_SENDER_H

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
	virtual ~IHttpSender() = default;

	//send url with http or https.
	//return the result code with the http library. The result code is depending on what library you use.
	virtual int send(const std::string& url) = 0;

};
} //NOP_Push_Notification
} //nightowl

#endif //NIGHTOWL_NOP_HTTP_SENDER_H