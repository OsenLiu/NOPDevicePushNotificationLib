#include "curlsender.h"

#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>

namespace
{
const int kCurlInitFail = 99;
const int kCurlFdsetFail = 100;
const int kCurlTimeoutFail = 101;
const int kTimeoutInSecond = 20L;
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
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, kTimeoutInSecond);
	auto res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return res;
}

NOP_Push_Notification::IHttpSender::Response CurlSender::post(const std::string& url, 
    const std::vector<NOP_Push_Notification::IHttpSender::PostInfo> parameters)
{
    CURL* curl;

    int still_running = 0;
    NOP_Push_Notification::IHttpSender::Response response;
    response.responseCode = 0;

    struct curl_httppost* formpost = NULL;
    struct curl_httppost* lastptr = NULL;
    struct curl_slist* headerlist = NULL;
    static const char buf[] = "Expect:";

    curl = curl_easy_init();
    if (!curl) {
        response.responseCode = kCurlInitFail;
        return response;
    }

    /* Fill in the file upload field. This makes libcurl load data from
   the given file name when curl_easy_perform() is called. */
    for (int i = 0; i < parameters.size(); ++i) {
        auto& parameter = parameters[i];
        CURLformoption formoption = CURLFORM_COPYCONTENTS;

        if (parameter.type == NOP_Push_Notification::IHttpSender::ParameterType::kFile) {
            formoption = CURLFORM_FILE;
        }
        curl_formadd(&formpost,
            &lastptr,
            CURLFORM_COPYNAME, parameter.key.c_str(),
            formoption, parameter.value.c_str(),
            CURLFORM_END);
    }

    /* initialize custom header list (stating that Expect: 100-continue is not
       wanted */
    headerlist = curl_slist_append(headerlist, buf);

    /* what URL that receives this POST */
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);

    auto callback = [](char* contents, size_t size, size_t nmemb, void* userp)  -> size_t {
        ((std::string*)userp)->append(contents, size * nmemb);
        return size * nmemb;
    };
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, (curl_write_callback) callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &(response.text));
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, kTimeoutInSecond);

    auto code = curl_easy_perform(curl);
    if (code == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.responseCode);
    }

    /* always cleanup */
    curl_easy_cleanup(curl);

    /* then cleanup the formpost chain */
    curl_formfree(formpost);
    /* free slist */
    curl_slist_free_all(headerlist);
    return response;
}
} //NOP
} //nightowl