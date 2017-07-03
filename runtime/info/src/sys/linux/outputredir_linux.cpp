
#ifndef __LIBLTINFO_H__
#include "libltinfo.h"
#endif


#ifdef LIBLTINFO_OUTPUT_REDIRECTION

#ifndef __OUTPUTREDIR_H__
#include "outputredir.h"
#endif

#include <ltassert.h>
#include <dsys.h>
#include <iostream>
#include <fstream>
#include <memory>

typedef std::ofstream* file_pt;
//	-------------------------------------------------------------------------
bool COutputRedir::OpenLogFile(ECOutput_ReDir logfile, const char* pFilename)
{
	// open a file and associate it with one of the logfile enums
	auto f = new std::ofstream();
	
	f->open(pFilename);

    bool open = f->is_open();
	m_pLogFiles[logfile - OUTPUT_REDIR_FILE0] = (uintptr_t)(f);
	
	return open;
}


//	-------------------------------------------------------------------------
bool COutputRedir::CloseLogFile(ECOutput_ReDir logfile)
{
	// close a file associated with one of the logfile enums
	bool result = false;
	auto f = (file_pt)m_pLogFiles[logfile - OUTPUT_REDIR_FILE0];
	if (f) {
		f->close();
		result = ! f->is_open();
		delete f;

		m_pLogFiles[logfile - OUTPUT_REDIR_FILE0] = 0;
	}
	return result;
}


//	-------------------------------------------------------------------------
void COutputRedir::OutputToFile(uint32 index)
{
	// outputs to the specified logfile
	auto f = (file_pt)m_pLogFiles[index];

	if (f) {
		f->write(m_pPrintBuffer, strlen(m_pPrintBuffer));
	}
}


//	-------------------------------------------------------------------------
void COutputRedir::OutputToCONIO()
{
	// outputs to the system console (printf)
	std::cout << m_pPrintBuffer;
}


//	-------------------------------------------------------------------------
void COutputRedir::OutputToDLL()
{
	// NOT YET IMPLEMENTED
	ASSERT(!"Output redirection to a logging DLL is not yet implemented.  Sorry."); 
}


//	-------------------------------------------------------------------------
void COutputRedir::OutputToASSERT()
{
	// putputs to the new & improved LT_ASSERTX
	//assert
	//(void)( (0) || (_assert(m_pPrintBuffer, __FILE__, __LINE__), 0) );

	ASSERT(!m_pPrintBuffer);
}


//	-------------------------------------------------------------------------
void COutputRedir::OutputToConsole()
{
	// prints to the LithTech in-game console
	dsi_PrintToConsole(m_pPrintBuffer);
}


//	-------------------------------------------------------------------------
void COutputRedir::OutputToIDE()
{
	// outputs to MSDEV

	std::cout << m_pPrintBuffer;

}


#endif // LIBLTINFO_OUTPUT_REDIRECTION
