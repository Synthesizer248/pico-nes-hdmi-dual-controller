# Roadmap

## Phase 1 - Bring-up (Done in this repo)

- Pico SDK project scaffold
- Dual custom push-button controller support
- Input debounce and sanitization
- Frame loop and render test pattern
- HDMI backend abstraction

## Phase 2 - Real HDMI Backend

- Integrate PicoDVI dependency
- Implement RGB565 frame submission in `hdmi_video.c`
- Validate stable 60Hz output

## Phase 3 - NES Emulator Core

- Import NES core source under `lib/`
- Implement adapter in `nes_core` module
- Add ROM loader strategy (flash, SD card, USB host, etc.)

## Phase 4 - Productization

- Controller PCB and enclosure
- Boot menu and ROM selector
- Save state support
- Audio output pipeline
