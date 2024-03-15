' Example script for launching a total conversion for EV Nova.
' Simply place this file in the folder of the total conversion, alongside its "Nova Files" folder.
' Feel free to copy, modify, or redistribute this script as much as you like.

On Error Resume Next
Set shell = CreateObject("WScript.Shell")
evn = shell.RegRead("HKCU\Software\Microsoft\Windows\CurrentVersion\App Paths\EV Nova.exe\")

If err.number = 0 Then
    shell.Run """" & evn & """"
End If

If err.number <> 0 Then
    response = MsgBox("EV Nova Community Edition r3 or newer is required to use this script." & vbCrLf & vbCrLf & "If you already have this version, try launching it once from its current location before continuing. If you don't have it yet you can download it from:" & vbCrLf & "https://github.com/andrews05/EV-Nova-CE" & vbCrLf & vbCrLf & "Would you like to download EV Nova CE now?", vbYesNo Or vbCritical Or vbDefaultButton2, "Unable to locate EV Nova.exe")
    If response = vbYes Then
        shell.Run "https://github.com/andrews05/EV-Nova-CE"
    End If
End If
