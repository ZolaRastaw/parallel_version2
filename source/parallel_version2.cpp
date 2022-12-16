#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

const int N = 1000000;

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    // Generate a random matrix of floating point numbers and save it to a file
    std::ofstream out("input/test_file/data.txt");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            float rand_num = static_cast<float>(rand()) / RAND_MAX;
            out << rand_num << " ";
        }
        out << std::endl;
    }
    out.close();

    // Read in the matrix from the file
    std::ifstream in("input/test_file/data.txt/");
    float matrix[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            in >> matrix[i][j];
        }
    }
    in.close();

    // Determine the indices of the columns where the number of negative elements is twice as large as the number of zeros
    omp_lock_t lock;
    omp_init_lock(&lock);
    std::vector<int> indices;
#pragma omp parallel for
    for (int j = 0; j < N; j++)
    {
        int negative_count = 0;
        int zero_count = 0;
        for (int i = 0; i < N; i++)
        {
            if (matrix[i][j] < 0)
            {
                negative_count++;
            }
            else if (matrix[i][j] == 0)
            {
                zero_count++;
            }
        }
        if (negative_count > zero_count * 2)
        {
            omp_set_lock(&lock);
            indices.push_back(j);
            omp_unset_lock(&lock);
        }
    }
    omp_destroy_lock(&lock);

    // Output the indices of the columns that meet the criterion
    for (int i = 0; i < indices.size(); i++)
    {
        std::cout << indices[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
