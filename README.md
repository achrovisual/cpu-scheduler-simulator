# CPU Scheduling Simulator
This is a simple C program that simulates basic CPU scheduling algorithms.

## How to Compile
You can invoke gcc compiler however you want, but in this example, you can execute the short command below to compile the code in macOS or Linux.
```
cc simulator.c
```
To run the program, just open the binary executable produced in terminal.

## Algorithms Supported
This program simulates the following CPU scheduling algorithms:
* First Come, First Served
* Non-Preemptive Shortest Job First
* Preemptive Shortest Job First
* Round Robin

## Test Cases
The test cases can be found in the *tests* folder. You can also find the results for these in the *results* subfolder.

If you would want to use your own test case, follow this format for the file:
* The first line contains 3 integers separated by space, 𝑋 𝑌 𝑍.
* 𝑋 denotes the CPU scheduling algorithm. Refer to the table below for the corresponding values.
* 𝑌 denotes the number of processes, where 3 ≤ 𝑌 ≤ 100.
* 𝑍 denotes a time slice value (applicable for Round-Robin algorithm only), where 1 ≤ 𝑍 ≤ 100.

| CPU Scheduling Algorithm  | Value of 𝑋 |
| ------------- | ------------- |
| First Come, First Served | 0 |
| Non-Preemptive Shortest Job First | 1 |
| Preemptive Shortest Job First | 2 |
| Round Robin | 3 |

## Screenshots
![alt text](/preview.png "Terminal displaying results of test cases.")
