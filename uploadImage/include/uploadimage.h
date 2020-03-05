#ifndef NIGHTOWL_NOP_UPLOAD_IMAGE_H
#define NIGHTOWL_NOP_UPLOAD_IMAGE_H

#include <string>
#include <memory>

#include <iHttpSender.h>

namespace nightowl
{
namespace NOP_upload_image
{
// UploadImage uploads the image to the uploading service.
// UploadImage is created with sender. The senders needs support https protocol.
// Example:
//    auto response = uploader->upload(kUid, kImagePath);
//    printf("image URL: %s", response.text.c_str());
class UploadImage
{
public:
	UploadImage(std::shared_ptr<NOP_Push_Notification::IHttpSender> sender);
	~UploadImage() = default;

	UploadImage(const UploadImage&) = delete;
	UploadImage& operator=(const UploadImage&) = delete;
	UploadImage(const UploadImage&&) = delete;
	UploadImage& operator=(const UploadImage&&) = delete;

	// set host for push notification. The default push host is notifications.no-protect.com. PushNotification will use default host if there isn't host.
	void setPushHost(const std::string& host);

	// upload image with UID 
	// return the result code and the URL
	NOP_Push_Notification::IHttpSender::Response upload(const std::string& uid, const std::string& imagePath);

private:
	std::shared_ptr<NOP_Push_Notification::IHttpSender> _sender{};
	std::string _uri;
};
} //NOP_upload_image
} //nightowl
#endif //NIGHTOWL_NOP_UPLOAD_IMAGE_H
