param(
    [string]$Command = "build",
    [string]$Config = "Release"
)

# Główne ścieżki
$BuildDir   = "build"
$BinDir     = Join-Path $BuildDir "bin/windows"
$SandboxExe = Join-Path $BinDir "Sandbox.exe"

function Invoke-MSYS2Build {
    param([string]$Cmd)
    $MSYS2 = "C:\msys64\usr\bin\bash.exe"
    if (!(Test-Path $MSYS2)) { 
        Write-Host "⚠ MSYS2 bash not found at $MSYS2"
        exit 1
    }
    & $MSYS2 -lc $Cmd
}

function Convert-ToMSYSPath {
    param([string]$winPath)
    $path = $winPath -replace ":", ""
    $path = $path -replace "\\", "/"
    return "/$path"
}

switch ($Command.ToLower()) {
    "build" {
       if (!(Test-Path $BuildDir)) {
            New-Item -ItemType Directory -Path $BuildDir | Out-Null
        }

        Write-Host "Building project ($Config) using MSYS2 MinGW64..."

        $MSYS2 = "C:/msys64/usr/bin/bash.exe"
        $SourceDir = Convert-ToMSYSPath (Resolve-Path ".").Path
        $BuildDirMSYS = Convert-ToMSYSPath (Resolve-Path $BuildDir).Path

        $CmdConfigure = "export PATH=/mingw64/bin:/usr/bin:\$PATH && cmake -S $SourceDir -B $BuildDirMSYS -G Ninja -DCMAKE_BUILD_TYPE=$Config -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++"
        & $MSYS2 -lc $CmdConfigure
        if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

        $CmdBuild = "export PATH=/mingw64/bin:/usr/bin:\$PATH && cmake --build $BuildDirMSYS"
        & $MSYS2 -lc $CmdBuild
        if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

        Write-Host "Build finished."
    }

    "run" {
        if (!(Test-Path $SandboxExe)) {
            Write-Host "⚠ Sandbox.exe does not exist. Please run build first."
            exit 1
        }
        Write-Host "▶ Running Sandbox..."
        & $SandboxExe
    }

    "rebuild" {
        & $PSCommandPath clean
        & $PSCommandPath build -Config $Config
    }

    "clean" {
        if (Test-Path $BuildDir) {
            Remove-Item -Recurse -Force $BuildDir
            Write-Host "Cleaned build directory."
        } else {
            Write-Host "No Build Folder to clean"
        }
    }

    "test" {
        Write-Host "Running unit tests..."

        $MSYS2 = "C:/msys64/usr/bin/bash.exe"
        $BuildDirMSYS = Convert-ToMSYSPath (Resolve-Path $BuildDir).Path

        $CmdTest = "export PATH=/mingw64/bin:/usr/bin:`$PATH && ctest --output-on-failure --test-dir $BuildDirMSYS"
        & $MSYS2 -lc $CmdTest
        if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

        Write-Host "Tests finished."
    }

    default {
        Write-Host "Unknown command. Use: build.ps1 build | run | rebuild | clean | test"
    }
}
