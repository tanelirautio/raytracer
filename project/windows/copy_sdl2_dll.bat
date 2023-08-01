@echo off

setlocal enabledelayedexpansion

set "sourceDir="
set "destinationDir=../../bin"

if "%1"=="x64-debug" (
    set "sourceDir=../../lib/windows/SDL-2.26.4/lib/x64/Debug"
) else if "%1"=="x64-release" (
    set "sourceDir=../../lib/windows/SDL-2.26.4/lib/x64/Release"
) else if "%1"=="win32-debug" (
    set "sourceDir=../../lib/windows/SDL-2.26.4/lib/win32/Debug"
) else if "%1"=="win32-release" (
    set "sourceDir=../../lib/windows/SDL-2.26.4/lib/win32/Release"
) else (
    echo Invalid command line argument. Please use one of the following options:
    echo x64-debug, x64-release, win32-debug, win32-release
    pause
    exit /b 1
)

if not exist "%sourceDir%\SDL2.dll" (
    echo SDL2.dll not found in the source directory.
    pause
    exit /b 1
)

if not exist "%destinationDir%" (
    mkdir "%destinationDir%"
)

copy "%sourceDir%\SDL2.dll" "%destinationDir%\"
echo SDL2.dll copied successfully.
pause