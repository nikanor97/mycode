#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

struct vert{
	int num;
	int color;
	vert* last;
};

inline bool fourDigNoZero(int n){
	int a1,a2,a3,a4;
	a1 = n % 10;
	n /= 10;
	a2 = n % 10;
	n /= 10;
	a3 = n % 10;
	n /= 10;
	a4 = n % 10;
	if (a1 != 0 && a2 != 0 && a3 != 0 && a4 != 0)
		return true;
	else return false;
}

void BFS_visit(vector<vector<int> > &matr, vector<vert> & g, queue<vert> &Q, bool nores, int to){
	vert u = Q.front();
	Q.pop();
	for (int i = 0; i < matr[u.num].size(); i++){
		int t = matr[u.num][i];
		if (g[t].color == 0){
			g[t].last = &g[u.num];
			g[t].color = 1;
			if (t == to) nores = true;
			Q.push(g[t]);
    }
	}
	g[u.num].color = 2;
}

int main(){ 
	//ifstream fin("input.txt");
	vector<vert> g;
	for (int i = 0; i < 10000; i++){
		vert emptyVert;
		g.push_back(emptyVert);
	}
	vector<vector<int> > matr;
	vector<int> emptyVint;
	matr.reserve(10000);
	for (int i = 0; i < 10000; i++)
		matr.push_back(emptyVint);
	matr.reserve(10000);
	for (int a1 = 1; a1 < 10; a1++){
		for (int a2 = 1; a2 < 10; a2++){
			for (int a3 = 1; a3 < 10; a3++){
				for (int a4 = 1; a4 < 10; a4++){
					vert tmpv;
					tmpv.color = 0;
					tmpv.last = 0;
					tmpv.num = 1000 * a1 + 100 * a2 + 10 * a3 + a4;
					g[1000 * a1 + 100 * a2 + 10 * a3 + a4] = tmpv;
					int i = 1000 * a1 + 100 * a2 + 10 * a3 + a4;
					if (fourDigNoZero(i + 1000))
						matr[i].push_back(i + 1000);
					if (fourDigNoZero(i - 1))
						matr[i].push_back(i - 1);
					int tmpi1 = i % 10;
					if (fourDigNoZero(tmpi1 * 1000 + i / 10))
						matr[i].push_back(tmpi1 * 1000 + i / 10);
					int tmpi2 = (i - i % 1000) / 1000 ;
					if (fourDigNoZero((i % 1000) * 10 + tmpi2))
						matr[i].push_back((i % 1000) * 10 + tmpi2);
				}
			}
		}
	}
	queue<vert> Q;
	int from, to;
	cin >> from >> to;
	g[from].color = 1;
	Q.push(g[from]);
	bool nores = false;
	while (!Q.empty() && nores == false){
		BFS_visit(matr, g, Q, nores, to);
	}
	vector<int> res;
	res.push_back(to);
	while (to != from){		
		to = g[to].last->num;
		res.push_back(to);
	}
	for (int i = res.size() - 1; i >= 0; i--){
		cout << res[i] << endl;
	}
	//system("pause");
	return 0;
}
