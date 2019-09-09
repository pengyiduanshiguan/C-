#pragma once 
#define _CRT_SECURE_NO_WARNINGS


#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif

#include <UIlib.h>
#include "mysql.h"
using namespace DuiLib;

string UnicodeToANSI(const CDuiString& str);
CDuiString ANSIToUnicode(const string& str);



