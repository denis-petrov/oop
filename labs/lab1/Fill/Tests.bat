@echo off

REM Path to tested program passed through the first(1-st) command line argument
SET Program="%~1"

REM Protect from run without argument, which sets the path to the program
if %Program%=="" (
	echo Please specify path to program
	exit /B 1
)

REM If command args correct then expected 0 return code
%Program% test-data\1-test.txt "%TEMP%\output.txt" 
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\1-test-result.txt > nul
if ERRORLEVEL 1 goto err
echo Test 1 passed

REM If command args correct then expected 0 return code
%Program% test-data\2-test.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\2-test-result.txt > nul
if ERRORLEVEL 1 goto err
echo Test 2 passed

REM If command args correct then expected 0 return code
%Program% test-data\3-test.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\3-test-result.txt > nul
echo Test 3 passed

REM If command args correct then expected 0 return code
%Program% test-data\4-test.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\4-test-result.txt > nul
echo Test 4 passed

REM If command args correct then expected 0 return code
%Program% test-data\5-test.txt "%TEMP%\output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\5-test-result.txt > nul
echo Test 5 passed

REM Tests pass success
echo All tests passed successfuly
exit /B 0


REM Tests pass with errors
:err
echo Testing failed
exit /B 1
