@echo off

    if exist "ex2.obj" del "ex2.obj"
    if exist "ex2.exe" del "ex2.exe"

    \masm32\bin\ml /c /coff "ex2.asm"
    if errorlevel 1 goto errasm

    \masm32\bin\PoLink /SUBSYSTEM:CONSOLE "ex2.obj"
    if errorlevel 1 goto errlink
    dir "ex2.*"
    goto TheEnd

  :errlink
    echo _
    echo Link error
    goto TheEnd

  :errasm
    echo _ 
    echo Assembly Error
    goto TheEnd
    
  :TheEnd

pause
