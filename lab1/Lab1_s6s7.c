// Name: Manpreet Sokhi
// Date: April 1, 2020
// Title: Lab assignment 1: Unix/Linux Commands and Overview of C Programming
// Description: This program calculates the probabilities values in Circuit Switching and Packet Switching

/*COEN 146L : Lab1 */
/*Sample C program for Lab assignment 1*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <pthread.h>
#include <math.h>

double factorial(int input){
    int i = 1;
    double result = 1;
    for (i = input; i > 1; --i){
        result *= i;
    }
    return result;
}

int main() {
    int linkBandwidth = 200;
    int userBandwidth = 20;
    double tPSuser = 0.1;
    int nPSusers = 19;

    // part 6
    int nCSusers = linkBandwidth / userBandwidth;
    printf ("The number of circuit-switched users that can be supported: %d\n", nCSusers);

    // part 7a
    double pPSuser = tPSuser;
    printf ("The probability that a given (specific) user is busy transmitting is: %f\n", pPSuser);

    // part 7b
    double pPSuserNotBusy = 1 - pPSuser;
    printf ("The probability that one specific other user is not busy is: %f\n", pPSuserNotBusy);

    // part 7c
    double allSpecificUsersNotBusy = pow(pPSuserNotBusy, (nPSusers - 1));
    printf ("The probability that all of the other specific other users are not busy is: %f\n", allSpecificUsersNotBusy);

    // part 7d
    double oneSpecificUserTransmitting = pPSuser * pow (pPSuserNotBusy, (nPSusers - 1));
    printf ("The probability that one specific user is transmitting and the remaining users are not transmitting is: %.2e\n", oneSpecificUserTransmitting);

    // part 7e
    double anyOne = 19 * pPSuser * pow(pPSuserNotBusy, (nPSusers - 1));
    printf("The probability that exactly one (any one) of the nPSusers users is busy is: %.2e\n", anyOne);

    // part 7f
    double tenUsers = pow(pPSuser, 10) * pow(pPSuserNotBusy, nPSusers - 10);
    printf("The probability that 10 specific users of nPSusers are transmitting and the others are idle is: %.2e\n", tenUsers);

    // part 7g
    double userCombos = factorial(nPSusers)/ factorial(10) /factorial(nPSusers - 10);
    double anyTen = tenUsers * userCombos;
    printf("The probability that any 10 users of nPSusers are transmitting and the others are idle is : %.2e\n", anyTen);

    // part 7h
    double result = 0;
    int i;
    for (i = 11; i < userBandwidth; i++){
        double countUsers = pow(pPSuser, i) * pow(pPSuserNotBusy, nPSusers - i);
        double combos = factorial(nPSusers)/ factorial(i) /factorial(nPSusers - i);
        result += countUsers * combos;
    }
    printf("The probability that more than 10 users of nPSusers are transmitting and the others are idle is: %.2e\n", result);

    return 0;
}