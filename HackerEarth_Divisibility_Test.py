t = int(input())
for tc in range(t):
	res = 0
	n = raw_input()
	d = int(input())
	l,r = raw_input().split(' ')
	l = int(l)-1
	r = int(r)+1
	for i in xrange (l,r):
		for j in xrange (i+1,r):
			a = int(n[i:j])
			if a%d==0:
				res+=1
	print(res)
	