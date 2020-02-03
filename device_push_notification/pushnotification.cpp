#include <memory>
#include <vector>
#include <sstream>

#include "pushnotification.h"

#include "base64.h"

namespace {
const std::string kScheme = "https://";
const std::string kURIPath = "/tpns";
const std::string kHost = "notifications.no-protect.com";
const std::string kStandalonePushURLFormat = "%s?cmd=event&uid=%s&event_time=%ld&event_type=%d&dev_type=%s&customized_payload=%s";
const std::string kDVRPushURLFormat = "%s?cmd=event&uid=%s&event_time=%ld&event_type=%d&dev_type=%s&channel=%d&customized_payload=%s";
const std::string kPayloadFormat = "{\"event_type\":\"%s\",\"arg1\":\"%s\", \"arg2\":\"%s\", \"arg3\":\"%s\"}";
const std::string kStandaloneMotionName = "E_SA_MOTION";
const std::string kStandaloneHumanName = "E_SA_HUMAN";
const std::string kStandaloneMovedName = "E_SA_DEVICE_MOVED";
const std::string kDVRMotionName = "E_DVR_MOTION";
const std::string kDVRHumanName = "E_DVR_HUMAN";
const std::string kDVRMovedName = "E_DVR_DEVICE_MOVED";
const char kEmptyString[] = "";
const int kNoSender = 999;

enum class EventType
{
	kMotion = 1,
	kHuman = 30302,
	kDeviceMoved = 30315
};

std::string getURI(std::string scheme, std::string host, std::string path)
{
	std::stringstream ss;
	ss << scheme << host << path;
	return ss.str();
}

std::string getEventName(nightowl::NOP_Push_Notification::PushNotification::EventKey eventType)
{
	switch (eventType) {
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion:
		return kStandaloneMotionName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneHuman:
		return kStandaloneHumanName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMoved:
		return kStandaloneMovedName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMotion:
		return kDVRMotionName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman:
		return kDVRHumanName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMoved:
		return kDVRMovedName;
	default:
		break;
	}
	return std::string();
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
	default:
		break;
	}
	return static_cast<int>(result);
}

void hexchar(unsigned char c, unsigned char& hex1, unsigned char& hex2)
{
	hex1 = c / 16;
	hex2 = c % 16;
	hex1 += hex1 <= 9 ? '0' : 'a' - 10;
	hex2 += hex2 <= 9 ? '0' : 'a' - 10;
}

std::string urlencode(std::string s)
{
	const char* str = s.c_str();
	std::vector<char> v(s.size());
	v.clear();
	for (size_t i = 0, l = s.size(); i < l; i++)
	{
		char c = str[i];
		if ((c >= '0' && c <= '9') ||
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			c == '-' || c == '_' || c == '.' || c == '!' || c == '~' ||
			c == '*' || c == '\'' || c == '(' || c == ')')
		{
			v.push_back(c);
		}
		else if (c == ' ')
		{
			v.push_back('+');
		}
		else
		{
			v.push_back('%');
			unsigned char d1, d2;
			hexchar(c, d1, d2);
			v.push_back(d1);
			v.push_back(d2);
		}
	}

	return std::string(v.cbegin(), v.cend());
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
		return kNoSender;
	}
	
	auto eventName = getEventName(eventKey);
	int length = snprintf(0, 0, kPayloadFormat.c_str(), eventName.c_str(), kEmptyString, kEmptyString, kEmptyString) + 1;
	std::unique_ptr<char[]> payload(new char[length]);
	snprintf(payload.get(), length, kPayloadFormat.c_str(), eventName.c_str(), kEmptyString, kEmptyString, kEmptyString);

	return send(eventKey, uid, eventTime, deviceType, payload, length);
}

int PushNotification::sendPushNotication(EventKey eventKey, const std::string& uid, long eventTime, 
	const std::string& deviceType, int channel, const std::string& channelName)
{	
	if (_sender == nullptr) {
		return kNoSender;
	}

	auto eventName = getEventName(eventKey);
	int length = snprintf(0, 0, kPayloadFormat.c_str(), eventName.c_str(), channelName.c_str(), kEmptyString, kEmptyString) + 1;
	std::unique_ptr<char[]> payload(new char[length]);
	snprintf(payload.get(), length, kPayloadFormat.c_str(), eventName.c_str(), channelName.c_str(), kEmptyString, kEmptyString);

	return send(eventKey, uid, eventTime, deviceType, channel, payload, length);
}

int PushNotification::send(EventKey eventKey, const std::string& uid, long eventTime,
	const std::string& deviceType, const std::unique_ptr<char[]>& payload, int payloadLength)
{
	auto payload64 = base64_encode(std::string(payload.get()));
	auto payloadEncode = urlencode(payload64);

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

int PushNotification::send(nightowl::NOP_Push_Notification::PushNotification::EventKey eventKey, const std::string& uid,
	long eventTime, const std::string& deviceType, int channel, const std::unique_ptr<char[]>& payload, int payloadLength)
{
	auto payload64 = base64_encode(std::string(payload.get()));
	auto payloadEncode = urlencode(payload64);

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
} //NOP_Push_Notification
} //nightowl