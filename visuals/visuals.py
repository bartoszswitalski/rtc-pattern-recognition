"""
    Name: visuals.py
    Purpose: creation of visual presentation of the results

    @author Bartosz Switalski

    Warsaw Univerity of Technology
    Faculty of Electronics and Information Technology
"""
import matplotlib.pyplot as plt
import sys
import math

MODE = 'r'
IDLE_RAW = 0
IDLE_PROC = 3
QUEUE_RAW = 1
QUEUE_PROC = 4
PROC_TIME = 2
NUMBER_OF_TIMES = 5
DECIMAL_POINTS = 2


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


def calc_ev(message_times):
    expected_values = []
    number_of_messages = len(message_times[IDLE_RAW])

    for _ in range(NUMBER_OF_TIMES):
        expected_values.append(0)

    for i in range(number_of_messages):
        for j in range(NUMBER_OF_TIMES):
            expected_values[j] += message_times[j][i]

    for i in range(NUMBER_OF_TIMES):
        expected_values[i] /= number_of_messages
        expected_values[i] = round(expected_values[i], DECIMAL_POINTS)

    return expected_values


def calc_std_deviation(message_times):
    standard_deviations = []
    expected_values = calc_ev(message_times)
    number_of_messages = len(message_times[IDLE_RAW])

    for i in range(NUMBER_OF_TIMES):
        tmp_sum = 0
        for j in range(number_of_messages):
            tmp_sum += math.pow(message_times[i][j] - expected_values[i], 2)

        s_deviation = math.sqrt(tmp_sum / number_of_messages)
        s_deviation = round(s_deviation, DECIMAL_POINTS)
        standard_deviations.append(s_deviation)

    return standard_deviations


def save_data(message_times):
    expected_values = calc_ev(message_times)
    standard_deviations = calc_std_deviation(message_times)

    file = open('output.txt', 'w')
    file.write(str(expected_values[IDLE_RAW]) + ' & ' +
               str(expected_values[QUEUE_RAW]) + ' & ' +
               str(expected_values[PROC_TIME]) + ' & ' +
               str(expected_values[IDLE_PROC]) + ' & ' +
               str(expected_values[QUEUE_PROC]) + '\n')
    file.write(str(standard_deviations[IDLE_RAW]) + ' & ' +
               str(standard_deviations[QUEUE_RAW]) + ' & ' +
               str(standard_deviations[PROC_TIME]) + ' & ' +
               str(standard_deviations[IDLE_PROC]) + ' & ' +
               str(standard_deviations[QUEUE_PROC]))
    file.close()


def plot_boxplot(message_times):
    fig, ax = plt.subplots()

    ax.set_title('Message processing time')
    ax.set_xlabel('message state')
    ax.set_ylabel('time')
    ax.set_yscale("log")

    ax.boxplot(message_times, labels=['raw idle', 'raw queue', 'raw->proc', 'proc idle', 'proc queue'])

    plt.savefig('graph.png')


def get_data(file_name):
    data = get_data_from_file(file_name)
    times = get_times_from_data(data)

    plot_boxplot(times)
    save_data(times)


def main():
    argv = sys.argv[1:]
    get_data(argv[0])


if __name__ == '__main__':
    main()
