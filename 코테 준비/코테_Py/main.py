def solution(n, k, cmd):
    answer = ''
    tmp = [i for i in range(n)]
    ans = [0 for i in range(n)]
    del_idx = []
    cur_idx = k

    for i in cmd:
        cont = i.split()
        if cont[0] == 'D':
            cur_idx = tmp[cur_idx]
            cur_idx += int(cont[1])
        elif cont[0] == 'U':
            cur_idx = tmp[cur_idx]
            cur_idx -= int(cont[1])
        elif cont[0] == 'C':
            del_idx.append(tmp[cur_idx])
            del tmp[cur_idx]
        else:
            idx = del_idx.pop()
            tmp.insert(idx, idx)
        print(tmp)

    for i in del_idx:
        ans[i] = 1

    for i in ans:
        if i == 0:
            answer += 'O'
        else:
            answer += 'X'

    return answer


print(solution(8, 2, ["D 2","C","U 3","C","D 4","C","U 2","Z","Z","U 1","C"]))