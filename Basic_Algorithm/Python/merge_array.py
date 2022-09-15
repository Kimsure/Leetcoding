from heapq import merge


# class Solution(object):
#     def merge(self, intervals):
#         intervals.sort(key = lambda x: x[0])
#         merged = []
#         for interval in intervals:
#             if len(merged)==0 or interval[0] > merged[-1][-1]:
#                 merged.append(interval)
#             else:
#                 merged[-1][-1] = max(merged[-1][-1], interval[-1])
#         res = 0
#         for i in range(len(merged)):
#             res = max(res, merged[i][1] - merged[i][0])
#         return merged
class Solution:
    def merge(self, intervals):
        def key_function(x):
            return x[0]
        intervals.sort(key=key_function)
        ans = []
        start = intervals[0][0]
        end = intervals[0][1]
        res = 0
        for i in range(1,len(intervals)):
            if intervals[i][0] > end and intervals[i][1] >end:
                res += intervals[i][1] - intervals[i][0]
                ans.append([start,end])
                start = intervals[i][0]
                end = intervals[i][1]
            else:
                if intervals[i][0] <= start:
                    res += intervals[i][1] - intervals[i][0]
                    res -= intervals[i-1][1] - intervals[i][0]
                    start = intervals[i][0]
                if intervals[i][1] >= end:
                    end = intervals[i][1]
        ans.append([start,end])
        return ans

s = Solution()
# m = [[1,3],[2,6],[4,10],[15,18]]

length = input()

m = []
for i in range(int(length)):
    a = input()
    m.append(a.split(','))

for i in range(len(m)):
    for j in range(len(m[0])):
        m[i][j] = int(m[i][j])
res = s.merge(m)
print(res)
