#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <stdio.h>
#include <sstream>
using namespace std;

#define ofile "patient_data.csv"
#define nfile "newpatient_data.csv"

#define ofile_d "file_d.csv"
#define nfile_d "newfile_d.csv"
#define oslot_list "slot_list.csv"
#define nslot_list "new_slot_list.csv"

#define todays_bookings "pat_booking_records.csv"

/*Structures used*/
struct patient_data // patient data structure.
{
    string patient_first_name, patient_last_name, dob;
    char gender;
    string contact_number, email, password, userName;
};
struct str_doctor_data // doctor data structure.
{
    string unique_id;
    string first_name, last_name;
    string specialisation;
    string contact, email;
};

/*Main functions.*/
void add_new_patient();           // code to register a patient.
int edit_existing_details();      // update existing patient details.
void find_specialists(string);    // find specialist using speciality code from displayed list.
void book_a_slot(string, string); // program to book a slot with a doctor using doc's UID.
void patient_section();           // MASTER FUNCTION

/*Complementary functions.*/
void ageApproximate(string);    // approximates age given dob in DD/MM/YYYY.
int tfour_adder(int, int);      // does 24 hour clock arithmetic.
bool printStrongNess(string);   // check password strength and return true if strong.
void fetch_doc_details(string); // fetch data of doctor using unique id.

