@echo off

set ROOT_DIR=%cd%
set LOG_DIR=%ROOT_DIR%\_log
set BUILD_DIR=%ROOT_DIR%\_build

if not exist "%LOG_DIR%" mkdir "%LOG_DIR%"
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

call :arguments_parsing %*
goto end

:help
    echo  Usage:  build.bat --cmake        Create a project
    echo          build.bat --build        Compile the project
    exit /b

:arguments_parsing
    set args_for_processing=%*
    if "x%args_for_processing%" == "x" (
        call :help
        exit /b
    )
    
    :LOOP
    if "x%args_for_processing%" == "x" exit /b
    for /f "tokens=1,2 delims= " %%G in ("%args_for_processing%") do (
        set arg=%%G
        set next_arg=%%H
    )

    if "%arg%" == "--cmake" (
        call :cmake
    ) else if "%arg%" == "--build" (
        call :build
    ) else (
        echo Arg = "%arg%"
        call :help
        exit /b
    )

    call set args_for_processing=%%args_for_processing:%arg% =%%
    call set args_for_processing=%%args_for_processing:%arg%=%%
    goto LOOP

:cmake
    echo -- Create a project ...
    cmake "%ROOT_DIR%"
    echo -- Create a project. Done
    exit /b

:build
    echo -- Build Release configuration ...
    set LOG_FILE=%LOG_DIR%\build.txt
    if exist "%LOG_FILE%" del "%LOG_FILE%"
    devenv.exe "%BUILD_DIR%/NeuralNetwork.sln" /build "Release|Win32" /out "%LOG_FILE%"
    type "%LOG_FILE%" | find ", 0 failed,"
    if %errorlevel% NEQ 0 (
        echo Error: Build of Release configuration failed.
        exit /b 1
    )
    echo -- Build Release configuration. Done
    exit /b

:end
cd "%ROOT_DIR%"