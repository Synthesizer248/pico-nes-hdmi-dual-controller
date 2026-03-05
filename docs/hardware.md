# Hardware Guide

## Core Console Hardware

- Raspberry Pi Pico (RP2040)
- HDMI/DVI output board compatible with RP2040 TMDS generation (PicoDVI style)
- 5V power supply (minimum 2A recommended)
- Optional level-safe ESD protection on controller lines

## Controller Concept (2 Players)

Each player remote has 8 push buttons:

- A
- B
- Select
- Start
- Up
- Down
- Left
- Right

Buttons are wired as active-low:

- one side of each button -> assigned GPIO
- other side -> GND
- internal pull-ups enabled in firmware

## Controller Circuit Diagram

- Reference diagram: `hardware/controllers/controller_circuit_diagram.svg`
- Wiring details: `hardware/controllers/wiring.md`

## Default Controller GPIO Mapping

| Function | Player 1 GPIO | Player 2 GPIO |
|---|---:|---:|
| A | GP2 | GP10 |
| B | GP3 | GP11 |
| Select | GP4 | GP12 |
| Start | GP5 | GP13 |
| Up | GP6 | GP14 |
| Down | GP7 | GP15 |
| Left | GP8 | GP16 |
| Right | GP9 | GP17 |

## HDMI Output Notes

- HDMI path is abstracted by `hdmi_video` module.
- For real signal output, integrate PicoDVI initialization and frame scanout in `src/hdmi_video.c`.
- Keep HDMI wiring short and follow your chosen DVI board reference design.

## HDMI Circuit Diagram

- Reference diagram: `hardware/hdmi/hdmi_circuit_diagram.svg`
- Design notes: `hardware/hdmi/README.md`

## Power and Grounding

- Share common GND between console and both controller remotes.
- Use twisted pairs or shielded cable for longer controller leads.
- Add TVS/ESD protection if controllers are hot-plugged.
