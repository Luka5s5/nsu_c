#include<bits/stdc++.h>
const int INF = 1000000000;
using namespace std;

int main(){
	int ans=-INF;
    int mx,n,m;
    cin>>mx>>n>>m;
    vector<vector<pair<int,int>>> g(n);
    vector<int> val(n);
    for(int i=0;i<m;i++){
        int v,u,c;
        cin>>v>>u>>c;
        g[v].push_back({c,u});
        g[u].push_back({c,v});
    }
    for(auto &i:val) cin>>i;
    int s=0;
    vector<int> d (n, INF),  p (n);
	d[s] = 0;
	set <pair<int,int>> q;
	q.insert (make_pair (d[s], s));
	while (!q.empty()) {
		int v = q.begin()->second;
		q.erase (q.begin());
		for (size_t j=0; j<g[v].size(); ++j) {
			int to = g[v][j].second,
				len = g[v][j].first;
			if (d[v] + len < d[to]) {
				q.erase (make_pair (d[to], to));
				d[to] = d[v] + len;
				p[to] = v;
				q.insert (make_pair (d[to], to));
			}
		}
	}
	for(int i=0;i<n;i++){
		cout<<d[i]<<" ";
		if(d[i]<=mx)
			ans=max(ans,val[i]);
	}
	cout<<"\n"<<ans<<"\n";
}
