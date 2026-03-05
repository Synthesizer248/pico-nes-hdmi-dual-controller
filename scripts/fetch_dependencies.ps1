param(
    [string]$PicoDviRepo = "https://github.com/Wren6991/PicoDVI.git"
)

$ErrorActionPreference = "Stop"

$root = Split-Path -Parent $PSScriptRoot
$libDir = Join-Path $root "lib"
$picoDviDir = Join-Path $libDir "PicoDVI"

if (-not (Test-Path $libDir)) {
    New-Item -ItemType Directory -Path $libDir | Out-Null
}

if (Test-Path $picoDviDir) {
    Write-Host "PicoDVI already exists at $picoDviDir"
    exit 0
}

Write-Host "Cloning PicoDVI into $picoDviDir"
git clone $PicoDviRepo $picoDviDir

Write-Host "Dependency fetch complete."
