#include <gtest/gtest.h>

#include <memory>

#include <pushnotification.h>
#include <iHttpSender.h>
#include <curlsender.h>

#include "printfLogger.h"

namespace
{
const std::string kStandaloneName = "Nightowl-IPC";
const std::string kDVRName = "Nightowl-DVR";
const std::string kUid = "B7V2GYDZXT5KF15K111A";
const std::string kStandaloneDeviceType = "standaloneIpCamera";
const std::string kDVRType = "videoRecorder";
const std::string kChannelName = "ch1";
const std::string kHost = "push-staging.kalay.us";
const int kChannelID = 1;
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

TEST_F(DeviceRealPushTest, StandalonePushMotion)
{
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion, 
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

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

TEST_F(DeviceRealPushTest, pushWithHost)
{
	_pusher->setPushHost(kHost);
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMotion,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}