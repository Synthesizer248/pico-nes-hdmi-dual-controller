# HDMI Circuit Diagram

![RP2040 HDMI reference circuit](./hdmi_circuit_diagram.svg)

## Summary

This diagram shows a practical HDMI TX wiring concept for RP2040 using PicoDVI-style TMDS output:

- 8 GPIO lines used for 4 differential TMDS pairs
- Per-line resistor network (commonly 270R series + 130R to GND)
- Optional DDC (`SCL`, `SDA`) and `HPD` readback lines
- ESD protection on HDMI-facing signals

## Design Notes

- Keep TMDS traces short and length-matched per pair.
- Use 1% resistors for repeatable TMDS levels.
- Place resistor ladder and ESD devices close to HDMI connector.
- Maintain a low-impedance continuous ground return.
- For production hardware, follow a validated PicoDVI reference layout.

## Files

- Diagram: `hardware/hdmi/hdmi_circuit_diagram.svg`
- This note: `hardware/hdmi/README.md`
