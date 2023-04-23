#include <vector>
#include <iostream>

void getQuadruples(std::vector<int> A, std::vector<int> B, std::vector<int> C, std::vector<int> D)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < B.size(); j++)
        {
            for (int k = 0; k < C.size(); k++)
            {
                for (int l = 0; l < D.size(); l++)
                {
                    if(A[i] + B[j] + C[k] + D[l] == 0)
                        std::cout << "Indicii sunt:" << i << " " << j << " " << k << " " << l << " " << std::endl;
                }
            }
        }
    }
}

int main()
{
    std::vector<int> A = {2, 3, 4, 6, 8, 0, -2, 5};
    std::vector<int> B = {10, 20, -4, 0, -1, -3};
    std::vector<int> C = {-20, -5, -6, -9, 100};
    std::vector<int> D = {-100, 20, 30, 40, 50, -100};
    getQuadruples(A, B, C, D);
}