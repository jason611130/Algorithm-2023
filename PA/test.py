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

capacity = 2
arr1 = [[2, 3, 1, 3], [1, 3, 1, 2], [1, 2, 1, 1], [1, 1, 1, 0], [1, 0, 0, 0]]
arr2 = [[1, 0, 1, 1], [1, 1, 1, 2], [1, 2, 1, 3]]
arr3 = [[0, 2, 1, 2], [1, 2, 1, 1], [1, 1, 2, 1], [2, 1, 3, 1], [3, 1, 3, 0]]

arrays = [arr1, arr2, arr3]

all_combination_counts = count_combinations(arrays)

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
    
        print(xls,yls,xle,yle)
        print(f"({xls},{yls})({xle},{yle})有{count}條線")
