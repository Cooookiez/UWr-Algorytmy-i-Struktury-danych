
# 1, 2, ... n+1
def brak(t, n):
    s = (n+2) * (n+1) // 2
    for tt in t:
        s -= tt
    return s



print(brak([1,2,3,4,5,7,8,9], 8))