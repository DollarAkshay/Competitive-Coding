t = int(input())


for tc in range(t):
    n = input()
    mid = (len(n) + 1) // 2
    l = n[:mid]
    r = n[mid:]

    pal = l + l[-2::-1] if len(n) % 2 == 1 else l + l[::-1]
    if pal <= n:
        l1 = str(int(l) + 1)
        if len(l1) > len(l):
            pal = l1[:-1] + l1[-2::-1] if len(n) % 2 == 1 else l1[:-1] + l1[::-1]
        else:
            pal = l1 + l1[-2::-1] if len(n) % 2 == 1 else l1 + l1[::-1]

    print(pal)

# Solvec
