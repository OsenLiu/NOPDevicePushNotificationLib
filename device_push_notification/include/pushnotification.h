#ifndef NIGHTOWL_NOP_PUSHNOTIFICATION_H
#define NIGHTOWL_NOP_PUSHNOTIFICATION_H

#include <string>
#include <memory>

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
		kStandaloneFaceDetect,
		kStandaloneLowBattery,
		kStandaloneBatteryFullCharged,
		kStandaloneDefectBattery,
		kStandaloneVehicleDetected,
		kDVRMotion,
		kDVRHuman,
		kDVRMoved,
		kDVRFaceDetect,
		kDVRLowBattery,
		kDVRBatteryFullCharged,
		kDVRDefectBattery,
		kDVRVehicleDetected,
		kFirmwareAvailable,
		kUpgradeSuccess,
		kUpgradeFail,
		kDoorbellRing
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

	// The device sends push notification with event key, uid, event time, and device type.
	int sendPushNotication(EventKey eventKey, const std::string& uid, long eventTime, const std::string& deviceType);

	// The device sends push notification with event key, uid, event time, device type, device name, channel number, and channel name.
	int sendPushNotication(EventKey eventKey, const std::string& uid, long eventTime, const std::string& deviceType, int channel, const std::string& channelName);

	// The device sends push image notification with event key, uid, event time, image URL and device type.
	int sendPushImageNotication(EventKey eventKey, const std::string& uid, long eventTime, const std::string& deviceType, const std::string& imageURL);

	// The device sends push image notification with event key, uid, event time, device type, device name, channel number, image URL and channel name.
	int sendPushImageNotication(EventKey eventKey, const std::string& uid, long eventTime, const std::string& deviceType, int channel, const std::string& channelName, const std::string& imageURL);

private:
	std::shared_ptr<IHttpSender> _sender {};
	std::shared_ptr<ILogger> _logger{};
	std::string _host;
	std::string _uri;
};
} //NOP_Push_Notification
} //nightowl

#endif //NIGHTOWL_NOP_PUSHNOTIFICATION_H
