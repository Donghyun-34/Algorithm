r = [' '] * 11

r.insert(10, 'e')

print(r)
code_dict = {codes[i][2:]: codes[i][0] for i in range(len(codes)) if codes[i][1] == '\t'}
idx = codes.find('[newline]')
code = list(code_dict.keys())
# 여기 없는 경우 \n으로 처리.

res = [' '] * len(encoded)
for str in code:
    while True:
        idx = encoded.find(str)
        if idx == -1:
            break
        else:
            res[idx] = code_dict[str]