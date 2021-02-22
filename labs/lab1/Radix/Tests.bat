@echo off

REM Path to tested program passed through the first(1-st) command line argument
SET Program="%~1"

REM Protect from run without argument, which sets the path to the program
if %Program%=="" (
	echo Please specify path to program
	exit /B 1
)

REM If command args correct then expected 0 return code
%Program% 2 25 0 "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\2-25-0.txt > nul
if ERRORLEVEL 1 goto err
echo Test 1 passed

REM If command args correct then expected 0 return code
%Program% 2 25 101011 "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\2-25-101011.txt > nul
if ERRORLEVEL 1 goto err
echo Test 2 passed

REM If command args correct then expected 1 return code
%Program% 36 18 ZZZZZZZ "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" test-data\36-18-ZZZZZZZ.txt > nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

REM If command args correct then expected 0 return code
%Program% 10 16 10 "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\10-16-10.txt > nul
if ERRORLEVEL 1 goto err
echo Test 4 passed

REM If command args correct then expected 0 return code
%Program% 16 8 C8 "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\16-8-C8.txt > nul
if ERRORLEVEL 1 goto err
echo Test 5 passed

REM If command args correct then expected 1 return code
%Program% 10 8 BB "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" test-data\10-8-BB.txt > nul
if ERRORLEVEL 1 goto err
echo Test 6 passed

REM If command args correct then expected 0 return code
%Program% 4 4 33 "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\4-4-33.txt > nul
if ERRORLEVEL 1 goto err
echo Test 7 passed

REM If command args correct then expected 0 return code
%Program% 10 16 -10 "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\10-16--10.txt > nul
if ERRORLEVEL 1 goto err
echo Test 8 passed

REM If command args correct then expected 1 return code
%Program% 10 16 -1@@0+ "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" test-data\10-16--1@@0+.txt > nul
if ERRORLEVEL 1 goto err
echo Test 9 passed

REM If command args correct then expected 0 return code
%Program% 2 36 11111111111 "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\2-36-11111111111.txt > nul
if ERRORLEVEL 1 goto err
echo Test 10 passed

REM If command args correct then expected 0 return code
%Program% 10 36 2147483647 "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\10-36-2147483647.txt > nul
if ERRORLEVEL 1 goto err
echo Test 11 passed

REM If command args correct then expected 1 return code
%Program% 10 36 2147483648 "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" test-data\10-36-2147483648.txt > nul
if ERRORLEVEL 1 goto err
echo Test 12 passed

REM If command args correct then expected 0 return code
%Program% 10 36 -2147483648 "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\10-36--2147483648.txt > nul
if ERRORLEVEL 1 goto err
echo Test 13 passed

REM If command args correct then expected 0 return code
%Program% 10 36 -21474836499999999999999 "%TEMP%\output.txt"
fc.exe "%TEMP%\output.txt" test-data\10-36--21474836499999999999999.txt > nul
if ERRORLEVEL 1 goto err
echo Test 14 passed

REM Tests pass success
echo All tests passed successfuly
exit /B 0


REM Tests pass with errors
:err
echo Testing failed
exit /B 1
