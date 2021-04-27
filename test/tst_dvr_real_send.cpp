#include <gtest/gtest.h>

#include <sys/stat.h>
#include <memory>
#include <thread>
#include <chrono>
#include <nlohmann/json.hpp>

#include <pushnotification.h>
#include <iHttpSender.h>
#include <curlsender.h>
#include <uploadimage.h>

#include "printfLogger.h"

namespace
{
const std::string kDVRName = "Nightowl-DVR";
const std::string kUid = "FFUU9X3WK1R48G6GY1RJ";
const std::string kDVRType = "videoRecorder";
const std::string kChannelName = "test ch1";
const std::string kHost = "push-staging.kalay.us";
const int kChannelID = 1;
const std::string kImagePath = "test.png";
const std::string kUploadURLKey = "url";
} //namespace

class DeviceRealPushTest : public testing::Test
{
protected:
	void SetUp() override
	{
		_logger = std::make_shared<nightowl::NOP::PrintfLogger>();
		_sender = std::make_shared<nightowl::NOP::CurlSender>();
		_pusher = std::make_unique<nightowl::NOP_Push_Notification::PushNotification>(_sender, _logger);
	}

	void TearDown() override
	{
	}

	std::shared_ptr<nightowl::NOP::CurlSender> _sender;
	std::shared_ptr<nightowl::NOP::PrintfLogger> _logger;
	std::unique_ptr<nightowl::NOP_Push_Notification::PushNotification> _pusher;
};

TEST_F(DeviceRealPushTest, DVRPushMotion)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMotion,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushHuman)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman, 
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushMoved)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMoved,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushFaceDetect)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRFaceDetect,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushLowBattery)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRLowBattery,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushDefectBattery)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRDefectBattery,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushBatteryFull)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRBatteryFullCharged,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}


TEST_F(DeviceRealPushTest, pushWithStageHost)
{
	_pusher->setPushHost(kHost);
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMotion,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushHumanWithImage)
{
	struct stat buffer;
	bool isFileExisted = false;
	if (stat(kImagePath.c_str(), &buffer) == 0) {
		isFileExisted = true;
	}
	ASSERT_TRUE(isFileExisted);
	auto sender = std::make_shared<nightowl::NOP::CurlSender>();
	auto uploader = std::make_unique<nightowl::NOP_upload_image::UploadImage>(sender);
	auto response = uploader->upload(kUid, kImagePath);
	auto json = nlohmann::json::parse(response.text);
	auto url = json.value(kUploadURLKey, "");
	ASSERT_EQ(response.responseCode, 200);
	ASSERT_FALSE(url.empty());
	printf("image URL: %s", url.c_str());
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, url);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushTwoEvent)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRFaceDetect,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	eventTime = static_cast<long int>(std::time(nullptr));
	result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushTwoImageEvent)
{
	struct stat buffer;
	bool isFileExisted = false;
	if (stat(kImagePath.c_str(), &buffer) == 0) {
		isFileExisted = true;
	}
	ASSERT_TRUE(isFileExisted);
	auto sender = std::make_shared<nightowl::NOP::CurlSender>();
	auto uploader = std::make_unique<nightowl::NOP_upload_image::UploadImage>(sender);
	auto response = uploader->upload(kUid, kImagePath);
	auto json = nlohmann::json::parse(response.text);
	auto url = json.value(kUploadURLKey, "");
	ASSERT_EQ(response.responseCode, 200);
	ASSERT_FALSE(url.empty());
	printf("image URL: %s", url.c_str());

	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRFaceDetect,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, url);
	EXPECT_EQ(result, 0);
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	eventTime = static_cast<long int>(std::time(nullptr));
	result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, url);
	EXPECT_EQ(result, 0);
}

TEST_F(DeviceRealPushTest, DVRPushVehicleDetect)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRVehicleDetected,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}
