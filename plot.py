import matplotlib.pyplot as plt

if __name__ == '__main__':

    #TODO add path to your data file here
    filepath = './data.txt' 

    # TODO: add the names of each sorting method in the order they are saved in the text file
    names = ['Selection Sort','Bubble Sort', 'Bubble Sort with Escape Clause'] 

    # this is the range of input sizes tested 
    x = list(range(1000, 20001, 1000)) 
    with open(filepath, 'r') as file:
        for i, line in enumerate(file):
            y = list(map(int, line.split(',')))
            plt.plot(x, y, label=names[i], linestyle=':')

    plt.xlabel('Input size')
    plt.ylabel('Time taken (ns)')

    plt.title('Comparison of sort procedures')

    plt.legend()

    plt.savefig('sorting.pdf')

    plt.show()


