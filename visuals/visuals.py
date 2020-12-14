"""
    Name: visuals.py
    Purpose: creation of visual presentation of the results

    @author Bartosz Switalski

    Warsaw Univerity of Technology
    Faculty of Electronics and Information Technology
"""
import matplotlib.pyplot as plt

MODE = 'r'
IDLE_RAW = 0
IDLE_PROC = 3
QUEUE_RAW = 1
QUEUE_PROC = 4
PROC_TIME = 2


def list_stoi(list):
    for i in range(len(list)):
        list[i] = int(list[i])

    return list


def get_data_from_file(file_name):
    message_data = []

    with open(file_name, MODE) as file:
        for line in file.readlines():
            message_data.append(list_stoi(line.strip().split(' ')))

    return message_data


def get_times_from_data(message_data):
    message_times = [[], [], [], [], []]

    for i in range(len(message_data)):
        message_times[IDLE_RAW].append(message_data[i][1] - message_data[i][0])
        message_times[QUEUE_RAW].append(message_data[i][2] - message_data[i][1])
        message_times[PROC_TIME].append(message_data[i][3] - message_data[i][2])
        message_times[IDLE_PROC].append(message_data[i][4] - message_data[i][3])
        message_times[QUEUE_PROC].append(message_data[i][5] - message_data[i][4])

    return message_times


def plot_boxplot(message_times):
    fig, ax = plt.subplots()

    ax.set_title('Message processing times')
    ax.set_xlabel('Processes')
    ax.set_ylabel('Times')

    ax.boxplot(message_times, labels=['raw idle', 'raw queue', 'raw->proc', 'proc idle', 'proc queue'])

    plt.savefig('graph.png')


def get_data_boxplot():
    data = get_data_from_file('output.txt')
    times = get_times_from_data(data)

    plot_boxplot(times)


def main():
    get_data_boxplot()


if __name__ == '__main__':
    main()
