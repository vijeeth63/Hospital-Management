#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include <regex>
#include <sstream>

using namespace std;

//For storing the details of the different patients
struct Patient {
    string patient_name;  //enter the patient name
    int patient_age;   //enter the age of patient in integers
    char patient_gender; // 'M' for Male, 'F' for Female
    string patient_phone; // 10 digit valid phone number of the patient
    string patient_bloodGroup;  //valid blood group of the patient
    int patient_priority;
};

// storing the details of appointment of the patient
struct Appointment{
    string patientName;  //store the patient name
    string app_date; // Format: DD-MM-YYYY (appointment date)
    string app_time; // Format: HH:MM(appointment time)
    bool isEmergency; // take input if the case is emergency or not from the patient
    int bedNumber; // Bed number allocated for the patient based on the appointment order
};

// storing the details about the beds need to be given  for the patients
struct Bed {
    int bedNumber;  // stores the bed number
    bool isOccupied;   //check if the bed is occupied or not
};

// to check whether the patient age entered is valid or not
int checkAge() {
    int age;
    while (true) {
        cout << "Enter age (0-150): ";
        cin >> age;
        if (cin.fail() || age < 0 || age > 150) {   //checking the range of age and also if the type of variable age is int or not
            cin.clear(); //  This line clears the error flags on the input stream.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This line discards the invalid input remaining in the input buffer.
            cout << "Invalid input. Please enter a valid age." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return age;
        }
    }
}

int checkPriority() {
    int priority;
    while (true) {
        cout << "Enter priority (0-100): ";
        cin >> priority;
        if (cin.fail() || priority < 0 || priority > 150) {   //checking the range of age and also if the type of variable age is int or not
            cin.clear(); //  This line clears the error flags on the input stream.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // This line discards the invalid input remaining in the input buffer.
            cout << "Invalid input. Please enter a valid priority." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return priority;
        }
    }
}

// to check whether the given input of gender is correct or not
char checkGender() {
    char gender;
    while (true) {
        cout << "Enter gender (M/F): ";
        cin >> gender;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the invalid input given
        gender = toupper(gender); // Convert to uppercase if given in lowercase
        if (gender == 'M' || gender == 'F') {
            return gender;
        } else {
            cout << "Invalid input. Please enter 'M' for Male or 'F' for Female." << endl;
        }
    }
}

// to check whether the given phone number is valid or not
string checkPhone() {
    string phoneNumber;
    while (true) {
        cout << "Enter phone number (10 digits): ";
        cin >> phoneNumber;
        if (phoneNumber.length() == 10 && all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit)) {  //to check whether it contains 10 digits
            return phoneNumber;
        } 
        else {
            cout << "Invalid input. Please enter a valid 10-digit phone number." << endl;
        }
    }
}

// to check given input of blood group is correct or not
string checkBlood() {
    string bloodGroup;
    while (true) {
        cout << "Enter blood group (EX: A+,A-,B+,B-,AB+,AB-,O+,O-): ";
        cin >> bloodGroup;
        if (bloodGroup == "A+" || bloodGroup == "A-" || bloodGroup == "B+" || bloodGroup == "B-" ||
            bloodGroup == "O+" || bloodGroup == "O-" || bloodGroup == "AB+" || bloodGroup == "AB-") {
            return bloodGroup;
        } 
        else {
            cout << "Invalid input. Please enter a valid blood group." << endl;
        }
    }
}

// To check the given year is leap year or not
bool isLeapYear(int year) {
    if(year%4 == 0){
        if(year%100 == 0){
            if(year%400 == 0){
                return true;
            }
            else{
                return false;
            }  
        return true;     
        }
    return false;
    }    
}


