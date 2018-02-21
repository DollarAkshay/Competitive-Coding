# ~~~~~~~~~~~~~~~~ #
#                  #
#  $DollarAkshay$  #
#                  #
# ~~~~~~~~~~~~~~~~ #

# https://projecteuler.net/problem=48


def fastPowMod(b, e):
    if (e == 0):
        return 1
    else:
        if (e % 2 == 0):
            res = fastPowMod(b, e / 2)
            return res * res % MOD
        else:
            return fastPowMod(b, e - 1) * b % MOD


# Main Code
MOD = 10000000000

n = 1000
sum = 0
for i in range(1, n + 1):
    sum = (sum + fastPowMod(i, i)) % MOD

print(sum)

# Solved
