import matplotlib.pyplot as plt
import numpy as np
# 檔案路徑
file_path = r'C:\Users\jason\OneDrive\文件\GitHub\Algorithm-2023\PA\output.txt'
inputsize = [60,60]
capacity = 45

def extract_pairs(combination):
    x1, y1, x2, y2 = combination
    return (tuple((x1, y1)), tuple((x2, y2)))

def count_combinations(arrays):
    combination_counts = {}  # Dictionary to store the count of each combination
    for arr in arrays:
        for combination in arr:
            
            pairs = extract_pairs(combination)
            samepairs = (pairs[1],pairs[0])
        
            if(combination_counts.get(pairs, 0)>=combination_counts.get(samepairs, 0)):
                combination_counts[pairs] = combination_counts.get(pairs, 0) + 1
                # print("                                                           pairs = ",pairs)
                # print("pairs cnt = " ,combination_counts.get(pairs, 0))
                # print("samepairs cnt = " ,combination_counts.get(samepairs, 0))
            else:
                combination_counts[samepairs] = combination_counts.get(samepairs, 0) + 1
                # print("                                                       samepairs = ",samepairs)
                # print("pairs cnt = " ,combination_counts.get(pairs, 0))
                # print("samepairs cnt = " ,combination_counts.get(samepairs, 0))

    return combination_counts

with open(file_path, 'r') as file:
    lines = file.readlines()    
    data = []
    for line in lines:
        words = line.split()
        numbers = list(map(int, words))
        data.append(numbers)
        numbers = []

arr = [[]]
index = 0
cnt = 0

while(cnt<len(data)):
    value = data[cnt][1]
    # print(value)
    for i in range(value):
        cnt = cnt+1
        arr[index].append(data[cnt])
    cnt = cnt+1
    if cnt < len(data):
        index = index + 1
        arr.append([])



# width_pixels = 1440
# height_pixels = 1920
# dpi = 100
# width_inches = width_pixels / dpi
# height_inches = height_pixels / dpi
# plt.figure(figsize=(width_inches, height_inches))
fig, ax = plt.subplots()
all_combination_counts = count_combinations(arr)
overflow = 0
for combination, count in all_combination_counts.items():
    
    if(count>capacity):
        
        x1,y1 = combination[0]
        x2,y2 = combination[1]
        if(x1 == x2):
            xls = x1+1
            yls = max(y1,y2)
            xle = x1
            yle = max(y1,y2)
        else:
            xls = max(x1,x2)
            yls = y1+1
            xle = max(x1,x2)
            yle = y1
        overflow = overflow +1
        # print(xls,yls,xle,yle)
        print(f"({xls},{yls})({xle},{yle})有{count}條線")
        plt.plot([xls,xle], [yls,yle], color="red")

# for list in arr:
#     print(list)

for list in arr:
    col = (np.random.random(), np.random.random(), np.random.random())
    for i in range(len(list)):
        plt.plot([list[i][0]+0.5,list[i][2]+0.5], [list[i][1]+0.5, list[i][3]+0.5], color=col)
    

plt.xlabel("X")
plt.ylabel("Y")
plt.title("routing")
major_ticks_top_x = np.linspace(0,inputsize[0] ,inputsize[0]+1)
major_ticks_top_y = np.linspace(0,inputsize[1] ,inputsize[1]+1)
plt.xticks(major_ticks_top_x)
plt.yticks(major_ticks_top_y)
plt.xlim(0, inputsize[0])
plt.ylim(0, inputsize[1])
# plt.gca().invert_yaxis()
# plt.title('Inverted Y-axis')
ax.grid(True, linestyle='--', linewidth=1, color='gray')


print(f"總共有{overflow}條overflow")
plt.show()
