/*
   A registry manager backed by a JSON document
   Rene Kjellerup (c) 2017, 
   release under GNU General Public License version 3 or later
   see https://www.gnu.org/licenses/gpl.html
*/
#include "linregmgr.h"

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <sstream>

bool CRegMgr::Init(const char* sCompany, const char* sApp, const char* sVersion, const char* sSubKey = nullptr, void* hRootKey = nullptr, char* sRoot2 = nullptr)
{
    std::ifstream json_file("LithTech.reg.json");
    if(json_file.is_open())
    {
        std::stringstream buff;
        buff << json_file.rdbuf();
        m_Doc.Parse(buff.str().c_str());
    }
    m_bInitialized = true;
    return m_bInitialized;
}

void CRegMgr::Term()
{
    rapidjson::StringBuffer buf;
    std::ofstream outf("LithTech.reg.json");
    rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
    m_Doc.Accept(writer);
    outf << buf.GetString();
    outf.close();
}

bool CRegMgr::SetSubKey(const char* sSubKey){return true;}
bool CRegMgr::Set(const char* sKey, const char* sValue){return true;}
bool CRegMgr::Set(const char* sKey, void* pValue, int nLen){return true;}
bool CRegMgr::Set(const char* sKey, DWORD nValue){return true;}
char* CRegMgr::Get(const char* sKey, char* sBuf, UINT32& nBufSize, const char* sDef = NULL){return nullptr;}
uint32 CRegMgr::Get(const char* sKey, DWORD nDef = 0){return 0;}
void* CRegMgr::Get(const char* sKey, void* pBuf, UINT32& nBufSize, void* pDef = NULL, UINT32 nDefSize = 0){return nullptr;}
bool CRegMgr::Delete(const char* sKey){return true;}
bool CRegMgr::DeleteApp(){return true;}
bool CRegMgr::DeleteSubKey(){return true;}
bool CRegMgr::DeleteUnderSubKey(const char* sKey){return true;}
  