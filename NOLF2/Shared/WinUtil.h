#ifndef __WINUTIL_H
#define __WINUTIL_H

#ifndef BOOL
	typedef int		    BOOL;
	#define FALSE		    0
	#define TRUE		    1
#endif

#ifndef DWORD
	typedef unsigned long	DWORD;
#endif

class CWinUtil
{
public:

	static BOOL GetMoviesPath (char* strPath);
	static BOOL DirExist (char const* strPath);
	static BOOL CreateDir (char const* strPath);
	static BOOL FileExist (char const* strPath);

	static BOOL	CopyDir( char const* pSrc, char const* pDest );
	static BOOL	EmptyDir( char const* pDir );
	static BOOL RemoveDir( char const* pDir );

	static DWORD WinGetPrivateProfileString (const char* lpAppName, const char* lpKeyName, const char* lpDefault, char* lpReturnedString, DWORD nSize, const char* lpFileName);
	static DWORD WinWritePrivateProfileString (const char* lpAppName, const char* lpKeyName, const char* lpString, const char* lpFileName);

	static void DebugOut (char const* str);
	static void DebugBreak();
	static float GetTime();

	static char* GetFocusWindow();

	static void WriteToDebugFile (char const* strText);
};

#ifdef __LINUX
void getLevelName(const std::string&,char*);
#include <dlfcn.h>
#include <linux/stddef.h>
// copied definition from unistd.h
extern "C" int rmdir (const char *__path) __THROW __nonnull ((1));
extern "C" char* getcwd (char *__path, size_t __len) __THROW __nonnull ((1));

static inline int _rmdir(const char *p){
	return rmdir(p);
}

static inline char* _getcwd(char *p, size_t l){
	return getcwd(p, l);
}

static inline void* LoadLibrary(const char *soname) {
	return ::dlopen(soname, RTLD_NOW);
}

static inline void* GetProcAddress(void *h, const char *fn_name) {
	return ::dlsym(h, fn_name);
}

static inline int FreeLibrary(void *handle) {
	return ::dlclose(handle);
}

#endif

#endif
