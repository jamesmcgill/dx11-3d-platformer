@echo off
:: Source files are located in the same directory as this batch file
set SRC_DIR=%~dp0

:: Output files will be created in the parent directory of this batch file
cd ..
%SRC_DIR%\MakeSpriteFont.exe "Verdana" verdana32.spritefont /FontSize:32
%SRC_DIR%\MakeSpriteFont.exe "Verdana" verdana16.spritefont /FontSize:16
%SRC_DIR%\MakeSpriteFont.exe "Verdana" verdana8.spritefont /FontSize:8
%SRC_DIR%\MakeSpriteFont.exe "Courier New" mono32.spritefont /FontSize:32
%SRC_DIR%\MakeSpriteFont.exe "Courier New" mono16.spritefont /FontSize:16
%SRC_DIR%\MakeSpriteFont.exe "Courier New" mono8.spritefont /FontSize:8