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

inline bool is_cached(set<int> &cacheset, int vid) {
	for(int cache: cacheset)
		if(cached[cache].count(vid))
			return true;
	return false;
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
		set<int> caches;
		for(auto x: Latency[i])
			if(x.second < L_d[i])
				caches.insert(x.first);
		for(map<int,int>::iterator vid = Requests[i].begin();
				vid != Requests[i].end(); vid++) {
			if(!is_cached(caches, vid->first)) {
				for(int c: caches) {
					if(FreeSpace[c] >= S[vid->first]) {
						FreeSpace[c] -= S[vid->first];
						cached[c].insert(vid->first);
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

