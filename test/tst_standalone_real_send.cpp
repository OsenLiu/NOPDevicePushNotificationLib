#include <gtest/gtest.h>

#include <memory>

#include <pushnotification.h>
#include <iHttpSender.h>
#include <curlsender.h>

#include "printfLogger.h"
#include <uploadImage/include/uploadimage.h>
#include <nlohmann/json.hpp>


namespace
{
	const std::string kStandaloneName = "Nightowl-IPC";
	const std::string kUid = "HDZTW6P1VKBJ5MM1111A";
	const std::string kStandaloneDeviceType = "standaloneIpCamera";
	const std::string kHost = "push-staging.kalay.us";
	const std::string kImagePath = "test.png";
	const std::string kUploadURLKey = "url";

} //namespace

class StandaloneRealPushTest : public testing::Test
{
protected:
	void SetUp() override
	{
		_logger = std::make_shared<nightowl::NOP::PrintfLogger>();
		_sender = std::make_shared<nightowl::NOP::CurlSender>();
		_pusher = std::make_unique<nightowl::NOP_Push_Notification::PushNotification>(_sender, _logger);
		//_pusher->setPushHost(kHost);
	}

	void TearDown() override
	{
	}

	std::shared_ptr<nightowl::NOP::CurlSender> _sender;
	std::shared_ptr<nightowl::NOP::PrintfLogger> _logger;
	std::unique_ptr<nightowl::NOP_Push_Notification::PushNotification> _pusher;
};

TEST_F(StandaloneRealPushTest, StandalonePushMotion)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(StandaloneRealPushTest, StandalonePushHuman)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneHuman,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(StandaloneRealPushTest, StandalonePushFaceDetect)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneFaceDetect,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(StandaloneRealPushTest, pushWithStageHost)
{
	_pusher->setPushHost(kHost);
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMotion,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(StandaloneRealPushTest, firmwareAvailable)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kFirmwareAvailable,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(StandaloneRealPushTest, upgradeSuccess)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kUpgradeSuccess,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(StandaloneRealPushTest, upgradeFail)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kUpgradeFail,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(StandaloneRealPushTest, StandalonePushRing)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDoorbellRing,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(StandaloneRealPushTest, StandaloneLowBattery)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneLowBattery,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(StandaloneRealPushTest, PushHumanWithImage)
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
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneHuman,
		kUid, eventTime, kStandaloneDeviceType, url);
	EXPECT_EQ(result, 0);
}