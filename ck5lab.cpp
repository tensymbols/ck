#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

void removeVx(vector<vector<int>>& edges,int vx){
    edges[vx].resize(0);
    for(size_t i =0; i<edges.size();i++){
       if(edges[i].size()>0 && edges[i][0]!=-1){
           vector<int>::iterator it;
           it=find(edges[i].begin(),edges[i].end(),vx);
           if(it!=edges[i].end()) edges[i].erase(it);
           if(edges[i].size()==0) edges[i].push_back(-1);
       }
    }
}

//=============================================================================================================

int maxdist(const vector<vector<int>>& edges,int v, bool flag) {
    int V=edges.size();
	vector<bool> explored(V, 0);
	vector<int> dist(V,-1);
	queue<int> Q;
	Q.push(v);
	dist[v]=0;
	while (Q.size() > 0) {
		int curr = Q.front();
		Q.pop();
        if(edges[curr].size()>0 && edges[curr][0]!=-1) {
            for (int i = 0; i < edges[curr].size(); i++) {
                if (!explored[edges[curr][i]]) {
                    dist[edges[curr][i]]  = dist[curr]+1;
                    explored[edges[curr][i]] = true;
                    Q.push(edges[curr][i]);
                }
            }
        }
	}

	int maxv;
    int maxd;
	for(int i=0; i<dist.size();i++){

        if(dist[i]>maxd) {maxd=dist[i]; maxv=i;}
	}
	if(flag) return maxv;
	else return maxd;
}

int diam(const vector<vector<int>>& edges){
    int maxv=maxdist(edges,1,1);
    int maxd=maxdist(edges,maxv,0);
    return maxd;
}
//=============================================================================================================
void path(const vector<vector<int>>& edges,int v, int w) {
    int V=edges.size();
	vector<bool> explored(V, 0);
	vector<int> pred(V, -1);
	vector<int> dist(V,numeric_limits<int>::max());
	queue<int> Q;
	Q.push(v);
	dist[v]=0;
	while (Q.size() > 0) {
		int curr = Q.front();
		Q.pop();

		if(edges[curr].size()>0 && edges[curr][0]!=-1) {
            for (int i = 0; i < edges[curr].size(); i++) {
                if (!explored[edges[curr][i]]) {
                    dist[edges[curr][i]]  = dist[curr]+1;
                    explored[edges[curr][i]] = true;
                    Q.push(edges[curr][i]);

                    pred[edges[curr][i]]=curr;
                }
            }
        }
	}

	int nextpred = pred[w];

	cout << "Path: " << "(" << dist[w] << ") "<<w<<" <== ";

	while (nextpred!=v) {
		cout << nextpred<<" <== "  ;
		nextpred = pred[nextpred];
	}
	cout << nextpred<<"\n";

}
//=============================================================================================================



int main() {

	ifstream fin("graphedges141.txt");


    int edgeCnt=0;
    int isolCnt=0;
    int maxDeg=0;
    int maxDegV=-1;
	vector<vector<int>> edges(1000, vector<int>());
	while (!fin.eof()) {
        int v,w;
		fin >> v >> w;
		v; w;
		edges[v].push_back(w);
		edges[w].push_back(v);
        edgeCnt++;
	}

	cout << "\nKolvo reber: "<<edgeCnt;
//=============================================================================================================


    cout << "\nIzolyati: ";

	for (size_t i = 0; i < edges.size(); i++)
	{
		if (edges[i].size() == 0) {
            isolCnt++;
			edges[i].push_back(-1); // добавление связи с -1 у изолятов, чтобы у изолятов был размер 1, т.к. 0 размер у несуществующих вершин
            cout<<i<<" ";
		}
	}	 cout << "("<< isolCnt<<" izolyatov)";

//=============================================================================================================

	for (size_t i = 0; i < edges.size(); i++)
	{
		if (edges[i].size() > maxDeg) { maxDeg = edges[i].size(); maxDegV = i; }
	}
	cout << "\nVershina s max stepeniyu:" << maxDegV <<" ("<<maxDeg << ")";

//=============================================================================================================


	cout <<"\nDiametr: "<<diam(edges)<<"\n";
//=============================================================================================================

    int A,B,C,D,E,F;
    A=233; B=661; C=633; D=665; E=399; F=177;
   cout<<"A-B "; path(edges,A,B);
   cout<<"C-D "; path(edges,C,D);
   cout<<"E-F "; path(edges,E,F);
//=============================================================================================================
    cout << "\n=============Vershiny udaleni=============\n";
    for(int i =0; i<edges.size();i++){
        if (i%17==0) removeVx(edges,i);
    }
    removeVx(edges,32);
    removeVx(edges,42);
    removeVx(edges,204);
    removeVx(edges,463);
    removeVx(edges,404);
    removeVx(edges,411);
//=============================================================================================================
    edgeCnt=0;
    for(int i =0; i<edges.size();i++){
        if(edges[i].size()>0 && edges[i][0]!=-1)  edgeCnt+=edges[i].size();
    }
    edgeCnt/=2;
    cout << "\nKolvo reber: "<<edgeCnt;

//=============================================================================================================
    cout << "\nIzolyati: ";
    isolCnt=0;
	for (size_t i = 0; i < edges.size(); i++)
	{
		if (edges[i].size() == 1 && edges[i][0]==-1) {
            isolCnt++;

            cout<<i<<" ";
		}
	}	 cout << "("<< isolCnt<<" izolyatov)";
//=============================================================================================================
maxDeg=0; maxDegV=-1;
	for (size_t i = 0; i < edges.size(); i++)
	{
        if(edges[i].size()>0 && edges[i][0]!=-1){
            if (edges[i].size() > maxDeg) { maxDeg = edges[i].size(); maxDegV = i; }
        }
	}
	cout << "\nVershina s max stepeniyu:" << maxDegV <<" ("<<maxDeg << ")";
//=============================================================================================================


	cout <<"\nDiametr: "<<diam(edges)<<"\n";
//=============================================================================================================
   cout<<"A-B "; path(edges,A,B);
   cout<<"C-D "; path(edges,C,D);
   cout<<"E-F "; path(edges,E,F);
}
