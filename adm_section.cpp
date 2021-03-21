#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream>
using namespace std;

#define ofile "patient_data.csv"
#define nfile "newpatient_data.csv"

#define ofile_d "file_d.csv"
#define nfile_d "newfile_d.csv"
/*Structures used.*/
struct patient_data // patient strcture
{
    string patient_first_name, patient_last_name, dob;
    char gender;
    string contact_number, email, password, userName;
};
struct doctor_data //doctor structure
{
    int unique_id;
    string first_name, last_name;
    string specialisation;
    string contact, email;
};

/*Main fuctions*/
int add_doctor();            //adds new doctor to file_d.csv
int delete_doctor_data();    //delete doctor data from file_d.csv.
int delete_patient_data();   //delete patient record from patient_data.csv.
void announce();             //announcement for notice board stored in announcement.csv.
extern void fetch_doc_details(string); //fetch doctor details from file_d.csv. Defined in patient_section.csv.


/*Fuction definitions*/
int add_doctor() //adds new doctor
{
    struct doctor_data new_doc;
    fstream read, write;
    read.open(ofile_d, ios::in);
    write.open(ofile_d, ios::out | ios::app);
    int id_no;
    string instream_id;

START:
    cout << "                    :: Complete the below database registration :: \n\n"
         << endl;

    cout << "Enter First Name :: ";
    getline(cin, new_doc.first_name);

    cout << "Enter Last Name :: ";
    getline(cin, new_doc.last_name);

    cout << "Enter  Speciality (one at a time) :: ";
    getline(cin, new_doc.specialisation);

    cout << "Enter Contact Info :: ";
    getline(cin, new_doc.contact);

    cout << "Enter Email :: ";
    getline(cin, new_doc.email);

    //input over. generate UID
    string junk;
    system("CLS");
    cout << "                   :: Verify the details to confirm :: \n\n"
         << endl;

    cout << "First Name :: ";
    cout << new_doc.first_name << endl;

    cout << "Last Name :: ";
    cout << new_doc.last_name << endl;

    cout << "Speciality :: ";
    cout << new_doc.specialisation << endl;

    cout << "Contact Info :: ";
    cout << new_doc.contact << endl;

    cout << "Email :: ";
    cout << new_doc.email << endl;
    cout << "\nCONFIRM (Y/N) :: ";
    char response;
    cin >> response;
    cin.ignore();
    if (response == 'N')
        goto START;
    while (true)
    {
        if (read.peek() == EOF)
            break;
        getline(read, instream_id, ',');
        getline(read, junk);
        //cout << instream_id << endl;
    }
    stringstream value(instream_id);
    //cout << instream_id << endl;
    value >> id_no;
    new_doc.unique_id = id_no + 1;
    cout << "Registration successful.\n Your Unique ID is " << new_doc.unique_id << endl;
    write << new_doc.unique_id << ','
          << new_doc.first_name << ',' << new_doc.last_name << ',' << new_doc.specialisation << ',' << new_doc.contact << ',' << new_doc.email << '\n';
    read.close();
    write.close();
    return 0;
}
int delete_doctor_data() //delete doctor data.
{
    string uid;
    cout << "ENTER UID :: " << endl;
    getline(cin, uid);
    ifstream read(ofile_d);
    ofstream write(nfile_d);
    string instream_id, junk;
    while (true)
    {
        if (read.peek() == EOF)
            break;
        getline(read, instream_id, ',');
        getline(read, junk);
        if (instream_id != uid)
        {
            write << instream_id << ',' << junk << '\n';
        }
    }
    read.close();
    write.close();
    remove(ofile_d);
    rename(nfile_d, ofile_d);
    return 0;
}
int delete_patient_data() //delete patient record.
{
    struct patient_data target;
    string givenUserName, fetchedUserName, gendertemp;
    cout << "Enter the user's username to be deleted :: ";
    getline(cin, givenUserName);
    fstream sourceFile, writeFile;
    sourceFile.open(ofile, ios::in);
    writeFile.open(nfile, ios::out);
    bool found = false;
    string garbage, temp;
    while (getline(sourceFile, fetchedUserName, ','))
    {
        if (fetchedUserName == givenUserName)
        {
            found = true;
            getline(sourceFile, garbage);
        }
        else
        {
            writeFile << fetchedUserName << ',';
            getline(sourceFile, temp);
            writeFile << temp << '\n';
        }
    }
    if (found == false)
        cout << "No records found. " << endl;
    else
    {
        cout << "Confirm deletion (Y/N)." << endl;
        char response;
        cin >> response;
        if (response == 'Y')
        {
            writeFile.close();
            sourceFile.close();
            remove(ofile);
            rename(nfile, ofile);
        }
        else
        {
            writeFile.close();
            sourceFile.close();
            remove(nfile);
            // rename(nfile, ofile);
        }
    }
    //cin.ignore();  //attention.
    // writeFile.close();
    // sourceFile.close();
    // remove(ofile);
    // rename(nfile, ofile);
    return 0;
}
void announce() // notice board announcement
{
    fstream write;
    write.open("announcement.csv", ios::out);
    string message;
    getline(cin, message);
    write << message << '\n';
    write.close();
}
void adm_section() // MASTER FUNCTION.
{
    cout << "      ____________________________________________________________________" << '\n'
         << "     |           ::              ADMINISTRATOR PORTAL           ::        |" << '\n'
         << "     |                         -------------------------                  |" << '\n'
         << "     |                 1. Announce                                        |" << '\n'
         << "     |                 2. Register a staff                                |" << '\n'
         << "     |                 3. View staff record                               |" << '\n'
         << "     |                 4. Remove staff from records                       |" << '\n'
         << "     |                 5. Remove patient from records                     |" << '\n'
         << "     |____________________________________________________________________|" << '\n'
         << '\n'
         << "Enter response :: " << endl;
    int response;
    cin >> response;
    cin.ignore();
    string uid;
    switch (response)
    {
    case 1:
        announce();
        break;

    case 2:
        add_doctor();
        break;

    case 3:
        cout << "Enter UID :: ";
        getline(cin, uid);
        fetch_doc_details(uid);
        break;

    case 4:
        delete_doctor_data();
        break;

    case 5:
        delete_patient_data();
        break;

    default:
        cout << "ERROR !" << endl;
        break;
    }
}