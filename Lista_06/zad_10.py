import copy
n = 8

ile_udan = 0

# 2 – hetman
# 1 – pola gdzie hetman bije
# 0 – puste pola

def dfs(tab, col=0): # n*(2n) = 2n^2 = O(n^2)
    global ile_udan
    if col == n:
        print('Udalo sie', tab, col)
        ile_udan += 1
        return
    
    for i in range(n): # n
        nx = i
        ny = col
        if tab[nx][ny] == 0: # *(2n) # po koleji patrzy kade 
            t2 = copy.deepcopy(tab)
            t2[nx][ny] = 2
            # zaznaczam pola kture "t2[nx][ny]" atakuje jako 1
            for j in range(n): # *n
                t2[j][ny] = max(t2[j][ny], 1) # zeby nie sprawdzac if-em mojego pola to biore maxa
                t2[nx][j] = max(t2[nx][j], 1) # tak ze jak dobiero co tu postawilem to jest max((2), 1), w innym przypadku mam max((0),1)
            for j in range(-n+1, n): # *n
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