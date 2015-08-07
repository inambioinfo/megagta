#include "nucl_kmer.h"

using namespace std;

class AStarNode
{
public:
	bool partial = true;
	AStarNode *discovered_from;
	NuclKmer kmer;
	// long fwd_hash, rc_hash;
	double score;
	char state;
	int state_no;
	int fval;
	double this_node_score;
	int indels;
	double real_score;
	int length;
	char emission;

	int negative_count = 0;
	double max_score = 0;

	AStarNode() {};
	AStarNode(AStarNode *discovered_from, NuclKmer &kmer, int &state_no, char &state)
	: discovered_from(discovered_from), kmer(kmer), state_no(state_no), state(state) {};
	// ~AStarNode();
	bool equals();
	bool operator< (const AStarNode &node2) {
		if (fval < node2.fval) {
			return true;
		}
		else if (fval > node2.fval) {
			return false;
		}
		else {
			if (state_no > node2.state_no) {
				return true;
			}
			else if (state_no < node2.state_no) {
				return false;
			}
			else {
				int s1 = 0;
				int s2 = 0;
				switch (state) {
					case 'm': s1 = 3; break;
					case 'd': s1 = 2; break;
					case 'i': s1 = 1; break;
				}
				switch (node2.state) {
					case 'm': s2 = 3; break;
					case 'd': s2 = 2; break;
					case 'i': s2 = 1; break;
				}
				return s1 < s2;
			}
		}
	}

	uint64_t hash() const {
		return CityHash64((const char*)kmer.kmers, sizeof(kmer.kmers[0]) * 2) + state + state_no;
	}
};