@echo off

set skipSetupArg=%2
if "%skipSetupArg%" NEQ "skip_setup_msvc" (
call "setup_msvc.bat"
)


call  "\\Gamerschoice\D$\Program Files\MATLAB\R2025a\bin\win64\checkMATLABRootForDriveMap.exe" "\\Gamerschoice\D$\Program Files\MATLAB\R2025a"  > mlEnv.txt
for /f %%a in (mlEnv.txt) do set "%%a"\n
cd .

if "%1"=="" (nmake MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN%  -f bildvorverarbeitung_rtw.mk all) else (nmake MATLAB_ROOT=%MATLAB_ROOT% ALT_MATLAB_ROOT=%ALT_MATLAB_ROOT% MATLAB_BIN=%MATLAB_BIN% ALT_MATLAB_BIN=%ALT_MATLAB_BIN%  -f bildvorverarbeitung_rtw.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1