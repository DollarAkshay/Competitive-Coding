s="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/A"
y=range
z=input
for _ in y(int(z())):l=int(z());x=z()[::-1];r=[s.find(x[i])*((i+1)%2+1)for i in y(l)];print(s[64-sum([i%64+i//64 for i in r])%64])