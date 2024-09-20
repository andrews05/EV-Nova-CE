#include "macros/setsym.h"


// vars

SETCGLOB(0x005914D8, g_nv_runInAWindow);
SETCGLOB(0x005914D9, g_nv_runInAWindowPref);
SETCGLOB(0x005914E0, g_nv_noHyperspaceEffects);
SETCGLOB(0x00591560, g_nv_beep1);
SETCGLOB(0x00596D1C, g_nv_mainContext);
SETCGLOB(0x00596D3A, g_nv_debugMode);
SETCGLOB(0x00597950, g_nv_mainBufferCanvas);
SETCGLOB(0x007353F2, g_nv_currentVolume);
SETCGLOB(0x007355DC, g_nv_statusBarAreas);
SETCGLOB(0x00735684, g_nv_mainFontFace);
SETCGLOB(0x007CDAB0, g_nv_debugLog);
SETCGLOB(0x007D0694, g_nv_newsDialog);
SETCGLOB(0x007D17B8, g_nv_commsDialog);
SETCGLOB(0x007D17C0, g_nv_plunderDialog);
SETCGLOB(0x007D2B84, g_nv_outfitterDialog);
SETCGLOB(0x007D2B8C, g_nv_shipyardDialog);
SETCGLOB(0x007D2B90, g_nv_shipInfoDialog);
SETCGLOB(0x007D2B94, g_nv_playerInfoDialog);
SETCGLOB(0x007D4C0E, g_nv_promptResult);
SETCGLOB(0x007D4D0E, g_nv_gridThumbBounds);
SETCGLOB(0x007D510E, g_nv_gridCellBounds);
SETCGLOB(0x007D51AE, g_nv_gridCellImageBounds);
SETCGLOB(0x007D8298, g_nv_buttonCanvas);
SETCGLOB(0x007DCF94, g_nv_mapDialog);
SETCGLOB(0x00864F40, g_nv_activeDialog);
SETCGLOB(0x00870064, g_nv_currentContext);
SETCGLOB(0x00870078, g_nv_hwnd);
SETCGLOB(0x008700A0, g_nv_screenWidth);
SETCGLOB(0x0087019C, g_nv_screenHeight);
SETCGLOB(0x00870D80, g_nv_argc);
SETCGLOB(0x00870D94, g_nv_argv);
SETCGLOB(0x00870DF8, g_nv_cursor);


// functions

SETCGLOB(0x00503F30, OriginalCRTStartup);
SETCGLOB(0x004D2A80, nv_WinMain);
SETCGLOB(0x00447F20, nv_EvaluteNCBTestExpression);
SETCGLOB(0x00448020, nv_ExecuteNCBSetExpression);
SETCGLOB(0x004622F0, nv_DrawPStringCentered);
SETCGLOB(0x00469CA0, nv_KeyCheck);
SETCGLOB(0x0046AAD0, nv_PlaySound);
SETCGLOB(0x0046f500, nv_LoadFilesInFolder);
SETCGLOB(0x004976B0, nv_ShowAlert);
SETCGLOB(0x00497900, nv_ShowPrompt);
SETCGLOB(0x004B45E0, nv_InitializeMonitor);
SETCGLOB(0x004B6920, nv_SetFontSize);
SETCGLOB(0x004B8D50, nv_ShiftRect);
SETCGLOB(0x004B9070, nv_DrawPict);
SETCGLOB(0x004BC760, nv_DrawText);
SETCGLOB(0x004CEDE0, nv_ProcessDitlEntry);
SETCGLOB(0x004CF960, nv_GetDialogItemAndBounds);
SETCGLOB(0x004CFD30, nv_GetDialogBounds);
SETCGLOB(0x004D86D0, nv_Alloc);
SETCGLOB(0x004D87D0, nv_Free);
SETCGLOB(0x004D9680, nv_ConvertMacPathToWin);
SETCGLOB(0x004ECBD0, nv_SetupScreen);
SETCGLOB(0x004F0EB0, nv_WriteLogFormat);
SETCGLOB(0x004F1080, nv_FlushLog);
SETCGLOB(0x004D2440, nv_Wndproc);

// imports

