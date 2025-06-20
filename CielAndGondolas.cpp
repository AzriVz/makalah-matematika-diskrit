#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 4005;
const int MAXK = 805;

int n, k;
int a[MAXN][MAXN];
int dp[MAXK][MAXN];

void compute(int g, int l, int r, int optL, int optR) {
    if (l > r) return;
    
    int mid = (l + r) >> 1;
    int best_val = INF;
    int best_pos = -1;
    
    int start = max(optL, g-1);
    int end = min(mid, optR);
    
    for (int i = start; i <= end; ++i) {
        int current = dp[g-1][i-1] + (a[mid][mid] - a[mid][i-1] - a[i-1][mid] + a[i-1][i-1]);
        if (current < best_val) {
            best_val = current;
            best_pos = i;
        }
    }
    
    dp[g][mid] = best_val;
    compute(g, l, mid-1, optL, best_pos);
    compute(g, mid+1, r, best_pos, optR);
}

int main() {
    scanf("%d %d", &n, &k);
    
    char buffer[10000];
    for (int i = 1; i <= n; ++i) {
        scanf(" %[^\n]", buffer);
        for (int j = 1; j <= n; ++j) {
            a[i][j] = buffer[2*(j-1)] - '0';
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        dp[1][i] = a[i][i];
    }
    
    for (int g = 2; g <= k; ++g) {
        compute(g, g, n, g-1, n);
    }
    
    printf("%d\n", dp[k][n] / 2);
    return 0;
}