filename = "main.cpp"
with open(filename, 'r') as f:
    with open('new_' + filename, 'w') as t:
        for line in f:
            s = line
            pos = s.find('.at(')
            while (pos != -1):
                s = s.replace('.at(', '[', 1)
                opened = 0
                closed = 0
                while (opened - closed > -1):
                    pos += 1
                    if (s[pos] == '('):
                        opened += 1
                    elif (s[pos] == ')'):
                        closed += 1
                s = s[:pos] + ']' + s[pos + 1:]
                pos = s.find('.at(')
            print(s, file=t, end='')
