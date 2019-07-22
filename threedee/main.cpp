/** Server Location optimization
 *
 * Minimizes the total distance between clients and servers.
 *
 * The client locations and the number of servers are specified.
 * Servers are located at client locations
 */

#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>

#include "cServitor.h"

using namespace std;

cServitor theServitor;


/**
 * @brief Recursive function to test all possible combinations of server positions
 * @param places  test server locations
 * @param placed  number of servers placed in test server locations
 * 
 *  For an explanation of how this works:
 *  https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
 */
void combination(
    vector<int> places,
    int placed )
{
	// check if all Servers have been placed
	if( placed == theServitor.myServerCount ) {
		theServitor.SaveIfBetter( places );
		return;
	}
	
	// loop over locations to the 'left' of last placed
	int i;
	if( ! placed )
		i = 0;
	else
		i = places[placed-1]+1;
	for( ; i < theServitor.ClientCount(); i++ ) {

		// place a server
		places[placed++] = i;

		// place the remaining Servers
		combination( places, placed+1 );
	}
}


int main(int argc, char** argv)
{
	theServitor.Test();

	theServitor.Input();

	theServitor.Optimize();

	cout << theServitor.ResultsText() << "\n";

	return 0;
}
