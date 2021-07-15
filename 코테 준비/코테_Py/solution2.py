def check_del(cur_idx, cont, del_idx, state):
    cnt = 0
    # U에 대한 체크
    if state == 1:
        for i in range(1, cont+1):
            tmp = cur_idx - i
            try:
                if del_idx.index(tmp) != -1:
                    cnt += 1
            except ValueError:
                pass
    # D에 대한 체크
    else:
        for i in range(1, cont + 1):
            tmp = cur_idx + i
            try:
                if del_idx.index(tmp) != -1:
                    cnt += 1
            except ValueError:
                pass

    return cnt


def solution(n, k, cmd):
    answer = ''
    tmp = [0 for i in range(n)]
    del_idx = []
    cur_idx = k

    for i in cmd:
        cont = i.split()
        if cont[0] == 'D':
            cnt = check_del(cur_idx, int(cont[1]), del_idx, 0)
            cur_idx += (int(cont[1]) + cnt)
        elif cont[0] == 'U':
            cnt = check_del(cur_idx, int(cont[1]), del_idx, 1)
            cur_idx -= (int(cont[1]) + cnt)
        elif cont[0] == 'C':
            if cur_idx == n-1:
                del_idx.append(cur_idx)
                cnt = check_del(cur_idx, 1, del_idx, 1)
                cur_idx -= (1 + cnt)
            else:
                del_idx.append(cur_idx)
                cnt = check_del(cur_idx, 1, del_idx, 0)
                cur_idx += (1 + cnt)
        else:
            del_idx.pop()

    for i in del_idx:
        tmp[i] = 1

    for i in tmp:
        if i == 0:
            answer += 'O'
        else:
            answer += 'X'

    return answer


print(solution(8, 2, ["D 2","C","U 3","C","D 4","C","U 2","Z","Z","U 1","C"]))