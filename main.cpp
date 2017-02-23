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

struct request_t {
	int vid_id, 
	    endp_id,
	    req_number;
	request_t(int a=0, int b=0, int c=0):
		vid_id(a), endp_id(b), req_number(c) {}
};

vector<request_t> Requests;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> V >> E >> R >> C >> X;
	S.resize(V);
	L_d.resize(E);
	for(int i = 0; i < V; cin >> S[i++]);
	for(int endp = 0, K, c, L_c; endp < E; endp ++) {
		cin >> L_d[endp] >> K;
		while(K --> 0) {
			cin >> c >> L_c;
			Latency[endp][c] = L_c;
		}
	}
	Requests.resize(R);
	for(int i = 0; i < R; i++)
		cin >> Requests[i].vid_id >> Requests[i].endp_id >> Requests[i].req_number;
	return 0;
}

