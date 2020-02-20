#ifndef NIGHTOWL_NOP_PAYLOAD_H
#define NIGHTOWL_NOP_PAYLOAD_H

#include <string>

#include "pushnotification.h"

namespace nightowl {
namespace NOP_Push_Notification {
class Payload
// Payload generates the payload string
{
public:
	Payload() = default;
	~Payload() = default;

	Payload(const Payload&) = delete;
	Payload& operator=(const Payload&) = delete;
	Payload(const Payload&&) = delete;
	Payload& operator=(const Payload&&) = delete;

	std::string generate(PushNotification::EventKey eventKey) const;

	std::string generate(PushNotification::EventKey eventKey, const std::string& channelName) const;
};
} //NOP_Push_Notification
} //nightowl

#endif //NIGHTOWL_NOP_PAYLOAD_H