i;
j;
h;
w;
Z;
n = 4e4;
p[50001];
m[101][100];
f() {
	if (j >= 0 & j < w & i >= 0 & i < h & p[m[i][j]] == Z && m[i][j]) {
		m[i][j] = 0;
		f(i--);
		f(i += 2);
		f(i--, j--);
		f(j += 2);
		j--;
	}
}
main(k, a, b) {
	memset(p, 1, n);
	for (i = 2; i < 99; i++)
		for (j = i; j < n; p[j += i] = 0)
			;
	for (scanf("%*d"); scanf("%d%d", &h, &w) > 0; printf("%d %d\n", a, b)) {
		for (i = h * w; i--; scanf("%d", &m[i / w][i % w]))
			;
		for (a = b = 0, k = h * w; k--;) {
			(Z = m[i = k / w][j = k % w]) ? Z = p[Z], f(), Z ? a++ : b++ : 0;
		}
	}
}