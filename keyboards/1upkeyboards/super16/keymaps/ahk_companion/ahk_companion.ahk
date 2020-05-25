#Persistent
#SingleInstance force

;=================================================================
;                      Macro Pad Shortcuts                       ;
;=================================================================

;=================================================================
;                       Layer 0
;;=================================================================
;Row 1

F13::Send ^#{Left}                 ;Left Windows Desktop
F14::Send #{Tab}                   ;Task View
F15::Send ^!a
F16::Send ^#{Right}                ;Right Windows Desktop

;Row 2

F17::Send ^+{Tab}                  ;Chrome Tab Left
F18::Send ^v
F19::Send ^v
F20::Send ^{Tab}                   ;Chrome Tab Right

;Row 3
F21::Run, https://google.com
F22::Send 'Hello world!'
F23::Send {Backspace}
F24::Send {Enter}


;=================================================================
;                       Layer 1
;;=================================================================
;Row 1
!F13::Run, https://mail.google.com
!F14::Run, https://mail.google.com
!F15::Run, https://mail.google.com
!F16::Run, https://mail.google.com


;Row 2
!F17::Run, https://mail.google.com
!F18::Run, https://mail.google.com
!F19::Run, https://mail.google.com
!F20::Run, https://mail.google.com

;Row 3
!F21::Run, https://mail.google.com
!F22::Run, https://mail.google.com
!F23::Run, "C:\Program Files (x86)\KeePass2x\KeePass.exe" -entry-url-open -uuid:9393DACF87EFEB40B4C72516A9B08A87
!F24::Send, 1

;=================================================================
;                       Layer 2
;;=================================================================
;Row 1
+F13::Send, A
+F14::
+F15::
+F16::

;Row 2
+F17::
+F18::
+F19::
+F20::

;Row 3
+F21::
+F22::
+F23::
+F24::

;=================================================================
;                       Layer 3
;;=================================================================
^F13::
^F14::
^F15::
^F16::

;Row 2
^F17::
^F18::
^F19::
^F20::

;Row 3
^F21::
^F22::
^F23::
^F24::

;Special Key
^!+F13::

