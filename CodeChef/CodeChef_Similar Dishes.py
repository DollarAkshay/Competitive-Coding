# ~~~~~~~~~~~~~~~~~ #
#                   #
#  $Dollar Akshay$  #
#                   #
# ~~~~~~~~~~~~~~~~~ #

# http: // www.codechef.com / MAY15 / problems / SETDIFF


n = int(input())
for i in range(n):
    dish_1 = sorted(input().split())
    dish_2 = sorted(input().split())
    similiar_count = 0
    for ingrident in dish_1:
        if ingrident in dish_2:
            similiar_count += 1

    if similiar_count >= 0.5 * len(dish_1):
        print("similar")
    else:
        print("dissimilar")
