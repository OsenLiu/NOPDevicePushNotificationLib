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
} //namespace

class DevicePushTest : public testing::Test
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

TEST_F(DevicePushTest, StandaloneDevicePushMotion)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneMotion, 
		kUid, eventTime, kStandaloneDeviceType, kStandaloneName);
	EXPECT_EQ(result, 0);
}

TEST_F(DevicePushTest, StandaloneDevicePushHuman)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kStandaloneHuman,
		kUid, eventTime, kStandaloneDeviceType, kStandaloneName);
	EXPECT_EQ(result, 0);
}

TEST_F(DevicePushTest, DVRPushHuman)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRHuman, 
		kUid, eventTime, kDVRType, kDVRName);
	EXPECT_EQ(result, 0);
}

TEST_F(DevicePushTest, DVRPushMoved)
{
	ON_CALL(*_sender, send(testing::_)).WillByDefault(testing::Return(0));
	auto eventTime = static_cast<long int>(std::time(nullptr));
	auto result = _pusher->sendPushNotication(nightowl::NOP_Push_Notification::PushNotification::EventKey::kDVRMoved,
		kUid, eventTime, kDVRType, kDVRName);
	EXPECT_EQ(result, 0);
}