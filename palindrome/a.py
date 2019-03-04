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
#   palindrome일 경우 단순히 뒤집은 결과와 원래 결과가 같으면 됨
    a = a.casefold()
    b = ''.join(reversed(a))

    if a == b:
        return 0
    else:
        return 1

def isPseudo(a):
#   psudo palindrome일 경우 글자를 index를 증가시키며 한 자리씩 빼서 뒤집은 결과가 같으면 됨
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

