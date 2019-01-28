#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <limits>

using namespace std;

int main() {
	int n;
	cin >> n;
	while(n--) {
		int candidates_number;
		cin >> candidates_number;
		string line;
		getline(cin, line);
		map<int, string> candidates;
		vector<vector<int> > votes;
		for(int i = 0; i < candidates_number; i++) {
			getline(cin, line);
			candidates[i+1] = line;
		}
		int number_of_voters = 0;
		
		getline(cin, line);
		while(!line.empty()) {
			number_of_voters++;
			istringstream ss(line);
			istream_iterator<int> beg(ss), end;
			vector<int> vote(beg, end);
			votes.push_back(vote);
			getline(cin, line);
		}
		int got_first = 0;
		map <int, int> candidate_is_out;
		while(got_first == 0) {
			map<int, int> number_of_votes;
			for(int i = 0; i < votes.size(); i++) {
				vector<int> vote = votes[i];
				for(int j = 0; j < vote.size(); j++) {
					if (candidate_is_out.find(vote[j]) == candidate_is_out.end()) {
						number_of_votes[vote[j]]++;
						// cout << " votes kiske badhe " << vote[j] << endl;
						break;
					} else {
						vote.erase(vote.begin() + j);
					}
				}
			}
			candidate_is_out.clear();
			int first, last;
			int first_votes = INT_MIN;
			int last_votes = INT_MAX;
			for(auto it = number_of_votes.begin(); it != number_of_votes.end(); it++ ) {
				if (first_votes < it->second) {
					first_votes = it->second;
					first = it->first;
				}
				if (last_votes > it->second) {
					last_votes = it->second;
					last = it->first;
				}
			}
			// cout << " First " << first << " " << first_votes << endl;
			// cout << " Last " << last << "  " << last_votes << endl;
			if (first_votes == last_votes) {
				for(auto it = number_of_votes.begin(); it != number_of_votes.end(); it++ ) {
					cout << candidates[it->first] << endl;
				}
				got_first = 1;
			} else if (first_votes > (number_of_voters/2)) {
				cout << candidates[first] << endl;
				got_first = 1;
			} else if (number_of_votes.size() == 1) {
				cout << candidates[first] << endl;
				got_first = 1;
			} else {
				for(auto it = number_of_votes.begin(); it != number_of_votes.end(); it++ ) {
					if (it->second == last_votes) {
						candidate_is_out[it->first] = 1;
						// cout << "Eliminated " << it->first << endl;
					}
				}
			}
			if (got_first && n != 0) 
				cout << endl;
		}
	}
}