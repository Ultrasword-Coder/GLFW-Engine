@echo off
cls

if exist "sora.exe" (
    del "sora.exe"
)

g++ -Isrc -Iinclude -o "sora.exe" "main.cpp" -lglfw3dll -luser32 -lopengl32 -lGdi32 -lShell32 -lglew32s -lglew32 -lirrKlang

if not errorlevel 1 (
    "sora.exe"
)
