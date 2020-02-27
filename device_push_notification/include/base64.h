#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A

#include <string>

namespace nightowl_utils
{
std::string base64_encode(const ::std::string& bindata);

std::string base64_decode(const ::std::string& bindata);

std::string urlEncode(std::string s);
} //nightowl_utils

#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */