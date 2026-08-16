
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

struct Student {
    int id;
    std::string name;
    std::string major;
    double gpa;
};

void addStudent(std::vector<Student>& students);
void displayStudents(const std::vector<Student>& students);
void searchStudent(const std::vector<Student>& students);
void deleteStudent(std::vector<Student>& students);
void saveStudents(const std::vector<Student>& students);
void loadStudents(std::vector<Student>& students);

int main()
{
    std::vector<Student> students;
    loadStudents(students);
    
    int choice;

    //having the user pick an option from the menu on what they would like to acomplish
    do {
        std::cout << "Student Database Menu:" << std::endl;
        std::cout << "1. Add Student" << std::endl;
        std::cout << "2. View Students" << std::endl;
        std::cout << "3. Search Student" << std::endl;
        std::cout << "4. Delete Student" << std::endl;
        std::cout << "5. Save Students" << std::endl;
        std::cout << "6. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                displayStudents(students);
                break;
            case 3:
                searchStudent(students);
                break;
            case 4:
                deleteStudent(students);
                break;
            case 5:
                saveStudents(students);
                break;
            case 6:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 6);

    return 0;
}

        //add new student
        void addStudent(std::vector<Student>& students) {
            Student newStudent;

            std::cout << "\nEnter Student ID: ";
            std::cin >> newStudent.id;

            std::cin.ignore(); // Ignore the newline character

            std::cout << "Enter Student Name: ";
            std::getline(std::cin, newStudent.name);

            std::cout << "Enter Student Major: ";
            std::getline(std::cin, newStudent.major);

            std::cout << "Enter Student GPA: ";
            std::cin >> newStudent.gpa;

            students.push_back(newStudent);
            std::cout << "\nStudent added successfully!\n";
        }

        //display all students
        void displayStudents(const std::vector<Student>& students) {
            if (students.empty()) {
                std::cout << "\nNo students found.\n";
                return;
            }

            std::cout << "\n===Student List===\n";
            std::cout << std::left 
                      << std::setw(10) << "ID" 
                      << std::setw(20) << "Name" 
                      << std::setw(20) << "Major" 
                      << std::setw(10) << "GPA" 
                      << std::endl;

            std::cout << std::string(60, '-') << std::endl;


            for (const Student& student : students) {
                std::cout << std::left << std::setw(10) << student.id
                          << std::setw(20) << student.name
                          << std::setw(20) << student.major
                          << std::setw(10) << std::fixed << std::setprecision(2) << student.gpa
                          << std::endl;
            }

        }

        //search for a student
        void searchStudent(const std::vector<Student>& students) {
            int id;

            std::cout << "\nEnter Student ID to search: ";
            std::cin >> id;

            for (const Student& student : students) {
                if (student.id == id) 
                {
                    std::cout << "\nStudent Found:\n";
                    std::cout << "ID: " << student.id << std::endl;
                    std::cout << "Name: " << student.name << std::endl;
                    std::cout << "Major: " << student.major << std::endl;
                    std::cout << "GPA: " << std::fixed << std::setprecision(2) << student.gpa << std::endl;
                    return;
                }
            }
            std::cout << "\nStudent not found.\n";
        }

        //delete a student
        void deleteStudent(std::vector<Student>& students) {
            int id;

            std::cout << "\nEnter Student ID to delete: ";
            std::cin >> id;

            for (auto it = students.begin(); it != students.end(); ++it) {
                if (it->id == id) {
                    students.erase(it);
                    std::cout << "\nStudent deleted successfully!\n";
                    return;
                }
            }
            std::cout << "\nStudent not found.\n";
        }

        //save students to a file
        void saveStudents(const std::vector<Student>& students) {
            std::ofstream file("students.txt");

            if (!file) {
                std::cout << "\nError opening file for writing.\n";
                return;
            }

            for (const Student& student : students) {
                file << student.id << "|";
                file << student.name << "|";
                file << student.major << "|";
                file << student.gpa << std::endl;
            }

            file.close();

            std::cout << "\nStudents saved to file successfully!\n";
        }

        //load students from a file
        void loadStudents(std::vector<Student>& students) {
            students.clear();
            std::ifstream file("students.txt");

            if (!file) {
                return;
            }

            Student student;
            std::string line;

            while (getline(file, line)) {
                size_t first = line.find('|');
                size_t second = line.find('|', first + 1);  
                size_t third = line.find('|', second + 1);
                
                student.id = stoi(line.substr(0, first));
                student.name = line.substr(first + 1, second - first - 1);
                student.major = line.substr(second + 1, third - second - 1);
                student.gpa = stod(line.substr(third + 1));

                students.push_back(student);
            }
            file.close();
    }