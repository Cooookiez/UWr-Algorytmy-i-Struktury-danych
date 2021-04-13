import copy
n = 8

ile_udan = 0

def dfs(tab, col=0):
    global ile_udan
    if col == n:
        print('Udalo sie', tab, col)
        ile_udan += 1
        return
    
    for i in range(n):
        nx = i
        ny = col
        if tab[nx][ny] == 0:
            t2 = copy.deepcopy(tab)
            t2[nx][ny] = 2
            for j in range(n):
                t2[j][ny] = max(t2[j][ny], 1)
                t2[nx][j] = max(t2[nx][j], 1)
            for j in range(-n+1, n):
                mx = i + j
                my = col + j
                if 0 <= mx < n and 0 <= my < n:
                    t2[mx][my] = max(t2[mx][my], 1)
                my = col - j
                if 0 <= mx < n and 0 <= my < n:
                    t2[mx][my] = max(t2[mx][my], 1)
                
            dfs(t2, col+1)
            

if __name__ == "__main__":
    tab = [[0] * n for _ in range(n)]

    dfs(tab)

    print(f"Udało się {ile_udan} razy")