 
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class phoneBook
{
    char name[20];
    char phno[11];

public:
    void createphonebook();
    void search();
    void update(char *nm, char *newteleno);
    void deleterec();
    char *getname()
    {
        return name;
    }
    char *getphno()
    {
        return phno;
    }
};

void phoneBook::createphonebook()
{
    fstream file;
    file.open("phone.txt", ios::out | ios::binary);
    int cnt;
    cout << "Enter the total number of records: ";
    cin >> cnt;
    for (int i = 0; i < cnt; i++)
    {
        cin.ignore();
        cout << "Enter the name of the person: ";
        cin.getline(name, 20);
        cout << "Enter the phone number of the person: ";
        cin >> phno;
        file.write((char *)this, sizeof(*this));
    }
    file.close();
}

void phoneBook::search()
{
    fstream file;
    file.open("phone.txt", ios::in | ios::binary);
    char bb[20];
    cout << "Enter the name of the person you want to search: ";
    cin.ignore();
    cin.getline(bb, 20);
    int found = 0;
    while (!file.eof())
    {
        file.read((char *)this, sizeof(*this));
        if (strcmp(bb, getname()) == 0)
        {
            found = 1;
            break;
        }
    }
    file.clear();
    if (found == 0)
        cout << "\n\n---Record Not found---\n";
    else
    {
        cout << "Name: " << getname() << endl;
        cout << "Phone number: " << getphno() << endl;
    }
    file.close();
}

void phoneBook::update(char *nm, char *newteleno)
{
    fstream file;
    file.open("phone.txt", ios::in | ios::out | ios::binary);
    phoneBook p;
    int found = 0;
    while (!file.eof())
    {
        file.read((char *)this, sizeof(*this));
        if (strcmp(nm, getname()) == 0)
        {
            strcpy(name, nm);
            strcpy(phno, newteleno);
            int pos = file.tellg() - sizeof(*this);
            file.seekg(pos, ios::beg);
            file.write((char *)this, sizeof(*this));
            found = 1;
            break;
        }
    }
    file.clear();
    file.close();
    if (found == 0)
        cout << "\n\n---Record Not found---\n";
    else
        cout << "\n\n---Record Updated---\n";
}

void phoneBook::deleterec()
{
    fstream file;
    file.open("phone.txt", ios::in | ios::out | ios::binary);
    char bb[20];
    cout << "Enter the name of the person you want to delete: ";
    cin.ignore();
    cin.getline(bb, 20);
    fstream fout;
    fout.open("tempfileph.txt", ios::out | ios::binary);
    file.seekg(0, ios::beg);
    int found = 0;
    while (!file.eof())
    {
        file.read((char *)this, sizeof(*this));
        if (strcmp(bb, getname()) != 0)
            fout.write((char *)this, sizeof(*this));
        else
            found = 1;
    }
    file.clear();
    file.close();
    fout.close();
    remove("phone.txt");
    rename("tempfileph.txt", "phone.txt");
    if (found == 0)
        cout << "\n\n---Record Not found---\n";
    else
        cout << "\n\n---Record Deleted---\n";
}

int main()
{
    phoneBook p;
    int ch;
    while (1)
    {
        cout << "\n1.Create Phone Book";
        cout << "\n2.Search a record";
        cout << "\n3.Update a record";
        cout << "\n4.Delete a record";
        cout << "\n5.Exit";
        cout << "\n\nEnter your choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            p.createphonebook();
            break;
        case 2:
            p.search();
            break;
        case 3:
        {
            char nm[20], newteleno[11];
            cout << "Enter the name of the person you want to update: ";
            cin.ignore();
            cin.getline(nm, 20);
            cout << "Enter the new phone number of the person: ";
            cin >> newteleno;
            p.update(nm, newteleno);
            break;
        }
        case 4:
        {
            char nm[20];
            cout << "Enter the name of the person you want to delete: ";
            cin.ignore();
            cin.getline(nm, 20);
            p.deleterec();
            break;
        }
        case 5:
            exit(0);
        default:
            cout << "\n\n---Invalid choice---\n";
        }
    }
    return 0;
}
