# Python3
s = input().strip()
p = input().strip()
nxt = []



def buildNxt():
    nxt.append(0)
    # next[0]必然是0
    x=1
    #因此从next[1]开始求
    now=0
    while x< len(p):
        if p[now]==p[x]:#如果P[now]= P[x]，则可以向右扩展一位
            now +=1
            x +=1
            nxt.append(now)
        elif now:
            now= nxt[now-1]#缩小now,，改成nxt[now-1]
        else:
            nxt.append(0)
        # now已经为0，无法再缩，故next[x]=0
            x+=1
def search():
    tar =0
# tar:主串中将要匹配的位置
    pos =0
# pos:模式串中将要匹配的位置
    while tar < len(s):
        if s[tar] ==p[pos]:#若两个字符相等，则tar, pos各进一步
            tar +=1
            pos +=1
        elif pos:
        #失配了。若pos +0，则依据next数组移动标尺
            pos = nxt[pos-1]
        else:
            tar +=1
        # pos[0]失配了。直接把标尺右移一位。
        if pos== len(p):
        # pos走到了len(p)，匹配成功
            print(tar - pos + 1)
            pos = nxt[pos-1]
#移动标尺
# buildNxt()


def getNxt(x):
#X next[x]
    for i in range(x, 0, -1):
    #从x到1枚举
        if p[0:i] == p[x-i+1:x+1]:
            return i
    #如果前缀等于后缀，则返回
    return 0
nxt = [getNxt(x) for x in range(len(p))]
search()
print("nxt is: "+''.join(map(str, nxt)))