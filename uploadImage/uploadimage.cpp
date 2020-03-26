#include <sstream>
#include <vector>

#include "uploadimage.h"

namespace {
const std::string kScheme = "https://";
const std::string kURIPath = "/filestorage/api/v1/upload";
const std::string kHost = "smart-notifications.nowlsp.com";
const std::string kRealm = "?realm=tutk";
const std::string kValidation = "validation";
const std::string kUploadFile = "uploadFile";

std::string getURI(std::string scheme, std::string host, std::string path)
{
	std::stringstream ss;
	ss << scheme << host << path << kRealm;
	return ss.str();
}
} //namespace

namespace nightowl {
namespace NOP_upload_image {
UploadImage::UploadImage(std::shared_ptr<NOP_Push_Notification::IHttpSender> sender) :
	_sender(std::move(sender))
{
	_uri = getURI(kScheme, kHost, kURIPath);
}

void UploadImage::setPushHost(const std::string& host)
{
	_uri = getURI(kScheme, host, kURIPath);
}

NOP_Push_Notification::IHttpSender::Response UploadImage::upload(const std::string& uid, const std::string& imagePath)
{
	std::vector<NOP_Push_Notification::IHttpSender::PostInfo> parameters;
	auto addParameter = [&](const std::string& key, const std::string& value, 
		nightowl::NOP_Push_Notification::IHttpSender::ParameterType type) {
		nightowl::NOP_Push_Notification::IHttpSender::PostInfo postInfo;
		postInfo.key = key;
		postInfo.value = value;
		postInfo.type = type;
		parameters.push_back(postInfo);
	};
	addParameter(kValidation, uid, nightowl::NOP_Push_Notification::IHttpSender::ParameterType::kContent);
	addParameter(kUploadFile, imagePath, nightowl::NOP_Push_Notification::IHttpSender::ParameterType::kFile);
	auto res = _sender->post(_uri, parameters);
	return res;
}
} //NOP_upload_image
} //nightowl