#include "body.hpp"

int RUN = 32;

std::vector<int> arr;

struct data {
    int left, mid, right;
};

void ReadVector(std::istream &fin)
{
    int num;

    while (fin >> num){
        arr.push_back(num);
    }
}

void WriteVector(std::ostream &fout)
{
    for (int elem : arr){
        fout << elem << '\n';
    }
}

void* InsertionSort(void* arguments)
{
    data *args = (data*)arguments;
    
    int left = args->left;
    int right = args->right;
    
    for (int i = left + 1; i <= right; ++i)
    {
        int temp = arr[i];
        int j = i - 1;

        while (j >= left && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = temp;
    }

    return NULL;
}
 
void* Merge(void* arguments)
{
    data *args = (data*)arguments;
    
    int left = args->left;
    int mid = args->mid;
    int right = args->right;

    int len1 = mid - left + 1;
    int len2 = right - mid;
    
    std::vector<int> temp1(len1);
    std::vector<int> temp2(len2);

    for (int i = 0; i < len1; ++i)
        temp1[i] = arr[left + i];

    for (int i = 0; i < len2; ++i)
        temp2[i] = arr[mid + i + 1];
 
    int i = 0;
    int j = 0;
    int k = left;
 
    while (i < len1 && j < len2)
    {
        if (temp1[i] <= temp2[j])
        {
            arr[k] = temp1[i];
            i++;
        }
        else
        {
            arr[k] = temp2[j];
            j++;
        }
        k++;
    }
 
    while (i < len1)
    {
        arr[k] = temp1[i];
        k++;
        i++;
    }
 
    while (j < len2)
    {
        arr[k] = temp2[j];
        k++;
        j++;
    }

    return NULL;
}

void TimSort(const int numOfThreads)
{
    if (numOfThreads <= 0){
        exit(EXIT_SUCCESS);
    }

    std::vector<pthread_t> threads(numOfThreads + 1);
    std::vector<data> args(numOfThreads + 1);

    int arrSize = arr.size();
    int RUN = arrSize / numOfThreads + 1;

    for (int i = 0; i < numOfThreads; ++i)
    {
        args[i].left = i * RUN;
        args[i].right = std::min(i * RUN + RUN - 1, arrSize - 1);

        if (pthread_create(&threads[i], NULL, &InsertionSort, (void*)&args[i]))
        {
            perror("Error in creating thread )");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < numOfThreads; ++i){   
        if (pthread_join(threads[i], NULL))
        {
            perror("Error in joining thread )");
            exit(EXIT_FAILURE);
        }
    }

    int i = 0;
    int j = 0;

    for (int step = RUN; step < arrSize; step = 2 * step)
    {
        for (int left = 0; left < arrSize; left += 2 * step)
        {
            args[i].mid = left + step - 1;
            args[i].right = std::min(left + 2 * step - 1, arrSize - 1);
 
            if (args[i].mid < args[i].right)
            {
                args[i].left = left;

                pthread_create(&threads[i], NULL, &Merge, (void*)&args[i]);
                ++i;
            }
        }

        for (; j < i; ++j)
        {
            if (pthread_join(threads[j], NULL))
            {
                perror("Error in joining thread )");
                exit(EXIT_FAILURE);
            }
        }

        j = i;
    }
}

void Routine(std::istream &fin, const int numOfThreads)
{
    std::string outPath;
    fin >> outPath;

    ReadVector(fin);
    TimSort(numOfThreads);

    std::ofstream fout(outPath);

    if (!fout.good())
    {
        perror("Error in writing to file )");
        exit(EXIT_FAILURE);
    }

    WriteVector(fout);

    fout.close();

    arr.clear();
}