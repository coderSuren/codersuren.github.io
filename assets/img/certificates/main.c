#include <bits/stdc++.h>
using namespace std;
 
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define RFOR(i,b,a) for (int i = (b) - 1; i >= (a); i--)
#define ITER(it,a) for (__typeof(a.begin()) it = a.begin(); it != a.end(); it++)
#define FILL(a,value) memset(a, value, sizeof(a))
 
#define SZ(a) (int)a.size()
#define ALL(a) a.begin(), a.end()
#define PB push_back
#define MP make_pair
 
typedef long long Int;
typedef long long LL;
typedef vector<int> VI;
typedef pair<int, int> PII;
 
const double PI = acos(-1.0);
const int INF = 1000 * 1000 * 1000;
const Int LINF = INF * (Int) INF;
const int MAX = 5007;
const int MAX2 = 1000;
const int MOD = 1000000007;

const int MAGIC = 10;
bool T[MAX][MAX];
int A[MAX][MAX];
bool U[MAX][MAX];
vector<PII> L;

vector<PII> R[MAX];

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int m, n, k;

int best;
vector<PII> P;
vector<PII> C;
void calc(int x, int y, int score, int kk) {
    if (SZ(C) == kk) {
        if (score > best) {
            best = score;
            P = C;
        }
        return;
    }
    FOR(dir, 0, 4) {
        int xx = (x + dx[dir] + n) % n;
        int yy = (y + dy[dir] + m) % m;
        if (U[xx][yy])
            continue;
        C.push_back(MP(xx, yy));
        U[xx][yy] = true;
        calc(xx, yy, score + A[xx][yy], kk);
        C.pop_back();
        U[xx][yy] = false;
    }
}

char getDir(PII a, PII b) {
    if ((a.first + 1) % n == b.first)
        return 'D';
    if ((a.first + n - 1) % n == b.first)
        return 'U';
    if ((a.second + 1) % m == b.second)
        return 'R';
    if ((a.second + m - 1) % m == b.second)
        return 'L';
    return 0;
}

int main(int argc, char* argv[])
{
	//ios::sync_with_stdio(false); cin.tie(0);
    
    cin >> m >> n >> k;
    FOR(i,0,k) {
        int l;
        cin >> l;
        L.push_back(MP(l, i));
    }
    sort(ALL(L));
    reverse(ALL(L));
    FOR(i,0,n)
        FOR(j,0,m) {
            string s;
            cin >> s;
            if (s == "*") {
                T[i][j] = 1;
                A[i][j] = 0;
            } else {
                A[i][j] = stoi(s);
            }
        }
    set<pair<int, PII> > S;

    FOR(i,0,n)
        FOR(j,0,m) {
            best = -INF;
            P.clear();
            U[i][j] = true;
            calc(i, j, 0, MAGIC);
            S.insert(MP(best + A[i][j], MP(i, j)));
            U[i][j] = false;
        }

    int c = 0;
    while (SZ(S) > 0 && c < k) {
        auto p = *S.rbegin();
        int x = p.second.first;
        int y = p.second.second;
        S.erase(p);
        // cout << x << ' ' << y << endl;
        if (U[x][y])
            continue;
        int l = L[c].first;
        best = -INF;
        P.clear();
        U[x][y] = true;
        calc(x, y, 0, MAGIC);
        U[x][y] = false;
        if (best + A[x][y] != p.first) {
            S.insert(MP(best + A[x][y], MP(x, y)));
            continue;
        }

        int id = L[c].second;
        R[id].push_back(MP(x, y));
        U[x][y] = true;

        FOR(i,0,l - 1) {
            best = -INF;
            P.clear();
            calc(x, y, 0, min(MAGIC, l - 1));

            if (best == -INF) {
                R[id].clear();
                break;
            }

            x = P[0].first;
            y = P[0].second;
            R[id].push_back(MP(x, y));
            U[x][y] = true;
        }
        if (SZ(R[id]) > 0) {
            c ++;
        }
        // cout << endl;
        // FOR(i,0,SZ(R[id])) {
        //     cout << R[id][i].first << ' ' << R[id][i].second << endl;
        // }
        // cout << endl;
        // return 0;
        
    }    

    FOR(i,0,k) {
        if (SZ(R[i]) == 0) {
            cout << endl;
        } else {
            cout << R[i][0].second << ' ' << R[i][0].first;
            FOR(j,1,SZ(R[i])) {
                cout << ' ' << getDir(R[i][j - 1], R[i][j]);
                int x = R[i][j].first;
                int y = R[i][j].second;
                if (T[x][y])
                    cout << ' ' << y << ' ' << x;
            }
            cout << endl;
        }
    }
    

	return 0;
}
