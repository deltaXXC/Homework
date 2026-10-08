#include <iostream>
using namespace std;

char S[3] = {'a', 'b', 'c'};
int choose[3] = {0};

void Powerset(int i)
{
    if (i == 3)
    {
        cout << "{";

        for (int j = 0; j < 3; j++)
        {
            if (choose[j] == 1)
                cout << S[j] << " ";
        }

        cout << "}" << endl;
        return;
    }

    choose[i] = 0;
    Powerset(i + 1);

    choose[i] = 1;
    Powerset(i + 1);
}

int main()
{
    Powerset(0);
    return 0;
}
