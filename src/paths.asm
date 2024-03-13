%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Change some paths to be relative to CWD instead of the exe
; This allows loading data from an alternate directory

; Add 2 to the existing string offsets to skip the "9:" prefix
@SET 0x004d2b05, { PUSH 0x0056f2fc + 2} ; Nova Files:Nova Music.mp3, check file exists
@SET 0x0049d85d, { PUSH 0x0056d1a0 + 2} ; Nova Plug-Ins, shipyard movie
@SET 0x0049d8da, { PUSH 0x0056d1b4 + 2} ; Nova Files, shipyard movie
@SET 0x0049db42, { PUSH 0x0056d1a0 + 2} ; Nova Plug-Ins, desc movie
@SET 0x0049dbbf, { PUSH 0x0056d1b4 + 2} ; Nova Files, desc movie
@SET 0x004ab636, { PUSH 0x0056d1f8 + 2} ; Nova Plug-Ins, music
@SET 0x004ab6da, { PUSH 0x0056d210 + 2} ; Nova Files, music

@SET 0x004bd0f4, { MOV AX, [0x0056ddc9 + 2]} ; // Pilots
@SET 0x004bd182, { MOV AX, [0x0056ddc9 + 2]} ; // Pilots
