@echo off
set now=0
set all=100

echo.��ʼʱ��: %time:~0,2%:%time:~3,2%:%time:~6,2%.%time:~9,2%

:loop
if "%now%"=="100" (goto end)
.\calc.exe %now%/%all%*100
title ����:%now%
set /a now+=1
goto loop

:end
echo.����ʱ��: %time:~0,2%:%time:~3,2%:%time:~6,2%.%time:~9,2%
pause