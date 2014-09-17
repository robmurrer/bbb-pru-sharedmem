# BBB PRU Shared Memory Test 

A simple PRU shared memory example 

The C program reads in an integer from stdin and copies that integer into the shared memory of the PRU.
The PRU polls that specific memory location for the a zero.
When a zero is found in the shared memory, the program resets the memory to one and exits. 

## Installation

An updated device tree compiler may be needed:

    wget -c https://raw.githubusercontent.com/RobertCNelson/tools/master/pkgs/dtc.sh; chmod +x dtc.sh; ./dtc.sh

The [PRU Drivers](https://github.com/beagleboard/am335x_pru_package) must also be installed:


The following will compile all the code for the PRU and main cpu:
    
    make

Compile the device tree overlay and enable it:

    cd device-tree
    make enable


## Running
    
    ./sharedmem



