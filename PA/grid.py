import matplotlib.pyplot as plt

# 檔案路徑
file_path = r'C:\Users\user\Documents\GitHub\Algorithm-2023\PA\input.txt'

with open(file_path, 'r') as file:
    lines = file.readlines()
    
    data = []
    for line in lines:
        words = line.split()
        numbers = list(map(int, words))
        data.append(numbers)

print(data[0][1])
cnt = data[0][1]
start = data[0][0]
array = []

for i in range(cnt):
    for j in range(4):
        array.append(data[i+1][j])


print(array)
    




# fig, ax = plt.subplots()
# plt.plot([0.5, 5.5], [0.5, 5.5], color="green")
# plt.plot([0.5, 5], [0, 5], color="red")
# plt.xlabel("X")
# plt.ylabel("Y")
# plt.title("Plot with 2 arbitrary Lines")
# plt.xlim(0, 6)
# plt.ylim(0, 6)
# ax.grid(True, linestyle='--', linewidth=0.5, color='gray')

# plt.show()