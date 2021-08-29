#include <iostream>
#include <string>

using namespace std;

int main() {
    int document_count;
    cin >> document_count;
    string message;
    if (document_count == 0)
        message = "No documents found"s;
    else if (document_count == 1)
        message = "One document found"s;
    else
        message = to_string(document_count) + " documents found"s;
    cout << message << endl;
}