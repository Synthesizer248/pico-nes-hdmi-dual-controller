# Pico NES HDMI Dual Controller

Open-source RP2040 project for building a NES-style emulator console with HDMI video output and two custom push-button controllers.

## About

This repository provides a complete starter architecture for:

- Raspberry Pi Pico / RP2040 based NES emulator host
- HDMI/DVI output pipeline abstraction (PicoDVI-ready)
- Two-player custom controller input using direct push buttons
- Modular emulator core adapter layer (`nes_core`) so you can plug in an NES core implementation

## Features

- RP2040 C/C++ firmware structure using Pico SDK
- Dual-controller input scanning with software debounce
- NES-style button mapping (`A`, `B`, `Select`, `Start`, `Up`, `Down`, `Left`, `Right`)
- Input sanitation (`Up+Down` and `Left+Right` conflict handling)
- Frame timing loop targeting 60 FPS
- Stub renderer and emulator adapter for bring-up testing
- HDMI reference circuit diagram and wiring notes
- Controller reference circuit diagram and wiring notes
- Build, hardware, and roadmap documentation

## Repository Layout

```text
.
|-- CMakeLists.txt
|-- pico_sdk_import.cmake
|-- include/
|   |-- project_config.h
|   |-- controller.h
|   |-- hdmi_video.h
|   `-- nes_core.h
|-- src/
|   |-- CMakeLists.txt
|   |-- main.c
|   |-- controller.c
|   |-- hdmi_video.c
|   `-- nes_core_stub.c
|-- docs/
|   |-- build.md
|   |-- hardware.md
|   `-- roadmap.md
|-- hardware/
|   |-- controllers/
|   |   |-- wiring.md
|   |   `-- controller_circuit_diagram.svg
|   `-- hdmi/
|       |-- README.md
|       `-- hdmi_circuit_diagram.svg
`-- scripts/
    `-- fetch_dependencies.ps1
```

## Hardware Overview

- Board: Raspberry Pi Pico (RP2040)
- Video output: HDMI/DVI via external RP2040-compatible DVI hardware (PicoDVI style)
- Controllers: two custom wired remotes, each with 8 push buttons + common GND
- HDMI reference diagram: `hardware/hdmi/hdmi_circuit_diagram.svg`
- Controller reference diagram: `hardware/controllers/controller_circuit_diagram.svg`

## Quick Start

1. Install Pico SDK toolchain.
2. Set `PICO_SDK_PATH` environment variable.
3. (Optional for HDMI) Fetch PicoDVI library:
   `powershell -ExecutionPolicy Bypass -File scripts/fetch_dependencies.ps1`
4. Configure and build:
   ```powershell
   cmake -S . -B build -DPICO_BOARD=pico
   cmake --build build
   ```
5. Flash generated `.uf2` to Pico.

## Emulator Core Integration

Current repository ships with a bring-up/test stub renderer.

To enable real NES emulation:

1. Add your emulator core source into `lib/` (for example a port of nofrendo/fceumm).
2. Implement adapter functions declared in `include/nes_core.h`.
3. Update `src/CMakeLists.txt` to compile and link the selected core.

## Controller Mapping

- `A`
- `B`
- `Select`
- `Start`
- `Up`
- `Down`
- `Left`
- `Right`

Pin assignment defaults are in `include/project_config.h`.

## License

MIT License (see `LICENSE`).
