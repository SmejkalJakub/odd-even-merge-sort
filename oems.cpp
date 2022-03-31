#include <cmath>
#include <mpi.h>
#include <string>
#include <time.h>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <algorithm> 

using namespace std;

#define INPUT_SIZE 8

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

void oddEvenMerge(int processRank, int recievedNumbers[2])
{
    int minimum = min(recievedNumbers[0], recievedNumbers[1]);
    int maximum = max(recievedNumbers[0], recievedNumbers[1]);

    switch(processRank)
    {
        case 0:
        {
            MPI_Send(&minimum, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 5, 0, MPI_COMM_WORLD);
            break;
        }
        case 1: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 4, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 5, 1, MPI_COMM_WORLD);
            break;
        }
        case 2: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 6, 0, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 7, 0, MPI_COMM_WORLD);
            break;
        }
        case 3: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 6, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 7, 1, MPI_COMM_WORLD);
            break;
        }
        case 4: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 10, 0, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 8, 0, MPI_COMM_WORLD);
            break;
        }
        case 5: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 8, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 13, 0, MPI_COMM_WORLD);
            break;
        }
        case 6: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 10, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 9, 0, MPI_COMM_WORLD);
            break;
        }
        case 7: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 9, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 13, 1, MPI_COMM_WORLD);
            break;
        }
        case 8: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 12, 0, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 11, 0, MPI_COMM_WORLD);
            break;
        }
        case 9: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 12, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 11, 1, MPI_COMM_WORLD);
            break;
        }
        case 10: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 14, 0, MPI_COMM_WORLD);
            break;
        }
        case 11: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 14, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 18, 0, MPI_COMM_WORLD);
            break;
        }
        case 12: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 16, 0, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 15, 0, MPI_COMM_WORLD);
            break;
        }
        case 13: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 15, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 0, 7, MPI_COMM_WORLD);
            break;
        }
        case 14: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 16, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 17, 0, MPI_COMM_WORLD);
            break;
        }
        case 15: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 17, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 18, 1, MPI_COMM_WORLD);
            break;
        }
        case 16: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
            break;
        }
        case 17: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 0, 4, MPI_COMM_WORLD);
            break;
        }
        case 18: 
        {
            MPI_Send(&minimum, 1, MPI_INT, 0, 5, MPI_COMM_WORLD);
            MPI_Send(&maximum, 1, MPI_INT, 0, 6, MPI_COMM_WORLD);
            break;
        }
    }
}

vector<int> loadNumbers()
{
    vector <int> loadedNumbersVector;
    string numbersFileName = "numbers";

    fstream numbersFile;

    numbersFile.open(numbersFileName, ios::in);

    if(numbersFile.is_open() == false)
    {
        cerr << "Error: Couldn't open numbers file";
        return {};
    }

    while(numbersFile.good())
    {
        int loadedNumber = numbersFile.get();

        if(numbersFile.eof())
        {
            break;
        }

        loadedNumbersVector.push_back(loadedNumber);
    }

    numbersFile.close();

    return loadedNumbersVector;
}

void printLoadedNumbers(vector<int> loadedNumbersVector)
{
    for(int i = 0; i < loadedNumbersVector.size(); i++)
    {
        cout << loadedNumbersVector[i];
        if(i != loadedNumbersVector.size() - 1)
        {
            cout << ' ';
        }
    }

    cout << endl << flush;
}

void printNumbersArray(int *numbers)
{
    for(int i = 0; i < INPUT_SIZE; i++)
    {
        cout << numbers[i] << endl;
    }
}

int main(int argc, char **argv)
{
    int numberOfProcessors = 0;
    int processRank = 0;
    int sizeOfGroup = 0; 

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numberOfProcessors);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    vector<int> numbers = {};

    if(processRank == 0)
    {
        numbers = loadNumbers();
        if(numbers.size() == 0)
        {
            return -1;
        }

        printLoadedNumbers(numbers);
        
        for(int i = 0; i < numbers.size(); i+=2)
        {
            MPI_Send(&(numbers[i]), 1, MPI_INT, i / 2, 0, MPI_COMM_WORLD);
            MPI_Send(&(numbers[i+1]), 1, MPI_INT, i / 2, 1, MPI_COMM_WORLD);
        }
    }

    int recievedNumbers[2] = {-1, -1};
    MPI_Recv(&recievedNumbers[0], 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, nullptr);
    MPI_Recv(&recievedNumbers[1], 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, nullptr);

    oddEvenMerge(processRank, recievedNumbers);

    if(processRank == 0)
    {
        int *nums = new int[INPUT_SIZE];
        for (int i = 0; i < INPUT_SIZE; i++)
		{
			MPI_Recv(&nums[i], 1, MPI_INT, MPI_ANY_SOURCE, i, MPI_COMM_WORLD, nullptr);
		}
        printNumbersArray(nums);
        delete nums;
    }

    MPI_Finalize();
}