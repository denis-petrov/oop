@echo off

REM Path to tested program passed through the first(1-st) command line argument
SET MyProgram="%~1"

REM Protect from run without argument, which sets the path to the program
if %MyProgram%=="" (
	echo Please specify path to program
	exit /B 1
)

REM Copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Copy non-empty file
%MyProgram% NonEmptyFile.txt "%TEMP%\output.txt" || goto err
fc NonEmptyFile.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM Copy missing file should fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" && goto err
echo Test 3 passed

REM If output file is not specified, program must fail
%MyProgram% MissingFile.txt && goto err
echo Test 4 passed

REM If input and output files is not specified, program must fail
%MyProgram% && goto err
echo Test 5 passed

REM Tests pass success
echo All tests passed successfuly
exit /B 0


REM Tests pass with errors
:err
echo Test faild
exit /B 1
