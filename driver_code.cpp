#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <sstream>
using namespace std;

#define adminpass "adminpass"

struct patient_data
{
    string patient_first_name, patient_last_name, dob;
    char gender;
    string contact_number, email, password, userName;
};
struct str_doctor_data
{
    string unique_id;
    string first_name, last_name;
    string specialisation;
    string contact, email;
};

extern void patient_section();
extern void doctor_section();
extern void adm_section();
void announcements();

void announcements() //show notice.
{
    ifstream read("announcement.csv");
    cout << "                          ::      NOTICE      ::                          " << endl;
    cout << "___________________________________________________________________________" << endl; // 75 length line.
    char c = ' ';
    while (true)
    {
        if(read.peek() == EOF) break;
        // cout << "|   ";
        for(int i = 0; i < 75 - 8; i++)
        {
            if(read.peek() == EOF) break;
            read.get(c);
            cout << c;
        }
        cout << '\n';
    }
}
int main() // MASTER FUNCTION.
{
    cout << "                      WELCOME TO XYZ HOSPITAL             " << '\n'
         << endl;
    announcements();
    cout << "___________________________________________________________________________" << endl; // 75 length line.

    cout << "      ____________________________________________________________________" << '\n'
         << "     |           ::              LOGIN PORTAL                   ::        |" << '\n'
         << "     |                         ----------------                           |" << '\n'
         << "     |                 1. Patients' Login                                 |" << '\n'
         << "     |                 2. Doctors' Login                                  |" << '\n'
         << "     |                 3. ADMINISTRATORS                                  |" << '\n'
         << "     |____________________________________________________________________|" << '\n'
         << '\n'
         << "ENTER YOUR CHOICE ::  " << endl;
    int response;
    cin >> response;
    cin.ignore();
    string fres;
    switch (response)
    {
    case 1:
        system("CLS");
        patient_section();
        break;

    case 2:
        system("CLS");
        doctor_section();
        system("PAUSE");
        break;

    case 3:
        cout << "Enter admin password :: ";
        getline(cin, fres);
        if (adminpass != fres)
            return 0;
        system("CLS");
        adm_section();
        break;

    default:
        system("CLS");
        cout << "ERROR ! RETRY." << endl;
        break;
    }
    system("PAUSE");
    return 0;
}
