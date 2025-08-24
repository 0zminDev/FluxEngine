param(
    [string]$Command = "build"
)

# Folder build
$BuildDir = "build"

# Ścieżka do exe
$SandboxExe = Join-Path $BuildDir "bin/windows/Sandbox.exe"

switch ($Command.ToLower()) {
    "build" {
        # Tworzymy folder build jeśli nie istnieje
        if (!(Test-Path $BuildDir)) {
            New-Item -ItemType Directory -Path $BuildDir | Out-Null
        }

        # Generowanie i budowa projektu w trybie Release
        Write-Host "Building project..."
        cmake -S . -B $BuildDir -G "Ninja" -DCMAKE_BUILD_TYPE=Release
        cmake --build $BuildDir --config Release
        Write-Host "Build finished."
    }

    "run" {
        if (!(Test-Path $SandboxExe)) {
            Write-Host "Sandbox.exe nie istnieje. Najpierw uruchom build."
            exit 1
        }
        Write-Host "Running Sandbox..."
        & $SandboxExe
    }

    default {
        Write-Host "Nieznana komenda. Użyj: build.ps1 build | run"
    }
}
