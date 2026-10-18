//======================================================
// Hannah Beyersdorf
// October 18, 2025
// CS300 Project 2
//======================================================

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Course {
	string courseNumber;
	string courseTitle;
	vector<string> prerequisites;
};
vector<Course> courses;

void loadData() { // loads data from the provided csv file
	string line;
	string fileName;
    fileName = "CS 300 ABCU_Advising_Program_Input.csv";
	ifstream file(fileName); // to open the file


	if (!file.is_open()) {  // error message if file isn't opened successfully
		cout << "File unable to be opened" << endl;
		return;
	}
	if (file.is_open()) {
		while (getline(file, line)) {
			vector<string> tokens;
			string token;
			stringstream ss(line);
			while (getline(ss, token, ',')) {
				tokens.push_back(token);
			}
			if (tokens.size() < 2) {
				cout << "Error" << line << endl;
				continue;

			}
			string courseNumber = tokens[0]; // adds course title and course number
			string courseTitle = tokens[1];

			vector<string> prerequisites;
			for (size_t i = 2; i < tokens.size(); ++i) {
				prerequisites.push_back(tokens[i]);
			}

			Course newCourse;
			newCourse.courseNumber = courseNumber;
			newCourse.courseTitle = courseTitle;
			newCourse.prerequisites = prerequisites;
			courses.push_back(newCourse);
		}

		file.close();
	}
}

bool validateCourse(vector<Course> courses) { // checks if course is valid in list
		bool valid = true;
		for (Course& course : courses) {
			for (string& prereq : course.prerequisites) {
				bool found = false;
				for (Course& allCourses : courses) {
					if (allCourses.courseNumber == prereq) {
						found = true;
						break;
					}
				}
				if (!found) {
					valid = false;
					break;
				}
			}
		}
		return valid;
	}
	
void printCourseList() { // prints course list
	cout << "Course List:" << endl;
	for (const Course& course : courses) {
		cout << course.courseNumber << ": " << course.courseTitle << endl;
	}
}
void printCourse(const string& courseNumber) {
	bool found = false;
	for (Course& course : courses) {
		if (course.courseNumber == courseNumber) {
			found = true;
			cout << "Course: " << course.courseTitle << ": " << course.courseNumber << endl;
			cout << "Prerequisites: ";
			if (course.prerequisites.empty()) {
				cout << "None" << endl;
			}
			else {
				for (const string& prereq : course.prerequisites) {
					cout << prereq << " ";
				}
				cout << endl;
			}
			break;
		}
	}
	if (!found) {
		cout << "Course could not be found." << endl;
	}
}
void displayMenu() { // displays menu choices
	int choice = 0;
	while (choice != 9) {
		cout << "1. Load Data" << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl;
		cout << "Please make a selection: ";
		cin >> choice;

		if (choice == 1) {
			loadData();
		}
		else if (choice == 2) {
			printCourseList();
		}
		else if (choice == 3) {
			string courseNumber;
			cout << "Enter course number: ";
			cin >> courseNumber;
			printCourse(courseNumber);
		}
		else if (choice == 9) {
			cout << "Thank you for using the course planner!." << endl; // exit message
			return;
		}
		else {
			cout << "Invalid. Please try again." << endl; // error for invalid input selection
		}

	}
}
int main() {
	displayMenu();
}
