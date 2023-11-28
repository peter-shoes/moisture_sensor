import sys
import matplotlib.pyplot as plt

def read_data(file_path):
    data = {'A0': [], 'A1': [], 'A2': []}
    with open(file_path, 'r') as file:
        for line in file:
            key, values = line.strip().split(': ')
            values = list(map(int, values.split()))
            data[key].extend(values)
    return data

def plot_data(data):
    x_values = list(range(1, len(data['A0']) + 1))
    plt.figure(figsize=(8, 6))
    plt.plot(x_values, data['A0'], label='A0')
    plt.plot(x_values, data['A1'], label='A1')
    plt.plot(x_values, data['A2'], label='A2')
    plt.xlabel('Index')
    plt.ylabel('Values')
    plt.title('Data Plot')
    plt.legend()
    plt.grid(True)
    plt.show()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <data_file>")
        sys.exit(1)

    data_file = sys.argv[1]
    data = read_data(data_file)
    plot_data(data)
