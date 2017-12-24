@echo off

set ROOT_DIR=%cd%
set LOG_DIR=%ROOT_DIR%\_log
set BUILD_DIR=%ROOT_DIR%\_build

if not exist "%LOG_DIR%" mkdir "%LOG_DIR%"
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

call :flags_initialization

:LOOP
set arg=%~1
set next_arg=%~2

if "x%arg%" == "x" goto ENDLOOP

if "%arg%" == "--cmake" (
    set run_cmake_enable=true
) else if "%arg%" == "--build" (
    set build_enable=true
) else if "%arg%" == "-G" (
    set generator=%next_arg%
    shift
) else if "%arg%" == "--help" (
    call :help
    goto end
) else (
    echo Arg = "%arg%"
    call :help
    goto end
)

shift
goto LOOP
:ENDLOOP

if "x%run_cmake_enable%"  == "xtrue" call :cmake
if "x%run_build%"  == "xtrue" call :build
goto end

:help
    echo  Usage:  build.bat --cmake                                   Create a VS 2015 project
    echo          build.bat --cmake -G "Visual Studio 15 2017"        Create a VS 2017 project
    echo          build.bat --build                                   Compile the project
    exit /b

:flags_initialization
    set run_cmake_enable=
    set build_enable=
    set generator=Visual Studio 14 2015
    exit /b

:cmake
    echo -- Create a project ...
    cmake -G "%generator%" "%ROOT_DIR%"
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