%include "macros/patch.inc"
%include "macros/datatypes.inc"

; Nova performs the following 7 font substitutions:
;
; Times     => Times New Roman
; Helvetica => Arial
; Geneva    => Arial
; Courier   => Courier New
; Chicago   => Arial
; Charcoal  => Arial
; New York  => Geneva
;
; Times is the hardcoded font for large titles. Times New Roman is very similar and an appropriate
; substitute.
;
; Geneva is the hardcoded font for all standard text. Arial is a poor substitute as it is much
; harder to read at small sizes. The substitution is also unncessary as Windows will default to
; Arial anyway if the font isn't found.
;
; Charcoal is Nova's font for button text, set in the data files. As above, this is unncessary.
;
; The remaining fonts are irrelevant.
;
; We want to keep the Times substitution but disable the others, so that users who install the
; appropriate font files can benefit from them. To do this we change the count from 7 to 1.

@SET 0x004BC4D6, { CMP EBP, 1 }
@SET 0x004BC4DB, { CMP EBP, 1 }
