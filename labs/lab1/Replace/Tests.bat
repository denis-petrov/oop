@echo off

REM Path to tested program passed through the first(1-st) command line argument
SET Program="%~1"

REM Protect from run without argument, which sets the path to the program
if %Program%=="" (
	echo Please specify path to program
	exit /B 1
)

REM If command args correct then expected 0 return code
%Program% test-data\RiskTaking.txt "%TEMP%\output.txt" we bananas
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\RiskTaking-replace-we-with-bananas.txt > nul
if ERRORLEVEL 1 goto err
echo Test 1 passed

REM If command args correct then expected 0 return code
%Program% test-data\SmartEnergy.txt "%TEMP%\output.txt" to and
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\SmartEnergy-replace-to-with-and.txt > nul
if ERRORLEVEL 1 goto err
echo Test 2 passed

REM If command args correct then expected 0 return code
%Program% test-data\StupidInput.txt "%TEMP%\output.txt" Mama Child
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\StupidInput-replace-Mama-with-Child.txt > nul
if ERRORLEVEL 1 goto err
echo Test 3 passed

REM If command args correct then expected 0 return code
%Program% test-data\Empty.txt "%TEMP%\output.txt" "" ""
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" test-data\Empty.txt > nul
if ERRORLEVEL 1 goto err
echo Test 4 passed


REM Tests pass success
echo All tests passed successfuly
exit /B 0


REM Tests pass with errors
:err
echo Testing failed
exit /B 1