/*Function definitions.*/
void add_new_patient()
{
    struct patient_data new_patient;
    cout << "                   FOR NEW USERS ONLY." << '\n'
         << "                :: COMPLETE THE FORM BELOW ::                 " << endl;
    cout << "Patient's First Name:: " << endl;
    getline(cin, new_patient.patient_first_name);
    cout << endl;

    cout << "Patient's Last Name:: " << endl;
    getline(cin, new_patient.patient_last_name);
    cout << endl;

    cout << "Date of Birth (DD/MM/YYYY):: ";
    getline(cin, new_patient.dob);
    ageApproximate(new_patient.dob);
    cout << '\n'
         << endl;

    cout << "Gender (M/F):: " << endl;
    char temp_input;

GENDER:
    cin >> temp_input;
    if (temp_input == 'M' || temp_input == 'F')
    {
        new_patient.gender = temp_input;
    }
    else
    {
        cout << "WRONG INPUT !" << '\n'
             << "Re-enter your gender:: " << endl;
        goto GENDER;
    }
    cout << endl;
    cin.ignore();
CONTACT:
    cout << "Contact number:: " << endl;
    getline(cin, new_patient.contact_number);
    if (new_patient.contact_number.length() != 10)
    {
        cout << "Invalid Contact Number. Retry." << endl;
        goto CONTACT;
    }
    cout << endl;

EMAIL:
    cout << "E-Mail Address:: " << endl;
    string tempInput;
    getline(cin, new_patient.email);
    cout << endl;
    system("CLS");

USER_CREDENTIALS:
    string userName;
    cout << "Username:: " << endl;
    getline(cin, new_patient.userName);
    bool match = false;
    // code to find a match in the CSV file.
    if (match == true)
        goto USER_CREDENTIALS;

    cout << endl;

    cout << "Enter password (Must include atleast one digit, one special character and upper and lower case alphabet):: " << endl;
    string password_cnfm;
PASSWORD:
    getline(cin, new_patient.password);
    bool goAhead = printStrongNess(new_patient.password);
    if (goAhead == false)
    {
        cout << "Retry:: " << endl;
        goto PASSWORD;
    }
    else
    {
        cout << "Confirm password :: " << endl;
        getline(cin, password_cnfm);
        if (password_cnfm == new_patient.password)
            cout << "User Credentails Set Successfully." << endl;
        else
        {
            cout << "Passwords Do Not Match. Retry." << endl;
            goto PASSWORD;
        }
    }
    fstream fout;
    fout.open("patient_data.csv", ios::out | ios::app);
    fout << new_patient.userName << ',' << new_patient.password << ',' << new_patient.patient_last_name << ',' << new_patient.patient_first_name << ',' << new_patient.gender << ',' << new_patient.dob << ',' << new_patient.contact_number << ',' << new_patient.email << '\n';
    fout.close();
}
int edit_existing_details()
{
    fstream newfile;
    fstream oldfile, oldfile_copy;
    newfile.open(nfile, ios::out | ios::app);
    oldfile.open(ofile, ios::in);
    oldfile_copy.open(ofile, ios::in);
    struct patient_data target;
START:
    cout << "Input your username :: " << endl;
    string givenUserName, verify_password;
    getline(cin, givenUserName);
    string finUserName;
    string gendertemp;
    string trash;
    bool found = false;
    while (getline(oldfile_copy, finUserName, ','))
    {
        if (finUserName == givenUserName)
        {
            found = true;
            target.userName = finUserName;
            getline(oldfile_copy, target.password, ',');
            verify_password = target.userName;
            getline(oldfile_copy, target.patient_last_name, ',');
            getline(oldfile_copy, target.patient_first_name, ',');
            getline(oldfile_copy, gendertemp, ',');
            target.gender = gendertemp[0];
            getline(oldfile_copy, target.dob, ',');
            getline(oldfile_copy, target.contact_number, ',');
            getline(oldfile_copy, target.email);
            break;
        }
        getline(oldfile_copy, trash);
    }
    verify_password = target.password;
    if (found == false)
    {
        cout << "                       NO RECORDS FOUND !!. Retry" << '\n'
             << endl;
        oldfile_copy.close();
        remove(nfile);
        oldfile_copy.open(ofile, ios::in);
        goto START;
    }
    cout << "Name:: " << target.patient_last_name << ',' << target.patient_first_name << '\n'
         << '\n';
    // return 0;
    // to confirm updation getline(cin, target_patient.password);
    cout << "           1. Last Name" << '\n'
         << "           2. First Name" << '\n'
         << "           3. Gender" << '\n'
         << "           4. Date of Birth" << '\n'
         << "           5. Contact number" << '\n'
         << "           6. E-Mail address" << '\n'
         << "Enter the choice to be updated :: " << endl;

    int response;
    cin >> response;
    cin.ignore();
    switch (response)
    {
    case 1:
        cout << "Input the new last name :: " << endl;
        getline(cin, target.patient_last_name);
        break;

    case 2:
        cout << "Input the new first name :: " << endl;
        getline(cin, target.patient_first_name);
        break;

    case 3:
        cout << "Update gender :: " << endl;
        getline(cin, gendertemp);
        target.gender = gendertemp[0];
        break;

    case 4:
        cout << "Input the updated Date of Birth :: " << endl;
        getline(cin, target.dob);
        break;

    case 5:
        cout << "Input the updated Contact Number :: " << endl;
        getline(cin, target.contact_number);
        break;

    case 6:
        cout << "Enter the updated email address :: " << endl;
        getline(cin, target.email);
        break;

    default:
        cout << "Invalid response. Retry" << endl;
        edit_existing_details();
        break;
    }

    string temp;
    while (getline(oldfile, temp, ','))
    {
        if (temp == givenUserName)
        {
            getline(oldfile, temp);
            newfile << target.userName << ',' << target.password << ',' << target.patient_last_name << ',' << target.patient_first_name << ',' << target.gender << ',' << target.dob << ',' << target.contact_number << ',' << target.email << '\n';
        }
        else
        {
            newfile << temp << ',';
            getline(oldfile, temp);
            newfile << temp << '\n';
        }
    }
    string password;
    cout << '\n'
         << endl;
    cout << "Enter password to confirm updation :: ";
    getline(cin, password);
    cout << "MESSAGE :: " << endl;
    // cout << verify_password << endl;
    if (password == verify_password)
    {
        cout << "Updation Successful !" << endl;
        newfile.close();
        oldfile.close();
        oldfile_copy.close();
        remove(ofile);
        rename(nfile, ofile);
    }
    else
    {
        cout << "Updation Unsuccesful !" << endl;
        oldfile.close();
        newfile.close();
        oldfile_copy.close();
        remove(nfile);
    }

    return 0;
}
void find_specialists(string spec_code)
{
    ifstream specialisation_list(oslot_list);
    string instream, junk;
    int counter = 1;
    while (true)
    {
        if (specialisation_list.peek() == EOF)
            break;
        getline(specialisation_list, instream, ',');
        if (instream == spec_code)
        {
            cout << endl;
            
            for(int i = 0; i < 4; i++)
            getline(specialisation_list, instream, ',');

            getline(specialisation_list, instream);
            cout << "______________________________________" << endl;
            cout << counter << ".)";
            fetch_doc_details(instream);
            cout << "______________________________________" << endl;
            ++counter;
        }
        else
        {
            getline(specialisation_list, junk);
        }
    }
    specialisation_list.close();
}
void book_a_slot(string patient_username, string doctor_id)
{
    string password, temp, trash, true_password;
    cout << "Enter password :: ";
    getline(cin, password);
    fstream read;
    read.open(ofile, ios::in);
    while (true)
    {
        if (read.peek() == EOF)
        {
            cout << "NO RECORD FOUND !!" << endl;
            break;
        }
        getline(read, temp, ',');
        if (temp == patient_username)
        {
            getline(read, true_password, ',');
            break;
        }
        getline(read, trash);
    }
    read.close();
    if (password != true_password)
    {
        cout << "Incorrect password. " << endl;
        return;
    }
    cout << "Enter doctor's ID :: ";
    ifstream specialisation_list(oslot_list);
    ofstream modified_file("new.csv");
    int attendance_time = 0, show_current;
    cout << "You are about to book a slot with :: \n"
         << endl;
    fetch_doc_details(doctor_id);
    system("PAUSE");
    cout << endl;
    string spec_code, instream_id;
    string current, opens, closes, time_per_slot;
    int int_current, int_opens, int_closes, int_time_per_slot;

    while (true)
    {
        if (specialisation_list.peek() == EOF)
        {
            cout << "Doctor currently unavailable." << endl;
            break;
        }
        getline(specialisation_list, spec_code, ',');
        getline(specialisation_list, current, ',');
        getline(specialisation_list, time_per_slot, ',');
        getline(specialisation_list, opens, ',');
        getline(specialisation_list, closes, ',');
        getline(specialisation_list, instream_id);

        cout << current << endl; //optional

        stringstream s0(current);
        s0 >> int_current;
        stringstream s1(opens);
        s1 >> int_opens;
        stringstream s2(closes);
        s2 >> int_closes;
        stringstream s3(time_per_slot);
        s3 >> int_time_per_slot;

        // cout << int_current << endl;//optional

        if (doctor_id == instream_id)
        {
            show_current = int_current;
            attendance_time = tfour_adder(int_current, int_time_per_slot);
            if (show_current > int_closes)
            {
                cout << "NO SLOTS LEFT !! INCOVENIENCE REGRETTED.\t PLEASE RETRY." << endl;
                return;
            }
            modified_file << spec_code << ',' << attendance_time << ',' << time_per_slot << ','
                          << opens << ',' << closes << ',' << instream_id << '\n';
        }
        else
            modified_file << spec_code << ',' << current << ',' << time_per_slot << ','
                          << opens << ',' << closes << ',' << instream_id << '\n';
    }

    system("CLS");

    cout << "APPOINTMENT BOOKED WITH :: \n"
         << endl;
    fetch_doc_details(doctor_id);
    cout << "________________________________________" << endl;
    cout << "\n\nAt Following Schedule :: " << '\n'
         << "DAY :: Today" << '\n'
         << "TIME :: " << show_current << "  Hours ." << endl;
    cout << "\nTHANKS !" << endl;

    fstream book;
    book.open(todays_bookings, ios::out | ios::app);
    book << patient_username << ',' << doctor_id << ',' << show_current << '\n';

    book.close();
    modified_file.close();
    specialisation_list.close();
    remove(oslot_list);
    rename("new.csv", oslot_list);
}

