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

using namespace std;

class cLoc
{
public:
	double x;
	double y;
	double z;

	double dist( const cLoc& o )
	{
		double dx = x - o.x;
		double dy = y - o.y;
		double dz = z - o.z;
		return sqrt( dx*dx+dy*dy+dz*dz );
	}

	string Text();
};

class cServitor
{
public:
	int myServerCount;						// specified number of servers to place
	vector< cLoc > myClientLocations;		// specified client locations

	// server locations giving minimum total distance
	// servers are located at the same location as one of the clients
	// this stores the index to the client where the server is located
	vector< int > myServerLocations;
	
	// minimum total distances between clients and their nearest server
	double myMinTotal;

	/// Input problem specs from stdin
	void Input();
	
	/// Human readable input specs
	string InputText();
	
	/// Optimize server locations
	void Optimize();
	
	/// Human readable results
	string ResultsText();
	
	/// Run unit tests
	void Test();

/**
 * @brief Save results if the minimum total distance is smaller than previous
 * @param ServerLocation  test locations of servers
 */
	void SaveIfBetter( const vector<int>& ServerLocation );
	
/**
 * @brief Calculate total distances between clients and their nearest server
 * @param ServerLocations locations of servers
 */
	int sum_all_distances( const vector<int>& ServerLocations ) const;

/**
 * @brief Set client locations
 * @param L vector of x,y,z locations for clients
 */
	void ClientLocations( const vector<double>& L );

/// Number of clients
	int ClientCount()
	{
		return myClientLocations.size();
	}
	
/// Location of kth client
	cLoc ClientLocation( int k );

};

cServitor theServitor;

// Input specifications
//int S;	 number of servers
//int L;   number of clients
//std::vector< cLoc > vl;	 the client locations
//
// Output results

//int min_total = 100000;	// min total distance found



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

cLoc cServitor::ClientLocation( int k )
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
	for( int ka = 0; ka < (int)theServitor.myClientLocations.size(); ka++ ) {
		int min_d = 20000;
		// loop over servers
		for( int kt = 0; kt < theServitor.myServerCount;  kt++ ) {

			// distance between server and client
			double d = theServitor.ClientLocation(ka).dist( theServitor.ClientLocation( locs[kt] ));

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
		places[placed] = i;

		// place the remaining Servers
		combination( places, placed+1 );
	}
}

void cServitor::Optimize()
{
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

int main(int argc, char** argv)
{
	theServitor.Test();

	theServitor.Input();

	theServitor.Optimize();

	cout << theServitor.ResultsText() << "\n";

	return 0;
}
