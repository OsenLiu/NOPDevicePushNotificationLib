#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <uploadimage.h>
#include <curlsender.h>

#include "mockihttpsender.h"

namespace
{
const std::string kUid = "CLYUAH14ZVRWVN6GU1D1";
const std::string kImagePath = "test.png";
const std::string kMockHttpURL = "https://asia-upload-tutk-stg.kalay.us/static/media/1583318616Capture.PNG";
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
	EXPECT_EQ(response.responseCode, 0);
}

TEST(UploadImageTest, uploadImage)
{
	auto sender = std::make_shared<nightowl::NOP::CurlSender>();
	auto uploader = std::make_unique<nightowl::NOP_upload_image::UploadImage>(sender);
	auto response = uploader->upload(kUid, kImagePath);
	printf("image URL: %s", response.text.c_str());
	EXPECT_EQ(response.responseCode, 0);
}