SETCGLOB(0x0058F984, _imp__wsprintfA);
SETCGLOB(0x0058FA1C, _imp__waveOutWrite);
SETCGLOB(0x0058FA04, _imp__waveOutUnprepareHeader);
SETCGLOB(0x0058FA14, _imp__waveOutSetVolume);
SETCGLOB(0x0058FA00, _imp__waveOutReset);
SETCGLOB(0x0058FA18, _imp__waveOutPrepareHeader);
SETCGLOB(0x0058F9FC, _imp__waveOutOpen);
SETCGLOB(0x0058FA10, _imp__waveOutGetVolume);
SETCGLOB(0x0058F9F8, _imp__waveOutGetNumDevs);
SETCGLOB(0x0058FA0C, _imp__waveOutGetDevCapsA);
SETCGLOB(0x0058FA08, _imp__waveOutClose);
SETCGLOB(0x0058F9F4, _imp__timeGetTime);
SETCGLOB(0x0058FA34, _imp__socket);
SETCGLOB(0x0058FA5C, _imp__shutdown);
SETCGLOB(0x0058FA4C, _imp__setsockopt);
SETCGLOB(0x0058FA58, _imp__sendto);
SETCGLOB(0x0058FA68, _imp__send);
SETCGLOB(0x0058FA54, _imp__recvfrom);
SETCGLOB(0x0058FA60, _imp__recv);
SETCGLOB(0x0058FA80, _imp__libiconv_open);
SETCGLOB(0x0058FA84, _imp__libiconv);
SETCGLOB(0x0058FA48, _imp__getsockopt);
SETCGLOB(0x0058FA44, _imp__getsockname);
SETCGLOB(0x0058FA38, _imp__gethostname);
SETCGLOB(0x0058FA3C, _imp__gethostbyname);
SETCGLOB(0x0058FA6C, _imp__gethostbyaddr);
SETCGLOB(0x0058FA40, _imp__connect);
SETCGLOB(0x0058FA30, _imp__closesocket);
SETCGLOB(0x0058FA50, _imp__bind);
SETCGLOB(0x0058FA64, _imp__accept);
SETCGLOB(0x0058F87C, _imp__WriteFile);
SETCGLOB(0x0058F9E4, _imp__WindowFromPoint);
SETCGLOB(0x0058F6B8, _imp__WidenPath);
SETCGLOB(0x0058F924, _imp__WaitMessage);
SETCGLOB(0x0058F7A0, _imp__WaitForSingleObject);
SETCGLOB(0x0058FA24, _imp__WSAStartup);
SETCGLOB(0x0058FA2C, _imp__WSAGetLastError);
SETCGLOB(0x0058FA28, _imp__WSACleanup);
SETCGLOB(0x0058F7BC, _imp__VirtualUnlock);
SETCGLOB(0x0058F7B4, _imp__VirtualLock);
SETCGLOB(0x0058F990, _imp__ValidateRect);
SETCGLOB(0x0058F8BC, _imp__UpdateWindow);
SETCGLOB(0x0058F8F8, _imp__UnhookWindowsHookEx);
SETCGLOB(0x0058F934, _imp__TranslateMessage);
SETCGLOB(0x0058F758, _imp__TlsSetValue);
SETCGLOB(0x0058F754, _imp__TlsGetValue);
SETCGLOB(0x0058F74C, _imp__TlsFree);
SETCGLOB(0x0058F728, _imp__TlsAlloc);
SETCGLOB(0x0058F6D0, _imp__TextOutA);
SETCGLOB(0x0058F840, _imp__TerminateThread);
SETCGLOB(0x0058F8FC, _imp__SystemParametersInfoA);
SETCGLOB(0x0058F774, _imp__SuspendThread);
SETCGLOB(0x0058F6F4, _imp__StretchDIBits);
SETCGLOB(0x0058F6E8, _imp__StretchBlt);
SETCGLOB(0x0058F748, _imp__SleepEx);
SETCGLOB(0x0058F710, _imp__Sleep);
SETCGLOB(0x0058F80C, _imp__SizeofResource);
SETCGLOB(0x0058F9A0, _imp__ShowWindow);
SETCGLOB(0x0058F988, _imp__ShowCursor);
SETCGLOB(0x0058F8A0, _imp__ShellExecuteA);
SETCGLOB(0x0058F908, _imp__SetWindowsHookExA);
SETCGLOB(0x0058F980, _imp__SetWindowTextA);
SETCGLOB(0x0058F97C, _imp__SetWindowPos);
SETCGLOB(0x0058F978, _imp__SetWindowLongA);
SETCGLOB(0x0058F674, _imp__SetViewportOrgEx);
SETCGLOB(0x0058F9B8, _imp__SetTimer);
SETCGLOB(0x0058F798, _imp__SetThreadPriority);
SETCGLOB(0x0058F610, _imp__SetTextColor);
SETCGLOB(0x0058F66C, _imp__SetTextAlign);
SETCGLOB(0x0058F694, _imp__SetRectRgn);
SETCGLOB(0x0058F994, _imp__SetRect);
SETCGLOB(0x0058F668, _imp__SetROP2);
SETCGLOB(0x0058F6A0, _imp__SetPixelV);
SETCGLOB(0x0058F644, _imp__SetPixel);
SETCGLOB(0x0058F650, _imp__SetPaletteEntries);
SETCGLOB(0x0058F664, _imp__SetMapMode);
SETCGLOB(0x0058F720, _imp__SetLastError);
SETCGLOB(0x0058F8AC, _imp__SetForegroundWindow);
SETCGLOB(0x0058F8B0, _imp__SetFocus);
SETCGLOB(0x0058F868, _imp__SetFilePointer);
SETCGLOB(0x0058F7A4, _imp__SetEvent);
SETCGLOB(0x0058F7F0, _imp__SetErrorMode);
SETCGLOB(0x0058F86C, _imp__SetEndOfFile);
SETCGLOB(0x0058F64C, _imp__SetDeviceGammaRamp);
SETCGLOB(0x0058F6F0, _imp__SetDIBitsToDevice);
SETCGLOB(0x0058F6F8, _imp__SetDIBits);
SETCGLOB(0x0058F654, _imp__SetDIBColorTable);
SETCGLOB(0x0058F970, _imp__SetCursor);
SETCGLOB(0x0058F7EC, _imp__SetCurrentDirectoryA);
SETCGLOB(0x0058F768, _imp__SetConsoleTitleA);
SETCGLOB(0x0058F740, _imp__SetConsoleCtrlHandler);
SETCGLOB(0x0058F928, _imp__SetCapture);
SETCGLOB(0x0058F60C, _imp__SetBkMode);
SETCGLOB(0x0058F624, _imp__SetBkColor);
SETCGLOB(0x0058F960, _imp__SendMessageA);
SETCGLOB(0x0058F630, _imp__SelectPalette);
SETCGLOB(0x0058F608, _imp__SelectObject);
SETCGLOB(0x0058F618, _imp__SelectClipRgn);
SETCGLOB(0x0058F81C, _imp__SearchPathA);
SETCGLOB(0x0058F9D0, _imp__ScreenToClient);
SETCGLOB(0x0058F658, _imp__SaveDC);
SETCGLOB(0x0058F894, _imp__RtlUnwind);
SETCGLOB(0x0058F778, _imp__ResumeThread);
SETCGLOB(0x0058F65C, _imp__RestoreDC);
SETCGLOB(0x0058F890, _imp__ResetEvent);
SETCGLOB(0x0058F7E4, _imp__RemoveDirectoryA);
SETCGLOB(0x0058F79C, _imp__ReleaseMutex);
SETCGLOB(0x0058F8C4, _imp__ReleaseDC);
SETCGLOB(0x0058F92C, _imp__ReleaseCapture);
SETCGLOB(0x0058F93C, _imp__RegisterWindowMessageA);
SETCGLOB(0x0058F900, _imp__RegisterClassA);
SETCGLOB(0x0058F5D4, _imp__RegSetValueExA);
SETCGLOB(0x0058F5D0, _imp__RegQueryValueExA);
SETCGLOB(0x0058F5E0, _imp__RegOpenKeyExA);
SETCGLOB(0x0058F5D8, _imp__RegFlushKey);
SETCGLOB(0x0058F5CC, _imp__RegCreateKeyExA);
SETCGLOB(0x0058F5DC, _imp__RegCloseKey);
SETCGLOB(0x0058F634, _imp__RealizePalette);
SETCGLOB(0x0058F878, _imp__ReadFile);
SETCGLOB(0x0058F788, _imp__QueryPerformanceFrequency);
SETCGLOB(0x0058F770, _imp__QueryPerformanceCounter);
SETCGLOB(0x0058F8EC, _imp__PostQuitMessage);
SETCGLOB(0x0058F920, _imp__PostMessageA);
SETCGLOB(0x0058F930, _imp__PeekMessageA);
SETCGLOB(0x0058F804, _imp__OutputDebugStringA);
SETCGLOB(0x0058F6FC, _imp__OffsetRgn);
SETCGLOB(0x0058F714, _imp__MulDiv);
SETCGLOB(0x0058F8B8, _imp__MoveWindow);
SETCGLOB(0x0058F6A8, _imp__MoveToEx);
SETCGLOB(0x0058F94C, _imp__MessageBoxA);
SETCGLOB(0x0058F974, _imp__MessageBeep);
SETCGLOB(0x0058F9D4, _imp__MapWindowPoints);
SETCGLOB(0x0058F814, _imp__LockResource);
SETCGLOB(0x0058F90C, _imp__LoadStringA);
SETCGLOB(0x0058F810, _imp__LoadResource);
SETCGLOB(0x0058F7AC, _imp__LoadLibraryA);
SETCGLOB(0x0058F7AC, _imp__LoadLibraryA_p);
SETCGLOB(0x0058F950, _imp__LoadIconA);
SETCGLOB(0x0058F918, _imp__LoadCursorA);
SETCGLOB(0x0058F6B0, _imp__LineTo);
SETCGLOB(0x0058F760, _imp__LeaveCriticalSection);
SETCGLOB(0x0058F698, _imp__LPtoDP);
SETCGLOB(0x0058F968, _imp__IsWindowVisible);
SETCGLOB(0x0058F8DC, _imp__IsIconic);
SETCGLOB(0x0058F838, _imp__IsBadWritePtr);
SETCGLOB(0x0058F834, _imp__IsBadReadPtr);
SETCGLOB(0x0058F998, _imp__InvertRect);
SETCGLOB(0x0058F98C, _imp__InvalidateRect);
SETCGLOB(0x0058F734, _imp__InitializeCriticalSection);
SETCGLOB(0x0058F5E8, _imp__InitCommonControls);
SETCGLOB(0x0058F830, _imp__HeapFree);
SETCGLOB(0x0058F82C, _imp__HeapAlloc);
SETCGLOB(0x0058F880, _imp__GlobalUnlock);
SETCGLOB(0x0058F7B8, _imp__GlobalSize);
SETCGLOB(0x0058F71C, _imp__GlobalMemoryStatus);
SETCGLOB(0x0058F7C0, _imp__GlobalFree);
SETCGLOB(0x0058F7B0, _imp__GlobalAlloc);
SETCGLOB(0x0058F7FC, _imp__GetWindowsDirectoryA);
SETCGLOB(0x0058F95C, _imp__GetWindowTextLengthA);
SETCGLOB(0x0058F9B4, _imp__GetWindowTextA);
SETCGLOB(0x0058F8E0, _imp__GetWindowRect);
SETCGLOB(0x0058F8D0, _imp__GetWindowLongA);
SETCGLOB(0x0058F7F4, _imp__GetVolumeInformationA);
SETCGLOB(0x0058F718, _imp__GetVersionExA);
SETCGLOB(0x0058F88C, _imp__GetVersion);
SETCGLOB(0x0058F5C8, _imp__GetUserNameA);
SETCGLOB(0x0058F784, _imp__GetTimeZoneInformation);
SETCGLOB(0x0058F744, _imp__GetTickCount);
SETCGLOB(0x0058F670, _imp__GetTextMetricsA);
SETCGLOB(0x0058F6CC, _imp__GetTextExtentPoint32A);
SETCGLOB(0x0058F628, _imp__GetTextColor);
SETCGLOB(0x0058F85C, _imp__GetTempPathA);
SETCGLOB(0x0058F77C, _imp__GetSystemTime);
SETCGLOB(0x0058F8B4, _imp__GetSystemMetrics);
SETCGLOB(0x0058F7F8, _imp__GetSystemDirectoryA);
SETCGLOB(0x0058F61C, _imp__GetStockObject);
SETCGLOB(0x0058F858, _imp__GetStdHandle);
SETCGLOB(0x0058F83C, _imp__GetStartupInfoA);
SETCGLOB(0x0058F68C, _imp__GetRgnBox);
SETCGLOB(0x0058F700, _imp__GetRegionData);
SETCGLOB(0x0058F72C, _imp__GetProcessHeap);
SETCGLOB(0x0058F73C, _imp__GetProcAddress);
SETCGLOB(0x0058F73C, _imp__GetProcAddress_p);
SETCGLOB(0x0058F640, _imp__GetPixel);
SETCGLOB(0x0058F958, _imp__GetParent);
SETCGLOB(0x0058FA74, _imp__GetOpenFileNameA);
SETCGLOB(0x0058F6E4, _imp__GetObjectType);
SETCGLOB(0x0058F738, _imp__GetModuleHandleA);
SETCGLOB(0x0058F76C, _imp__GetModuleFileNameA);
SETCGLOB(0x0058F8D4, _imp__GetMenu);
SETCGLOB(0x0058F6EC, _imp__GetMapMode);
SETCGLOB(0x0058F860, _imp__GetLogicalDrives);
SETCGLOB(0x0058F780, _imp__GetLocalTime);
SETCGLOB(0x0058F724, _imp__GetLastError);
SETCGLOB(0x0058F8A8, _imp__GetKeyState);
SETCGLOB(0x0058F800, _imp__GetFullPathNameA);
SETCGLOB(0x0058F914, _imp__GetForegroundWindow);
SETCGLOB(0x0058F870, _imp__GetFileSize);
SETCGLOB(0x0058F7D0, _imp__GetFileAttributesA);
SETCGLOB(0x0058F84C, _imp__GetEnvironmentStrings);
SETCGLOB(0x0058F864, _imp__GetDriveTypeA);
SETCGLOB(0x0058F9C4, _imp__GetDlgCtrlID);
SETCGLOB(0x0058F9A4, _imp__GetDialogBaseUnits);
SETCGLOB(0x0058F648, _imp__GetDeviceGammaRamp);
SETCGLOB(0x0058F604, _imp__GetDeviceCaps);
SETCGLOB(0x0058F948, _imp__GetDesktopWindow);
SETCGLOB(0x0058F6C4, _imp__GetDIBits);
SETCGLOB(0x0058F6DC, _imp__GetDIBColorTable);
SETCGLOB(0x0058F8C0, _imp__GetDC);
SETCGLOB(0x0058F9E0, _imp__GetCursorPos);
SETCGLOB(0x0058F730, _imp__GetCurrentThreadId);
SETCGLOB(0x0058F844, _imp__GetCurrentThread);
SETCGLOB(0x0058F820, _imp__GetCurrentProcessId);
SETCGLOB(0x0058F884, _imp__GetCurrentProcess);
SETCGLOB(0x0058F6A4, _imp__GetCurrentPositionEx);
SETCGLOB(0x0058F6C0, _imp__GetCurrentObject);
SETCGLOB(0x0058F854, _imp__GetCurrentDirectoryA);
SETCGLOB(0x0058F764, _imp__GetConsoleTitleA);
SETCGLOB(0x0058F848, _imp__GetCommandLineA);
SETCGLOB(0x0058F688, _imp__GetClipRgn);
SETCGLOB(0x0058F964, _imp__GetClientRect);
SETCGLOB(0x0058F62C, _imp__GetBkColor);
SETCGLOB(0x0058F9D8, _imp__GetAsyncKeyState);
SETCGLOB(0x0058F660, _imp__GdiFlush);
SETCGLOB(0x0058F818, _imp__FreeLibrary);
SETCGLOB(0x0058F850, _imp__FreeEnvironmentStringsA);
SETCGLOB(0x0058F874, _imp__FlushFileBuffers);
SETCGLOB(0x0058F910, _imp__FindWindowA);
SETCGLOB(0x0058F808, _imp__FindResourceA);
SETCGLOB(0x0058F7D8, _imp__FindNextFileA);
SETCGLOB(0x0058F7D4, _imp__FindFirstFileA);
SETCGLOB(0x0058F7DC, _imp__FindClose);
SETCGLOB(0x0058F8F4, _imp__FillRect);
SETCGLOB(0x0058F6BC, _imp__FillPath);
SETCGLOB(0x0058F7CC, _imp__FileTimeToSystemTime);
SETCGLOB(0x0058F7C8, _imp__FileTimeToLocalFileTime);
SETCGLOB(0x0058F69C, _imp__ExtSelectClipRgn);
SETCGLOB(0x0058F704, _imp__ExtCreateRegion);
SETCGLOB(0x0058F828, _imp__ExitProcess);
SETCGLOB(0x0058F9CC, _imp__EqualRect);
SETCGLOB(0x0058F9DC, _imp__EnumWindows);
SETCGLOB(0x0058F684, _imp__EnumFontFamiliesA);
SETCGLOB(0x0058F9C8, _imp__EnumChildWindows);
SETCGLOB(0x0058F75C, _imp__EnterCriticalSection);
SETCGLOB(0x0058F6B4, _imp__EndPath);
SETCGLOB(0x0058F8E8, _imp__EndPaint);
SETCGLOB(0x0058F6D8, _imp__EndDoc);
SETCGLOB(0x0058F9AC, _imp__EndDialog);
SETCGLOB(0x0058F9C0, _imp__EnableWindow);
SETCGLOB(0x0058F888, _imp__DuplicateHandle);
SETCGLOB(0x0058F8C8, _imp__DrawTextA);
SETCGLOB(0x0058F938, _imp__DispatchMessageA);
SETCGLOB(0x0058F9A8, _imp__DialogBoxIndirectParamA);
SETCGLOB(0x0058F9B0, _imp__DestroyWindow);
SETCGLOB(0x0058F954, _imp__DestroyCursor);
SETCGLOB(0x0058F5F8, _imp__DeleteObject);
SETCGLOB(0x0058F7E0, _imp__DeleteFileA);
SETCGLOB(0x0058F5FC, _imp__DeleteDC);
SETCGLOB(0x0058F750, _imp__DeleteCriticalSection);
SETCGLOB(0x0058F8F0, _imp__DefWindowProcA);
SETCGLOB(0x0058F690, _imp__DPtoLP);
SETCGLOB(0x0058F904, _imp__CreateWindowExA);
SETCGLOB(0x0058F794, _imp__CreateThread);
SETCGLOB(0x0058F620, _imp__CreateSolidBrush);
SETCGLOB(0x0058F614, _imp__CreateRectRgn);
SETCGLOB(0x0058F680, _imp__CreatePen);
SETCGLOB(0x0058F67C, _imp__CreatePatternBrush);
SETCGLOB(0x0058F63C, _imp__CreatePalette);
SETCGLOB(0x0058F78C, _imp__CreateMutexA);
SETCGLOB(0x0058F708, _imp__CreateFontIndirectA);
SETCGLOB(0x0058F600, _imp__CreateFontA);
SETCGLOB(0x0058F824, _imp__CreateFileMappingA);
SETCGLOB(0x0058F7C4, _imp__CreateFileA);
SETCGLOB(0x0058F790, _imp__CreateEventA);
SETCGLOB(0x0058F7E8, _imp__CreateDirectoryA);
SETCGLOB(0x0058F5F4, _imp__CreateDIBSection);
SETCGLOB(0x0058F96C, _imp__CreateCursor);
SETCGLOB(0x0058F5F0, _imp__CreateCompatibleDC);
SETCGLOB(0x0058F6E0, _imp__CreateCompatibleBitmap);
SETCGLOB(0x0058F678, _imp__CreateBitmap);
SETCGLOB(0x0058F91C, _imp__CopyIcon);
SETCGLOB(0x0058FA78, _imp__CommDlgExtendedError);
SETCGLOB(0x0058F6C8, _imp__CombineRgn);
SETCGLOB(0x0058F7A8, _imp__CloseHandle);
SETCGLOB(0x0058F940, _imp__ClipCursor);
SETCGLOB(0x0058F944, _imp__ClientToScreen);
SETCGLOB(0x0058F9E8, _imp__ChildWindowFromPointEx);
SETCGLOB(0x0058F9BC, _imp__ChildWindowFromPoint);
SETCGLOB(0x0058F8CC, _imp__CallNextHookEx);
SETCGLOB(0x0058F638, _imp__BitBlt);
SETCGLOB(0x0058F6AC, _imp__BeginPath);
SETCGLOB(0x0058F8E4, _imp__BeginPaint);
SETCGLOB(0x0058F8D8, _imp__AdjustWindowRectEx);
SETCGLOB(0x0058F99C, _imp__AdjustWindowRect);
SETCGLOB(0x0058F6D4, _imp__AbortDoc);