// to check the given date is valid or not and also check for the proper date format
bool checkDate(const string &date) {
    regex datePattern(R"(\d{2}-\d{2}-\d{4})");    //to check the date format
    if (!regex_match(date, datePattern)) 
        return false;    //if it do not match the date format then return false

    int day, month, year;
    char dash1, dash2; // To consume the dashes in between the date, month and year
    istringstream ss(date);

    // Extract day, month, and year from the given input
    ss >> day >> dash1 >> month >> dash2 >> year;

    if (dash1 != '-' || dash2 != '-') 
    return false; // Check for correct format
    if (month < 1 || month > 12) 
    return false;

    // Days in each month
    int daysInMonth[] = {0, 31, (isLeapYear(year) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (day > 0 && day <= daysInMonth[month]);
}

// to check the valid time format
bool checkTime(const string &time) {
    regex timePattern(R"((0[0-9]|1[0-9]|2[0-3]):[0-5][0-9])");   //check whether the hour is from 00 to 23 and minutes from 00 to 59
    return regex_match(time, timePattern);
    //regex_match checks if the entire string matches the specified regex pattern.
    //This is the regex pattern that describes valid time format(HH:MM).
}

// to check whether the input patient name is in correct format or not

bool checkName(const string &name) {
    // Check if the name is empty or consists only of spaces
    if (name.empty() || all_of(name.begin(), name.end(), ::isspace)) {
        return false; // Invalid if empty or only spaces
    }
    
    // Check if all characters are alphabets or spaces
    for (char c : name) {
        if (!isalpha(c) && !isspace(c)) {
            return false; // Invalid if it contains non-alphabetic characters
        }
    }
    
    return true; // Valid name
}


// Registering of new patients
void registerPatient(Patient &patient) {
    while (true) {
        cout << "Enter patient name: ";
        cin.ignore(); // To clear the invalid input
        getline(cin, patient.patient_name);
        
        if (checkName(patient.patient_name)) {
            break; //we can exit the loop if the name is in valid format
        } 
        else {
            cout << "Invalid input. Please enter a valid name (only alphabets and spaces allowed)." << endl;
        }
    }

    patient.patient_age = checkAge();
    patient.patient_gender = checkGender();
    patient.patient_phone = checkPhone();
    patient.patient_bloodGroup = checkBlood();
    patient.patient_priority = checkPriority();

    cout << "Patient registered successfully!" << endl;
}

// To display the details of the patient
void displayPatient(const Patient &patient) {
    cout << "Name: " << patient.patient_name << endl;
    cout << "Age: " << patient.patient_age << endl;
    cout << "Gender: " << patient.patient_gender << endl;
    cout << "Phone Number: " << patient.patient_phone << endl;
    cout << "Blood Group: " << patient.patient_bloodGroup << endl;
    cout << "Priority: " << patient.patient_priority << endl;
    cout << "-----------------------------\n";
}


//performing binary search to find the patient is registered or not
auto findPatient(const vector<Patient> &patients, const string &patientName) {
    int left = 0;
    int right = patients.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (patients[mid].patient_name == patientName) {
            return patients.begin() + mid; // Return iterator to the found patient
        } else if (patients[mid].patient_name < patientName) {
            left = mid + 1; // Search right half
        } else {
            right = mid - 1; // Search left half
        }
    }
    return patients.end(); // Return end if not found
}

// To book or schedule an appointment for the patient
void scheduleAppointment(vector<Appointment> &appointments, vector<Bed> &beds, const vector<Patient> &patients) {
    Appointment appointment;   //declares a variable named appointment of type Appointment
    cout << "Enter patient name for appointment: ";
    cin.ignore();
    getline(cin, appointment.patientName);

    

    auto check = findPatient(patients, appointment.patientName);
    if (check == patients.end()) {
        cout << "Patient not found! Please register the patient first." << endl;
        return;
    }

    while (true) {
        cout << "Enter appointment date (DD-MM-YYYY): ";
        cin >> appointment.app_date;
        if (checkDate(appointment.app_date)) {
            break; // Exit the loop since the date is valid and is in valid format
        } 
        else {
            cout << "Invalid date format or invalid date! Please use DD-MM-YYYY." << endl;
        }
    }

    while (true) {
        cout << "Enter appointment time (HH:MM): ";
        cin >> appointment.app_time;
        if (checkTime(appointment.app_time)) {
            break; // Exit the loop since the time is in valid format
        }
         else {
            cout << "Invalid time format! Please use HH:MM." << endl;
        }
    }

    // Take input from the patient whether it is an emergency case or not 
    char emergency;
    while (true) {
        cout << "Is this an emergency case? (Y/N): ";
        cin >> emergency;
        emergency= toupper(emergency);
        if (emergency == 'Y') {
            appointment.isEmergency = true;
            break;
        } else if (emergency == 'N') {
            appointment.isEmergency = false;
            break;
        } 
        else {
            cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
        }
    }

    // Allocate a bed for the patient
    for (auto &bed : beds) {
        if (!bed.isOccupied) {
            bed.isOccupied = true; // Mark bed as occupied
            appointment.bedNumber = bed.bedNumber; // Assign bed number to patient who took the appointment
            cout << (appointment.isEmergency ? "Emergency" : "Regular") << " bed allocated: Bed Number " << bed.bedNumber << endl;
            break;
        }
    }

    appointments.push_back(appointment);  // adding new element into the vector
    cout << " Your Appointment has been scheduled successfully!" << endl;
}

// To display the appointments of the patients
void displayAppointments(const vector<Appointment> &appointments) {
    if (appointments.empty()) {
        cout << "No appointments are scheduled yet." << endl;
        return;
    }

    cout << "\nScheduled Appointments:\n";
    for (const auto &appointment : appointments) {
        cout << "Patient: " << appointment.patientName;
        cout << ", Date: " << appointment.app_date ;
        cout << ", Time: " << appointment.app_time ;
        cout << (appointment.isEmergency ? " (Emergency)" : "") ;
        cout << ", Bed Number: " << appointment.bedNumber ;
        cout << endl;
    }
    cout << "-----------------------------\n";
}



    
 


// to sort the patients based on their names in alphabetical order
void sort_by_name(const Patient patients[], int count) {
    // Create a vector to hold the patients names and sort them
    vector<Patient> sortedPatients(patients, patients + count);

    // sorting the names using bubble sort algorithm
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (sortedPatients[j].patient_name > sortedPatients[j + 1].patient_name) {
                // Swap the patients
                swap(sortedPatients[j], sortedPatients[j + 1]);
            }
        }
    }

    // to Display sorted patients 
    cout << "\nPatients sorted by name:\n";
    for (const auto &patient : sortedPatients) {
        displayPatient(patient);
    }
}




