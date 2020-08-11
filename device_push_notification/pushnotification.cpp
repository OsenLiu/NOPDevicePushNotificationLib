#include <sstream>

#include "pushnotification.h"
#include "payload.h"
#include "base64.h"

namespace {
const std::string kScheme = "https://";
const std::string kURIPath = "/tpns";
const std::string kHost = "notifications.no-protect.com";
const std::string kStandalonePushURLFormat = "%s?cmd=event&uid=%s&event_time=%ld&event_type=%d&dev_type=%s&customized_payload=%s";
const std::string kDVRPushURLFormat = "%s?cmd=event&uid=%s&event_time=%ld&event_type=%d&dev_type=%s&channel=%d&customized_payload=%s";
const std::string kStandalonePushImageFormat = "%s?cmd=event&uid=%s&event_time=%ld&event_type=%d&dev_type=%s&img=%s&customized_payload=%s";
const std::string kDVRPushImageFormat = "%s?cmd=event&uid=%s&event_time=%ld&event_type=%d&dev_type=%s&channel=%d&img=%s&customized_payload=%s";
const int kErrorNoSender = 999;
const int kErrorNoImage = 1000;

enum class EventType
{
	kMotion = 1,
	kHuman = 30302,
	kFaceDetected = 30303,
	kBatteryLow = 30309,
	kBatteryFull = 30310,
	kBatteryDefective = 30311,
	kDeviceMoved = 30315,
	kFirmwareAvailable = 30601,
	kUpgradeSuccess = 30602,
	kUpgradeFail = 30603
};

std::string getURI(std::string scheme, std::string host, std::string path)
{
	std::stringstream ss;
	ss << scheme << host << path;
	return ss.str();
}

int getEventType(nightowl::NOP_Push_Notification::PushNotification::EventKey eventType)
{
	auto result = EventType::kMotion;
	switch (eventType) {
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion:
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMotion:
		result = EventType::kMotion;
		break;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman:
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneHuman:
		result = EventType::kHuman;
		break;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMoved:
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMoved:
		result = EventType::kDeviceMoved;
		break;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRFaceDetect:
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneFaceDetect:
		result = EventType::kFaceDetected;
		break;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRLowBattery:
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneLowBattery:
		result = EventType::kBatteryLow;
		break;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRBatteryFullCharged:
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneBatteryFullCharged:
		result = EventType::kBatteryFull;
		break;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRDefectBattery:
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneDefectBattery:
		result = EventType::kBatteryDefective;
		break;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kFirmwareAvailable:
		result = EventType::kFirmwareAvailable;
		break;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kUpgradeSuccess:
		result = EventType::kUpgradeSuccess;
		break;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kUpgradeFail:
		result = EventType::kUpgradeFail;
		break;
	default:
		break;
	}
	return static_cast<int>(result);
}
} //namespace

