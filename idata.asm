; Imports for EV_Nova.dat
ImageBase equ 0x400000

section .idata

; ADVAPI32.dll
dd 0x18F104   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x18FB08   ; Name
dd 0x18F5C8   ; FirstThunk

; COMCTL32.dll
dd 0x18F124   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x18FB16   ; Name
dd 0x18F5E8   ; FirstThunk

; GDI32.dll
dd 0x18F12C   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x18FFAA   ; Name
dd 0x18F5F0   ; FirstThunk

; KERNEL32.dll
dd 0x18F24C   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x1906D8   ; Name
dd 0x18F710   ; FirstThunk

; OPENGL32.dll
dd 0x18F3D8   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x1906E6   ; Name
dd 0x18F89C   ; FirstThunk

; SHELL32.dll
dd 0x18F3DC   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x190706   ; Name
dd 0x18F8A0   ; FirstThunk

; USER32.dll
dd 0x18F3E4   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x190C90   ; Name
dd 0x18F8A8   ; FirstThunk

; VERSION.dll
dd 0x18F52C   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x190C9C   ; Name
dd 0x18F9F0   ; FirstThunk

; WINMM.dll
dd 0x18F530   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x190D7E   ; Name
dd 0x18F9F4   ; FirstThunk

; WSOCK32.dll
dd 0x18F560   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x190D88   ; Name
dd 0x18FA24   ; FirstThunk

; comdlg32.dll
dd 0x18F5B0   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x190DC0   ; Name
dd 0x18FA74   ; FirstThunk

; iconv.dll
dd 0x18F5BC   ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x190DEC   ; Name
dd 0x18FA80   ; FirstThunk

; END
dd 0x0        ; OriginalFirstThunk
dd 0x0        ; TimeDateStamp
dd 0x0        ; ForwarderChain
dd 0x0        ; Name
dd 0x0        ; FirstThunk

