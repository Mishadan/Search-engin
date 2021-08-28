#include <iostream>
#include <string>

using namespace std;

int main() {
    int count = 0;
    string s1 = " documents found";
    cin >> count;
    s1 = to_string(count) + s1;
    cout << s1;
    return 0;
}