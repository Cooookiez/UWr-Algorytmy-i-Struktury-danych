
# b)
def T(n):
    if n == 0: return 1
    else:
        s = 0
        for i in range(n):
            s += T(i) * T(n-i-1)
        return s


# b')
def T_p(n):
    if n == 0: return 1
    elif n == 1: return 1
    else:
        s = 0
        for i in range(n//2):
            s += T_p(i) * T_p(n-i-1)
        s *= 2

        if n%2 != 0:
            s += T_p(n//2)**2

        return s

# c)
def T_pp(n):
    mem = [1]
    for k in range(1, n):
        s = 0
        for i in range(k):
            s += mem[i] * mem[k - i - 1]
        mem.append(s)
    return mem

if __name__ == '__main__':
    print(G(5))

