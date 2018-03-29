# Start uIPTool utility for AUTO folder

(c) 2018 by Matthias Arndt <marndt@asmsoftware.de>

The MIT License applies, see LICENSE for details


## Abstract
This is a utility for the Atari ST AUTO folder.
It allows to run the uIPTool (https://bitbucket.org/sqward/uip-tools)
at system startup without having to manually click on the desktop.

Place it in AUTO folder before running MiNT/MagiC or any network stacks like STING.

## System requirements

- Atari ST or compatible computer
- uIPTool and a compatible Atari NIC (Netusbee, Hydra)

## Installation

1. copy uIPTool as UIP.TOS in the root of your boot drive
2. place STARTUIP.PRG in your AUTO folder (preferrably at the beginning)
3. reboot

## Operation

- The tool waits until 5s timeout for keyboard input.
- If there is no keyboard input, the AUTO boot sequence is resumed.
- Press 'U' to activate uIPTool once. Boot continues after its termination.
- Press 'R' to activate uIPTool in repeating mode.

## Repeating mode

In repeating mode uIPTool is started.
When the tool crashes or terminates, the user can quit and resume the
system boot sequence if desired.
After a small timeout of 5s uIPTool will start again.

I had troubles on my LAN with lossing connection and it was tedious
to restart uIPTool by hand in these cases.
