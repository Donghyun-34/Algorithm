def solution(places):
    answer = [1, 1, 1, 1, 1]
    tmp = [[[0 for _ in range(5)] for _ in range(5)] for _ in range(5)]

    idx_room = 0
    for i in places:
        idx_class = 0
        for j in i:
            tmp[idx_room][idx_class] = list(j)
            idx_class += 1
        idx_room += 1

    idx_room = 0
    for i in tmp:
        idx_class = 0
        for j in i:
            idx_desk = 0
            for q in j:
                if q == 'P':
                    try:
                        if tmp[idx_room][idx_class][idx_desk + 1] == 'P' or \
                                tmp[idx_room][idx_class + 1][idx_desk] == 'P':
                            answer[idx_room] = 0
                            break
                        elif tmp[idx_room][idx_class + 1][idx_desk - 1] == 'P' and idx_desk != 0:
                            if tmp[idx_room][idx_class + 1][idx_desk] == 'O' or \
                                    tmp[idx_room][idx_class][idx_desk - 1] == 'O':
                                answer[idx_room] = 0
                                break
                            else:
                                idx_desk += 1
                        elif tmp[idx_room][idx_class + 1][idx_desk + 1] == 'P':
                            if tmp[idx_room][idx_class + 1][idx_desk] == 'O' or \
                                    tmp[idx_room][idx_class][idx_desk + 1] == 'O':
                                answer[idx_room] = 0
                                break
                            else:
                                idx_desk += 1
                        elif tmp[idx_room][idx_class + 2][idx_desk] == 'P':
                            if tmp[idx_room][idx_class + 1][idx_desk] == 'O':
                                answer[idx_room] = 0
                            else:
                                idx_desk += 1
                        else:
                            idx_desk += 1
                    except IndexError:
                        idx_desk += 1
                        pass
                else:
                    idx_desk += 1
            if answer[idx_room] == 0:
                break
            else:
                idx_class += 1
        idx_room += 1

    return answer


places = [["PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"], ["POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"],
          ["POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"], ["PXOPX", "OXOXP", "OXPXX", "OXXXP", "POOXX"],
          ["OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"]]

print(solution(places))
