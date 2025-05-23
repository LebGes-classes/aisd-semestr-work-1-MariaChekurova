#include <iostream>
#include <vector>
#include "SegmentTreeProject.h"

using namespace std;

int main()
{
    std::vector<int> data = { 2, 4, 7, 1, 8, 9, 7, 2, 3, 5, 9, 7, 6, 4, 2 };
    SegmentTree tree(data);

    int sum = tree.getSum(4, 9);      // 8 + 9 + 7 + 2 + 3 + 5 = 34
    int min = tree.getMin(1, 6);      // min(4, 7, 1, 8, 9, 7) = 1
    int max = tree.getMax(8, 14);     // max(3, 5, 9, 7, 6, 4, 2) = 9

    cout << "Data: " << endl;
    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
    cout << "---------------------------" << endl;
    cout << "Sum of [4, 9]: " << sum << endl;
    cout << "Min of [1, 6]: " << min << endl;
    cout << "Max of [8, 14]: " << max << endl;

    cout << "-------------" << endl;

    data.push_back(1);
    data.push_back(13);
    data.insert(data.begin() + 8, 15);


    cout << "New Data: " << endl;
    for (int i = 0; i < tree.startArray.size(); i++)
    {
        cout << tree.startArray[i] << " ";
    }

    cout << endl;
    cout << "---------------------------" << endl;
    cout << "Max of [7, 9]: " << tree.getMax(7, 9) << endl;       // max(2, 15, 3, 5) = 15
    cout << "Min of [10, 16]: " << tree.getMin(10, 16) << endl;       // min(9, 7, 6, 4, 2, 1, 13) = 1
    cout << "Sum: " << tree.getSum(8, 15) << endl;       // 15 + 3 + 5 + 9 + 7 + 6 + 4 + 2 = 51
}