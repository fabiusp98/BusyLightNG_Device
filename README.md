# BusyLightNG_Device
Companion device firmware for the [controller](https://github.com/fabiusp98/BusyLightNG-controller)

## Working principle
The firmware implements a simple loop consisting of reading the control character from the serial port (if available) to update the current requested color.
A filling animation is played back from the current to the requested color.

## Controller interface
Interface with the controller is by way of a 115200 serial port, sending 0 or 1 depending on the color.

# License
This code is provinded under the GNU AFFERO GENERAL PUBLIC LICENSE version 3, which is available in the repo.