#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

struct Patient {
    int id;
    string name;
    int age;
    string gender;
    string contact;
    string address;
};

struct Doctor {
    int id;
    string name;
    string specialty;
    string contact;
};

struct Appointment {
    int id;
    int patientId;
    int doctorId;
    string date;
    string time;
    string reason;
    double fee;
};

class HospitalManagement {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    int nextPatientId = 1;
    int nextDoctorId = 1;
    int nextAppointmentId = 1;

public:
    static void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    static int promptInt(const string &prompt) {
        int value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                clearInput();
                return value;
            }
            cout << "Invalid entry. Please enter a number.\n";
            clearInput();
        }
    }

    static double promptDouble(const string &prompt) {
        double value;
        while (true) {
            cout << prompt;
            if (cin >> value) {
                clearInput();
                return value;
            }
            cout << "Invalid entry. Please enter a valid number.\n";
            clearInput();
        }
    }

    static string promptLine(const string &prompt) {
        string value;
        cout << prompt;
        getline(cin, value);
        return value;
    }

public:
    void addPatient() {
        Patient patient;
        patient.id = nextPatientId++;
        cout << "\n=== Add New Patient ===\n";
        patient.name = promptLine("Patient name: ");
        patient.age = promptInt("Patient age: ");
        patient.gender = promptLine("Gender: ");
        patient.contact = promptLine("Contact number: ");
        patient.address = promptLine("Address: ");

        patients.push_back(patient);
        cout << "Patient added successfully with ID " << patient.id << ".\n\n";
    }

    void addDoctor() {
        Doctor doctor;
        doctor.id = nextDoctorId++;
        cout << "\n=== Add New Doctor ===\n";
        doctor.name = promptLine("Doctor name: ");
        doctor.specialty = promptLine("Specialty: ");
        doctor.contact = promptLine("Contact number: ");

        doctors.push_back(doctor);
        cout << "Doctor added successfully with ID " << doctor.id << ".\n\n";
    }

    void listPatients() const {
        cout << "\n=== Patient List ===\n";
        if (patients.empty()) {
            cout << "No patients registered yet.\n\n";
            return;
        }
        cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(6) << "Age"
             << setw(12) << "Gender" << setw(16) << "Contact" << "Address\n";
        cout << string(70, '-') << "\n";
        for (auto &p : patients) {
            cout << left << setw(6) << p.id << setw(20) << p.name << setw(6) << p.age
                 << setw(12) << p.gender << setw(16) << p.contact << p.address << '\n';
        }
        cout << '\n';
    }

    void listDoctors() const {
        cout << "\n=== Doctor List ===\n";
        if (doctors.empty()) {
            cout << "No doctors registered yet.\n\n";
            return;
        }
        cout << left << setw(6) << "ID" << setw(25) << "Name" << setw(20)
             << "Specialty" << "Contact\n";
        cout << string(65, '-') << "\n";
        for (auto &d : doctors) {
            cout << left << setw(6) << d.id << setw(25) << d.name
                 << setw(20) << d.specialty << d.contact << '\n';
        }
        cout << '\n';
    }

    Patient *findPatient(int patientId) {
        for (auto &patient : patients) {
            if (patient.id == patientId) {
                return &patient;
            }
        }
        return nullptr;
    }

    Doctor *findDoctor(int doctorId) {
        for (auto &doctor : doctors) {
            if (doctor.id == doctorId) {
                return &doctor;
            }
        }
        return nullptr;
    }

    void scheduleAppointment() {
        if (patients.empty() || doctors.empty()) {
            cout << "\nPlease add both patients and doctors before scheduling an appointment.\n\n";
            return;
        }

        cout << "\n=== Schedule Appointment ===\n";
        int patientId = promptInt("Enter patient ID: ");
        Patient *patient = findPatient(patientId);
        if (!patient) {
            cout << "Patient not found. Please verify the ID.\n\n";
            return;
        }

        int doctorId = promptInt("Enter doctor ID: ");
        Doctor *doctor = findDoctor(doctorId);
        if (!doctor) {
            cout << "Doctor not found. Please verify the ID.\n\n";
            return;
        }

        Appointment appointment;
        appointment.id = nextAppointmentId++;
        appointment.patientId = patientId;
        appointment.doctorId = doctorId;
        appointment.date = promptLine("Appointment date (YYYY-MM-DD): ");
        appointment.time = promptLine("Appointment time (HH:MM): ");
        appointment.reason = promptLine("Reason for visit: ");
        appointment.fee = promptDouble("Consultation fee: $");

        appointments.push_back(appointment);
        cout << "Appointment scheduled successfully with ID " << appointment.id << ".\n\n";
    }

    void listAppointments() const {
        cout << "\n=== Appointment List ===\n";
        if (appointments.empty()) {
            cout << "No appointments scheduled yet.\n\n";
            return;
        }

        cout << left << setw(6) << "ID" << setw(10) << "Pat.ID" << setw(10) << "Doc.ID"
             << setw(12) << "Date" << setw(8) << "Time" << setw(20) << "Reason"
             << "Fee\n";
        cout << string(80, '-') << "\n";
        for (auto &appt : appointments) {
            cout << left << setw(6) << appt.id << setw(10) << appt.patientId
                 << setw(10) << appt.doctorId << setw(12) << appt.date << setw(8)
                 << appt.time << setw(20) << appt.reason
                 << "$" << fixed << setprecision(2) << appt.fee << '\n';
        }
        cout << "\n";
    }

    void searchPatient() const {
        int patientId = promptInt("Enter patient ID to search: ");
        auto it = find_if(patients.begin(), patients.end(), [patientId](const Patient &p) {
            return p.id == patientId;
        });

        if (it == patients.end()) {
            cout << "Patient not found.\n\n";
            return;
        }

        cout << "\nPatient Details:\n";
        cout << "ID: " << it->id << "\n";
        cout << "Name: " << it->name << "\n";
        cout << "Age: " << it->age << "\n";
        cout << "Gender: " << it->gender << "\n";
        cout << "Contact: " << it->contact << "\n";
        cout << "Address: " << it->address << "\n\n";
    }

    void searchDoctor() const {
        int doctorId = promptInt("Enter doctor ID to search: ");
        auto it = find_if(doctors.begin(), doctors.end(), [doctorId](const Doctor &d) {
            return d.id == doctorId;
        });

        if (it == doctors.end()) {
            cout << "Doctor not found.\n\n";
            return;
        }

        cout << "\nDoctor Details:\n";
        cout << "ID: " << it->id << "\n";
        cout << "Name: " << it->name << "\n";
        cout << "Specialty: " << it->specialty << "\n";
        cout << "Contact: " << it->contact << "\n\n";
    }

    void generateBill() const {
        int appointmentId = promptInt("Enter appointment ID for billing: ");
        auto it = find_if(appointments.begin(), appointments.end(), [appointmentId](const Appointment &a) {
            return a.id == appointmentId;
        });

        if (it == appointments.end()) {
            cout << "Appointment not found.\n\n";
            return;
        }

        const Appointment &appt = *it;
        const Patient *patient = nullptr;
        const Doctor *doctor = nullptr;

        for (auto &p : patients) {
            if (p.id == appt.patientId) {
                patient = &p;
                break;
            }
        }
        for (auto &d : doctors) {
            if (d.id == appt.doctorId) {
                doctor = &d;
                break;
            }
        }

        cout << "\n=== Bill Receipt ===\n";
        if (patient) {
            cout << "Patient: " << patient->name << " (ID " << patient->id << ")\n";
        }
        if (doctor) {
            cout << "Doctor: " << doctor->name << " (" << doctor->specialty << ")\n";
        }
        cout << "Appointment ID: " << appt.id << "\n";
        cout << "Date: " << appt.date << "\n";
        cout << "Time: " << appt.time << "\n";
        cout << "Reason: " << appt.reason << "\n";
        cout << "Consultation fee: $" << fixed << setprecision(2) << appt.fee << "\n";
        cout << "Service charge: $" << fixed << setprecision(2) << 0.00 << "\n";
        cout << string(30, '-') << "\n";
        cout << "Total amount due: $" << fixed << setprecision(2) << appt.fee << "\n\n";
    }
    //menu function
    void showMenu() {
        cout << "Hospital Management System\n";
        cout << "1. Add patient\n";
        cout << "2. Add doctor\n";
        cout << "3. List patients\n";
        cout << "4. List doctors\n";
        cout << "5. Schedule appointment\n";
        cout << "6. List appointments\n";
        cout << "7. Search patient\n";
        cout << "8. Search doctor\n";
        cout << "9. Generate bill\n";
        cout << "0. Exit\n";
    }
};

int main() {
    HospitalManagement hospital;
    while (true) {
        hospital.showMenu();
        int choice = HospitalManagement::promptInt("Choose an option: ");

        switch (choice) {
            case 1:
                hospital.addPatient();
                break;
            case 2:
                hospital.addDoctor();
                break;
            case 3:
                hospital.listPatients();
                break;
            case 4:
                hospital.listDoctors();
                break;
            case 5:
                hospital.scheduleAppointment();
                break;
            case 6:
                hospital.listAppointments();
                break;
            case 7:
                hospital.searchPatient();
                break;
            case 8:
                hospital.searchDoctor();
                break;
            case 9:
                hospital.generateBill();
                break;
            case 0:
                cout << "Exiting hospital management system. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid option, please try again.\n\n";
        }
    }

    return 0;
}
