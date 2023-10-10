%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Nova creates asteroids in the corner regions of a square box framing the game area. In widescren
; resolutions, when the difference between width and height are sufficiently large, asteroids spawn
; too far away from the game area and immediately despawn. To fix this we must change the box size.

; Change a JLE to a JMP, so the square is always based on the height rather than the longest side
@SJMP 0x00421961, 0x00421980

; Now to avoid asteroids sometimes spawning slightly inside the game area, clear a couple of
; calculations on the Y midpoint.

; Remove a +128 addition
@CLEAR 0x00421950, 0x90, 0x00421953
; Remove a *0.7 multiplier
@CLEAR 0x00421989, 0x90, 0x0042198F
