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
    } else {
        const char *base = "{\"HKEY_LOCAL_MACHINE\":{\"software\":{}},\"HKEY_CURRENT_USER\":{\"software\":{}}}";
        m_Doc.Parse(base);
    }
    auto && alloc = m_Doc.GetAllocator();
    const char *pSubKey = (sRoot2 != nullptr) ? sRoot2 : "software";
    rootPath = std::string{hRootKey->key} + "/" + pSubKey + "/" + sCompany + "/" + sApp;

    m_hRootKey.SetObject();
    if (!m_hRootKey.HasMember("version"))
        m_hRootKey.AddMember(Value("version"), Value(sVersion, alloc), alloc);

    if(!m_Doc[hRootKey->key][pSubKey].HasMember(sCompany))
        m_Doc[hRootKey->key][pSubKey].AddMember(Value{sCompany, alloc}, Value{Type::kObjectType}, alloc);
    
    if(!m_Doc[hRootKey->key][pSubKey][sCompany].HasMember(sApp))
        m_Doc[hRootKey->key][pSubKey][sCompany].AddMember(Value{sApp, alloc}, m_hRootKey, alloc);
    

    m_bInitialized = true;
    return m_bInitialized;
}

void CRegMgr::Term()
{
    FILE *jfp = fopen("LithTech.reg.json", "w");
    if(jfp)
    {
        FileWriteStream osw(jfp, iobuffer, sizeof(iobuffer));
        Writer<FileWriteStream> writer(osw);
        m_Doc.Accept(writer);
        fclose(jfp);
    }
}

bool CRegMgr::SetSubKey(const char* sSubKey){return true;}
bool CRegMgr::Set(const char* sKey, const char* sValue){return true;}
bool CRegMgr::Set(const char* sKey, void* pValue, int nLen){return true;}
bool CRegMgr::Set(const char* sKey, DWORD nValue){return true;}

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
    } else {
        auto && a = m_Doc.GetAllocator();
        m_hRootKey.AddMember(Value{sKey,a}, Value{nDef}, a);
    }
    return nDef;
}

void* CRegMgr::Get(const char* sKey, void* pBuf, UINT32& nBufSize, void* pDef, UINT32 nDefSize){return pDef;}
bool CRegMgr::Delete(const char* sKey){return true;}
bool CRegMgr::DeleteApp(){return true;}
bool CRegMgr::DeleteSubKey(){return true;}
bool CRegMgr::DeleteUnderSubKey(const char* sKey){return true;}
  
