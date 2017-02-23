#include <bits/stdc++.h>
using namespace std;
int32_t V, // number of videos
	E, // number of endpoints
	R, // number of requests
	C, // number of cache servers
	X; // capacity of each cache server in MB
vector<int32_t> S; // S[i] is size of i-th video
vector<int32_t> L_d; // latency from data center to [1]endpoint
map<int, map<int, int> > Latency; // from [2]endpoint to [1]cache server
vector<map<int, int> > Requests; //[1]th endpoint want [3] copies of [2]video

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	srand( time(0) );
	cin >> V >> E >> R >> C >> X;
	S.resize(V);
	L_d.resize(E);
	Requests.resize(E);
	for(int i = 0; i < V; cin >> S[i++]);
	for(int endp = 0, K, c, L_c; endp < E; endp ++) {
		cin >> L_d[endp] >> K;
		while(K --> 0) {
			cin >> c >> L_c;
			Latency[c][endp] = L_c;
		}
	}
	for(int i = 0, a, b, c; i < R; cin >> a >> b >> c, Requests[b][a]+=c, i++);
	set<int> servers_used;
	while (servers_used.size() < C){
		int server = rand() % C;
		if (servers_used.find(server) != servers_used.end()){
			serveers_used.insert(server);
			vector <long long> files(V, 0);
			for(auto ep: Latency[server]){
				
			}
		}
	}
	return 0;
}

