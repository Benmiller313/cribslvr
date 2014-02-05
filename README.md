CribSlvr
========
An application for simulating and solving Cribbage games. 

Contents
----
Currently, this package includes an executable 'solve_hand' that determines the ideal discard for a given hand, and 'simulate_hands', an executable which runs repeated simulated crib hands with two computer players. 'simulate_hands' updates the discard point value tables so running it has the effect of teaching the program more accurate expected point values.

Also included is a set of unit tests focused on testing the underlying object files. 

Building
----
To compile the programs and run the unit tests, use the included Makefile.