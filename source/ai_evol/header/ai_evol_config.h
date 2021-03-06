#define HRIR_VERSION_MAJOR 
#define HRIR_VERSION_MINOR 

/** 
* @mainpage AI Evolution algorithm
* @section intro Introduction.
* This project contains an abstract implementation of Evolution algorithm.
* It is an iteration based algorithm. In this implementation is based on states.
* One state describe one evolution iteration. It basically contains the population
* the mutatins, and the rank calculation function pointer. Via this function pointer
* one can adapt this algorithm.
*
* @section basic_things Basic Statements
* This library contains a list and a priority list. This containers always do a whole
* copy from the given object with specific function pointers. Due to this one has to
* always gaurantee the correct function usage to avoid memory leaks.
*/
