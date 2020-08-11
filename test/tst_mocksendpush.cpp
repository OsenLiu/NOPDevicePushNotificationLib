#include <gtest/gtest.h>

#include <memory>

#include <pushnotification.h>

#include "mockihttpsender.h"
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
const std::string kImageURL = "http://upload.tutk/image/abcdefgsdjfsl.jpg";
const int kChannelID = 1;
} //namespace

class MockDevicePushTest : public testing::Test
{
protected:
	void SetUp() override
	{
		_logger = std::make_shared<nightowl::NOP::PrintfLogger>();
		_sender = std::make_shared<nightowl::NOP::MockIHTTPSender>();
		_pusher = std::make_unique< nightowl::NOP_Push_Notification::PushNotification>(_sender, _logger);
	}

	void TearDown() override
	{
	}

	std::shared_ptr<nightowl::NOP::MockIHTTPSender> _sender;
	std::shared_ptr<nightowl::NOP::PrintfLogger> _logger;
	std::unique_ptr<nightowl::NOP_Push_Notification::PushNotification> _pusher;
};

TEST_F(MockDevicePushTest, StandaloneDevicePushMotion)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion, 
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, StandaloneDevicePushHuman)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneHuman,
		kUid, eventTime, kStandaloneDeviceType);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, DVRPushHuman)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman, 
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, DVRPushMoved)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMoved,
		kUid, eventTime, kDVRType);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, DVRPushFaceDetect)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRFaceDetect,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, pushWithStageHost)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	_pusher->setPushHost(kHost);
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMoved,
		kUid, eventTime, kDVRType, kChannelID, kChannelName);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, DVRPushHumanImage)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, kImageURL);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, DVRPushLowBattery)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRLowBattery,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, kImageURL);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, StandalonePushLowBattery)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneLowBattery,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, kImageURL);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, DVRPushBatteryFull)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRBatteryFullCharged,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, kImageURL);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, DVRPushDefectBattery)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRDefectBattery,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, kImageURL);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, firmwareAvailable)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kFirmwareAvailable,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, kImageURL);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, upgradeSuccess)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kUpgradeSuccess,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, kImageURL);
	EXPECT_EQ(result, 0);
}

TEST_F(MockDevicePushTest, upgradeFail)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushImageNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kUpgradeFail,
		kUid, eventTime, kDVRType, kChannelID, kChannelName, kImageURL);
	EXPECT_EQ(result, 0);
}