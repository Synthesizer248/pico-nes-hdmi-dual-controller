# Build Guide

## Prerequisites

- Raspberry Pi Pico SDK toolchain installed
- CMake 3.19+
- Ninja or Make
- ARM GCC (`arm-none-eabi-gcc`)

## 1) Set Pico SDK Path

PowerShell:

```powershell
$env:PICO_SDK_PATH = "C:\path\to\pico-sdk"
```

## 2) Configure

```powershell
cmake -S . -B build -DPICO_BOARD=pico
```

## 3) Build

```powershell
cmake --build build
```

Output artifacts are generated in `build/src/`.

## 4) Flash UF2

1. Hold `BOOTSEL` on Pico and connect USB.
2. Copy generated `.uf2` file to `RPI-RP2` drive.

## Optional: PicoDVI Dependency

Run:

```powershell
powershell -ExecutionPolicy Bypass -File scripts/fetch_dependencies.ps1
```

Then build with:

```powershell
cmake -S . -B build -DPICO_BOARD=pico -DUSE_PICODVI=ON
cmake --build build
```

## Notes

- Current firmware includes a stub `hdmi_video` backend.
- Integrate your PicoDVI backend in `src/hdmi_video.c`.
