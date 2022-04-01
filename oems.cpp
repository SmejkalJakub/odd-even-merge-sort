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

#define DEBUG 1

#ifdef DEBUG
#include <chrono>
#endif

// Simple min function to get minimum from the 2 input values
int min(int a, int b)
{
    return a < b ? a : b;
}

// Simple max function to get maximum from the 2 input values
int max(int a, int b)
{
    return a > b ? a : b;
}

/**
 * @brief Main function that takes care of most of the work
 *        Every processor calls this when it gets both input values and then based on its rank sends the minimum and maximum to the respective processors.
 * 
 * @param processRank - rank of the processor that called this function. Needed for the decision on where to send the values
 * @param recievedNumbers - two input numbers that the processor got from another processor or from input
 */
void oddEvenMerge(int processRank, int recievedNumbers[2])
{
    // Get minimum and maximum from the input
    int minimum = min(recievedNumbers[0], recievedNumbers[1]);
    int maximum = max(recievedNumbers[0], recievedNumbers[1]);

    // Send the minimum and maximum values to the processors based on the current processor rank
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

/**
 * @brief Master processor will call this function to load the numbers from the generated numbers file
 * 
 * @return vector<int> - Vector of the loaded numbers
 */
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

/**
 * @brief This function will print the loaded numbers at the start of the program
 * 
 * @param loadedNumbersVector - numbers that should be printed out
 */
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

/**
 * @brief This function will print the sorted numbers at the end of the program
 * 
 * @param numbers - array of the sorted numbers that should be pronted out
 */
void printNumbersArray(int *numbers)
{
    for(int i = 0; i < INPUT_SIZE; i++)
    {
        cout << numbers[i] << endl;
    }
}

int main(int argc, char **argv)
{
    int processRank = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &processRank);

    vector<int> numbers = {};

    // Master processor will load numbers and distribute them to the first processors
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

    // Wait for two input numbers from another processors
    int recievedNumbers[2] = {-1, -1};
    MPI_Recv(&recievedNumbers[0], 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, nullptr);
    MPI_Recv(&recievedNumbers[1], 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, nullptr);

    #ifdef DEBUG
	chrono::time_point<chrono::high_resolution_clock> start, end;
	if (processRank == 0) start = chrono::high_resolution_clock::now();
    #endif

    oddEvenMerge(processRank, recievedNumbers);

    #ifdef DEBUG
        if (processRank == 0) end = chrono::high_resolution_clock::now();
    #endif


    // Master processor will print the sorted numbers array
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

    #ifdef DEBUG
	if (processRank == 0)
	{
		chrono::duration<double> diff = end - start;
		cout << endl << "Time: " << diff.count() << endl;
	}
    #endif

    MPI_Finalize();
}