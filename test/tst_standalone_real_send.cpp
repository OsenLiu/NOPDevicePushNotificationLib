#include <gtest/gtest.h>

#include <memory>

#include <pushnotification.h>
#include <iHttpSender.h>
#include <curlsender.h>

#include "printfLogger.h"

namespace
{
	const std::string kStandaloneName = "Nightowl-IPC";
	const std::string kUid = "F3KA852CUZ74UGPGY1D1";
	const std::string kStandaloneDeviceType = "standaloneIpCamera";
	const std::string kHost = "push-staging.kalay.us";
} //namespace

class StandaloneRealPushTest : public testing::Test
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