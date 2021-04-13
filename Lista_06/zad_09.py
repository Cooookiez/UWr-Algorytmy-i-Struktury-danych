import copy
n = 8
max_lvl = n**2
def czy_koniec(state):
    isEmpty = True
    for row in state[0]:
        for cell in row:
            if cell == 0:
                isEmpty = False
                break
    return isEmpty

dx = [2, -2, 2, -2, 1, -1, 1, -1]
dy = [1, 1, -1, -1, 2, 2, -2, -2]

def dfs(state, level=1):
    # if czy_koniec(state):
    if level == max_lvl:
        print('Udalo sie', state, level)
        return
    
    tab, skoczek = state
    sx, sy = skoczek[-1]

    for i in range(8):
        nx = sx+dx[i]
        ny = sy+dy[i]
        if 0 <= nx < n and 0 <= ny < n and tab[nx][ny] == 0:
            # tab1 = copy.deepcopy(tab)
            tab[nx][ny] = 1
            skoczek.append((nx, ny))
            new_state = (tab, skoczek)
            dfs(new_state, level+1)
            # cofniecie ruchu
            tab[nx][ny] = 0
            del skoczek[-1]
            

if __name__ == "__main__":

    tab = [[0] * n for _ in range(n)]
    tab[0][0] = 1

    state = (tab, [(0, 0)])
    dfs(state)
    pass