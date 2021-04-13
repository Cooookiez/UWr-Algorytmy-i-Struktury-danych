
import plotly.graph_objects as go
import numpy as np

n = 8
max_lvl = n**2

dx = [2, 1, -1, -2, -2, -1, 1, 2]
dy = [1, 2, 2, 1, -1, -2, -2, -1]

def printBoard(board):
    for row in board:
        for cell in row:
            print(cell, end="\t")
        print(end="\n\n")

def printHtml(skoczek):
    # unzip
    y, x = [
        [i for i, j in skoczek],
        [j for i, j in skoczek]
    ]
    fig = go.Figure()
    fig.add_trace(go.Scatter(x=x, y=y, mode="lines+markers", name="Skoczek"))
    fig.show()
    pass


def dfs(state, level=1):
    
    board, skoczek = state
    sx, sy = skoczek[-1]

    if level == max_lvl:
        print('Udalo sie')
        printBoard(board)
        printHtml(skoczek)
        return True

    for i in range(8):
        nx = sx+dx[i]
        ny = sy+dy[i]
        if 0 <= nx < n and 0 <= ny < n and board[nx][ny] == 0:
            board[nx][ny] = level+1
            skoczek.append((nx, ny))
            new_state = (board, skoczek)
            if dfs(new_state, level+1):
                return True
            else:
            # cofniecie ruchu
                board[nx][ny] = 0
                del skoczek[-1]
            

if __name__ == "__main__":

    board = [[0] * n for _ in range(n)]
    board[0][0] = 1

    state = (board, [(0, 0)])
    dfs(state)