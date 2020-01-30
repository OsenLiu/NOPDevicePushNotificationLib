#include "curlsender.h"

#include <curl.h>

namespace
{
const int kCurlInitFail = 99;
} //namespace

namespace nightowl {
namespace NOP {
int CurlSender::send(const std::string& url)
{
	curl_global_init(CURL_GLOBAL_DEFAULT);
	auto curl = curl_easy_init();
	if (!curl) {
		return kCurlInitFail;
	}
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, TRUE);
	curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert-2020-01-01.pem");
	auto res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return res;
}
} //NOP
} //nightowl