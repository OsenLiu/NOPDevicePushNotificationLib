#ifndef NIGHTOWL_NOP_PAYLOAD_H
#define NIGHTOWL_NOP_PAYLOAD_H

#include <string>

#include "pushnotification.h"

namespace nightowl_utils
{
std::string generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey eventKey);

std::string generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey eventKey, const std::string& channelName);
} //nightowl_utils
#endif //NIGHTOWL_NOP_PAYLOAD_H