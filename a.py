def inp(lists):
    f = open("./palin.inp", 'r')
    for line in f:
        lists.append(line.rstrip('\n'))
    f.close()

def out(result):
    f = open("./palin.out", 'w')
    for x in result:
        f.write(str(x) + '\n')

    f.close()

def isPalindrome(a):
    a = a.casefold()
    b = ''.join(reversed(a))

    if a == b:
        return 0
    else:
        return 1

def isPseudo(a):
    leng = len(a)

    for i in range(leng):
        new = a[:i] + a[i+1:]

        if isPalindrome(new) == 0:
            return 0
    
    return 1

def solver():
    lists = []
    result = []
    inp(lists)

    for x in lists:
        if isPalindrome(x) == 1:
            if isPseudo(x) == 1:
                result.append(3) # pseudo nor palindrome
            else:
                result.append(2) # pseudo
        else:
            result.append(1) # palindrome

    out(result)

if __name__ == "__main__":
    solver()

