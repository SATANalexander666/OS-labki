#include <vector>
#include <string>

int Sum(std::vector<int> &arr)
{
    int result = 0;

    for (int elem : arr){
        result += elem;
    }

    return result;
}
