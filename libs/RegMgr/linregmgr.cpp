/*
   A registry manager backed by a JSON document
   Rene Kjellerup (c) 2017, 
   release under GNU General Public License version 3 or later
   see https://www.gnu.org/licenses/gpl.html
*/
#include "linregmgr.h"

#include <fstream>
#include <vector>
#include "base_string_manip.h"

using nlohmann::json;
/*
the json registry:
{
    'HKEY_CURRENT_USER':{
        'software':{
            'LithTech': {
                'F.E.A.R': {
                    'version': '1.0'
                }
            }
        }
    },
    'HKEY_LOCAL_MACHINE': {
        'software':{
            'LithTech': {
                'Game1': {
                    'version':'1.0',
                    'gamma': 5,
                    'brightness': 4,
                    'vulkan':{
                        'sheight': 1080,
                        'swidth': 1980,
                        'anti-alias':'x2'
                    }
                },
                'Game2': {
                    'version':'1.1',
                    'gamma': 2,
                    'brightness': 8,
                    'vulkan':{
                        'sheight': 1080,
                        'swidth': 1980,
                        'anti-alias':'off'
                    }
                }
            }
        }
    }
}
*/
struct rootKeys
{
    const char* key;
};

rootKeys hklm{"HKEY_LOCAL_MACHINE"};
rootKeys hkcu{"HKEY_CURRENT_USER"};
rootKeys hkcr{"HKEY_CLASSES_ROOT"};
rootKeys hkus{"HKEY_USERS"};

HKEY HKEY_LOCAL_MACHINE{&hklm};
HKEY HKEY_CURRENT_USER{&hkcu};
HKEY HKEY_CLASSES_ROOT{&hkcr};
HKEY HKEY_USERS{&hkus};

bool CRegMgr::Init(const char* sCompany, const char* sApp, const char* sVersion, const char* sSubKey, HKEY hRootKey, const char* sRoot2)
{
    const char *pSubKey = (sRoot2 != nullptr) ? sRoot2 : "software";
    std::string base{"{\"HKEY_LOCAL_MACHINE\":{\"software\":{}},\"HKEY_CURRENT_USER\":{\"software\":{}}}\n"};
    auto a = split(base, ',');
    std::ifstream json_file{"LithTech.reg.json"};
    if (json_file.is_open()) {
        m_jDoc = json::parse(json_file);
    } 
    if (m_jDoc.is_null()) {
        m_jDoc = json::parse(base);
    }
    
    m_jDoc[hRootKey->key][pSubKey][sCompany][sApp]["version"] = sVersion;
    m_jCurKey = &(m_jDoc[hRootKey->key][pSubKey][sCompany][sApp]);

    m_bInitialized = true;
    return m_bInitialized;
}

void CRegMgr::Term()
{
    std::ofstream json_file{"LithTech.reg.json"};
    if(json_file.is_open())
        json_file << m_jDoc << '\n';

    m_bInitialized = false;
}

bool CRegMgr::SetSubKey(const char* sSubKey){
    json &key = *m_jCurKey;
    if (m_jCurKey->is_object())
        m_jCurKey = &(key[sSubKey]);
    else
        return false;
    return true;
}
bool CRegMgr::Set(const char* sKey, const char* sValue){
    json &key = *m_jCurKey;
    if(key[sKey].is_string() || key[sKey].is_null())
        key[sKey] = sValue;
    else
        return false;
    return true;
}

bool CRegMgr::Set(const char* sKey, void* pValue, int nLen){
    json &key = *m_jCurKey;
    if (key[sKey].is_null() || key[sKey].find("base64") != key[sKey].end()) {
        key[sKey]["base64"] = b64enc(pValue, nLen);
        return true;
    }
    return false;
}

bool CRegMgr::Set(const char* sKey, DWORD nValue){
    json &key = *m_jCurKey;
    if(key[sKey].is_null() || key[sKey].is_number_unsigned())
        key[sKey] = nValue;
    else if(!key.is_null())
        return false;
    return true;
}

/*
 * returns the string through sBuf, and creates the key with sDef if it doesn't exist.
 * based on usage in NOLF2 VersionMgr.cpp VersionMgr constructor
 */
const char* CRegMgr::Get(const char* sKey, char* sBuf, UINT32& nBufSize, const char* sDef){
    if((*m_jCurKey)[sKey].is_string()) {
        std::strncpy(sBuf, std::string{(*m_jCurKey)[sKey]}.c_str(), nBufSize);
        return sBuf;
    } else {
        if(sDef != nullptr) {
            (*m_jCurKey)[sKey] = sDef;
            std::strncpy(sBuf, sDef, nBufSize);
        }
        return sDef;
    }
}

DWORD CRegMgr::Get(const char* sKey, DWORD nDef){
    if((*m_jCurKey)[sKey].is_null())
        (*m_jCurKey)[sKey] = nDef;
    if((*m_jCurKey)[sKey].is_number_unsigned())
        return (*m_jCurKey)[sKey];

    return nDef;
}

void* CRegMgr::Get(const char* sKey, void* pBuf, UINT32& nBufSize, void* pDef, UINT32 nDefSize){
    json &key = *m_jCurKey;
    if(key[sKey].is_object()) {
        if(key[sKey].find("base64") != key[sKey].end())
            if(b64dec(key[sKey]["base64"], pBuf, nBufSize))
                return pBuf;
    } else if(pDef != nullptr) {
        Set(sKey, pDef, nDefSize);
        return Get(sKey, pBuf, nBufSize);
    }
    return nullptr;
}

bool CRegMgr::Delete(const char* sKey){return true;}
bool CRegMgr::DeleteApp(){return true;}
bool CRegMgr::DeleteSubKey(){return true;}
bool CRegMgr::DeleteUnderSubKey(const char* sKey){return true;}
  
template<typename B>
std::vector<std::basic_string<B>> split(const std::basic_string<B> &src, B sep)
{
    if(src.empty())
        return std::vector<std::basic_string<B>>();

    using sizeT = typename std::basic_string<B>::size_type;
    std::vector<std::basic_string<B>> vec{};
    sizeT start = 0, pos = 0;
    sizeT e = std::basic_string<B>::npos;
    while((pos = src.find(sep, start)) != e) {      
        vec.emplace_back(src.substr(start,(pos - start)));
        start = ++pos;
    }
    vec.emplace_back(src.substr(start,(pos - start)));
    
    return vec;        
}

#include "cppcodec/base64_rfc4648.hpp"

std::string b64enc(const void *ptr, size_t len)
{
    using base64 = cppcodec::base64_rfc4648;
    std::vector<uint8_t> data(len);
    memcpy(data.data(), ptr, len);
    return base64::encode(data);
}

bool b64dec(const std::string &b64str, void *ptr, size_t len)
{
    using base64 = cppcodec::base64_rfc4648;
    try {
        auto decoded = base64::decode(b64str);
        if(len < decoded.size())
            return false;
        memcpy(ptr,decoded.data(), len);
    }
    catch (cppcodec::parse_error)
    {
        return false;
    }
    return true;    
}