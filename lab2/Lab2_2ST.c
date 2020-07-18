// Name: Manpreet Sokhi
// Date: April 8, 2020
// Title: Lab assignment 2: Multithreading in C and network commands
// Description: Part 2 step 4: This program calculates persistent and non-persistent RTT

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // RTT
    int RTT1 = 3;
    int RTT2 = 20;
    int RTT3 = 26;
    int RTTHTTP = 47;
    int total = 0;
    int temp;

    // part A
    total = RTT1 + RTT2 + RTT3 + (2 * RTTHTTP);
    printf("part A in ms: %d\n", total);

    // part B
    total = RTT1 + RTT2 + RTT3 + (2 * RTTHTTP) + (12 * RTTHTTP);
    printf("part B in ms: %d\n", total);

    // part C
    if (argc < 2) {
        printf("Usage\n");
    } else {
        temp = atoi(argv[1]);
        double packets = 6 / temp;
        int max;

        if ((packets - (int)packets) < 0.5) {
            max = (int)packets;
        } else {
            max = (int)packets + 1;
        }

        total = RTT1 + RTT2 + RTT3 + (2 * RTTHTTP) + (2 * RTTHTTP) + (max * RTTHTTP);
        printf("part C persistent in ms: %d\n", total);

        total = RTT1 + RTT2 + RTT3 + (2 * RTTHTTP) + RTTHTTP;
        printf("part C non-persistent in ms: %d\n", total);
    }

    return 0;
}