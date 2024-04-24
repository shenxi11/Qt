#ifndef TRY_H
#define TRY_H

#pragma once
#include <windows.h>
#include <DbgHelp.h>

LONG WINAPI ExceptionFilter(LPEXCEPTION_POINTERS lpExceptionInfo);


#endif // TRY_H
