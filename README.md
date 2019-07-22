# Servitor
Minimize total distance between clients and servers.

/** Server Location optimization
 * 
 * Minimizes the total distance between clients and servers.
 * 
 * The client locations and the number of servers are specified.
 */
 
 /** Read problem spacifcation from stdin
 * 
 * line 0: Number of servers to be located
 * line 1: Number of clients
 * line 2: client location
 * line 3: client location
 * ...
 */
 
 sample data:
 
 5
10
1 0 0
2 0 0
3 0 0
6 0 0
7 0 0
9 0 0
11 0 0
22 0 0 
44 0 0
50 0 0

Two optimizing algorithms are implemented:

 - Exhaustive search gives the absolute minimum total distance, but is too slow from more than ~30 clients
 
 - K-Means clustering gives an answer in a reasonable time for larger number of clients with a total distance reasonably close to the absolute minimum
