#include <bits/stdc++.h>
using namespace std;
int32_t V, // number of videos
	E, // number of endpoints
	R, // number of requests
	C, // number of cache servers
	X; // capacity of each cache server in MB
vector<int32_t> S; // S[i] is size of i-th video
vector<int32_t> L_d; // latency from data center to [1]endpoint
map<int, map<int, int> > Latency; // from [1]endpoint to [2]cache server
vector<map<int, int> > Requests; //[1]th endpoint want [3] copies of [2]video
vector<int> FreeSpace;
vector<set<int> > cached;

inline bool is_cached(vector<int> &cacheset, int vid) {
	for(int cache: cacheset)
		if(cached[cache].count(vid))
			return true;
	return false;
}

#define MAGIC 2

inline void sort_nearest(vector<int> &cacheset, int ep) {
	struct {
		int point_of_view;
		bool operator () (const int& a, const int &b) {
			return Latency[point_of_view][a] < Latency[point_of_view][b];
		}
	} yoba_comparator;
	yoba_comparator.point_of_view = ep;
	sort(cacheset.begin(), cacheset.end(), yoba_comparator);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> V >> E >> R >> C >> X;
	S.resize(V);
	L_d.resize(E);
	Requests.resize(E);
	FreeSpace.assign(C, X);
	cached.resize(C);
	for(int i = 0; i < V; cin >> S[i++]);
	for(int endp = 0, K, c, L_c; endp < E; endp ++) {
		cin >> L_d[endp] >> K;
		while(K --> 0) {
			cin >> c >> L_c;
			Latency[endp][c] = L_c;
		}
	}
	for(int i = 0, a, b, c; i < R; cin >> a >> b >> c, Requests[b][a]+=c, i++);
	/////////////////
	for(size_t i = 0; i < Requests.size(); i++) {
		vector<int> caches;
		for(auto x: Latency[i])
			if(x.second < L_d[i])
				caches.push_back(x.first);
		sort_nearest(caches, i);
		set<pair<int, int> > vids;
		unsigned int candidates_sum_weight = 0;
		for(map<int,int>::iterator vid = Requests[i].begin();
				vid != Requests[i].end(); vid++) {
			vids.insert(make_pair(vid->second, vid->first));
			candidates_sum_weight += S[vid->first];
			if(candidates_sum_weight > caches.size() * X * MAGIC) {
				candidates_sum_weight -= S[vids.begin()->second];
				vids.erase(vids.begin());
			}
		}
		for(set<pair<int,int> >::iterator vid = vids.begin();
				vid != vids.end(); vid++) {
			if(!is_cached(caches, vid->second)) {
				for(int c: caches) {
					if(FreeSpace[c] >= S[vid->second]) {
						FreeSpace[c] -= S[vid->second];
						cached[c].insert(vid->second);
						break;
					}
				}
			}
		}
	}	
	/////////////////
	int ans_sz = 0;
	for(size_t i = 0 ; i < cached.size(); ans_sz += !cached[i++].empty());
	cout << ans_sz << '\n';
	for(size_t i = 0 ; i < cached.size(); i++) {
		if(!cached[i].empty()) {
			cout << i << ' ';
			for(auto x: cached[i])
				cout << x << ' ';
			cout << '\n';
		}
	}
	return 0;
}

