#include <iostream>
#include <string>
#include <locale> 
#include <fstream>
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
};

// функции проверки ввода
int InputInt(const string& msg, int minVal, int maxVal) {
    int x;
    cout << msg;
    while (!(cin >> x) || x < minVal || x > maxVal) {
        cout << "Ошибка ввода.\nВведите снова: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();
    return x;
}

float InputFloat(const string& msg, float minVal, float maxVal) {
    float x;
    cout << msg;
    while (!(cin >> x) || x < minVal || x > maxVal) {
        cout << "Ошибка ввода.\nВведите снова: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();
    return x;
}

bool InputBool(const string& msg) {
    int x;
    cout << msg;
    while (!(cin >> x) || (x != 0 && x != 1)) {
        cout << "Ошибка ввода.\nВведите снова (0 или 1): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    cin.ignore();
    return x;
}

string InputString(const string& msg) {
    string s;
    cout << msg;
    getline(cin, s);
    while (s.empty()) {
        cout << "Ошибка ввода.\nВведите снова: ";
        getline(cin, s);
    }
    return s;
}

// сохранение/загрузка из файла
void SaveToFile(const Pipe& t, const Compress& c) {
    ofstream fout("data.txt");
    if (!fout) {
        cout << "Ошибка открытия файла\n";
        return;
    }
    fout << t.name << "\n" << t.length << "\n" << t.diametr << "\n" << t.repair << "\n";
    fout << c.name << "\n" << c.count << "\n" << c.count_working << "\n" << c.classification << "\n";
    fout.close();
    cout << "Данные сохранены\n";
}

void FromFile(Pipe& t, Compress& c) {
    ifstream fin("data.txt");
    if (!fin) {
        cout << "Файл не найден\n";
        return;
    }
    getline(fin, t.name);
    fin >> t.length >> t.diametr >> t.repair;
    fin.ignore();
    getline(fin, c.name);
    fin >> c.count >> c.count_working;
    fin.ignore();
    getline(fin, c.classification);
    fin.close();

    if (t.name.empty() && c.name.empty())
        cout << "Файл пустой или поврежден\n";
    else
        cout << "Данные загружены\n";
}

// меню
void Menu(Pipe& t, Compress& c) {
    while (true) {
        cout << "\nВыберите действие: \n"
            << "1. Добавить трубу\n"
            << "2. Добавить КС\n"
            << "3. Просмотр всех объектов\n"
            << "4. Редактировать трубу\n"
            << "5. Редактировать КС\n"
            << "6. Сохранить в файл\n"
            << "7. Загрузить из файла\n"
            << "0. Выход\n> ";

        int option = InputInt("", 0, 7);

        switch (option) {
        case 1:
            cout << "-- Добавление трубы --\n";
            t.name = InputString("Введите название трубы: ");
            t.length = InputFloat("Введите длину (км): ", 0.1, 1000000);
            t.diametr = InputInt("Введите диаметр (мм): ", 1, 10000);
            t.repair = InputBool("В ремонте? (1 - да, 0 - нет): ");
            break;

        case 2:
            cout << "-- Добавление КС --\n";
            c.name = InputString("Введите название КС: ");
            c.count = InputInt("Введите количество цехов: ", 1, 10000);
            c.count_working = InputInt("Введите количество цехов в работе: ", 0, c.count);
            c.classification = InputString("Класс станции: ");
            break;

        case 3:
            cout << "\n-- Все объекты --\n";
            if (!t.name.empty()) {
                cout << "\n--- ТРУБА ---\n";
                cout << "Название: " << t.name << "\n";
                cout << "Длина: " << t.length << " км\n";
                cout << "Диаметр: " << t.diametr << " мм\n";
                cout << "В ремонте: " << (t.repair ? "Да" : "Нет") << "\n";
            } else {
                cout << "\n--- ТРУБА ---\nДанных нет.\n";
            }

            if (!c.name.empty()) {
                cout << "\n--- КС ---\n";
                cout << "Название: " << c.name << "\n";
                cout << "Цехов всего: " << c.count << "\n";
                cout << "В работе: " << c.count_working << "\n";
                cout << "Класс станции: " << c.classification << "\n";
            } else {
                cout << "\n--- КС ---\nДанных нет.\n";
            }
            break;

        case 4:
            cout << "-- Редактирование трубы --\n";
            t.repair = InputBool("Изменить статус ремонта (1 - да, 0 - нет): ");
            break;

        case 5:
            cout << "-- Редактирование КС --\n";
            if (c.count == 0) {
                cout << "Сначала добавьте КС!\n";
                break;
            }
            {
                int action = InputInt("1. Запустить цех\n2. Остановить цех\n> ", 1, 2);
                if (action == 1) {
                    if (c.count_working < c.count)
                        c.count_working++;
                    else
                        cout << "Все цеха уже работают!\n";
                } else {
                    if (c.count_working > 0)
                        c.count_working--;
                    else
                        cout << "Нет работающих цехов!\n";
                }
            }
            break;

        case 6:
            SaveToFile(t, c);
            break;

        case 7:
            FromFile(t, c);
            break;

        case 0:
            cout << "Выход...\n";
            return;
        }
    }
}

int main() {
    Pipe truba;
    Compress station;
    Menu(truba, station);
}
