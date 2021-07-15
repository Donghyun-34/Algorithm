# 1번 - clear
import math
import os
import random
import re
import sys
def maxTickets(tickets):
    sorted_tickets = sorted(tickets)

    cnt = 0
    sub = [sorted_tickets[0]]
    idx = 0
    for i in sorted_tickets[1:]:
        tmp = i - sub[idx]
        if tmp == 0 or tmp == 1:
            sub.append(i)
            idx = idx + 1
        else:
            if len(sub) > cnt:
                cnt = len(sub)
            sub = [i]
            idx = 0

    return cnt


# 2번 - clear
def getMinDeletions(s):
    # Write your code here
    origin_len = len(s)
    res = ''.join(set(s))

    return origin_len - len(res)

# 3번 - clear
def calcul_dist(grid):
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]

    n = len(grid)
    m = len(grid[0])
    q = [(0, 0)]
    dist = [[0] * m for _ in range(n)]
    dist[0][0] = 1

    while q:
        x, y = q.pop(0)
        if (x, y) == (n - 1, m - 1):
            break

        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0 <= nx < n and 0 <= ny < m:
                if dist[nx][ny] == 0 and grid[nx][ny] == '.':
                    dist[nx][ny] = dist[x][y] + 1
                    q.append((nx, ny))

    return dist[n - 1][m - 1]


def reachTheEnd(grid, maxTime):
    # Write your code here
    time = calcul_dist(grid)

    if 0 < time <= maxTime:
        res = "Yes"
    else:
        res = "No"

    return res

# 4번 - clear
def maxEvents(arrival, duration):
    # Write your code here
    duration = [x + y for x, y in zip(arrival, duration)]
    time = list(zip(arrival, duration))
    time = sorted(time, key=lambda time: (time[1], time[0]))

    n = len(arrival)
    cnt = 1
    e_time = time[0][1]
    for i in range(n):
        if time[i][0] >= e_time:
            cnt += 1
            e_time = time[i][1]

    return cnt

# 5번
def split_code(codes):
    key = []
    values = []
    code_dict = list(map(str, codes))
    for i in range(len(code_dict)):
        w, c = code_dict[i].split('\t')
        key.append(c)
        values.append(w)

    return dict(zip(key, values))


def decode(codes, encoded):
    # Write your code here
    code_dict = split_code(codes)
    code = sorted(code_dict.items(), key=lambda x: x[0])

    res = ""
    while encoded:
        for k, v in code:
            if v == '[newline]':
                v = '\n'

            if encoded.startswith(k):
                res += v
                encoded = encoded[len(k):]

    return res
