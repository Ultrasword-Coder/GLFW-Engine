@echo off
cls

if exist "test.exe" (
    del "test.exe"
)

g++ -Isrc -Iinclude -o "test.exe" "test.cpp" -Llibraries -lglfw3dll -luser32 -lopengl32 -lGdi32 -lShell32 -lglew32s -lglew32

if not errorlevel 1 (
    "test.exe"
)

