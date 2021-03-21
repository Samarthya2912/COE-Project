#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <sstream>
using namespace std;

#define ofile "patient_data.csv"
#define nfile "newpatient_data.csv"

#define ofile_d "file_d.csv"
#define nfile_d "newfile_d.csv"

#define slot_list "appointment_register.csv"

#define todays_bookings "pat_booking_records.csv"

/*Structures used*/
struct patient_data // patient data
{
    string patient_first_name, patient_last_name, dob;
    char gender;
    string contact_number, email, password, userName;
};
struct doctor_data  // doctor data.
{
    int unique_id;
    string first_name, last_name;
    string specialisation;
    string contact, email;
};
struct appointment_settings //data needed from doctor to add him/her to the slot_list database.
{ 
    int speciality, estimate_per_visit, opens, closes, current, doctor_id;
};

/*Main functions*/
int announce_schedule();           // set visiting hours and open for booking.
int fetch_data_byref(string);      // fetch patient data given username.
void view_my_appointments(string); // view all the appointments of the doctor given the username.
void doctor_section();             //MASTER FUNCTION.

/*Function definitions.*/
int fetch_data_byref(string username) //fetches patient data by username reference.
{
    struct patient_data target;
    string givenUserName, fetchedUserName, gendertemp;
    givenUserName = username;
    fstream sourceFile;
    sourceFile.open(ofile, ios::in);
    bool found = false;
    string garbage;
    while (getline(sourceFile, fetchedUserName, ','))
    {
        if (fetchedUserName == givenUserName)
        {
            found = true;
            target.userName = fetchedUserName;
            getline(sourceFile, target.password, ',');
            getline(sourceFile, target.patient_last_name, ',');
            getline(sourceFile, target.patient_first_name, ',');
            getline(sourceFile, gendertemp, ',');
            target.gender = gendertemp[0];
            getline(sourceFile, target.dob, ',');
            getline(sourceFile, target.contact_number, ',');
            getline(sourceFile, target.email);
            cout << "Username       :: " << givenUserName << endl;
            cout << "Patient's name :: " << target.patient_last_name << ", " << target.patient_first_name << endl;
            cout << "Gender         :: " << target.gender << endl;
            cout << "Date of Birth  :: " << target.dob << endl;
            cout << "Contact Number :: " << target.contact_number << endl;
            cout << "E-Mail address :: " << target.email << endl;
            break;
        }
        getline(sourceFile, garbage);
    }
    if (found == false)
        cout << "No records found. " << endl;
    sourceFile.close();
    return 0;
}
int announce_schedule() //add to file for finding specialists.
{
    struct appointment_settings new_entry;
    fstream write;
    write.open(slot_list, ios::out | ios::app);
    cout << "Enter your Unique ID :: ";
    string doctor_id_input;
    getline(cin, doctor_id_input);
    stringstream s(doctor_id_input);
    s >> new_entry.doctor_id;

    cout << " ::               Choose from the following specialities               ::\n"
         << endl;
    cout << " 1. Allergy & Clinical Immunology          8. Anaesthesia" << '\n'
         << " 2. Blood Disorders/ Haematology           9. Cardiac Surgery/ Cardio Thoracic Vascular Surgery" << '\n'
         << " 3. Dental Sciences                       10. Cardiology" << '\n'
         << " 4. Dermatology / Cosmetology             11. Diabetes And Endocrinology" << '\n'
         << " 5. Dietetics & Clinical Nutrition        12. ENT/ Otorhinolaryngology" << '\n'
         << " 6. Eye/ Ophthalmology                    13. Mental Health And Behavioural Sciences" << '\n'
         << " 7. Paediatrics                           14. Urology / Andrology" << endl;

    cin >> new_entry.speciality;

    cout << "Enter the slot opening (in 24 hour format) :: ";
    cin >> new_entry.opens;

    cout << "Enter the slot closing (in 24 hour format) :: ";
    cin >> new_entry.closes;

    cout << "Enter Maximum Consulatation Period (in minutes) :: ";
    cin >> new_entry.estimate_per_visit;

    new_entry.current = new_entry.opens;

    write << new_entry.speciality << ',' << new_entry.current << ',' << new_entry.estimate_per_visit << ','
          << new_entry.opens << ',' << new_entry.closes << ',' << new_entry.doctor_id << '\n';

    cout << '\n'
         << "Entry successful ! Open for patients for booking !" << endl;
    return 0;
}
void view_my_appointments(string myID) //view appointments using UID.
{
    ifstream sourceFile(todays_bookings);
    string pat_username, instream_id, visit_time;
    int counter = 1;
    while (true)
    {
        if (sourceFile.peek() == EOF)
            break;
        getline(sourceFile, pat_username, ',');
        getline(sourceFile, instream_id, ',');
        getline(sourceFile, visit_time);
        if (myID == instream_id)
        {
            cout << counter << ".) " << "Scheduled visiting time     :: " << visit_time << " Hours." << endl;
            fetch_data_byref(pat_username);
            ++counter;
            cout << "_________________________________________________________________" << '\n' << endl;
        }
    }
    sourceFile.close();
}

void doctor_section() //MASTER FUNCTION.
{
    system("CLS");
    cout << "      ____________________________________________________________________" << '\n'
         << "     |           ::              DOCTOR'S PORTAL                ::        |" << '\n'
         << "     |                         ----------------                           |" << '\n'
         << "     |                 1. View today's Appointments                       |" << '\n'
         << "     |                 2. View Patient's Data                             |" << '\n'
         << "     |                 3. Announce Visiting Hours                         |" << '\n'
         << "     |____________________________________________________________________|" << '\n'
         << '\n'
         << "ENTER YOUR CHOICE ::  " << endl;
    int response;
    cin >> response;
    cin.ignore();
    string myID, pat_username;
    switch (response)
    {
    case 1:
        cout << "Enter your ID :: ";
        getline(cin, myID);
        view_my_appointments(myID);
        break;

    case 2:
        cout << "Enter patient's Username :: ";
        getline(cin, pat_username);
        fetch_data_byref(pat_username);
        break;

    case 3:
        cout << "Enter the following required details :: ";
        announce_schedule();
        break;

    default:
        cout << "ERROR ! RETRY." << endl;
        break;
    }
}