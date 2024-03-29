%include "macros/setsym.inc"


; vars

setcglob 0x005914D8, g_nv_runInAWindow
setcglob 0x005914D9, g_nv_runInAWindowPref
setcglob 0x005914E0, g_nv_noHyperspaceEffects
setcglob 0x00591560, g_nv_beep1
setcglob 0x00596D1C, g_nv_mainContext
setcglob 0x00596D3A, g_nv_debugMode
setcglob 0x00597950, g_nv_mainBufferCanvas
setcglob 0x007353F2, g_nv_currentVolume
setcglob 0x007355DC, g_nv_statusBarAreas
setcglob 0x00735684, g_nv_mainFontFace
setcglob 0x007CDAB0, g_nv_debugLog
setcglob 0x007D0694, g_nv_newsDialog
setcglob 0x007D17B8, g_nv_commsDialog
setcglob 0x007D17C0, g_nv_plunderDialog
setcglob 0x007D2B84, g_nv_outfitterDialog
setcglob 0x007D2B8C, g_nv_shipyardDialog
setcglob 0x007D2B90, g_nv_shipInfoDialog
setcglob 0x007D2B94, g_nv_playerInfoDialog
setcglob 0x007D4C0E, g_nv_promptResult
setcglob 0x007D4D0E, g_nv_gridThumbBounds
setcglob 0x007D510E, g_nv_gridCellBounds
setcglob 0x007D51AE, g_nv_gridCellImageBounds
setcglob 0x007D8298, g_nv_buttonCanvas
setcglob 0x007DCF94, g_nv_mapDialog
setcglob 0x00864F40, g_nv_activeDialog
setcglob 0x00870064, g_nv_currentContext
setcglob 0x00870078, g_nv_hwnd
setcglob 0x008700A0, g_nv_screenWidth
setcglob 0x0087019C, g_nv_screenHeight
setcglob 0x00870D80, g_nv_argc
setcglob 0x00870D94, g_nv_argv


; functions

setcglob 0x00447F20, nv_EvaluteNCBTestExpression
setcglob 0x00448020, nv_ExecuteNCBSetExpression
setcglob 0x004622F0, nv_DrawPStringCentered
setcglob 0x00469CA0, nv_KeyCheck
setcglob 0x0046AAD0, nv_PlaySound
setcglob 0x0046F740, nv_ConfigureBitmap
setcglob 0x004976B0, nv_ShowAlert
setcglob 0x00497900, nv_ShowPrompt
setcglob 0x004B45E0, nv_InitializeMonitor
setcglob 0x004B6920, nv_SetFontSize
setcglob 0x004B8D50, nv_ShiftRect
setcglob 0x004B9070, nv_DrawPict
setcglob 0x004BC760, nv_DrawText
setcglob 0x004CEDE0, nv_ProcessDitlEntry
setcglob 0x004CF960, nv_GetDialogItemAndBounds
setcglob 0x004CFD30, nv_GetDialogBounds
setcglob 0x004D2A80, WinMain
setcglob 0x004D86D0, nv_Alloc
setcglob 0x004D87D0, nv_Free
setcglob 0x004ECBD0, nv_SetupScreen
setcglob 0x004F0EB0, nv_WriteLogFormat
setcglob 0x004F1080, nv_FlushLog

; imports

