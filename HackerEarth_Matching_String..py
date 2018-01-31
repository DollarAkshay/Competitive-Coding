n = input()
for tc in range(n):
	a = raw_input()
	b = raw_input()
	ans = 0
	for i in range(min(len(a),len(b))):
		if a[i] == b[i]:
			ans+=1
	print ans