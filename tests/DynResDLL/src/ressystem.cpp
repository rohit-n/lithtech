/* 
  my template c++ file which implements the internal resource 
  lookup and storage
*/

#include "dynres.h"
#include "../src/resources.h" // from myres.rc
#include <string>
#include <unordered_map>

static std::unordered_map<uint32, std::string> g_string_table;

void Add2StringTable(uint32 id, const char* str)
{
    g_string_table[id] = std::string{str};
}


const char* LoadString(uint32 id)
{
    auto res = g_string_table.find(id);
    if(res != g_string_table.end())
        return res->second.c_str()
    else
        return nullptr;
}

void setup_string_tables() { // all discardable string table labels here
  Add2StringTable(IDS_SCMD_LOGINOK, "SCMD login successful."); 
  Add2StringTable(IDS_SCMD_ADMINLOGGEDIN,  "Admin already logged into SCMD.");
  Add2StringTable(IDS_SCMD_INCORRECTPASSWORD, "Incorrect SCMD password.");
}