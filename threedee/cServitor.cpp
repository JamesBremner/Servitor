#include <sstream>
#include <iostream>
#include <cmath>

#include "cRunWatch.h"

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
    for( int k = 0; k < (int)L.size(); k += 3 )
    {
        l.x = L[k];
        l.y = L[k+1];
        l.z = L[k+2];
        myClientLocations.push_back( l );
    }
}

void cServitor::ClientLocations( int count )
{
    /* initialize random seed: */
    srand (time(NULL));
    vector<double> L;
    for( int k = 0; k < 3 * count; k++ )
    {
        L.push_back( rand() % (count * 10 ) );
    }
    ClientLocations( L );
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
    for( int kl = 0; kl < L; kl++ )
    {
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
    for( int ka = 0; ka < (int)myClientLocations.size(); ka++ )
    {
        int min_d = 20000;
        // loop over servers
        for( int kt = 0; kt < myServerCount;  kt++ )
        {

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

int cServitor::sum_all_distances( const vector<cLoc>& locs ) const
{
    int total = 0;
    // loop over clients
    for( int ka = 0; ka < (int)myClientLocations.size(); ka++ )
    {
        int min_d = 20000;
        // loop over servers
        for( auto& s : locs )
        {

            // distance between server and client
            double d = ClientLocation(ka).dist( s );

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
    for( auto& l : myServerLocations )
        ss << l.Text() << ", ";
    return ss.str();
}

void cServitor::SaveIfBetter( const vector<int>& ServerLocation )
{
    // calculate total distance from all clients to their nearest server
    int td = sum_all_distances( ServerLocation );
    if( td < myMinTotal )
    {
        // record a new minimum
        myMinTotal = td;
        myServerLocIndex = ServerLocation;
    }
}
void cServitor::Optimize()
{
    void combination(
        vector<int> places,
        int placed );

    myMinTotal = 1000000;
    vector< int > P( myServerCount );

    raven::set::cRunWatch::Clear();
    raven::set::cRunWatch::Start();
    {

        raven::set::cRunWatch w("cServitor::Optimize");

        switch( myOptimizer )
        {
        default:
        case eOptimizer::exhaustive_search:
            combination( P, 0 );
            myServerLocations.clear();
            for( auto i : myServerLocIndex )
            {
                myServerLocations.push_back( ClientLocation( i ) );
            }
            break;

        case eOptimizer::kmeans:
            KMeans();
            break;
        }
    }

    raven::set::cRunWatch::Report();
}

void cServitor::KMeans()
{
    // initialize server locations among client locations by index
    myServerLocIndex.clear();
    for( int k = 0; k < myServerCount; k++ )
    {
        int ic = k * (double)ClientCount()/myServerCount;
        //cout << ClientLocation( ic ).Text() << ", ";
        myServerLocations.push_back( ClientLocation(ic) );
    }
    //cout << "\n";
    //cout << "\nKMeans " << sum_all_distances( myServerLocations ) << "\n";

    // iteration loop
    for( int kiter = 0; kiter < 4; kiter++ )
    {
        // assign clients to nearest server
        vector<int> server_group;
        for( auto& cl : myClientLocations )
        {
            double m = 1000000000000000000000.0;
            int sg;
            for( int si = 0; si < myServerCount; si++ )
            {
                double td = cl.dist( myServerLocations[ si ] );
                if( td < m )
                {
                    m = td;
                    sg = si;
                }
            }
            server_group.push_back( sg );
        }

        // move servers to mean location of clients assigned
        for( int ks = 0; ks < myServerCount; ks++ )
        {
            double ax = 0;
            double ay = 0;
            double az = 0;
            int count = 0;
            for( int kc = 0; kc < ClientCount(); kc++ )
            {
                if( ks == server_group[ kc ] )
                {
                    cLoc l = ClientLocation( kc );
                    ax += l.x;
                    ay += l.y;
                    az += l.z;
                    count++;
                }
            }
            cLoc l;
            l.x = ax / count;
            l.y = ay / count;
            l.z = az / count;
            myServerLocations[ ks ] = l;
        }

//        for( auto& l : myServerLocations )
//            cout << l.Text() << ", ";
//        cout << " sum all distances " << sum_all_distances( myServerLocations ) << "\n";
    }
    myMinTotal = sum_all_distances( myServerLocations );
}

void cServitor::Test()
{
    myServerCount = 5;
    ClientLocations(
    {
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
    if( (int)R.find("min total 9") == -1 )
    {
        cout << InputText() << "\n";
        cout << R << "\n";
        throw runtime_error("Test Failed");
    }
    cout << "Test Passed\n";
}

void cServitor::TestPerformance()
{
    myOptimizer = eOptimizer::kmeans;

    cout << "\n10 clients\n";
    myServerCount = 5;
    ClientLocations( 10 );
    myOptimizer = eOptimizer::kmeans;
    Optimize();
    cout << ResultsText() << "\n";
    myOptimizer = eOptimizer::exhaustive_search;
    Optimize();
    cout << ResultsText() << "\n";

    cout << "\n20 clients\n";
    myServerCount = 10;
    ClientLocations( 20 );
    Optimize();
    cout << ResultsText() << "\n";


    cout << "\n30 clients\n";
    myServerCount = 10;
    ClientLocations( 30 );
    Optimize();
    cout << ResultsText() << "\n";

    myOptimizer = eOptimizer::exhaustive_search;

    cout << "10 clients\n";
    myServerCount = 5;
    ClientLocations( 10 );
    Optimize();
    cout << ResultsText() << "\n";


    cout << "20 clients\n";
    myServerCount = 10;
    ClientLocations( 20 );
    Optimize();
    cout << ResultsText() << "\n";


    cout << "30 clients\n";
    myServerCount = 10;
    ClientLocations( 30 );
    Optimize();
    cout << ResultsText() << "\n";
}
