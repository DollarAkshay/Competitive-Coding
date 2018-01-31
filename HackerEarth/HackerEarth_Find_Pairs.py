

t  = int(raw_input())
for tc in range(t):
	n = int(raw_input())
	a = [int(i) for i in raw_input().split()]
	dic = {i:a.count(i) for i in set(a)}
	ans =0
	for i in dic:
		x = dic[i]
		ans+= x*(x+1)//2
	print(ans)
