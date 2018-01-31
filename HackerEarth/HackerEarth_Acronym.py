#https://www.hackerearth.com/september-easy-15/algorithm/acronym-2/

t = int(raw_input())
dis = [raw_input() for i in range(t)]	
usless_variable_which_I_will_never_use = int(raw_input())	
print '.'.join([i[0].upper() for i in [i for i in raw_input().split() if i not in dis]])