// Function to sort and display patients by age
void sort_by_age(const Patient patients[], int count) {
    // Create a vector to hold the patients age
    vector<Patient> sortedPatients(patients, patients + count);

    // sorting the age of the patients using bubble sort algorithm
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (sortedPatients[j].patient_age > sortedPatients[j + 1].patient_age) {
                // Swap the patients
                //swap(sortedPatients[j], sortedPatients[j + 1]);
                Patient temp = sortedPatients[j];          
                sortedPatients[j] = sortedPatients[j + 1]; 
                sortedPatients[j + 1] = temp;  
            }
        }
    }

    // Display sorted patients
    cout << "\nPatients sorted by age:\n";
    for (const auto &patient : sortedPatients) {
        displayPatient(patient);
    }
}

// Function to sort and display patients by priority
void sort_by_priority(const Patient patients[], int count) {
    // Create a vector to hold the patients age
    vector<Patient> sortedPatients(patients, patients + count);

    // sorting the priority of the patients using bubble sort algorithm
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (sortedPatients[j].patient_priority > sortedPatients[j + 1].patient_priority) {
                // Swap the patients
                //swap(sortedPatients[j], sortedPatients[j + 1]);
                Patient temp = sortedPatients[j];          
                sortedPatients[j] = sortedPatients[j + 1]; 
                sortedPatients[j + 1] = temp;  
            }
        }
    }

    // Display sorted patients
    cout << "\nPatients sorted by priority:\n";
    for (const auto &patient : sortedPatients) {
        displayPatient(patient);
    }
}


int main() {
    /*const int MAX_PATIENTS = 1000; // define the maximum number of patients the array can store
    Patient patients[MAX_PATIENTS]; // defining an array to store the details of the patients
    vector<Appointment> appointments; //defining a Vector to store appointments
    vector<Bed> beds; // defining a vector to store the details of the beds
    */
   const int MAX_PATIENTS = 1000; // Maximum number of patients
   const int MAX_APPOINTMENTS = 100; // Maximum number of appointments
   const int MAX_BEDS = 10; // Maximum number of beds
   Patient patients[MAX_PATIENTS]; // Array to store patient details
   vector<Appointment> appointments; // Vector to store appointments
   vector<Bed> beds(MAX_BEDS); // Vector to store bed details
    
    for (int i = 0; i < MAX_BEDS; ++i) {
        beds[i].bedNumber = i + 1; // Assigning the bed numbers
        beds[i].isOccupied = false; // Initially all beds are free in the starting
    }

    int patientCount = 0; // initial Counter for registered patients
    int choice;

    do {

        cout << "Welcome to the Hospital Management System\n";
        cout << "-------------------------------------------\n";

        cout << "1. Register Patient details\n";
        cout << "2. Display Patient details\n";
        cout << "3. Schedule Appointments of the patients\n";
        cout << "4. Display Appointments of the patients\n";
        cout << "5. Sort and Display Patients by their Name\n";
        cout << "6. Sort and Display Patients by their Age\n";
        cout << "7. Sort and Display Patients by their Priority\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (patientCount < MAX_PATIENTS) {
                    registerPatient(patients[patientCount]);
                    patientCount++; // Increment the patient count when the new patient details are added
                } 
                else {
                    cout << "Patient registration limit reached!" << endl;
                }
                break;

            case 2:
                if (patientCount > 0) {
                    cout << "\nRegistered Patients:\n";
                    for (int i = 0; i < patientCount; i++) {
                        cout << "Patient " << (i + 1) << ":\n";
                        displayPatient(patients[i]);
                    }
                } 
                else {
                    cout << "No patients have been registered yet.\n";
                }
                break;

            case 3:
                if (patientCount > 0) {
                    scheduleAppointment(appointments, beds, vector<Patient>(patients, patients + patientCount));
                } 
                else {
                    cout << "No patients registered yet. Please register a patient first." << endl;
                }
                break;

            case 4:
                displayAppointments(appointments);
                break;

            case 5:
                if (patientCount > 0) {
                    sort_by_name(patients, patientCount);
                } 
                else {
                    cout << "No patients registered yet." << endl;
                }
                break;

            case 6:

                if (patientCount > 0) {
                    sort_by_age(patients, patientCount);
                } 
                else {
                    cout << "No patients registered yet." << endl;
                }
                break;

            case 7:
                if (patientCount > 0) {
                     sort_by_priority(patients, patientCount);
                } 
                else {
                    cout << "No patients registered yet." << endl;
                }

            case 8:
                cout << "Exiting the Hospital Management system. Thank you!!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again with the correct choice" << endl;
        }
    } 
    while (choice != 8);

    return 0;
}






