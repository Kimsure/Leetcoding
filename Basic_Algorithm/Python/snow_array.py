inputArray = input().split(" ")
num = inputArray[0]
height = inputArray[1]
num = int(num)
height = int(height)
vec = []
for i in range(num):
    inputArray2 = input().split()
    for j in range(len(inputArray2)):
        inputArray2[j] = int(inputArray2[j])
    vec.append(inputArray2)

# print(vec)
# map_a = dict()
map_a = [0]*10000
for i in range(len(vec)):
    # print(vec[i][0])
    for z in range(vec[i][0], vec[i][1] + 1):
        # print(z)
        map_a[z] = 0

for i in range(len(vec)):
    for z in range(vec[i][0], vec[i][1] + 1):
        map_a[z] += 1

res = 0
# print(map_a)
# for k, v in map_a.items():
#     if v >= height:
#         res += 1
for i in range(len(map_a) - 1):
    if map_a[i] >= height and map_a[i+1] >= height:
        res += 1

print(res)

    