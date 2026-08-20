/*
 * ProjectTwo.cpp
 *
 *  Created on: Aug 8, 2026
 *      Author: Administrator
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Stores the information for one course
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Loads course data from the input file into the vector
bool loadCourses(string fileName, vector<Course>& courses) {
	ifstream file(fileName.c_str());

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return false;
    }

    courses.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string item;
        vector<string> values;

        while (getline(ss, item, ',')) {
            values.push_back(item);
        }

        // Each line must contain at least a course number and title
        if (values.size() < 2) {
            cout << "Invalid file format." << endl;
            file.close();
            return false;
        }

        Course course;
        course.courseNumber = values[0];
        course.courseTitle = values[1];

        // Any remaining values are prerequisites
        for (size_t i = 2; i < values.size(); ++i) {
            course.prerequisites.push_back(values[i]);
        }

        courses.push_back(course);
    }

    file.close();
    cout << courses.size() << " courses loaded." << endl;
    return true;
}

// Compares course numbers for alphanumeric sorting
bool compareCourses(const Course& a, const Course& b) {
    return a.courseNumber < b.courseNumber;
}

// Sorts and prints all courses in alphanumeric order
void printCourseList(vector<Course> courses) {
    sort(courses.begin(), courses.end(), compareCourses);

    cout << "Here is a sample schedule:" << endl;

    for (size_t i = 0; i < courses.size(); ++i) {
        cout << courses[i].courseNumber << ", "
             << courses[i].courseTitle << endl;
    }
}

// Searches for and prints information about one course
void printCourseInformation(const vector<Course>& courses, string courseNumber) {
    for (const Course& course : courses) {
        if (course.courseNumber == courseNumber) {
            cout << course.courseNumber << ", "
                 << course.courseTitle << endl;

            cout << "Prerequisites: ";

            if (course.prerequisites.empty()) {
                cout << "None" << endl;
            } else {
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    string prerequisiteNumber = course.prerequisites[i];

                    // Find the prerequisite course title
                    for (const Course& prerequisite : courses) {
                        if (prerequisite.courseNumber == prerequisiteNumber) {
                            cout << prerequisite.courseNumber << ", "
                                 << prerequisite.courseTitle;

                            if (i < course.prerequisites.size() - 1) {
                                cout << "; ";
                            }
                            break;
                        }
                    }
                }
                cout << endl;
            }

            return;
        }
    }

    cout << "Course not found." << endl;
}

int main() {
    vector<Course> courses;
    int choice = 0;
    string fileName;
    string courseNumber;
    bool dataLoaded = false;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << endl;
        cout << "What would you like to do? ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter 1, 2, 3, or 9." << endl;
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter the file name: ";
            cin.ignore(10000, '\n');
            getline(cin, fileName);

            dataLoaded = loadCourses(fileName, courses);
            break;

        case 2:
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            } else {
                printCourseList(courses);
            }
            break;

        case 3:
            if (!dataLoaded) {
                cout << "Please load the course data first." << endl;
            } else {
                cout << "What course do you want to know about? ";
                cin >> courseNumber;

                printCourseInformation(courses, courseNumber);
            }
            break;

        case 9:
            cout << "Thank you for using the course planner!" << endl;
            break;

        default:
            cout << choice << " is not a valid option." << endl;
            break;
        }
    }

    return 0;
}
