; A script to intercept Linux Unicode hotkey on Windows.
; (c) 2015 Simon A. Eugster Public Domain
; This script listens for Shift+Ctrl+u and then shows a Unicode input field.
; The Unicode point (e.g. 2013 for an en dash) is then inserted in the active application.

; To run, download AutoHotkey from http://www.autohotkey.com/, save this script
; as e.g. UnicodeInput.ahk, and double-click it.

#SingleInstance force

+^u::
InputBox, codepoint, Unicode code point, U+
if not ErrorLevel
Send {U+%codepoint%}
return
