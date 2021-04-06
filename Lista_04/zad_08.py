
# zad 8

def G(n):
    if n == 0: return 1
    else:
        s = 0
        for l in range(n):
            for m in range(n - l):
                r = n - 1 - l - m
                s += G(l) * G(m) * G(r)
        return s

if __name__ == '__main__':
    print(G(5))
