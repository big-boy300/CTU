def read_classification_from_file(filename):
    arr = []
    dictionary = {}
    with open(filename, 'r', encoding='utf-8') as f:
        for lines in f:
            arr.append(lines.strip().split(" "))
 
    for i in range(len(arr)):
        dictionary[arr[i][0]] = arr[i][1]
    return (dictionary)
 
if __name__ == "__main__":
    filename = 'pokus.txt'
    print(read_classification_from_file(filename)) 
    