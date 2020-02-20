#include <vector>

#include "payload.h"
#include "base64.h"

namespace {
const std::string kPayloadFormat = "{\"event_type\":\"%s\",\"arg1\":\"%s\", \"arg2\":\"%s\", \"arg3\":\"%s\"}";
const std::string kStandaloneMotionName = "E_SA_MOTION";
const std::string kStandaloneHumanName = "E_SA_HUMAN";
const std::string kStandaloneMovedName = "E_SA_DEVICE_MOVED";
const std::string kStandaloneFaceDetectName = "E_SA_FACE_DETECTION";
const std::string kDVRMotionName = "E_DVR_MOTION";
const std::string kDVRHumanName = "E_DVR_HUMAN";
const std::string kDVRMovedName = "E_DVR_DEVICE_MOVED";
const std::string kDVRFaceDetectName = "E_DVR_FACE_DETECTION";
const char kEmptyString[] = "";

std::string getEventName(nightowl::NOP_Push_Notification::PushNotification::EventKey eventType)
{
	switch (eventType) {
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion:
		return kStandaloneMotionName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneHuman:
		return kStandaloneHumanName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMoved:
		return kStandaloneMovedName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneFaceDetect:
		return kStandaloneFaceDetectName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMotion:
		return kDVRMotionName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman:
		return kDVRHumanName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMoved:
		return kDVRMovedName;
	case nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRFaceDetect:
		return kDVRFaceDetectName;
	default:
		break;
	}
	return std::string();
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
std::string Payload::generate(PushNotification::EventKey eventKey) const
{
	auto eventName = getEventName(eventKey);
	int length = snprintf(0, 0, kPayloadFormat.c_str(), eventName.c_str(), kEmptyString, kEmptyString, kEmptyString) + 1;
	std::unique_ptr<char[]> payload(new char[length]);
	snprintf(payload.get(), length, kPayloadFormat.c_str(), eventName.c_str(), kEmptyString, kEmptyString, kEmptyString);

	auto payload64 = base64_encode(std::string(payload.get()));
	return urlencode(payload64);
}

std::string Payload::generate(PushNotification::EventKey eventKey, const std::string& channelName) const
{
	auto eventName = getEventName(eventKey);
	int length = snprintf(0, 0, kPayloadFormat.c_str(), eventName.c_str(), channelName.c_str(), kEmptyString, kEmptyString) + 1;
	std::unique_ptr<char[]> payload(new char[length]);
	snprintf(payload.get(), length, kPayloadFormat.c_str(), eventName.c_str(), channelName.c_str(), kEmptyString, kEmptyString);

	auto payload64 = base64_encode(std::string(payload.get()));
	return urlencode(payload64);
}
} //NOP_Push_Notification
} //nightowl