#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include <sstream>

#include <payload.h>
#include <base64.h>

namespace
{
const std::string kChannelName = "ch1";

const std::string kEventType = "event_type";
const std::string kArg1 = "arg1";
const std::string kArg2 = "arg2";
const std::string kArg3 = "arg3";

const char kEmptyString[] = "";
const std::string kStandaloneMotionName = "E_SA_MOTION";
const std::string kStandaloneHumanName = "E_SA_HUMAN";
const std::string kStandaloneMovedName = "E_SA_DEVICE_MOVED";
const std::string kStandaloneFaceDetectName = "E_SA_FACE_DETECTION";
const std::string kDVRMotionName = "E_DVR_MOTION";
const std::string kDVRHumanName = "E_DVR_HUMAN";
const std::string kDVRMovedName = "E_DVR_DEVICE_MOVED";
const std::string kDVRFaceDetectName = "E_DVR_FACE_DETECTION";

unsigned char hexToChar(const std::string& str) {
	short c = 0;

	if (!str.empty()) {
		std::istringstream in(str);

		in >> std::hex >> c;

		if (in.fail()) {
			throw std::runtime_error("stream decode failure");
		}
	}

	return static_cast<unsigned char>(c);
}

std::string urldecode(const std::string& toDecode)
{
	std::ostringstream out;

	for (std::string::size_type i = 0, len = toDecode.length(); i < len; ++i) {
		if (toDecode.at(i) == '%') {
			std::string str(toDecode.substr(i + 1, 2));
			out << hexToChar(str);
			i += 2;
		}
		else {
			out << toDecode.at(i);
		}
	}

	return out.str();
}
} //namespace

class PayloadTest : public testing::Test
{
protected:
	nlohmann::json decode(std::string data) const
	{
		auto urlDecode = urldecode(data);
		auto decode = nightowl_utils::base64_decode(urlDecode);
		return nlohmann::json::parse(decode);
	}
};

TEST_F(PayloadTest, StandaloneMotion)
{
	auto data = nightowl_utils::generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion);
	auto json = decode(data);
	EXPECT_STREQ(json.value(kEventType, "").c_str(), kStandaloneMotionName.c_str());
	EXPECT_STREQ(json.value(kArg1, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg2, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg3, "").c_str(), kEmptyString);
}

TEST_F(PayloadTest, StandaloneHuman)
{
	auto data = nightowl_utils::generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneHuman);
	auto json = decode(data);
	EXPECT_STREQ(json.value(kEventType, "").c_str(), kStandaloneHumanName.c_str());
	EXPECT_STREQ(json.value(kArg1, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg2, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg3, "").c_str(), kEmptyString);
}

TEST_F(PayloadTest, StandaloneDeviceMoved)
{
	auto data = nightowl_utils::generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMoved);
	auto json = decode(data);
	EXPECT_STREQ(json.value(kEventType, "").c_str(), kStandaloneMovedName.c_str());
	EXPECT_STREQ(json.value(kArg1, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg2, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg3, "").c_str(), kEmptyString);
}

TEST_F(PayloadTest, StandaloneFaceDetect)
{
	auto data = nightowl_utils::generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneFaceDetect);
	auto json = decode(data);
	EXPECT_STREQ(json.value(kEventType, "").c_str(), kStandaloneFaceDetectName.c_str());
	EXPECT_STREQ(json.value(kArg1, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg2, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg3, "").c_str(), kEmptyString);
}

TEST_F(PayloadTest, DVRMotion)
{
	auto data = nightowl_utils::generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMotion, kChannelName);
	auto json = decode(data);
	EXPECT_STREQ(json.value(kEventType, "").c_str(), kDVRMotionName.c_str());
	EXPECT_STREQ(json.value(kArg1, "").c_str(), kChannelName.c_str());
	EXPECT_STREQ(json.value(kArg2, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg3, "").c_str(), kEmptyString);
}

TEST_F(PayloadTest, DVRHuman)
{
	auto data = nightowl_utils::generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman, kChannelName);
	auto json = decode(data);
	EXPECT_STREQ(json.value(kEventType, "").c_str(), kDVRHumanName.c_str());
	EXPECT_STREQ(json.value(kArg1, "").c_str(), kChannelName.c_str());
	EXPECT_STREQ(json.value(kArg2, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg3, "").c_str(), kEmptyString);
}

TEST_F(PayloadTest, DVRFaceDetect)
{
	auto data = nightowl_utils::generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRFaceDetect, kChannelName);
	auto json = decode(data);
	EXPECT_STREQ(json.value(kEventType, "").c_str(), kDVRFaceDetectName.c_str());
	EXPECT_STREQ(json.value(kArg1, "").c_str(), kChannelName.c_str());
	EXPECT_STREQ(json.value(kArg2, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg3, "").c_str(), kEmptyString);
}

TEST_F(PayloadTest, DVRDeviceMoved)
{
	auto data = nightowl_utils::generatePayload(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMoved);
	auto json = decode(data);
	EXPECT_STREQ(json.value(kEventType, "").c_str(), kDVRMovedName.c_str());
	EXPECT_STREQ(json.value(kArg1, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg2, "").c_str(), kEmptyString);
	EXPECT_STREQ(json.value(kArg3, "").c_str(), kEmptyString);
}