namespace nightowl {
namespace NOP_Push_Notification {
PushNotification::PushNotification(std::shared_ptr<IHttpSender> sender):
	_sender(std::move(sender))
{
	_uri = getURI(kScheme, kHost, kURIPath);
}

PushNotification::PushNotification(std::shared_ptr<IHttpSender> sender, std::shared_ptr<ILogger> logger) :
	_sender(std::move(sender)), _logger(std::move(logger))
{
	_uri = getURI(kScheme, kHost, kURIPath);
}

void PushNotification::setPushHost(const std::string& host)
{
	_host = host;
	_uri = getURI(kScheme, host, kURIPath);
}

int PushNotification::sendPushNotication(EventKey eventKey, const std::string& uid, long eventTime,
	const std::string& deviceType)
{
	if (_sender == nullptr) {
		return kErrorNoSender;
	}

	auto payloadEncode = nightowl_utils::generatePayload(eventKey);
	auto eventType = getEventType(eventKey);
	int length = snprintf(0, 0, kStandalonePushURLFormat.c_str(), _uri.c_str(), uid.c_str(), eventTime, eventType, deviceType.c_str(), payloadEncode.c_str()) + 1;
	std::unique_ptr<char[]> buf(new char[length]);
	snprintf(buf.get(), length, kStandalonePushURLFormat.c_str(), _uri.c_str(), uid.c_str(), eventTime,
		getEventType(eventKey), deviceType.c_str(), payloadEncode.c_str());
	if (_logger) {
		_logger->log("Push URL: %s\n", buf.get());
	}
	return _sender->send(std::string(buf.get()));
}

int PushNotification::sendPushNotication(EventKey eventKey, const std::string& uid, long eventTime, 
	const std::string& deviceType, int channel, const std::string& channelName)
{	
	if (_sender == nullptr) {
		return kErrorNoSender;
	}

	auto payloadEncode = nightowl_utils::generatePayload(eventKey, channelName);

	auto eventType = getEventType(eventKey);
	int length = snprintf(0, 0, kDVRPushURLFormat.c_str(), _uri.c_str(), uid.c_str(), eventTime, eventType, deviceType.c_str(), channel, payloadEncode.c_str()) + 1;
	std::unique_ptr<char[]> buf(new char[length]);
	snprintf(buf.get(), length, kDVRPushURLFormat.c_str(), _uri.c_str(), uid.c_str(), eventTime,
		getEventType(eventKey), deviceType.c_str(), channel, payloadEncode.c_str());
	if (_logger) {
		_logger->log("Push URL: %s\n", buf.get());
	}
	return _sender->send(std::string(buf.get()));
}

int PushNotification::sendPushImageNotication(EventKey eventKey, const std::string& uid, long eventTime,
	const std::string& deviceType, const std::string& imageURL)
{
	if (_sender == nullptr) {
		return kErrorNoSender;
	}
	if (imageURL.empty()) {
		return kErrorNoImage;
	}

	auto payloadEncode = nightowl_utils::generatePayload(eventKey);
	auto encodedImageURL = nightowl_utils::urlEncode(imageURL);

	auto eventType = getEventType(eventKey);
	int length = snprintf(0, 0, kStandalonePushImageFormat.c_str(), _uri.c_str(), uid.c_str(), eventTime, eventType, deviceType.c_str(), encodedImageURL.c_str(), payloadEncode.c_str()) + 1;
	std::unique_ptr<char[]> buf(new char[length]);
	snprintf(buf.get(), length, kStandalonePushImageFormat.c_str(), _uri.c_str(), uid.c_str(), eventTime,
		getEventType(eventKey), deviceType.c_str(), encodedImageURL.c_str(), payloadEncode.c_str());
	if (_logger) {
		_logger->log("Push URL: %s\n", buf.get());
	}
	return _sender->send(std::string(buf.get()));
}

int PushNotification::sendPushImageNotication(EventKey eventKey, const std::string& uid, long eventTime,
	const std::string& deviceType, int channel, const std::string& channelName, const std::string& imageURL)
{
	if (_sender == nullptr) {
		return kErrorNoSender;
	}
	if (imageURL.empty()) {
		return kErrorNoImage;
	}

	auto payloadEncode = nightowl_utils::generatePayload(eventKey, channelName);
	auto encodedImageURL = nightowl_utils::urlEncode(imageURL);

	auto eventType = getEventType(eventKey);
	int length = snprintf(0, 0, kDVRPushImageFormat.c_str(), _uri.c_str(), uid.c_str(), eventTime, eventType, deviceType.c_str(), channel, encodedImageURL.c_str(), payloadEncode.c_str()) + 1;
	std::unique_ptr<char[]> buf(new char[length]);
	snprintf(buf.get(), length, kDVRPushImageFormat.c_str(), _uri.c_str(), uid.c_str(), eventTime,
		getEventType(eventKey), deviceType.c_str(), channel, encodedImageURL.c_str(), payloadEncode.c_str());
	if (_logger) {
		_logger->log("Push URL: %s\n", buf.get());
	}
	return _sender->send(std::string(buf.get()));
}
} //NOP_Push_Notification
} //nightowl