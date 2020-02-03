#ifndef NIGHTOWL_NOP_PUSHNOTIFICATION_H
#define NIGHTOWL_NOP_PUSHNOTIFICATION_H

#include <string>

#include "iHttpSender.h"
#include "iLogger.h"

namespace nightowl {
namespace NOP_Push_Notification {
// PushNotification send push with event key, uid, event time, channel number, device type, and device name.
// PushNotification is created with sender. The senders needs support https protocol.
// Example:
//    _sender = std::make_shared<nightowl::NOP::CurlSender>();
//    auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion, kUid, eventTime, kStandaloneDeviceType, kStandaloneName);
class PushNotification
{
public:
	enum class EventKey {
		kStandaloneMotion,
		kStandaloneHuman,
		kStandaloneMoved,
		kDVRMotion,
		kDVRHuman,
		kDVRMoved
	};

public:
	PushNotification(std::shared_ptr<IHttpSender> sender);
	PushNotification(std::shared_ptr<IHttpSender> sender, std::shared_ptr<ILogger> logger);
	~PushNotification() = default;

	PushNotification(const PushNotification&) = delete;
	PushNotification& operator=(const PushNotification&) = delete;
	PushNotification(const PushNotification&&) = delete;
	PushNotification& operator=(const PushNotification&&) = delete;

	// set host for push notification. The default push host is notifications.no-protect.com. PushNotification will use default host if there isn't host.
	void setPushHost(const std::string& host);

	std::string getPushHost() const { return _host; };

	// The standalone device sends push notification with event key, uid, event time, and device type.
	int sendPushNotication(EventKey eventKey, const std::string& uid, long eventTime, const std::string& deviceType);

	// The DVR/NVR/WNVR device sends push notification with event key, uid, event time, device type, device name, channel number, and channel name.
	int sendPushNotication(EventKey eventKey, const std::string& uid, long eventTime, const std::string& deviceType, int channel, const std::string& channelName);

private:
	int send(nightowl::NOP_Push_Notification::PushNotification::EventKey eventKey, const std::string& uid, 
		long eventTime, const std::string& deviceType, const std::unique_ptr<char[]>& payload, int payloadLength);

	int send(nightowl::NOP_Push_Notification::PushNotification::EventKey eventKey, const std::string& uid,
		long eventTime, const std::string& deviceType, int channel, const std::unique_ptr<char[]>& payload, int payloadLength);

private:
	std::shared_ptr<IHttpSender> _sender {};
	std::shared_ptr<ILogger> _logger{};
	std::string _host;
	std::string _uri;
};
} //NOP_Push_Notification
} //nightowl

#endif //NIGHTOWL_NOP_PUSHNOTIFICATION_H
