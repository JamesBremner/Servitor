#include <string>
#include <vector>
using namespace std;

/**
 * @class cLoc
 * @author James
 * @date 22/07/2019
 * @file cServitor.h
 * @brief A location in 3D space
 */
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

/**
 * @class cServitor
 * @author James
 * @date 22/07/2019
 * @file cServitor.h
 * @brief Locate servers among clients
 */
class cServitor
{
public:

    enum class eOptimizer {
        exhaustive_search,
        kmeans
        } myOptimizer;

	int myServerCount;						// specified number of servers to place
	vector< cLoc > myClientLocations;		// specified client locations

	// server locations giving minimum total distance
	// servers are located at the same location as one of the clients
	// this stores the index to the client where the server is located
	vector< int > myServerLocIndex;

	// server locations
	vector< cLoc > myServerLocations;

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

	void TestPerformance();

	// Locate servers using K-Means clustering
	// https://en.wikipedia.org/wiki/K-means_clustering
	void KMeans();

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

	int sum_all_distances( const vector<cLoc>& ServerLocations ) const;



/**
 * @brief Set client locations
 * @param L vector of x,y,z locations for clients
 */
	void ClientLocations( const vector<double>& L );

	void ClientLocations( int count );

/// Number of clients
	int ClientCount()
	{
		return myClientLocations.size();
	}

/// Location of kth client
	cLoc ClientLocation( int k ) const;

};