bool printStrongNess(string input)
{
    int n = input.length();
    bool goAhead = false;

    // Checking lower alphabet in string
    bool hasLower = false, hasUpper = false;
    bool hasDigit = false, specialChar = false;
    string normalChars = "abcdefghijklmnopqrstu"
                         "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";

    for (int i = 0; i < n; i++)
    {
        if (islower(input[i]))
            hasLower = true;
        if (isupper(input[i]))
            hasUpper = true;
        if (isdigit(input[i]))
            hasDigit = true;

        size_t special = input.find_first_not_of(normalChars);
        if (special != string::npos)
            specialChar = true;
    }

    // Strength of password
    cout << "Strength of password:-";
    if (hasLower && hasUpper && hasDigit && specialChar && (n >= 8))
    {
        cout << "Strong" << endl;
        goAhead = true;
        return goAhead;
    }

    else if ((hasLower || hasUpper) && specialChar && (n >= 6))
    {
        cout << "Moderate" << endl;
        return goAhead;
    }

    else
    {
        cout << "Weak" << endl;
        return goAhead;
    }
}
void ageApproximate(string str)
{
    int place = 1000;
    int b;
    int year = 0;
    for (int i = 6; i < 10; i++)
    {
        b = str[i];
        year += place * (b - 48);
        place /= 10;
    }
    //cout << year;
    int age = 2021 - year;
    cout << "Age :: " << age - 1 << " - " << age + 1 << " years." << endl;
}
int tfour_adder(int time, int addend)
{
    int hour_adder = addend / 60;
    int minute_adder = addend % 60;
    time += 100 * hour_adder;
    time += minute_adder;
    return time;
}
void fetch_doc_details(string uid)
{
    fstream doc_book;
    doc_book.open(ofile_d, ios::in);
    while (true)
    {
        string instream_id;
        string instream, junk;
        if (doc_book.peek() == EOF)
            break;
        getline(doc_book, instream_id, ',');
        if (instream_id == uid)
        {
            cout << "Unique ID     :: " << uid << endl;
            getline(doc_book, instream, ',');
            cout << "Name          :: " << instream << ' ';
            getline(doc_book, instream, ',');
            cout << instream << endl;
            getline(doc_book, instream, ',');
            cout << "Profile       :: " << instream << endl;
            getline(doc_book, instream, ',');
            cout << "Contact Info  :: " << instream << endl;
            getline(doc_book, instream);
            cout << "Email         :: " << instream << endl;
            break;
        }
        else
        {
            getline(doc_book, junk);
        }
    }
    doc_book.close();
}

