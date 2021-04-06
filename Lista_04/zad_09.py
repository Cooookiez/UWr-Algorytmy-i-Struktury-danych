# zad 9

def comb(i, n):
    if i == 1:
        return [[n]]
    else:
        res =[]
        for k in range(n+1):  # ile kul ma byc w pierwszym kubelku
            pozostale_comb = comb(i-1, n - k)
            for c in pozostale_comb:
                # jesli k = 1  i c == [2, 3] -> [1, 2, 3]
                res.append([k] + c)
        return res

def T(i, n):
    if n == 0:
        return 1
    
    s = 0
    for c in comb(i, n-1):
        # np. c == [0, 1, 2]  
        # chcemy obliczyc T(0) * T(1) * T(2)
        p = 1
        for v in c:
            p *= T(i, v)
        s += p
    return s

if __name__ == '__main__':
    print(T(2, 4))
