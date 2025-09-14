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

// сохранить данные в файл
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

// загрузить данные из файла
void FromFile(Pipe& t, Compress& c) {
    ifstream fin("data.txt");
    if (!fin) {
        cout << "Файл не найден\n";
        return;
    }
    getline(fin, t.name);
    fin >> t.length >> t.diametr >> t.repair;
    fin.ignore(); // убрать лишний перевод строки
    getline(fin, c.name);
    fin >> c.count >> c.count_working;
    fin.ignore();
    getline(fin, c.classification);
    fin.close();
    cout << "Данные загружены\n";
}

void Menu(Pipe& t, Compress& c) {
    while (1) {
        cout << "\nВыберите действие: \n"
            << "1. Добавить трубу\n"
            << "2. Добавить КС\n"
            << "3. Просмотр всех объектов\n"
            << "4. Редактировать трубу\n"
            << "5. Редактировать КС\n"
            << "6. Сохранить в файл\n"
            << "7. Загрузить из файла\n"
            << "0. Выход\n> ";

        int option;
        cin >> option;
        cin.ignore(); // убрать \n после числа

        switch (option) {
        case 1:
            cout << "-- Добавление трубы --\n";

            cout << "Введите название трубы: ";
            getline(cin, t.name); // для ввода названия с пробелом
            while (t.name.empty()) { // проверка названия
                cout << "Ошибка ввода.\nВведите снова: ";
                getline(cin, t.name);
            }

            // проверка длины
            cout << "Введите длину (км): ";
            while (!(cin >> t.length) || t.length <= 0) {
                cout << "Ошибка ввода.\nВведите снова: ";
                cin.clear();             // сброс ошибки
                cin.ignore(10000, '\n'); // очистка буфера
            }

            // проверка диаметра
            cout << "Введите диаметр (мм): ";
            while (!(cin >> t.diametr) || t.diametr <= 0) {
                cout << "Ошибка ввода.\nВведите снова: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            // проверка статуса ремонта
            cout << "В ремонте? (1 - да, 0 - нет): ";
            while (!(cin >> t.repair) || (t.repair != 0 && t.repair != 1)) {
                cout << "Ошибка ввода.\nВведите снова: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            break;

        case 2:
            cout << "-- Добавление КС --\n";

            // проверка названия
            cout << "Введите название КС: ";
            getline(cin, c.name);
            while (c.name.empty()) {
                cout << "Ошибка ввода.\nВведите снова: ";
                getline(cin, c.name);
            }

            // проверка количества цехов
            cout << "Введите количество цехов: ";
            while (!(cin >> c.count) || c.count <= 0) {
                cout << "Ошибка ввода.\nВведите снова: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            // проверка количества цехов в работе
            cout << "Введите количество цехов в работе: ";
            while (!(cin >> c.count_working) || c.count_working < 0 || c.count_working > c.count) {
                cout << "Ошибка ввода.\nВведите снова: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }

            cin.ignore(); // очищаем буфер после чисел

            // проверка класса станции
            cout << "Класс станции: ";
            getline(cin, c.classification);
            while (c.classification.empty()) {
                cout << "Ошибка ввода.\nВведите снова: ";
                getline(cin, c.classification);
            }
            break;

        case 3:
            cout << "\n-- Все объекты --\n";

            if (!t.name.empty()) { // если данные введены
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
            cout << "Изменить статус ремонта (1 - да, 0 - нет): ";
            cin >> t.repair;
            break;

        case 5:
            cout << "-- Редактирование КС --\n";
            if (c.count == 0) {
                cout << "Сначала добавьте КС!\n";
                break;
            }
            cout << "1. Запустить цех\n2. Остановить цех\n> ";
            int action;
            cin >> action;
            if (action == 1) {
                if (c.count_working < c.count)
                c.count_working++;
                else
                    cout << "Все цеха уже работают!\n";
            } else if (action == 2) {
                if (c.count_working > 0)
                    c.count_working--;
                else
                    cout << "Нет работающих цехов!\n";
            } else {
                cout << "Неверный ввод!\n";
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

        default:
            cout << "Неверный ввод!\n";
            break;
        }
    }
}

int main() {

    Pipe truba;
    Compress station;
    Menu(truba, station);
    
}