void patient_section()
{
    string spec_code;
    string usernamr, docID;
    cout << " ______________________________________________________" << '\n'
         << "|           ::         PATIENT'S PORTAL          ::    |" << '\n'
         << "|                  ----------------------              |" << '\n'
         << "|                  1. Register new user                |" << '\n'
         << "|                  2. Edit Existing Record             |" << '\n'
         << "|                  3. Book An Appointment              |" << '\n'
         << "|                  4. Find Doctor                      |" << '\n'
         << "|                  5. Exit program                     |" << '\n'
         << "|______________________________________________________|" << endl;

    cout << "Input your response:   ";
    int response;
    cin >> response;
    cin.ignore();
    switch (response)
    {
    case 1:
        system("CLS");
        add_new_patient();
        break;

    case 2:
        system("CLS");
        edit_existing_details();
        break;

    case 3:
        cout << "Enter Username :: ";
        getline(cin, usernamr);
        cout << "Enter Doctor ID :: ";
        getline(cin, docID);
        book_a_slot(usernamr, docID);
        break;

    case 4:

        cout << " ::               Choose from the following specialities               ::\n"
             << endl;
        cout << " 1. Allergy & Clinical Immunology          8. Anaesthesia" << '\n'
             << " 2. Blood Disorders/ Haematology           9. Cardiac Surgery/ Cardio Thoracic Vascular Surgery" << '\n'
             << " 3. Dental Sciences                       10. Cardiology" << '\n'
             << " 4. Dermatology / Cosmetology             11. Diabetes And Endocrinology" << '\n'
             << " 5. Dietetics & Clinical Nutrition        12. ENT/ Otorhinolaryngology" << '\n'
             << " 6. Eye/ Ophthalmology                    13. Mental Health And Behavioural Sciences" << '\n'
             << " 7. Paediatrics                           14. Urology / Andrology" << endl;
        cout << "Response :: ";
        getline(cin, spec_code);
        find_specialists(spec_code);
        break;

    case 5:
        cout << "Program ended by user." << endl;
        break;

    default:
        cout << "Error!" << endl;
        break;
    }
}
