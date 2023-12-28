# An MIDI adapter for KB connector of SFG-01/05 

The adapter allows to use Auto Bass Chord function (and see a marks of pressed keys on the screen) of SFG-05 with a MIDI keyboard using KB connector. Tested with a SFG-01/05 clone by RBSC: https://github.com/RBSC/SFG_Cartridge .

Built with Arduino Nano clone and WCH CH446Q switch matrix IC. Due to lack of a possibility to install a diode on each switch inside the matrix the adapter is not free from phantom key pressings in some occasions.

Depends on Arduino MIDI Library ( https://www.arduino.cc/reference/en/libraries/midi-library/ ) .
