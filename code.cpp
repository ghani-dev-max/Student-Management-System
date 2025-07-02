#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string n = "", int a = 0) : name(n), age(a) {}
    virtual void display() const = 0;
    virtual ~Person() {}
};

class Student : public Person {
    string department;
    float gpa;
public:
    Student(string n = "", int a = 0, string dept = "", float g = 0.0)
        : Person(n, a), department(dept), gpa(g) {}

    void display() const {
        cout << "Student: " << name << ", Age: " << age
             << ", Department: " << department << ", GPA: " << gpa << endl;
    }

    friend bool operator>(const Student& s1, const Student& s2) {
        return s1.gpa > s2.gpa;
    }

    float getGPA() const { return gpa; }
    string getName() const { return name; }

    void saveSummary() const {
        ofstream file("student_summary.txt", ios::app);
        if (file.is_open()) {
            file << "Name: " << name << ", Age: " << age
                 << ", Department: " << department << ", GPA: " << gpa << endl;
            file.close();
            cout << "Summary saved to file.\n";
        } else {
            cout << "Error opening file.\n";
        }
    }
};

class Faculty : public Person {
    string subject;
    double salary;
    static double bonusRate;
public:
    Faculty(string n = "", int a = 0, string subj = "", double s = 0.0)
        : Person(n, a), subject(subj), salary(s) {}

    void display() const {
        cout << "Faculty: " << name << ", Age: " << age
             << ", Subject: " << subject << ", Salary: " << salary << endl;
    }

    void applyBonus() {
        salary += salary * bonusRate;
        cout << "Bonus applied. New salary: " << salary << endl;
    }
};
double Faculty::bonusRate = 0.10;

class ResearchProject {
    string title;
    int duration;
    string lead;
public:
    ResearchProject(string t = "", int d = 0, string l = "")
        : title(t), duration(d), lead(l) {}

    void saveToFile() const {
        ofstream file("project.txt", ios::app);
        if (file.is_open()) {
            file << "Title: " << title << ", Duration: " << duration << " months"
                 << ", Lead: " << lead << endl;
            file.close();
            cout << "Project saved to file.\n";
        } else {
            cout << "Failed to save project.\n";
        }
    }
};

template <typename T>
class PerformanceLogger {
    vector<T> records;
public:
    void log(const T& entry) {
        records.push_back(entry);
    }

    void showAll() const {
        for (const auto& e : records)
            e.display();
    }
};

class InvalidInputException : public runtime_error {
public:
    InvalidInputException(string msg) : runtime_error(msg) {}
};

int main() {
    PerformanceLogger<Student> studentLog;
    Student s1, s2;
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Add Student\n";
        cout << "2. Add Faculty\n";
        cout << "3. Save Research Project\n";
        cout << "4. Compare Students\n";
        cout << "5. Generate Student Summary\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                string name, dept;
                int age;
                float gpa;
                cout << "Enter name, age, department, GPA: ";
                cin >> name >> age >> dept >> gpa;
                s1 = Student(name, age, dept, gpa);
                studentLog.log(s1);
                s1.display();
                break;
            }
            case 2: {
                string name, subject;
                int age;
                double salary;
                cout << "Enter name, age, subject, salary: ";
                cin >> name >> age >> subject >> salary;
                Faculty f(name, age, subject, salary);
                f.applyBonus();
                f.display();
                break;
            }
            case 3: {
                string title, lead;
                int duration;
                cout << "Enter project title, duration (months), and lead: ";
                cin >> title >> duration >> lead;
                ResearchProject p(title, duration, lead);
                p.saveToFile();
                break;
            }
            case 4: {
                string name, dept;
                int age;
                float gpa;
                cout << "Enter second student name, age, department, GPA: ";
                cin >> name >> age >> dept >> gpa;
                s2 = Student(name, age, dept, gpa);
                cout << "Comparing students...\n";
                if (s1 > s2)
                    cout << s1.getName() << " has a higher GPA.\n";
                else
                    cout << s2.getName() << " has a higher GPA.\n";
                break;
            }
            case 5: {
                s1.saveSummary();
                break;
            }
            case 6: {
                cout << "Exiting program.\n";
                break;
            }
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
