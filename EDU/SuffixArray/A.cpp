#include <cstdio>
#include <algorithm>
using namespace std;

constexpr int N = 1e5 + 10;
int A[N];
int n, B;
int t;

int main() {
	
	scanf("%d", &t);
	for (int i = 1; i <= t; i ++) {
		scanf("%d%d", &n, &B);
		for (int j = 0; j < n; j ++) scanf("%d", A + j);
		sort(A, A + n);
		int s = 0, ans = 0;
		for (int j = 0; j < n; j ++) {
			if (s + A[j] > B) break;
			s += A[j];
			ans ++;
		}
		printf("Case #%d: %d\n", i, ans);
	}
	return 0;
}