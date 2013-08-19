#include "board.h"

using namespace std;

/* Public members. */

Board::Board()/*:
	nodes{
		Node(0, "eSW", {37}),
		Node(1, "eSE", {33}),
		Node(2, "dS-3", {22, 36, 37}),
		Node(3, "dS-2", {21, 22, 36}),
		Node(4, "dS-1", {21, 35, 36}),
		Node(5, "dS", {20, 21, 35}),
		Node(6, "dS1", {20, 34, 35}),
		Node(7, "dS2", {19, 20, 34}),
		Node(8, "dS3", {19, 33, 34}),
		Node(9, "dW-3", {22, 37, 38}),
		Node(10, "dE-3", {19, 32, 33}),
		Node(11, "cS-2", {11, 21, 22}),
		Node(12, "cS-1", {10, 11, 21}),
		Node(13, "cS", {10, 20, 21}),
		Node(14, "cS1", {9, 10, 20}),
		Node(15, "cS2", {9, 19, 20}),
		Node(16, "dW-2", {22, 23, 38}),
		Node(17, "cW-2", {11, 22, 23}),
		Node(18, "cE-2", {9, 18, 19}),
		Node(19, "dE-2", {18, 19, 32}),
		Node(20, "bS-1", {4, 10, 11}),
		Node(21, "bS", {3, 4, 10}),
		Node(22, "bS1", {3, 9, 10}),
		Node(23, "dW-1", {22, 23, 38}),
		Node(24, "cW-1", {11, 12, 23}),
		Node(25, "bW-1", {4, 11, 12}),
		Node(26, "bE-1", {3, 8, 9}),
		Node(27, "cE-1", {8, 9, 18}),
		Node(28, "dE-1", {18, 31, 32}),
		Node(29, "aS", {0, 3, 4}),
		Node(30, "dW", {23, 24, 39}),
		Node(31, "cW", {12, 23, 24}),
		Node(32, "bW", {1, 4, 12}),
		Node(33, "aW", {0, 1, 4}),
		Node(34, "0", {0}),
		Node(35, "aE", {0, 2, 3}),
		Node(36, "bE", {2, 3, 8}),
		Node(37, "cE", {8, 17, 18}),
		Node(38, "dE", {17, 18, 31}),
		Node(39, "aN", {0, 1, 2}),
		Node(40, "dW1", {24, 39, 40}),
		Node(41, "cW1", {5, 12, 24}),
		Node(42, "bW1", {1, 5, 12}),
		Node(43, "bE1", {2, 7, 8}),
		Node(44, "cE1", {7, 8, 17}),
		Node(45, "dE1", {17, 30, 31}),
		Node(46, "bN-1", {1, 5, 6}),
		Node(47, "bN", {1, 2, 6}),
		Node(48, "bN1", {2, 6, 7}),
		Node(49, "dW2", {13, 24, 40}),
		Node(50, "cW2", {5, 13, 24}),
		Node(51, "cE2", {7, 16, 17}),
		Node(52, "dE2", {16, 17, 30}),
		Node(53, "cN-2", {5, 13, 14}),
		Node(54, "cN-1", {5, 6, 14}),
		Node(55, "cN", {6, 14, 15}),
		Node(56, "cN1", {6, 7, 15}),
		Node(57, "cN2", {7, 15, 16}),
		Node(58, "dW3", {13, 25, 40}),
		Node(59, "dE3", {16, 29, 30}),
		Node(60, "dN-3", {13, 25, 26}),
		Node(61, "dN-2", {13, 14, 26}),
		Node(62, "dN-1", {14, 26, 27}),
		Node(63, "dN", {14, 15, 27}),
		Node(64, "dN1", {15, 27, 28}),
		Node(65, "dN2", {15, 16, 28}),
		Node(66, "dN3", {16, 28, 29}),
		Node(67, "eNW", {25}),
		Node(68, "eNE", {29})
	},
	faces{
                Face(0, "A", {29, 33, 34, 35, 39}, {1, 2, 3, 4}),
                Face(1, "BNW", {32, 33, 39, 42, 46, 47}, {0, 2, 4, 5, 6, 12}),
                Face(2, "BNE", {35, 36, 39, 43, 47, 48}, {0, 1, 3, 6, 7, 8}),
                Face(3, "BSE", {21, 22, 26, 29, 35, 36}, {0, 2, 4, 8, 9, 10}),
                Face(4, "BSW", {20, 21, 25, 29, 32, 33}, {0, 1, 3, 10, 11, 12}),
                Face(5, "CNW", {41, 42, 46, 50, 53, 54}, {1, 6, 12, 13, 14, 24}),
                Face(6, "CN", {46, 47, 48, 54, 55, 56}, {1, 2, 5, 7, 14, 15}),
                Face(7, "CNE", {43, 44, 48, 51, 56, 57}, {2, 6, 8, 15, 16, 17}),
                Face(8, "CE", {26, 27, 36, 37, 43, 44}, {2, 3, 7, 9, 17, 18}),
                Face(9, "CSE", {14, 15, 18, 22, 26, 27}, {3, 8, 10, 18, 19, 20}),
                Face(10, "CS", {12, 13, 14, 20, 21, 22}, {3, 4, 9, 11, 20, 21}),
                Face(11, "CSW", {11, 12, 17, 20, 24, 25}, {4, 10, 12, 21, 22, 23}),
                Face(12, "CW", {24, 25, 31, 32, 41, 42}, {1, 4, 5, 11, 23, 24}),
                Face(13, "DNW", {49, 50, 53, 58, 60, 61}, {5, 14, 24, 25, 26, 40}),
                Face(14, "DN-1", {53, 54, 55, 61, 62, 63}, {5, 6, 13, 15, 26, 27}),
                Face(15, "DN1", {55, 56, 57, 63, 64, 65}, {6, 7, 14, 16, 27, 28}),
                Face(16, "DNE", {51, 52, 57, 59, 65, 66}, {7, 15, 17, 28, 29, 30}),
                Face(17, "DE1", {37, 38, 44, 45, 51, 52}, {7, 8, 16, 18, 30, 31}),
                Face(18, "DE-1", {18, 19, 27, 28, 37, 38}, {8, 9, 17, 19, 31, 32}),
                Face(19, "DSE", {7, 8, 10, 15, 18, 19}, {9, 18, 20, 32, 33, 34}),
                Face(20, "DS1", {5, 6, 7, 13, 14, 15}, {9, 10, 19, 21, 34, 35}),
                Face(21, "DS-1", {3, 4, 5, 11, 12, 13}, {10, 11, 20, 22, 35, 36}),
                Face(22, "DSW", {2, 3, 9, 11, 16, 17}, {11, 21, 23, 36, 37, 38}),
                Face(23, "DW-1", {16, 17, 23, 24, 30, 31}, {11, 12, 22, 24, 38, 39}),
                Face(24, "DW1", {30, 31, 40, 41, 49, 50}, {5, 12, 13, 23, 39, 40}),
                Face(25, "ENW", {58, 60, 67}, {13, 26, 40}),
                Face(26, "EN-1", {60, 61, 62}, {13, 14, 25, 27}),
                Face(27, "EN", {62, 63, 64}, {14, 15, 26, 28}),
                Face(28, "EN1", {64, 65, 66}, {15, 16, 27, 29}),
                Face(29, "ENE", {59, 66, 68}, {16, 28, 30}),
                Face(30, "EE1", {45, 52, 59}, {16, 17, 29, 31}),
                Face(31, "EE", {28, 38, 45}, {17, 18, 30, 32}),
                Face(32, "EE-1", {10, 19, 28}, {18, 19, 31, 33}),
                Face(33, "ESE", {1, 8, 10}, {19, 32, 34}),
                Face(34, "ES1", {6, 7, 8}, {19, 20, 33, 35}),
                Face(35, "ES", {4, 5, 6}, {20, 21, 34, 36}),
                Face(36, "ES-1", {2, 3, 4}, {21, 22, 35, 37}),
                Face(37, "ESW", {0, 2, 9}, {22, 36, 38}),
                Face(38, "EW-1", {9, 16, 23}, {22, 23, 37, 39}),
                Face(39, "EW", {23, 30, 40}, {23, 24, 38, 40}),
                Face(40, "EW1", {40, 49, 58}, {13, 24, 25, 39})
	}*/
{
	std::vector<NodeID> adj_faces; adj_faces.push_back(37);
	nodes.push_back(Node(0, "eSW", adj_faces));
	adj_faces.clear(); adj_faces.push_back(33);
	nodes.push_back(Node(1, "eSE", adj_faces));
	adj_faces.clear(); adj_faces.push_back(22); adj_faces.push_back(36); adj_faces.push_back(37);
	nodes.push_back(Node(2, "dS-3", adj_faces));
	adj_faces.clear(); adj_faces.push_back(21); adj_faces.push_back(32); adj_faces.push_back(36);
	nodes.push_back(Node(3, "dS-2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(21); adj_faces.push_back(35); adj_faces.push_back(36);
	nodes.push_back(Node(4, "dS-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(20); adj_faces.push_back(21); adj_faces.push_back(35);
	nodes.push_back(Node(5, "dS", adj_faces));
	adj_faces.clear(); adj_faces.push_back(20); adj_faces.push_back(34); adj_faces.push_back(35);
	nodes.push_back(Node(6, "dS1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(19); adj_faces.push_back(20); adj_faces.push_back(34);
	nodes.push_back(Node(7, "dS2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(19); adj_faces.push_back(33); adj_faces.push_back(34);
	nodes.push_back(Node(8, "dS3", adj_faces));
	adj_faces.clear(); adj_faces.push_back(22); adj_faces.push_back(37); adj_faces.push_back(38);
	nodes.push_back(Node(9, "dW-3", adj_faces));
	adj_faces.clear(); adj_faces.push_back(19); adj_faces.push_back(32); adj_faces.push_back(33);
	nodes.push_back(Node(10, "dE-3", adj_faces));
	adj_faces.clear(); adj_faces.push_back(11); adj_faces.push_back(21); adj_faces.push_back(22);
	nodes.push_back(Node(11, "cS-2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(10); adj_faces.push_back(11); adj_faces.push_back(21);
	nodes.push_back(Node(12, "cS-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(10); adj_faces.push_back(20); adj_faces.push_back(21);
	nodes.push_back(Node(13, "cS", adj_faces));
	adj_faces.clear(); adj_faces.push_back(9); adj_faces.push_back(10); adj_faces.push_back(20);
	nodes.push_back(Node(14, "cS1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(9); adj_faces.push_back(19); adj_faces.push_back(20);
	nodes.push_back(Node(15, "cS2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(22); adj_faces.push_back(23); adj_faces.push_back(38);
	nodes.push_back(Node(16, "dW-2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(11); adj_faces.push_back(2); adj_faces.push_back(23);
	nodes.push_back(Node(17, "cW-2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(9); adj_faces.push_back(18); adj_faces.push_back(19);
	nodes.push_back(Node(18, "cE-2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(18); adj_faces.push_back(19); adj_faces.push_back(32);
	nodes.push_back(Node(19, "dE-2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(4); adj_faces.push_back(10); adj_faces.push_back(11);
	nodes.push_back(Node(20, "bS-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(3); adj_faces.push_back(4); adj_faces.push_back(10);
	nodes.push_back(Node(21, "bS", adj_faces));
	adj_faces.clear(); adj_faces.push_back(3); adj_faces.push_back(9); adj_faces.push_back(10);
	nodes.push_back(Node(22, "bS1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(22); adj_faces.push_back(23); adj_faces.push_back(38);
	nodes.push_back(Node(23, "dW-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(11); adj_faces.push_back(12); adj_faces.push_back(23);
	nodes.push_back(Node(24, "cW-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(4); adj_faces.push_back(11); adj_faces.push_back(12);
	nodes.push_back(Node(25, "bW-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(3); adj_faces.push_back(8); adj_faces.push_back(9);
	nodes.push_back(Node(26, "bE-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(8); adj_faces.push_back(9); adj_faces.push_back(18);
	nodes.push_back(Node(27, "cE-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(18); adj_faces.push_back(31); adj_faces.push_back(32);
	nodes.push_back(Node(28, "dE-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(0); adj_faces.push_back(3); adj_faces.push_back(4);
	nodes.push_back(Node(29, "aS", adj_faces));
	adj_faces.clear(); adj_faces.push_back(23); adj_faces.push_back(24); adj_faces.push_back(39);
	nodes.push_back(Node(30, "dW", adj_faces));
	adj_faces.clear(); adj_faces.push_back(1); adj_faces.push_back(23); adj_faces.push_back(24);
	nodes.push_back(Node(31, "cW", adj_faces));
	adj_faces.clear(); adj_faces.push_back(1); adj_faces.push_back(4); adj_faces.push_back(12);
	nodes.push_back(Node(32, "bW", adj_faces));
	adj_faces.clear(); adj_faces.push_back(0); adj_faces.push_back(1); adj_faces.push_back(4);
	nodes.push_back(Node(33, "aW", adj_faces));
	adj_faces.clear(); adj_faces.push_back(0);
	nodes.push_back(Node(34, "0", adj_faces));
	adj_faces.clear(); adj_faces.push_back(0); adj_faces.push_back(2); adj_faces.push_back(3);
	nodes.push_back(Node(35, "aE", adj_faces));
	adj_faces.clear(); adj_faces.push_back(2); adj_faces.push_back(3); adj_faces.push_back(8);
	nodes.push_back(Node(36, "bE", adj_faces));
	adj_faces.clear(); adj_faces.push_back(8); adj_faces.push_back(17); adj_faces.push_back(18);
	nodes.push_back(Node(37, "cE", adj_faces));
	adj_faces.clear(); adj_faces.push_back(17); adj_faces.push_back(18); adj_faces.push_back(31);
	nodes.push_back(Node(38, "dE", adj_faces));
	adj_faces.clear(); adj_faces.push_back(0); adj_faces.push_back(1); adj_faces.push_back(2);
	nodes.push_back(Node(39, "aN", adj_faces));
	adj_faces.clear(); adj_faces.push_back(24); adj_faces.push_back(39); adj_faces.push_back(40);
	nodes.push_back(Node(40, "dW1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(5); adj_faces.push_back(12); adj_faces.push_back(24);
	nodes.push_back(Node(41, "cW1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(1); adj_faces.push_back(5); adj_faces.push_back(12);
	nodes.push_back(Node(42, "bW1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(2); adj_faces.push_back(7); adj_faces.push_back(8);
	nodes.push_back(Node(43, "bE1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(7); adj_faces.push_back(8); adj_faces.push_back(17);
	nodes.push_back(Node(44, "cE1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(17); adj_faces.push_back(30); adj_faces.push_back(31);
	nodes.push_back(Node(45, "dE1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(1); adj_faces.push_back(5); adj_faces.push_back(6);
	nodes.push_back(Node(46, "bN-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(1); adj_faces.push_back(2); adj_faces.push_back(6);
	nodes.push_back(Node(47, "bN", adj_faces));
	adj_faces.clear(); adj_faces.push_back(2); adj_faces.push_back(6); adj_faces.push_back(7);
	nodes.push_back(Node(48, "bN1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(13); adj_faces.push_back(24); adj_faces.push_back(40);
	nodes.push_back(Node(49, "dW2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(5); adj_faces.push_back(13); adj_faces.push_back(24);
	nodes.push_back(Node(50, "cW2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(7); adj_faces.push_back(16); adj_faces.push_back(17);
	nodes.push_back(Node(51, "cE2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(16); adj_faces.push_back(17); adj_faces.push_back(30);
	nodes.push_back(Node(52, "dE2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(5); adj_faces.push_back(13); adj_faces.push_back(14);
	nodes.push_back(Node(53, "cN-2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(5); adj_faces.push_back(6); adj_faces.push_back(14);
	nodes.push_back(Node(54, "cN-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(6); adj_faces.push_back(14); adj_faces.push_back(15);
	nodes.push_back(Node(55, "cN", adj_faces));
	adj_faces.clear(); adj_faces.push_back(6); adj_faces.push_back(7); adj_faces.push_back(15);
	nodes.push_back(Node(56, "cN1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(7); adj_faces.push_back(15); adj_faces.push_back(16);
	nodes.push_back(Node(57, "cN2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(13); adj_faces.push_back(25); adj_faces.push_back(40);
	nodes.push_back(Node(58, "dW3", adj_faces));
	adj_faces.clear(); adj_faces.push_back(16); adj_faces.push_back(29); adj_faces.push_back(30);
	nodes.push_back(Node(59, "dE3", adj_faces));
	adj_faces.clear(); adj_faces.push_back(13); adj_faces.push_back(25); adj_faces.push_back(26);
	nodes.push_back(Node(60, "dN-3", adj_faces));
	adj_faces.clear(); adj_faces.push_back(13); adj_faces.push_back(14); adj_faces.push_back(26);
	nodes.push_back(Node(61, "dN-2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(14); adj_faces.push_back(26); adj_faces.push_back(27);
	nodes.push_back(Node(62, "dN-1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(14); adj_faces.push_back(15); adj_faces.push_back(27);
	nodes.push_back(Node(63, "dN", adj_faces));
	adj_faces.clear(); adj_faces.push_back(15); adj_faces.push_back(27); adj_faces.push_back(28);
	nodes.push_back(Node(64, "dN1", adj_faces));
	adj_faces.clear(); adj_faces.push_back(15); adj_faces.push_back(16); adj_faces.push_back(28);
	nodes.push_back(Node(65, "dN2", adj_faces));
	adj_faces.clear(); adj_faces.push_back(16); adj_faces.push_back(28); adj_faces.push_back(29);
	nodes.push_back(Node(66, "dN3", adj_faces));
	adj_faces.clear(); adj_faces.push_back(25);
	nodes.push_back(Node(67, "eNW", adj_faces));
	adj_faces.clear(); adj_faces.push_back(29);
	nodes.push_back(Node(68, "eNE", adj_faces));

	std::vector<NodeID> adj_nodes; adj_nodes.push_back(29); adj_nodes.push_back(33); adj_nodes.push_back(34); adj_nodes.push_back(35); adj_nodes.push_back(39);
	adj_faces.clear(); adj_faces.push_back(1); adj_faces.push_back(2); adj_faces.push_back(3); adj_faces.push_back(4);
	faces.push_back(Face(0, "A", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(32); adj_nodes.push_back(33); adj_nodes.push_back(39); adj_nodes.push_back(42); adj_nodes.push_back(46); adj_nodes.push_back(47);
	adj_faces.clear(); adj_faces.push_back(0); adj_faces.push_back(2); adj_faces.push_back(4); adj_faces.push_back(5); adj_faces.push_back(6); adj_faces.push_back(12);
    faces.push_back(Face(1, "BNW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(35); adj_nodes.push_back(36); adj_nodes.push_back(39); adj_nodes.push_back(43); adj_nodes.push_back(47); adj_nodes.push_back(48);
	adj_faces.clear(); adj_faces.push_back(0); adj_faces.push_back(1); adj_faces.push_back(3); adj_faces.push_back(6); adj_faces.push_back(7); adj_faces.push_back(8);
    faces.push_back(Face(2, "BNE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(21); adj_nodes.push_back(22); adj_nodes.push_back(26); adj_nodes.push_back(29); adj_nodes.push_back(35); adj_nodes.push_back(36);
	adj_faces.clear(); adj_faces.push_back(0); adj_faces.push_back(2); adj_faces.push_back(4); adj_faces.push_back(8); adj_faces.push_back(9); adj_faces.push_back(10);
    faces.push_back(Face(3, "BSE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(20); adj_nodes.push_back(21); adj_nodes.push_back(25); adj_nodes.push_back(29); adj_nodes.push_back(32); adj_nodes.push_back(33);
	adj_faces.clear(); adj_faces.push_back(0); adj_faces.push_back(1); adj_faces.push_back(3); adj_faces.push_back(10); adj_faces.push_back(11); adj_faces.push_back(12);
    faces.push_back(Face(4, "BSW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(41); adj_nodes.push_back(42); adj_nodes.push_back(46); adj_nodes.push_back(50); adj_nodes.push_back(53); adj_nodes.push_back(54);
	adj_faces.clear(); adj_faces.push_back(1); adj_faces.push_back(6); adj_faces.push_back(12); adj_faces.push_back(13); adj_faces.push_back(14); adj_faces.push_back(24);
    faces.push_back(Face(5, "CNW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(46); adj_nodes.push_back(47); adj_nodes.push_back(48); adj_nodes.push_back(54); adj_nodes.push_back(55); adj_nodes.push_back(56);
	adj_faces.clear(); adj_faces.push_back(1); adj_faces.push_back(2); adj_faces.push_back(5); adj_faces.push_back(7); adj_faces.push_back(14); adj_faces.push_back(15);
    faces.push_back(Face(6, "CN", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(43); adj_nodes.push_back(44); adj_nodes.push_back(48); adj_nodes.push_back(51); adj_nodes.push_back(56); adj_nodes.push_back(57);
	adj_faces.clear(); adj_faces.push_back(2); adj_faces.push_back(6); adj_faces.push_back(8); adj_faces.push_back(15); adj_faces.push_back(16); adj_faces.push_back(17);
    faces.push_back(Face(7, "CNE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(26); adj_nodes.push_back(27); adj_nodes.push_back(36); adj_nodes.push_back(37); adj_nodes.push_back(43); adj_nodes.push_back(44);
	adj_faces.clear(); adj_faces.push_back(2); adj_faces.push_back(3); adj_faces.push_back(7); adj_faces.push_back(9); adj_faces.push_back(17); adj_faces.push_back(18);
    faces.push_back(Face(8, "CE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(14); adj_nodes.push_back(15); adj_nodes.push_back(18); adj_nodes.push_back(22); adj_nodes.push_back(26); adj_nodes.push_back(27);
	adj_faces.clear(); adj_faces.push_back(3); adj_faces.push_back(8); adj_faces.push_back(10); adj_faces.push_back(18); adj_faces.push_back(19); adj_faces.push_back(20);
    faces.push_back(Face(9, "CSE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(12); adj_nodes.push_back(13); adj_nodes.push_back(14); adj_nodes.push_back(20); adj_nodes.push_back(21); adj_nodes.push_back(22);
	adj_faces.clear(); adj_faces.push_back(3); adj_faces.push_back(4); adj_faces.push_back(9); adj_faces.push_back(11); adj_faces.push_back(20); adj_faces.push_back(21);
    faces.push_back(Face(10, "CS", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(11); adj_nodes.push_back(12); adj_nodes.push_back(17); adj_nodes.push_back(20); adj_nodes.push_back(24); adj_nodes.push_back(25);
	adj_faces.clear(); adj_faces.push_back(4); adj_faces.push_back(10); adj_faces.push_back(12); adj_faces.push_back(21); adj_faces.push_back(22); adj_faces.push_back(23);
    faces.push_back(Face(11, "CSW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(24); adj_nodes.push_back(25); adj_nodes.push_back(31); adj_nodes.push_back(32); adj_nodes.push_back(41); adj_nodes.push_back(42);
	adj_faces.clear(); adj_faces.push_back(1); adj_faces.push_back(4); adj_faces.push_back(5); adj_faces.push_back(11); adj_faces.push_back(23); adj_faces.push_back(24);
    faces.push_back(Face(12, "CW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(49); adj_nodes.push_back(50); adj_nodes.push_back(53); adj_nodes.push_back(58); adj_nodes.push_back(60); adj_nodes.push_back(61);
	adj_faces.clear(); adj_faces.push_back(5); adj_faces.push_back(14); adj_faces.push_back(24); adj_faces.push_back(25); adj_faces.push_back(26); adj_faces.push_back(40);
    faces.push_back(Face(13, "DNW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(53); adj_nodes.push_back(54); adj_nodes.push_back(55); adj_nodes.push_back(61); adj_nodes.push_back(62); adj_nodes.push_back(63);
	adj_faces.clear(); adj_faces.push_back(5); adj_faces.push_back(6); adj_faces.push_back(13); adj_faces.push_back(15); adj_faces.push_back(26); adj_faces.push_back(27);
    faces.push_back(Face(14, "DN-1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(55); adj_nodes.push_back(56); adj_nodes.push_back(57); adj_nodes.push_back(63); adj_nodes.push_back(64); adj_nodes.push_back(65);
	adj_faces.clear(); adj_faces.push_back(6); adj_faces.push_back(7); adj_faces.push_back(14); adj_faces.push_back(16); adj_faces.push_back(27); adj_faces.push_back(28);
    faces.push_back(Face(15, "DN1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(51); adj_nodes.push_back(52); adj_nodes.push_back(57); adj_nodes.push_back(59); adj_nodes.push_back(65); adj_nodes.push_back(66);
	adj_faces.clear(); adj_faces.push_back(7); adj_faces.push_back(15); adj_faces.push_back(17); adj_faces.push_back(28); adj_faces.push_back(29); adj_faces.push_back(30);
    faces.push_back(Face(16, "DNE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(37); adj_nodes.push_back(38); adj_nodes.push_back(44); adj_nodes.push_back(45); adj_nodes.push_back(51); adj_nodes.push_back(52);
	adj_faces.clear(); adj_faces.push_back(7); adj_faces.push_back(8); adj_faces.push_back(16); adj_faces.push_back(18); adj_faces.push_back(30); adj_faces.push_back(31);
    faces.push_back(Face(17, "DE1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(18); adj_nodes.push_back(19); adj_nodes.push_back(27); adj_nodes.push_back(28); adj_nodes.push_back(37); adj_nodes.push_back(38);
	adj_faces.clear(); adj_faces.push_back(8); adj_faces.push_back(9); adj_faces.push_back(17); adj_faces.push_back(19); adj_faces.push_back(31); adj_faces.push_back(32);
    faces.push_back(Face(18, "DE-1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(7); adj_nodes.push_back(8); adj_nodes.push_back(10); adj_nodes.push_back(15); adj_nodes.push_back(18); adj_nodes.push_back(19);
	adj_faces.clear(); adj_faces.push_back(9); adj_faces.push_back(18); adj_faces.push_back(20); adj_faces.push_back(32); adj_faces.push_back(33); adj_faces.push_back(34);
    faces.push_back(Face(19, "DSE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(5); adj_nodes.push_back(6); adj_nodes.push_back(7); adj_nodes.push_back(13); adj_nodes.push_back(14); adj_nodes.push_back(15);
	adj_faces.clear(); adj_faces.push_back(9); adj_faces.push_back(10); adj_faces.push_back(19); adj_faces.push_back(21); adj_faces.push_back(34); adj_faces.push_back(35);
    faces.push_back(Face(20, "DS1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(3); adj_nodes.push_back(4); adj_nodes.push_back(5); adj_nodes.push_back(11); adj_nodes.push_back(12); adj_nodes.push_back(13);
	adj_faces.clear(); adj_faces.push_back(10); adj_faces.push_back(11); adj_faces.push_back(20); adj_faces.push_back(22); adj_faces.push_back(35); adj_faces.push_back(36);
    faces.push_back(Face(21, "DS-1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(2); adj_nodes.push_back(3); adj_nodes.push_back(9); adj_nodes.push_back(11); adj_nodes.push_back(16); adj_nodes.push_back(17);
	adj_faces.clear(); adj_faces.push_back(11); adj_faces.push_back(21); adj_faces.push_back(23); adj_faces.push_back(36); adj_faces.push_back(37); adj_faces.push_back(38);
    faces.push_back(Face(22, "DSW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(16); adj_nodes.push_back(17); adj_nodes.push_back(23); adj_nodes.push_back(24); adj_nodes.push_back(30); adj_nodes.push_back(31);
	adj_faces.clear(); adj_faces.push_back(11); adj_faces.push_back(12); adj_faces.push_back(22); adj_faces.push_back(24); adj_faces.push_back(38); adj_faces.push_back(39);
    faces.push_back(Face(23, "DW-1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(30); adj_nodes.push_back(31); adj_nodes.push_back(40); adj_nodes.push_back(41); adj_nodes.push_back(49); adj_nodes.push_back(50);
	adj_faces.clear(); adj_faces.push_back(5); adj_faces.push_back(12); adj_faces.push_back(13); adj_faces.push_back(23); adj_faces.push_back(39); adj_faces.push_back(40);
    faces.push_back(Face(24, "DW1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(58); adj_nodes.push_back(60); adj_nodes.push_back(67);
	adj_faces.clear(); adj_faces.push_back(13); adj_faces.push_back(26); adj_faces.push_back(40);
    faces.push_back(Face(25, "ENW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(60); adj_nodes.push_back(61); adj_nodes.push_back(62);
	adj_faces.clear(); adj_faces.push_back(13); adj_faces.push_back(14); adj_faces.push_back(25); adj_faces.push_back(27);
    faces.push_back(Face(26, "EN-1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(62); adj_nodes.push_back(63); adj_nodes.push_back(64);
	adj_faces.clear(); adj_faces.push_back(14); adj_faces.push_back(15); adj_faces.push_back(26); adj_faces.push_back(28);
    faces.push_back(Face(27, "EN", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(64); adj_nodes.push_back(65); adj_nodes.push_back(66);
	adj_faces.clear(); adj_faces.push_back(15); adj_faces.push_back(16); adj_faces.push_back(27); adj_faces.push_back(29);
    faces.push_back(Face(28, "EN1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(59); adj_nodes.push_back(66); adj_nodes.push_back(68);
	adj_faces.clear(); adj_faces.push_back(16); adj_faces.push_back(28); adj_faces.push_back(30);
    faces.push_back(Face(29, "ENE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(45); adj_nodes.push_back(52); adj_nodes.push_back(59);
	adj_faces.clear(); adj_faces.push_back(16); adj_faces.push_back(17); adj_faces.push_back(29); adj_faces.push_back(31);
    faces.push_back(Face(30, "EE1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(28); adj_nodes.push_back(38); adj_nodes.push_back(45);
	adj_faces.clear(); adj_faces.push_back(17); adj_faces.push_back(18); adj_faces.push_back(30); adj_faces.push_back(32);
    faces.push_back(Face(31, "EE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(10); adj_nodes.push_back(19); adj_nodes.push_back(28);
	adj_faces.clear(); adj_faces.push_back(18); adj_faces.push_back(19); adj_faces.push_back(31); adj_faces.push_back(33);
    faces.push_back(Face(32, "EE-1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(1); adj_nodes.push_back(8); adj_nodes.push_back(10);
	adj_faces.clear(); adj_faces.push_back(19); adj_faces.push_back(32); adj_faces.push_back(34);
    faces.push_back(Face(33, "ESE", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(6); adj_nodes.push_back(7); adj_nodes.push_back(8);
	adj_faces.clear(); adj_faces.push_back(19); adj_faces.push_back(20); adj_faces.push_back(3); adj_faces.push_back(35);
    faces.push_back(Face(34, "ES1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(4); adj_nodes.push_back(5); adj_nodes.push_back(6);
	adj_faces.clear(); adj_faces.push_back(20); adj_faces.push_back(21); adj_faces.push_back(34); adj_faces.push_back(36);
    faces.push_back(Face(35, "ES", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(2); adj_nodes.push_back(3); adj_nodes.push_back(4);
	adj_faces.clear(); adj_faces.push_back(21); adj_faces.push_back(22); adj_faces.push_back(35); adj_faces.push_back(37);
    faces.push_back(Face(36, "ES-1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(0); adj_nodes.push_back(2); adj_nodes.push_back(9);
	adj_faces.clear(); adj_faces.push_back(22); adj_faces.push_back(36); adj_faces.push_back(38);
    faces.push_back(Face(37, "ESW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(9); adj_nodes.push_back(16); adj_nodes.push_back(23);
	adj_faces.clear(); adj_faces.push_back(22); adj_faces.push_back(23); adj_faces.push_back(37); adj_faces.push_back(39);
    faces.push_back(Face(38, "EW-1", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(23); adj_nodes.push_back(30); adj_nodes.push_back(40);
	adj_faces.clear(); adj_faces.push_back(23); adj_faces.push_back(24); adj_faces.push_back(38); adj_faces.push_back(40);
    faces.push_back(Face(39, "EW", adj_nodes, adj_faces));
	adj_nodes.clear(); adj_nodes.push_back(40); adj_nodes.push_back(49); adj_nodes.push_back(58);
	adj_faces.clear(); adj_faces.push_back(13); adj_faces.push_back(24); adj_faces.push_back(25); adj_faces.push_back(39);
    faces.push_back(Face(40, "EW1", adj_nodes, adj_faces));

	initMaps();
}

void Board::reset()
{
	/* Reset the nodes. */
	for(unsigned int i=0; i<nodes.size(); i++)
		nodes[i].owner = 0;

	/* Reset the faces. */
	for(unsigned int i=0; i<faces.size(); i++){
		Face& face(faces[i]);
		face.owner = 0;
		face.num_adj_nodes_player[0] = 0;
		face.num_adj_nodes_player[1] = 0;
	}
}

bool Board::placeGem(NodeLabel const& label, PlayerID player_id,
		vector<FaceLabel>& new_markers)
{
	Node& node(nodes[node_map[label]]);

	if(!node.owner){
		node.owner = player_id+1;

		/* Update counts of adjacent faces. */
		for(unsigned int i=0; i<node.adj_faces.size(); i++){
			Face& face(faces[node.adj_faces[i]]);
			face.num_adj_nodes_player[player_id]++;
		}

		/* Check if new markers have to be placed. */
		for(unsigned int i=0; i<node.adj_faces.size(); i++){
			Face& face(faces[node.adj_faces[i]]);

			if(face.num_adj_nodes_player[player_id]*2 >= face.adj_nodes.size()
					&& face.owner == 0){
				placeMarker(face.label, player_id);
				new_markers.push_back(face.label);
			}
		}
	}
	else{
		return false;
	}

	return true;
}

bool Board::placeMarker(FaceLabel const& label, PlayerID player_id)
{
	Face& face(faces[face_map[label]]);

	if(!face.owner)
		face.owner = player_id+1;
	else
		return false;

	return true;
}

bool Board::removeGem(NodeLabel const& label, vector<FaceLabel>& removed_markers)
{
	Node& node(nodes[node_map[label]]);

	if(node.owner){
		PlayerID old_owner_id = node.owner-1;
		node.owner = 0;

		/* Update counts of adjacent faces. */
		for(unsigned int i=0; i<node.adj_faces.size(); i++){
			Face& face(faces[node.adj_faces[i]]);
			face.num_adj_nodes_player[old_owner_id]--;
			assert(face.num_adj_nodes_player[old_owner_id] >= 0);
		}

		/* Check if markers have to be removed. */
		for(unsigned int i=0; i<node.adj_faces.size(); i++){
			Face& face(faces[node.adj_faces[i]]);

			if(face.num_adj_nodes_player[old_owner_id]*2 < face.adj_nodes.size()
					&& face.owner == old_owner_id+1){
				removeMarker(face.label);
				removed_markers.push_back(face.label);
			}
		}
	}
	else{
		return false;
	}

	return true;
}

bool Board::removeMarker(FaceLabel const& label)
{
	Face& face(faces[face_map[label]]);

	if(face.owner)
		face.owner = 0;
	else
		return false;

	return true;
}

bool Board::isNodeLabel(NodeLabel const& label) const
{
	return node_map.count(label);
}

bool Board::isFaceLabel(FaceLabel const& label) const
{
	return face_map.count(label);
}

bool Board::nodeHasOwner(NodeLabel const& label) const
{
	return nodes[node_map.at(label)].owner;
}

bool Board::faceHasOwner(FaceLabel const& label) const
{
	return faces[face_map.at(label)].owner;
}

bool Board::checkVictoryCondition(PlayerID player_id) const
{
	vector<FaceID> start_faces;
	vector<FaceID> end_faces;

	if(player_id){
		//start_faces = {25, 37, 38, 39, 40};
		//end_faces = {29, 30, 31, 32, 33};
		start_faces.push_back(25);
		start_faces.push_back(37);
		start_faces.push_back(38);
		start_faces.push_back(39);
		start_faces.push_back(40);
		end_faces.push_back(29);
		end_faces.push_back(30);
		end_faces.push_back(31);
		end_faces.push_back(32);
		end_faces.push_back(33);
	}
	else{
		//start_faces = {33, 34, 35, 36, 37};
		//end_faces = {25, 26, 27, 28, 29};
		start_faces.push_back(33);
		start_faces.push_back(34);
		start_faces.push_back(35);
		start_faces.push_back(36);
		start_faces.push_back(37);
		end_faces.push_back(25);
		end_faces.push_back(26);
		end_faces.push_back(27);
		end_faces.push_back(28);
		end_faces.push_back(29);
	}

	return existsPathBetween(start_faces, end_faces, player_id);
}

/* Private members. */

void Board::initMaps()
{
	/* Init node_map. */
	for(unsigned int i=0; i<nodes.size(); i++){
		Node const& node(nodes[i]);
		node_map.insert(pair<NodeLabel, NodeID>(node.label, node.id));
	}

	/* Init face_map. */
	for(unsigned int i=0; i<faces.size(); i++){
		Face const& face(faces[i]);
		face_map.insert(pair<FaceLabel, FaceID>(face.label, face.id));
	}
}

bool Board::existsPathBetween(vector<FaceID> const& start_faces,
				vector<FaceID> const& end_faces, PlayerID player_id) const
{
	vector<FaceID> stack;
	vector<bool> visited(faces.size(), false);

	for(unsigned int i=0; i<start_faces.size(); i++){

		FaceID face(start_faces[i]);
		if(faces[face].owner == player_id + 1){
			stack.push_back(face);
			visited[face] = true;
		}
	}

	while(!stack.empty()){
		
		Face const& face(faces[stack.back()]);
		stack.pop_back();

		/* Add yet unvisited neighbours to the stack. */
		vector<FaceID> const& adj_faces(face.adj_faces);
		for(unsigned int i=0; i<adj_faces.size(); i++){

			Face const& adj_face(faces[adj_faces[i]]);
			if(adj_face.owner == player_id + 1 && !visited[adj_face.id]){
				stack.push_back(adj_face.id);
				visited[adj_face.id] = true;

				if(isEndFace(adj_face.id, end_faces))
					return true;
			}
		}
	}

	return false;
}

bool Board::isEndFace(FaceID id, vector<FaceID> const& end_faces) const
{
	for(unsigned int i=0; i<end_faces.size(); i++)
		if(end_faces[i] == id)
			return true;

	return false;
}
