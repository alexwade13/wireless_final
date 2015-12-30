Current Node Status
====================

## About

This file contains information about the current status of the sensor node. It
will contain what is assumed to be the next steps and what has been done. It
can also be used to pass instructions between individuals who are working on
this part of the project.

## Design Decisions

### Transmission

We had decided that each class would be responsible for its own transmission.
I've concluded that this is not the best option as much code is repeated in
each class. So, I've decided that a better option is to create a class that
handles all transmissions. It also encapsulates all XBee setup. I believe this
will enable a cleaner design and more intuitive transmissions.

## Next Steps

### 03/27/2015

Complete the classes for the sensors and ensure that they work properly with
the transmitter class.
