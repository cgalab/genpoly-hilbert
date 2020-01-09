The code make_hilbert generates instances of (closed) Hilbert curves. All
vertices have integer coordinates.

Compilation: 
Any standard C compiler will do. E.g.: 

    gcc -O2 -Wall -o make_hilbert make_hilbert.c

Usage:
    make_hilbert --number N --output XYZ
       where N is a positive integer.

Generating polygonal data: 

The runtime-option "--number N" specifies the order of the Hilbert curve.
The curve is written to the file named XYZ, as specified in "--output XYZ". 

Please direct bug reports or suggestions to Martin Held at held@cs.sbg.ac.at.
