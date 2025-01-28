#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>  // For setting precision of GPA output
using namespace std;

// Define a structure to represent student data
struct Student {
    int textID;
    string name;
    int age;
    string major;
    double GPA;
};

// Function to read students from a CSV file
vector<Student> readStudentsFromCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);  // Open the file for reading
    
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return students;
    }

    string line;
    getline(file, line);  // Skip the header line

    // Read the data for each student
    while (getline(file, line)) {
        stringstream ss(line);
        Student student;
        string field;

        // Read each field and assign to corresponding attributes
        getline(ss, field, ','); student.textID = stoi(field);
        getline(ss, field, ','); student.name = field;
        getline(ss, field, ','); student.age = stoi(field);
        getline(ss, field, ','); student.major = field;
        getline(ss, field, ','); student.GPA = stod(field);

        students.push_back(student);  // Add student to the vector
    }

    file.close();  // Close the file after reading
    return students;
}

// Function to filter students based on GPA
vector<Student> filterByGPA(const vector<Student>& students, double minGPA) {
    vector<Student> filteredStudents;
    for (const auto& student : students) {
        if (student.GPA >= minGPA) {
            filteredStudents.push_back(student);
        }
    }
    return filteredStudents;
}

// Function to calculate the average age of students
double calculateAverageAge(const vector<Student>& students) {
    double totalAge = 0;
    for (const auto& student : students) {
        totalAge += student.age;
    }
    return students.empty() ? 0.0 : totalAge / students.size();
}

// Function to write filtered students to a CSV file
void writeStudentsToCSV(const vector<Student>& students, const string& filename) {
    ofstream file(filename);  // Open the file for writing
    
    if (!file.is_open()) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    file << "textID,Name,Age,Major,GPA\n";  // Write the header
    for (const auto& student : students) {
        file << student.textID << ","
             << student.name << ","
             << student.age << ","
             << student.major << ","
             << fixed << setprecision(2) << student.GPA << "\n";  // Set GPA precision
    }

    file.close();  // Close the file after writing
}

int main() {
    // Read students from the CSV file
    vector<Student> students = readStudentsFromCSV("student.csv");

    // Filter students by GPA (e.g., students with GPA >= 3.0)
    vector<Student> filteredStudents = filterByGPA(students, 3.0);

    // Calculate the average age of all students
    double avgAge = calculateAverageAge(students);
    cout << "Average Age: " << avgAge << endl;

    // Write the filtered students to a new CSV file
    writeStudentsToCSV(filteredStudents, "filtered_students.csv");

    return 0;
}
