/** \file utils.h \brief Macros and definitions if not defined in the operation system
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _MSC_VER
#include <windows.h>
#endif	// _MSC_VER

#ifdef __cplusplus
extern "C" {
#endif

#ifndef min
	/** A macro that returns the minimum of a and b if not defined in Operation System. */
        #define min(a,b)        ((a) <= (b) ? (a) : (b))
#endif

#ifndef max
	/** A macro that returns the maximum of a and b if not defined in Operation System. */
        #define max(a,b)        ((a) >= (b) ? (a) : (b))
#endif

#ifndef TRUE
	/** Define TRUE if not defined in Operation System. */
	#define TRUE 1
#endif

#ifndef FALSE
	/** Define FALSE if not defined in Operation System. */
	#define FALSE 0
#endif


typedef char TCHAR;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef long LONG;
typedef int BOOL;
typedef char *HANDLE;
typedef char *LPSTR;
typedef char *LPTSTR;
typedef const char *LPCSTR;
typedef const char *LPCTSTR;
typedef wchar_t *LPWSTR;
typedef const wchar_t *LPCWSTR;
typedef void *HMODULE;
typedef DWORD WPARAM;
typedef DWORD LPARAM;
typedef void *HINSTANCE;
typedef unsigned char* PBYTE;
typedef unsigned long ULONG;
typedef char CHAR;
typedef unsigned char UCHAR;


#define far

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)           ((BYTE)(((WORD)(w) >> 8) & 0xFF))

#ifndef MB_OK
#define MB_OK 0
#endif	// MB_OK

#define O_BINARY 0

#define MAX_PATH 256
#define WINAPI
#define CALLBACK
#define __cdecl


#ifdef __cplusplus
}; //extern "C"
#endif

inline void *mycopy(void *dest, const void *src, size_t count)
{
	char *pDest=static_cast<char *>(dest);
	const char *pSrc=static_cast<const char *>(src);

	if( pDest>pSrc && pDest<pSrc+count )
	{
		for(size_t i=count-1; i<=0; ++i)
		{
			pDest[i]=pSrc[i];
		}
	}
	else
	{
		for(size_t i=0; i<count; ++i)
		{
			pDest[i]=pSrc[i];
		}
	}

	return pDest;
}

// Add:2016.6.6 MaKai-[SM2&SM4$openssl] Start
#ifndef _LZ_USED_COMMAND
inline void __COMMAND_XX0(){return;};
inline void __COMMAND_XX1(){return;};
inline void __COMMAND_XX2(){return;};
#else
inline void __COMMAND_XX0()
{
	_asm
	{
		jmp label_1
			push -1
			push 111111
			push 222222
			push eax
			pop eax
label_1:
	}
};

inline void __COMMAND_XX1()
{
	_asm
	{
		jmp label_2
			push -1
			push 111111
			push 222222
			push eax
			pop eax
			pop eax
			pop eax
			pop eax
			pop eax
label_2:
	}
};

inline void __COMMAND_XX2()
{
	_asm
	{
		jmp label_1
			push -1
			push 111111
			push 222222
label_1:
		jmp label_2
			push eax
			pop eax
label_2:
		jmp label_3
			pop eax
			pop eax
			pop eax
			pop eax
label_3:
	}
};

#endif
// Add:2016.6.6 MaKai-[SM2&SM4$openssl] End
#endif	// _UTILS_H_
