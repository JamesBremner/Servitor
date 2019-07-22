#include <sstream>
#include <iostream>
#include <cmath>

#include "cServitor.h"

string cLoc::Text()
{
	stringstream ss;
	ss << x <<" "<< y <<" "<< z;
	return ss.str();
}

void cServitor::ClientLocations( const vector<double>& L )
{
	myClientLocations.clear();
	cLoc l;
	for( int k = 0; k < (int)L.size(); k += 3 ) {
		l.x = L[k];
		l.y = L[k+1];
		l.z = L[k+2];
		myClientLocations.push_back( l );
	}
}

cLoc cServitor::ClientLocation( int k ) const
{
	if( 0 > k || k >= (int)myClientLocations.size() )
		throw std::runtime_error("AOB");
	return myClientLocations[ k ];
}


/** Read problem spacifcation from stdin
 *
 * line 0: Number of servers to be located
 * line 1: Number of clients
 * line 2: client location
 * line 3: client location
 * ...
 */
void cServitor::Input()
{
	myClientLocations.clear();

	cin >> myServerCount;
	int L;
	cin >> L;
	for( int kl = 0; kl < L; kl++ ) {
		cLoc l;
		cin >> l.x;
		cin >> l.y;
		cin >> l.z;
		myClientLocations.push_back( l );
	}

	cout << InputText() << "\n";
}

string cServitor::InputText()
{
	stringstream ss;
	ss << " client locations: ";
	for( auto& l : myClientLocations )
		ss << l.x <<" "<< l.y <<" "<< l.z << ", ";
	return ss.str();
}

int cServitor::sum_all_distances( const vector<int>& locs ) const
{
	int total = 0;
	// loop over clients
	for( int ka = 0; ka < (int)myClientLocations.size(); ka++ ) {
		int min_d = 20000;
		// loop over servers
		for( int kt = 0; kt < myServerCount;  kt++ ) {

			// distance between server and client
			double d = ClientLocation(ka).dist( ClientLocation( locs[kt] ));

			// save if closest server to client
			if( d < min_d )
				min_d = d;
		}

		// add to total for all clients
		total += min_d;
	}
	return total;
}

string cServitor::ResultsText()
{
	stringstream ss;
	ss << "min total " << myMinTotal << "\n";
	for( auto i : myServerLocations )
		ss << ClientLocation(i).Text() << ", ";
	return ss.str();
}

void cServitor::SaveIfBetter( const vector<int>& ServerLocation )
{
	// calculate total distance from all clients to their nearest server
	int td = sum_all_distances( ServerLocation );
	if( td < myMinTotal ) {
		// record a new minimum
		myMinTotal = td;
		myServerLocations = ServerLocation;
	}
}
void cServitor::Optimize()
{
	void combination(
	    vector<int> places,
	    int placed );
		
	myMinTotal = 1000000;
	vector< int > P( myServerCount );
	combination( P, 0 );
}

void cServitor::Test()
{
	myServerCount = 5;
	ClientLocations( {
		1, 0, 0,
		2, 0, 0,
		3, 0, 0,
		6, 0, 0,
		7, 0, 0,
		9, 0, 0,
		11, 0, 0,
		22, 0, 0,
		44, 0, 0,
		50, 0, 0
	} );

	Optimize();

	string R = ResultsText();
	if( (int)R.find("min total 9") == -1 ) {
		cout << InputText() << "\n";
		cout << R << "\n";
		throw runtime_error("Test Failed");
	}
	cout << "Test Passed\n";
}