setcglob 0x0058F984, _imp__wsprintfA
setcglob 0x0058FA1C, _imp__waveOutWrite
setcglob 0x0058FA04, _imp__waveOutUnprepareHeader
setcglob 0x0058FA14, _imp__waveOutSetVolume
setcglob 0x0058FA00, _imp__waveOutReset
setcglob 0x0058FA18, _imp__waveOutPrepareHeader
setcglob 0x0058F9FC, _imp__waveOutOpen
setcglob 0x0058FA10, _imp__waveOutGetVolume
setcglob 0x0058F9F8, _imp__waveOutGetNumDevs
setcglob 0x0058FA0C, _imp__waveOutGetDevCapsA
setcglob 0x0058FA08, _imp__waveOutClose
setcglob 0x0058F9F4, _imp__timeGetTime
setcglob 0x0058FA34, _imp__socket
setcglob 0x0058FA5C, _imp__shutdown
setcglob 0x0058FA4C, _imp__setsockopt
setcglob 0x0058FA58, _imp__sendto
setcglob 0x0058FA68, _imp__send
setcglob 0x0058FA54, _imp__recvfrom
setcglob 0x0058FA60, _imp__recv
setcglob 0x0058FA80, _imp__libiconv_open
setcglob 0x0058FA84, _imp__libiconv
setcglob 0x0058FA48, _imp__getsockopt
setcglob 0x0058FA44, _imp__getsockname
setcglob 0x0058FA38, _imp__gethostname
setcglob 0x0058FA3C, _imp__gethostbyname
setcglob 0x0058FA6C, _imp__gethostbyaddr
setcglob 0x0058FA40, _imp__connect
setcglob 0x0058FA30, _imp__closesocket
setcglob 0x0058FA50, _imp__bind
setcglob 0x0058FA64, _imp__accept
setcglob 0x0058F87C, _imp__WriteFile
setcglob 0x0058F9E4, _imp__WindowFromPoint
setcglob 0x0058F6B8, _imp__WidenPath
setcglob 0x0058F924, _imp__WaitMessage
setcglob 0x0058F7A0, _imp__WaitForSingleObject
setcglob 0x0058FA24, _imp__WSAStartup
setcglob 0x0058FA2C, _imp__WSAGetLastError
setcglob 0x0058FA28, _imp__WSACleanup
setcglob 0x0058F7BC, _imp__VirtualUnlock
setcglob 0x0058F7B4, _imp__VirtualLock
setcglob 0x0058F990, _imp__ValidateRect
setcglob 0x0058F8BC, _imp__UpdateWindow
setcglob 0x0058F8F8, _imp__UnhookWindowsHookEx
setcglob 0x0058F934, _imp__TranslateMessage
setcglob 0x0058F758, _imp__TlsSetValue
setcglob 0x0058F754, _imp__TlsGetValue
setcglob 0x0058F74C, _imp__TlsFree
setcglob 0x0058F728, _imp__TlsAlloc
setcglob 0x0058F6D0, _imp__TextOutA
setcglob 0x0058F840, _imp__TerminateThread
setcglob 0x0058F8FC, _imp__SystemParametersInfoA
setcglob 0x0058F774, _imp__SuspendThread
setcglob 0x0058F6F4, _imp__StretchDIBits
setcglob 0x0058F6E8, _imp__StretchBlt
setcglob 0x0058F748, _imp__SleepEx
setcglob 0x0058F710, _imp__Sleep
setcglob 0x0058F80C, _imp__SizeofResource
setcglob 0x0058F9A0, _imp__ShowWindow
setcglob 0x0058F988, _imp__ShowCursor
setcglob 0x0058F8A0, _imp__ShellExecuteA
setcglob 0x0058F908, _imp__SetWindowsHookExA
setcglob 0x0058F980, _imp__SetWindowTextA
setcglob 0x0058F97C, _imp__SetWindowPos
setcglob 0x0058F978, _imp__SetWindowLongA
setcglob 0x0058F674, _imp__SetViewportOrgEx
setcglob 0x0058F9B8, _imp__SetTimer
setcglob 0x0058F798, _imp__SetThreadPriority
setcglob 0x0058F610, _imp__SetTextColor
setcglob 0x0058F66C, _imp__SetTextAlign
setcglob 0x0058F694, _imp__SetRectRgn
setcglob 0x0058F994, _imp__SetRect
setcglob 0x0058F668, _imp__SetROP2
setcglob 0x0058F6A0, _imp__SetPixelV
setcglob 0x0058F644, _imp__SetPixel
setcglob 0x0058F650, _imp__SetPaletteEntries
setcglob 0x0058F664, _imp__SetMapMode
setcglob 0x0058F720, _imp__SetLastError
setcglob 0x0058F8AC, _imp__SetForegroundWindow
setcglob 0x0058F8B0, _imp__SetFocus
setcglob 0x0058F868, _imp__SetFilePointer
setcglob 0x0058F7A4, _imp__SetEvent
setcglob 0x0058F7F0, _imp__SetErrorMode
setcglob 0x0058F86C, _imp__SetEndOfFile
setcglob 0x0058F64C, _imp__SetDeviceGammaRamp
setcglob 0x0058F6F0, _imp__SetDIBitsToDevice
setcglob 0x0058F6F8, _imp__SetDIBits
setcglob 0x0058F654, _imp__SetDIBColorTable
setcglob 0x0058F970, _imp__SetCursor
setcglob 0x0058F7EC, _imp__SetCurrentDirectoryA
setcglob 0x0058F768, _imp__SetConsoleTitleA
setcglob 0x0058F740, _imp__SetConsoleCtrlHandler
setcglob 0x0058F928, _imp__SetCapture
setcglob 0x0058F60C, _imp__SetBkMode
setcglob 0x0058F624, _imp__SetBkColor
setcglob 0x0058F960, _imp__SendMessageA
setcglob 0x0058F630, _imp__SelectPalette
setcglob 0x0058F608, _imp__SelectObject
setcglob 0x0058F618, _imp__SelectClipRgn
setcglob 0x0058F81C, _imp__SearchPathA
setcglob 0x0058F9D0, _imp__ScreenToClient
setcglob 0x0058F658, _imp__SaveDC
setcglob 0x0058F894, _imp__RtlUnwind
setcglob 0x0058F778, _imp__ResumeThread
setcglob 0x0058F65C, _imp__RestoreDC
setcglob 0x0058F890, _imp__ResetEvent
setcglob 0x0058F7E4, _imp__RemoveDirectoryA
setcglob 0x0058F79C, _imp__ReleaseMutex
setcglob 0x0058F8C4, _imp__ReleaseDC
setcglob 0x0058F92C, _imp__ReleaseCapture
setcglob 0x0058F93C, _imp__RegisterWindowMessageA
setcglob 0x0058F900, _imp__RegisterClassA
setcglob 0x0058F5D4, _imp__RegSetValueExA
setcglob 0x0058F5D0, _imp__RegQueryValueExA
setcglob 0x0058F5E0, _imp__RegOpenKeyExA
setcglob 0x0058F5D8, _imp__RegFlushKey
setcglob 0x0058F5CC, _imp__RegCreateKeyExA
setcglob 0x0058F5DC, _imp__RegCloseKey
setcglob 0x0058F634, _imp__RealizePalette
setcglob 0x0058F878, _imp__ReadFile
setcglob 0x0058F788, _imp__QueryPerformanceFrequency
setcglob 0x0058F770, _imp__QueryPerformanceCounter
setcglob 0x0058F8EC, _imp__PostQuitMessage
setcglob 0x0058F920, _imp__PostMessageA
setcglob 0x0058F930, _imp__PeekMessageA
setcglob 0x0058F804, _imp__OutputDebugStringA
setcglob 0x0058F6FC, _imp__OffsetRgn
setcglob 0x0058F714, _imp__MulDiv
setcglob 0x0058F8B8, _imp__MoveWindow
setcglob 0x0058F6A8, _imp__MoveToEx
setcglob 0x0058F94C, _imp__MessageBoxA
setcglob 0x0058F974, _imp__MessageBeep
setcglob 0x0058F9D4, _imp__MapWindowPoints
setcglob 0x0058F814, _imp__LockResource
setcglob 0x0058F90C, _imp__LoadStringA
setcglob 0x0058F810, _imp__LoadResource
setcglob 0x0058F7AC, _imp__LoadLibraryA
setcglob 0x0058F7AC, _imp__LoadLibraryA_p
setcglob 0x0058F950, _imp__LoadIconA
setcglob 0x0058F918, _imp__LoadCursorA
setcglob 0x0058F6B0, _imp__LineTo
setcglob 0x0058F760, _imp__LeaveCriticalSection
setcglob 0x0058F698, _imp__LPtoDP
setcglob 0x0058F968, _imp__IsWindowVisible
setcglob 0x0058F8DC, _imp__IsIconic
setcglob 0x0058F838, _imp__IsBadWritePtr
setcglob 0x0058F834, _imp__IsBadReadPtr
setcglob 0x0058F998, _imp__InvertRect
setcglob 0x0058F98C, _imp__InvalidateRect
setcglob 0x0058F734, _imp__InitializeCriticalSection
setcglob 0x0058F5E8, _imp__InitCommonControls
setcglob 0x0058F830, _imp__HeapFree
setcglob 0x0058F82C, _imp__HeapAlloc
setcglob 0x0058F880, _imp__GlobalUnlock
setcglob 0x0058F7B8, _imp__GlobalSize
setcglob 0x0058F71C, _imp__GlobalMemoryStatus
setcglob 0x0058F7C0, _imp__GlobalFree
setcglob 0x0058F7B0, _imp__GlobalAlloc
setcglob 0x0058F7FC, _imp__GetWindowsDirectoryA
setcglob 0x0058F95C, _imp__GetWindowTextLengthA
setcglob 0x0058F9B4, _imp__GetWindowTextA
setcglob 0x0058F8E0, _imp__GetWindowRect
setcglob 0x0058F8D0, _imp__GetWindowLongA
setcglob 0x0058F7F4, _imp__GetVolumeInformationA
setcglob 0x0058F718, _imp__GetVersionExA
setcglob 0x0058F88C, _imp__GetVersion
setcglob 0x0058F5C8, _imp__GetUserNameA
setcglob 0x0058F784, _imp__GetTimeZoneInformation
setcglob 0x0058F744, _imp__GetTickCount
setcglob 0x0058F670, _imp__GetTextMetricsA
setcglob 0x0058F6CC, _imp__GetTextExtentPoint32A
setcglob 0x0058F628, _imp__GetTextColor
setcglob 0x0058F85C, _imp__GetTempPathA
setcglob 0x0058F77C, _imp__GetSystemTime
setcglob 0x0058F8B4, _imp__GetSystemMetrics
setcglob 0x0058F7F8, _imp__GetSystemDirectoryA
setcglob 0x0058F61C, _imp__GetStockObject
setcglob 0x0058F858, _imp__GetStdHandle
setcglob 0x0058F83C, _imp__GetStartupInfoA
setcglob 0x0058F68C, _imp__GetRgnBox
setcglob 0x0058F700, _imp__GetRegionData
setcglob 0x0058F72C, _imp__GetProcessHeap
setcglob 0x0058F73C, _imp__GetProcAddress
setcglob 0x0058F73C, _imp__GetProcAddress_p
setcglob 0x0058F640, _imp__GetPixel
setcglob 0x0058F958, _imp__GetParent
setcglob 0x0058FA74, _imp__GetOpenFileNameA
setcglob 0x0058F6E4, _imp__GetObjectType
setcglob 0x0058F738, _imp__GetModuleHandleA
setcglob 0x0058F76C, _imp__GetModuleFileNameA
setcglob 0x0058F8D4, _imp__GetMenu
setcglob 0x0058F6EC, _imp__GetMapMode
setcglob 0x0058F860, _imp__GetLogicalDrives
setcglob 0x0058F780, _imp__GetLocalTime
setcglob 0x0058F724, _imp__GetLastError
setcglob 0x0058F8A8, _imp__GetKeyState
setcglob 0x0058F800, _imp__GetFullPathNameA
setcglob 0x0058F914, _imp__GetForegroundWindow
setcglob 0x0058F870, _imp__GetFileSize
setcglob 0x0058F7D0, _imp__GetFileAttributesA
setcglob 0x0058F84C, _imp__GetEnvironmentStrings
setcglob 0x0058F864, _imp__GetDriveTypeA
setcglob 0x0058F9C4, _imp__GetDlgCtrlID
setcglob 0x0058F9A4, _imp__GetDialogBaseUnits
setcglob 0x0058F648, _imp__GetDeviceGammaRamp
setcglob 0x0058F604, _imp__GetDeviceCaps
setcglob 0x0058F948, _imp__GetDesktopWindow
setcglob 0x0058F6C4, _imp__GetDIBits
setcglob 0x0058F6DC, _imp__GetDIBColorTable
setcglob 0x0058F8C0, _imp__GetDC
setcglob 0x0058F9E0, _imp__GetCursorPos
setcglob 0x0058F730, _imp__GetCurrentThreadId
setcglob 0x0058F844, _imp__GetCurrentThread
setcglob 0x0058F820, _imp__GetCurrentProcessId
setcglob 0x0058F884, _imp__GetCurrentProcess
setcglob 0x0058F6A4, _imp__GetCurrentPositionEx
setcglob 0x0058F6C0, _imp__GetCurrentObject
setcglob 0x0058F854, _imp__GetCurrentDirectoryA
setcglob 0x0058F764, _imp__GetConsoleTitleA
setcglob 0x0058F848, _imp__GetCommandLineA
setcglob 0x0058F688, _imp__GetClipRgn
setcglob 0x0058F964, _imp__GetClientRect
setcglob 0x0058F62C, _imp__GetBkColor
setcglob 0x0058F9D8, _imp__GetAsyncKeyState
setcglob 0x0058F660, _imp__GdiFlush
setcglob 0x0058F818, _imp__FreeLibrary
setcglob 0x0058F850, _imp__FreeEnvironmentStringsA
setcglob 0x0058F874, _imp__FlushFileBuffers
setcglob 0x0058F910, _imp__FindWindowA
setcglob 0x0058F808, _imp__FindResourceA
setcglob 0x0058F7D8, _imp__FindNextFileA
setcglob 0x0058F7D4, _imp__FindFirstFileA
setcglob 0x0058F7DC, _imp__FindClose
setcglob 0x0058F8F4, _imp__FillRect
setcglob 0x0058F6BC, _imp__FillPath
setcglob 0x0058F7CC, _imp__FileTimeToSystemTime
setcglob 0x0058F7C8, _imp__FileTimeToLocalFileTime
setcglob 0x0058F69C, _imp__ExtSelectClipRgn
setcglob 0x0058F704, _imp__ExtCreateRegion
setcglob 0x0058F828, _imp__ExitProcess
setcglob 0x0058F9CC, _imp__EqualRect
setcglob 0x0058F9DC, _imp__EnumWindows
setcglob 0x0058F684, _imp__EnumFontFamiliesA
setcglob 0x0058F9C8, _imp__EnumChildWindows
setcglob 0x0058F75C, _imp__EnterCriticalSection
setcglob 0x0058F6B4, _imp__EndPath
setcglob 0x0058F8E8, _imp__EndPaint
setcglob 0x0058F6D8, _imp__EndDoc
setcglob 0x0058F9AC, _imp__EndDialog
setcglob 0x0058F9C0, _imp__EnableWindow
setcglob 0x0058F888, _imp__DuplicateHandle
setcglob 0x0058F8C8, _imp__DrawTextA
setcglob 0x0058F938, _imp__DispatchMessageA
setcglob 0x0058F9A8, _imp__DialogBoxIndirectParamA
setcglob 0x0058F9B0, _imp__DestroyWindow
setcglob 0x0058F954, _imp__DestroyCursor
setcglob 0x0058F5F8, _imp__DeleteObject
setcglob 0x0058F7E0, _imp__DeleteFileA
setcglob 0x0058F5FC, _imp__DeleteDC
setcglob 0x0058F750, _imp__DeleteCriticalSection
setcglob 0x0058F8F0, _imp__DefWindowProcA
setcglob 0x0058F690, _imp__DPtoLP
setcglob 0x0058F904, _imp__CreateWindowExA
setcglob 0x0058F794, _imp__CreateThread
setcglob 0x0058F620, _imp__CreateSolidBrush
setcglob 0x0058F614, _imp__CreateRectRgn
setcglob 0x0058F680, _imp__CreatePen
setcglob 0x0058F67C, _imp__CreatePatternBrush
setcglob 0x0058F63C, _imp__CreatePalette
setcglob 0x0058F78C, _imp__CreateMutexA
setcglob 0x0058F708, _imp__CreateFontIndirectA
setcglob 0x0058F600, _imp__CreateFontA
setcglob 0x0058F824, _imp__CreateFileMappingA
setcglob 0x0058F7C4, _imp__CreateFileA
setcglob 0x0058F790, _imp__CreateEventA
setcglob 0x0058F7E8, _imp__CreateDirectoryA
setcglob 0x0058F5F4, _imp__CreateDIBSection
setcglob 0x0058F96C, _imp__CreateCursor
setcglob 0x0058F5F0, _imp__CreateCompatibleDC
setcglob 0x0058F6E0, _imp__CreateCompatibleBitmap
setcglob 0x0058F678, _imp__CreateBitmap
setcglob 0x0058F91C, _imp__CopyIcon
setcglob 0x0058FA78, _imp__CommDlgExtendedError
setcglob 0x0058F6C8, _imp__CombineRgn
setcglob 0x0058F7A8, _imp__CloseHandle
setcglob 0x0058F940, _imp__ClipCursor
setcglob 0x0058F944, _imp__ClientToScreen
setcglob 0x0058F9E8, _imp__ChildWindowFromPointEx
setcglob 0x0058F9BC, _imp__ChildWindowFromPoint
setcglob 0x0058F8CC, _imp__CallNextHookEx
setcglob 0x0058F638, _imp__BitBlt
setcglob 0x0058F6AC, _imp__BeginPath
setcglob 0x0058F8E4, _imp__BeginPaint
setcglob 0x0058F8D8, _imp__AdjustWindowRectEx
setcglob 0x0058F99C, _imp__AdjustWindowRect
setcglob 0x0058F6D4, _imp__AbortDoc
