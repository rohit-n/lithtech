/*
   A registry manager backed by a JSON document
   Rene Kjellerup (c) 2017, 
   release under GNU General Public License version 3 or later
   see https://www.gnu.org/licenses/gpl.html
*/
#include "linregmgr.h"

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <cstdio>
#include <vector>
#include "base_string_manip.h"

using std::FILE;
using std::fopen;
using std::fclose;
using rapidjson::Document;
using rapidjson::Writer;
using rapidjson::Type;
using rapidjson::Value;
using rapidjson::FileReadStream;
using rapidjson::FileWriteStream;
/*
using rapidjson::IStreamWrapper;
using rapidjson::OStreamWrapper;
*/
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
    FILE *jfp = fopen("LithTech.reg.json", "r");
    if(jfp)
    {
        FileReadStream isw(jfp, iobuffer, sizeof(iobuffer));
        m_Doc.ParseStream(isw);
        fclose(jfp);
        memset(iobuffer,0,sizeof(iobuffer));
    } else {
        const char *base = "{\"HKEY_LOCAL_MACHINE\":{\"software\":{}},\"HKEY_CURRENT_USER\":{\"software\":{}}}";
        m_Doc.Parse(base);
    }
    auto && alloc = m_Doc.GetAllocator();
    const char *pSubKey = (sRoot2 != nullptr) ? sRoot2 : "software";
    rootPath = std::string{hRootKey->key} + "/" + pSubKey + "/" + sCompany + "/" + sApp;

    if(!m_Doc[hRootKey->key][pSubKey].IsObject())
        m_Doc[hRootKey->key][pSubKey].SetObject();

    if(!m_Doc[hRootKey->key][pSubKey].HasMember(sCompany))
        m_Doc[hRootKey->key][pSubKey].AddMember(Value{sCompany, alloc}, Value{Type::kObjectType}, alloc);
    
    if(!m_Doc[hRootKey->key][pSubKey][sCompany].HasMember(sApp)) {
        m_Doc[hRootKey->key][pSubKey][sCompany].AddMember(Value{sApp, alloc}, Value{Type::kObjectType}, alloc);
    } else {
        m_hRootKey.CopyFrom(m_Doc[hRootKey->key][pSubKey][sCompany][sApp], alloc);
    }

    if(!m_hRootKey.IsObject())
        m_hRootKey.SetObject();
    if (!m_hRootKey.HasMember("version"))
        m_hRootKey.AddMember(Value{"version"}, Value{sVersion, alloc}, alloc);
    else
        m_hRootKey["version"].SetString(sVersion,alloc);

    m_bInitialized = true;
    return m_bInitialized;
}

void CRegMgr::Term()
{
    auto path = split(rootPath, '/');
    m_Doc[path.at(0).c_str()][path.at(1).c_str()][path.at(2).c_str()][path.at(3).c_str()] = m_hRootKey;
    FILE *jfp = fopen("LithTech.reg.json", "w");
    if(jfp)
    {
        FileWriteStream osw(jfp, iobuffer, sizeof(iobuffer));
        Writer<FileWriteStream> writer(osw);
        m_Doc.Accept(writer);
        fwrite("\n",1,1,jfp);
        fclose(jfp);
    }
    m_bInitialized = false;
}

bool CRegMgr::SetSubKey(const char* sSubKey){
    auto && a = m_Doc.GetAllocator();
    if(m_hRootKey.HasMember(sSubKey)){
        if(! m_hRootKey[sSubKey].IsObject())
            m_hRootKey[sSubKey].SetObject();
    } else {
        m_hRootKey.AddMember(Value{sSubKey, a}, Value{Type::kObjectType}, a);
    }

    m_hRootKey.CopyFrom(m_hRootKey[sSubKey], a);
    rootPath += std::string{"/"} + sSubKey;
    return true;
}
bool CRegMgr::Set(const char* sKey, const char* sValue){
    if(m_hRootKey.HasMember(sKey) ){ 
        if(m_hRootKey[sKey].IsString()) {
            auto &&a = m_Doc.GetAllocator();
            m_hRootKey[sKey].SetString(sValue, a);
            return true;
        }
    } else {
        auto &&a = m_Doc.GetAllocator();
        m_hRootKey.AddMember(Value{sKey,a}, Value{sValue, a}, a);
        return true;
    }
    return false;
}
bool CRegMgr::Set(const char* sKey, void* pValue, int nLen){
    if(m_hRootKey.HasMember(sKey) ){ 
        if(m_hRootKey[sKey].IsObject() && m_hRootKey[sKey].HasMember("base64")) {
            auto &&a = m_Doc.GetAllocator();
            m_hRootKey[sKey]["base64"].SetString(b64enc(pValue,nLen).c_str(),a);
            return true;
        }
    } else {
        auto &&a = m_Doc.GetAllocator();
        Value b64data;
        b64data.SetObject();
        b64data.AddMember(Value{"base64",a}, Value{b64enc(pValue, nLen).c_str(),a}, a);
        m_hRootKey.AddMember(Value{sKey,a}, b64data, a);
        return true;
    }

    return false;
}
bool CRegMgr::Set(const char* sKey, DWORD nValue){
    if(m_hRootKey.HasMember(sKey) ){ 
        if(m_hRootKey[sKey].IsNumber()) {
            m_hRootKey[sKey].SetUint(nValue);
            return true;
        }
    } else {
        auto &&a = m_Doc.GetAllocator();
        m_hRootKey.AddMember(Value{sKey,a}, Value{nValue},a);
    }
    return false;
}

/*
 * returns the string through sBuf, and creates the key with sDef if it doesn't exist.
 * based on usage in NOLF2 VersionMgr.cpp VersionMgr constructor
 */
const char* CRegMgr::Get(const char* sKey, char* sBuf, UINT32& nBufSize, const char* sDef){
    if(m_hRootKey.HasMember(sKey) ){ 
        if(m_hRootKey[sKey].IsString())
            std::strncpy(sBuf, m_hRootKey[sKey].GetString(), nBufSize);
            return sBuf;
    } else {
        if(sDef != nullptr) {
            auto && a = m_Doc.GetAllocator();
            m_hRootKey.AddMember(Value{sKey,a}, Value{sDef, a}, a);
            std::strncpy(sBuf, sDef, nBufSize);
        }
    }
    return sDef;
}

DWORD CRegMgr::Get(const char* sKey, DWORD nDef){
    if(m_hRootKey.HasMember(sKey) ){ 
        if(m_hRootKey[sKey].IsNumber())
            return m_hRootKey[sKey].GetUint();
        return -1;
    } else {
        auto && a = m_Doc.GetAllocator();
        m_hRootKey.AddMember(Value{sKey,a}, Value{nDef}, a);
    }
    return nDef;
}

void* CRegMgr::Get(const char* sKey, void* pBuf, UINT32& nBufSize, void* pDef, UINT32 nDefSize){
    if(m_hRootKey.HasMember(sKey) ){ 
        if(m_hRootKey[sKey].IsObject() && m_hRootKey[sKey].HasMember("base64")) {
            if(!b64dec(std::string{m_hRootKey[sKey]["base64"].GetString()},pBuf,nBufSize))
                return nullptr;
            return pBuf;
        }
    } else {
        Set(sKey, pDef, nDefSize);
        return Get(sKey, pBuf, nBufSize);
    }
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