#include <iostream>
#include <random>
#include <vector>
#include <list>
#include <chrono>
#include <ctime>
#include <fstream>

using namespace std;

void generateVector(vector<long long> &numbers, int N)
{
    numbers.clear();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    for (int i = 0; i < N; i++)
    {
        numbers.push_back(dis(gen));
    }
}

vector<long long> selectionSort(vector<long long> numbers)
{

    int minPos;
    int temp;
    for (int i = 0; i <= numbers.size() - 2; i++)
    {
        minPos = i;
        for (int j = i + 1; j <= numbers.size() - 1; j++)
        {
            if (numbers[j] < numbers[minPos])
            {
                minPos = j;
            }
        }
        //swap
        temp = numbers[minPos];
        numbers[minPos] = numbers[i];
        numbers[i] = temp;
    }
    return numbers;
}

vector<long long> bubbleSort(vector<long long> numbers)
{

    int temp;
    for (int i = numbers.size() - 1; i >= 1; i--)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                //swap
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
    return numbers;
}

vector<long long> bubbleSortEscapeClause(vector<long long> numbers)
{

    int temp;

    int i = numbers.size() - 1;
    bool sorting = true;
    bool swopped;
    while (i >= 1 && sorting == true)
    {
        swopped = false;
        for (int j = 0; j <= i - 1; j++)
        {
            if (numbers[j] > numbers[j + 1])
            {
                //swap
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
                swopped = true;
            }
        }
        if (swopped == false)
        {
            sorting = false;
        }
        else
        {
            i = i - 1;
        }
    }
    return numbers;
}

int main()
{
    vector<long long> numbers;

    //clear text file to re-write it each time attempt is re-run
    std::ofstream outfile;
    fstream ofs;
    ofs.open("data.txt", ios::out | ios::trunc);
    ofs.close();
    outfile.open("data.txt", std::ios_base::app);

    //lists to store time data
    list<long long> bSort;
    list<long long> bSortEsc;
    list<long long> sSort;

    //set average runs to 5
    int n_runs = 5;
    vector<long long> numbers2;
    long long average_time1, average_time2, average_time3;

    //get average of times
    for (int N = 1000; N <= 20000; N += 1000)
    {
        //output what N is so that it is known where algo currently is in running state
        cout << N << endl;
        long long total_time1 = 0;
        long long total_time2 = 0;
        long long total_time3 = 0;
        for (int i = 0; i < n_runs; i++)
        {
            //generate the random number filled vector of size N
            generateVector(numbers, N);

            //time selection sort
            auto start = chrono::high_resolution_clock::now();
            numbers2 = selectionSort(numbers);
            auto finish = chrono::high_resolution_clock::now();
            long long nanoseconds = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            total_time1 = total_time1 + nanoseconds;

            //time bubble sort
            start = chrono::high_resolution_clock::now();
            numbers2 = bubbleSort(numbers);
            finish = chrono::high_resolution_clock::now();
            nanoseconds = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            total_time2 = total_time2 + nanoseconds;

            //time bubble sort with escape clause
            start = chrono::high_resolution_clock::now();
            numbers2 = bubbleSortEscapeClause(numbers);
            finish = chrono::high_resolution_clock::now();
            nanoseconds = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
            total_time3 = total_time3 + nanoseconds;
        }
        average_time1 = total_time1 / n_runs;
        sSort.push_back(average_time1);
        average_time2 = total_time2 / n_runs;
        bSort.push_back(average_time2);
        average_time3 = total_time3 / n_runs;
        bSortEsc.push_back(average_time3);
    }

    //display that algo is done
    cout << "done" << endl;

    std::list<long long>::iterator it;
    //append to text file
    for (it = sSort.begin(); it != sSort.end(); ++it)
    {
        if (std::prev(sSort.end())==it){
        outfile << *it;
        }else{
         outfile << *it << ",";   
        }
        
    }
    outfile << "\n";
    for (it = bSort.begin(); it != bSort.end(); ++it)
    {
        if (std::prev(bSort.end())==it){
        outfile << *it;
        }else{
         outfile << *it << ",";   
        }
        
    }
    outfile << "\n";
    for (it = bSortEsc.begin(); it != bSortEsc.end(); ++it)
    {
        if (std::prev(bSortEsc.end())==it){
        outfile << *it;
        }else{
         outfile << *it << ",";   
        }
        
    }

    return 0;
}
