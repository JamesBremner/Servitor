/** 1D Server Location optimization
 * 
 * Minimizes the total distance between clients and servers.
 * 
 * Clients and servers are located along a line.
 * The client locations and the number of servers are specified.
 */
#include <iostream>
#include <vector>

using namespace std;

// Input specifications
int S;	// number of servers
int L;  // number of clients
std::vector< int > vl;	// the locations

// Output results

int min_total = 100000;	// min total distance found
vector<int> min_loc;	// server locations giving minimum total distance

/** Read problem spacifcation from stdin
 * 
 * line 0: Number of servers to be located
 * line 1: Number of clients
 * line 2: client location
 * line 3: client location
 * ...
 */
void Input()
{
	cin >> S;
	cin >> L;
	for( int kl = 0; kl < L; kl++ ) {
		int l;
		cin >> l;
		vl.push_back( l );
	}

	cout << "area locations: ";
	for( int l : vl )
		cout << l << " ";
	cout << "\n";
	return ;
}

int sum_all_distances( vector<int>& locs )
{
	int total = 0;
	// loop over clients
	for( int ka = 0; ka < L; ka++ ) {
		int min_d = 20000;
		// loop over servers
		for( int kt = 0; kt < S;  kt++ ) {
			
			// distance between server and client
			int d = abs( vl[ka] - vl[ locs[kt ] ] );
			
			// save if closest server to client
			if( d < min_d )
				min_d = d;
		}
		
		// add to total for all clients
		total += min_d;
	}
	return total;
}

void Dump()
{
	cout << "min total " << min_total << "\n";
	for( auto l : min_loc )
		cout << vl[l] << " ";
	cout << "\n";
}

// https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
void combination(
    vector<int> places,
    int placed )
{
	// check if all Servers have beem placed
	if( placed == S ) {
		
		// calculate total distance from all clients to their nearest server
		int td = sum_all_distances( places );
		if( td < min_total )
		{
			// record a new minimum
			min_total = td;
			min_loc = places;
		}
		return;
	}
	// loop over locations to the 'left' of last placed 
	int i;
	if( ! placed )
		i = 0;
	else
		i = places[placed-1]+1;
	for( ; i < L; i++ ) {
		
		// place an ATM
		places[placed] = i;
		
		// place the remaining ATMs
		combination( places, placed+1 );
	}
}

int main(int argc, char** argv)
{

	Input();

	vector< int > P( S );
	combination( P, 0 );
	Dump();

	return 0;
}
