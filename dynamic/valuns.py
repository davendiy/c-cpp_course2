

def task(dp, i, mask, s, vals):
    if dp[i][mask][s] != -1:
        return dp[i][mask][s]

    if mask >> i & 1 == 1:
        dp[i][mask][s] = 0
        return 0

    else:
        res = 0
        p1, p2 = vals[i][s - 1], vals[i][s - 2]
        for j in range(1, len(vals)):
            for t in range(3):
                tmp_p1, tmp_p2 = vals[j][t - 1], vals[j][t - 2]
                if (tmp_p1 <= p1 and tmp_p2 <= p2) or (tmp_p1 <= p2 and tmp_p2 <= p1):
                    res = max(res, task(dp, j, mask | 1 << i, t, vals))
        dp[i][mask][s] = res + vals[i][s]
        return res + vals[i][s]


with open('input.txt', 'r') as file:
    tests = int(file.readline())
    for test in range(tests):
        n = int(file.readline())
        valuns = []

        mask_l = 1
        for i in range(n):
            tmp = list(map(int, file.readline().split()))
            valuns.append(tmp)

        dp = [[[-1 for _ in range(3)] for _ in range(1 << n)] for _ in range(n + 1)]

        max_res = 0
        for i in range(n):
            for s in range(3):
                max_res = max(max_res, task(dp, i, 0, s, valuns))
        print(max_res)
