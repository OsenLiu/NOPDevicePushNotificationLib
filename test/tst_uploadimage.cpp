#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <uploadimage.h>
#include <curlsender.h>

#include "mockihttpsender.h"
#include <thread>

namespace
{
const std::string kUid = "FFUU9X3WK1R48G6GY1RJ";
const std::string kImagePath = "test.png";
const std::string kMockHttpURL = "https://asia-upload-tutk-stg.kalay.us/static/media/1583318616Capture.PNG";
const std::string kStageUploadServer = "asia-upload-tutk-stg.kalay.us";
} //namespace

class MockUploadImageTest : public testing::Test
{
protected:
	void SetUp() override
	{
		_sender = std::make_shared<nightowl::NOP::MockIHTTPSender>();
		_uploader = std::make_unique<nightowl::NOP_upload_image::UploadImage>(_sender);
	}

	void TearDown() override
	{
	}

	std::shared_ptr<nightowl::NOP::MockIHTTPSender> _sender;
	std::unique_ptr<nightowl::NOP_upload_image::UploadImage> _uploader;
};

TEST_F(MockUploadImageTest, uploadImage)
{
	nightowl::NOP_Push_Notification::IHttpSender::Response mockResponse;
	mockResponse.responseCode = 0;
	mockResponse.text = kMockHttpURL;
	EXPECT_CALL(*_sender, post(testing::_, testing::_)).WillOnce(testing::Return(mockResponse));
	auto response = _uploader->upload(kUid, kImagePath);
	EXPECT_EQ(response.responseCode, 200);
}

TEST(UploadImageTest, uploadImage)
{
	auto sender = std::make_shared<nightowl::NOP::CurlSender>();
	auto uploader = std::make_unique<nightowl::NOP_upload_image::UploadImage>(sender);
	auto response = uploader->upload(kUid, kImagePath);
	printf("image URL: %s\n", response.text.c_str());
	EXPECT_EQ(response.responseCode, 200);
}

TEST(UploadImageTest, uploadImageToStage)
{
	auto sender = std::make_shared<nightowl::NOP::CurlSender>();
	auto uploader = std::make_unique<nightowl::NOP_upload_image::UploadImage>(sender);
	uploader->setPushHost(kStageUploadServer);
	auto response = uploader->upload(kUid, kImagePath);
	printf("image URL: %s\n", response.text.c_str());
	EXPECT_EQ(response.responseCode, 200);
}

TEST(UploadImageTest, uploadTwentyImage)
{
	auto sender = std::make_shared<nightowl::NOP::CurlSender>();
	auto uploader = std::make_unique<nightowl::NOP_upload_image::UploadImage>(sender);
	for (auto i = 0; i < 10; ++i) {
		auto response = uploader->upload(kUid, kImagePath);
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		printf("image URL: %s\n", response.text.c_str());
		EXPECT_EQ(response.responseCode, 200);
	}
	
}