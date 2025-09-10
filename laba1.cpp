#include <iostream>
#include <string>

using namespace std;

struct Pipe {
    string name;
    float length;
    int diametr;
    bool repair;
};

struct Compress {
    string name;
    int count;
    int count_working;
    string classification;
    bool working;
};

void Menu(Pipe t) {
    while (1)
    {
        cout << "Choose option:\n1. Add pipe\n2. Add CS\n";
        int option;
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Insert pipe name: ";
            cin >> t.name;
            break;
        case 3:
            cout << "Pipe name: " << t.name;
            break;
        };
    };
};

int main()
{
    cout << "Hello Word!\n";
    Pipe truba;
    truba.name = "Uchastok 1\n";
    cout << truba.name;
    Menu(truba);
}