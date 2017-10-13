#ifndef RegMgr_H_Private
#define RegMgr_H_Private

#include <vector>
#include <string>

template<typename B>
std::vector<std::basic_string<B>> split(const std::basic_string<B> &src, B sep);

// returns a 7bit encode ascii string base64 representation
// of the bytes from data_ptr
std::string b64enc(const void *data_ptr, size_t len);

// returns the decoded base64, memcpy'ed into data_ptr if len is large
// enough to hold the decoded data
bool b64dec(const std::string &b64str, void *data_ptr, size_t len);

#endif // RegMgr_H_Private