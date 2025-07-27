#include <iostream>
#include <string>
using namespace std;

// Forward declaration of CourseHashTable
class CourseHashTable;

// Student class for Singly Linked List
class Student {
public:
    int ID;
    string name;
    string email;
    string phone;
    string address;
    string password;
    Student* next;

    Student(int id, string n, string e, string p, string a, string pw)
        : ID(id), name(n), email(e), phone(p), address(a), password(pw), next(nullptr) {}
};

// Singly Linked List for Student Records
class StudentList {
public:
    Student* head;

    StudentList() : head(nullptr) {}

    bool isStudentExist(int id) {
        Student* temp = head;
        while (temp != nullptr) {
            if (temp->ID == id) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void add() {
        int id;
        string name, email, phone, address, password;

        // Input validation for student ID
        cout << "Enter student ID: ";
        while (!(cin >> id)) {
            cout << "Invalid input! Please enter a valid numeric student ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        if (isStudentExist(id)) {
            cout << "Error: Student with ID " << id << " already exists!" << endl;
            return;
        }

        cout << "Enter student Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter student Email: ";
        getline(cin, email);
        cout << "Enter student Phone: ";
        getline(cin, phone);
        cout << "Enter student Address: ";
        getline(cin, address);
        cout << "Enter student Password: ";
        getline(cin, password);

        Student* newStudent = new Student(id, name, email, phone, address, password);
        newStudent->next = head;
        head = newStudent;
        cout << "Student added successfully!" << endl;
    }

    void deleteStudent() {
        int id;
        cout << "Enter student ID to delete: ";
        while (!(cin >> id)) {
            cout << "Invalid input! Please enter a valid numeric student ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        if (head == nullptr) {
            cout << "Student list is empty!" << endl;
            return;
        }

        Student* temp = head;
        Student* prev = nullptr;

        if (temp != nullptr && temp->ID == id) {
            head = temp->next;
            delete temp;
            cout << "Student with ID " << id << " deleted." << endl;
            return;
        }

        while (temp != nullptr && temp->ID != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Student with ID " << id << " not found!" << endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "Student with ID " << id << " deleted." << endl;
    }

    void display() {
        if (head == nullptr) {
            cout << "No student records available." << endl;
            return;
        }

        Student* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->ID <<endl<< "Name: " << temp->name <<endl <<"Email: " << temp->email
                 <<endl<< "Phone: " << temp->phone << endl<<"Address: " << temp->address << endl;
            temp = temp->next;
        }
    }

    Student* searchStudent(int id) {
        Student* temp = head;
        while (temp != nullptr) {
            if (temp->ID == id) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

// Course class for Binary Search Tree
class Course {
public:
    int CourseID;
    string CourseName;
    int CourseCredits;
    string CourseInstructor;
    Course* left;
    Course* right;

    Course(int id, string name, int credits, string instructor)
        : CourseID(id), CourseName(name), CourseCredits(credits), CourseInstructor(instructor), left(nullptr), right(nullptr) {}
};

// Hash Table for Fast Course Access
class CourseHashTable {
private:
    struct HashNode {
        int courseID;
        Course* course;
        HashNode* next;
    };
    static const int TABLE_SIZE = 100;
    HashNode* table[TABLE_SIZE];

    int hashFunction(int courseID) {
        return courseID % TABLE_SIZE;
    }

public:
    CourseHashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void insert(Course* course) {
        int index = hashFunction(course->CourseID);
        HashNode* newNode = new HashNode{course->CourseID, course, table[index]};
        table[index] = newNode;
    }

    Course* search(int courseID) {
        int index = hashFunction(courseID);
        HashNode* temp = table[index];
        while (temp != nullptr) {
            if (temp->courseID == courseID) {
                return temp->course;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};

// Binary Search Tree for Course Records
class CourseBST {
public:
    Course* root;

    CourseBST() : root(nullptr) {}

    bool isCourseExist(int id) {
        Course* temp = root;
        while (temp != nullptr) {
            if (temp->CourseID == id) {
                return true;
            } else if (id < temp->CourseID) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        return false;
    }

    void addCourse(CourseHashTable& courseHashTable) {
        int id, credits;
        string name, instructor;
        cout << "Enter Course ID: ";
        while (!(cin >> id)) {
            cout << "Invalid input! Please enter a valid numeric course ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        if (isCourseExist(id)) {
            cout << "Error: Course with ID " << id << " already exists!" << endl;
            return;
        }

        cout << "Enter Course Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Course Credits: ";
        while (!(cin >> credits)) {
            cout << "Invalid input! Please enter a valid numeric value for course credits: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Enter Course Instructor: ";
        cin.ignore();
        getline(cin, instructor);

        Course* newCourse = new Course(id, name, credits, instructor);
        root = addCourseRecursive(root, id, name, credits, instructor);
        courseHashTable.insert(newCourse); // Insert the new course into the hash table
        cout << "Course added successfully!" << endl;
    }

    Course* addCourseRecursive(Course* root, int id, string name, int credits, string instructor) {
        if (root == nullptr) {
            return new Course(id, name, credits, instructor);
        }

        if (id < root->CourseID) {
            root->left = addCourseRecursive(root->left, id, name, credits, instructor);
        } else {
            root->right = addCourseRecursive(root->right, id, name, credits, instructor);
        }

        return root;
    }

    void dropCourse() {
        int id;
        cout << "Enter Course ID to drop: ";
        while (!(cin >> id)) {
            cout << "Invalid input! Please enter a valid numeric course ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        root = dropCourseRecursive(root, id);
        cout << "Course with ID " << id << " dropped." << endl;
    }

    Course* dropCourseRecursive(Course* root, int id) {
        if (root == nullptr) {
            cout << "Course not found!" << endl;
            return root;
        }

        if (id < root->CourseID) {
            root->left = dropCourseRecursive(root->left, id);
        } else if (id > root->CourseID) {
            root->right = dropCourseRecursive(root->right, id);
        } else {
            if (root->left == nullptr) {
                Course* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Course* temp = root->left;
                delete root;
                return temp;
            }

            Course* temp = findMin(root->right);
            root->CourseID = temp->CourseID;
            root->CourseName = temp->CourseName;
            root->CourseCredits = temp->CourseCredits;
            root->CourseInstructor = temp->CourseInstructor;
            /// i don't understand this next line !!
            root->right = dropCourseRecursive(root->right, temp->CourseID);
        }

        return root;
    }

    Course* findMin(Course* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    void displayCourses() {
        inOrderTraversal(root);
    }

    void inOrderTraversal(Course* root) {
        if (root != nullptr) {
            inOrderTraversal(root->left);
            cout << "Course ID: " << root->CourseID << ", Name: " << root->CourseName
                 << ", Credits: " << root->CourseCredits << ", Instructor: " << root->CourseInstructor << endl;
            inOrderTraversal(root->right);
        }
    }

    Course* searchCourse(int id) {
        Course* temp = root;
        while (temp != nullptr) {
            if (temp->CourseID == id) {
                return temp;
            } else if (id < temp->CourseID) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        return nullptr;
    }
};

// Enrollment class for Doubly Linked List
class Enrollment {
public:
    int studentID;
    int courseID;
    Enrollment* prev;
    Enrollment* next;

    Enrollment(int sID, int cID) : studentID(sID), courseID(cID), prev(nullptr), next(nullptr) {}
};

// Doubly Linked List for Enrollment History
class EnrollmentHistory {
public:
    Enrollment* head;
    Enrollment* tail;

    EnrollmentHistory() : head(nullptr), tail(nullptr) {}

    void add() {
        int studentID, courseID;
        cout << "Enter Student ID: ";
        while (!(cin >> studentID)) {
            cout << "Invalid input! Please enter a valid numeric student ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        cout << "Enter Course ID: ";
        while (!(cin >> courseID)) {
            cout << "Invalid input! Please enter a valid numeric course ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        Enrollment* newEnrollment = new Enrollment(studentID, courseID);
        if (head == nullptr) {
            head = tail = newEnrollment; 
        } else {
            tail->next = newEnrollment;
            newEnrollment->prev = tail;
            tail = newEnrollment;
        }

        cout << "Enrollment added successfully!" << endl;
    }

    void view() {
        int studentID;
        cout << "Enter Student ID to view enrollment history: ";
        while (!(cin >> studentID)) {
            cout << "Invalid input! Please enter a valid numeric student ID: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        Enrollment* temp = head;
        bool found = false;
        while (temp != nullptr) {
            if (temp->studentID == studentID) {
                cout << "Student ID: " << temp->studentID << ", Course ID: " << temp->courseID << endl;
                found = true;
            }
            temp = temp->next;
        }

        if (!found) {
            cout << "No enrollment records found for Student ID " << studentID << endl;
        }
    }
};

// Stack for Course Prerequisites
class PrerequisiteStack {
private:
    struct Node {
        int courseID;
        Node* next;
    };
    Node* top;

public:
    PrerequisiteStack() : top(nullptr) {}

    void push(int courseID) {
        Node* newNode = new Node{courseID, top};
        top = newNode;
    }

    void pop() {
        if (top == nullptr) {
            cout << "Stack is empty!" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void displayRemaining() {
        if (top == nullptr) {
            cout << "No remaining prerequisites." << endl;
            return;
        }
        Node* temp = top;
        cout << "Remaining prerequisites: ";
        while (temp != nullptr) {
            cout << temp->courseID << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Queue for Course Waitlist
class WaitlistQueue {
private:
    struct Node {
        int studentID;
        Node* next;
    };
    Node* front;
    Node* rear;

public:
    WaitlistQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(int studentID) {
        Node* newNode = new Node{studentID, nullptr};
        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (front == nullptr) {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int getFront() {
        if (front == nullptr) {
            return -1;
        }
        return front->studentID;
    }

    void displayWaitlist() {
        if (front == nullptr) {
            cout << "Waitlist is empty!" << endl;
            return;
        }
        Node* temp = front;
        cout << "Waitlist: ";
        while (temp != nullptr) {
            cout << temp->studentID << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// Main program
int main() {
    StudentList studentList;
    CourseBST courseBST;
    EnrollmentHistory enrollmentHistory;
    PrerequisiteStack prerequisiteStack;
    WaitlistQueue waitlistQueue;
    CourseHashTable courseHashTable;
    int choice;

    do {
        cout << "1. Student Records Management (Singly Linked List)" << endl;
        cout << "2. Course Records Management (Binary Search Tree)" << endl;
        cout << "3. Course Enrollment History (Doubly Linked List)" << endl;
        cout << "4. Course Registration (Stack)" << endl;
        cout << "5. Course Waitlist (Queue)" << endl;
        cout << "6. Search and Sort Operations" << endl;
        cout << "7. Fast Access Using Hashing" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int studentChoice;
                do {
                    cout << "1. Add Student" << endl;
                    cout << "2. Delete Student" << endl;
                    cout << "3. Display All Students" << endl;
                    cout << "4. Back" << endl;
                    cout << "Enter your choice: ";
                    cin >> studentChoice;

                    switch (studentChoice) {
                        case 1:
                            studentList.add();
                            break;
                        case 2:
                            studentList.deleteStudent();
                            break;
                        case 3:
                            studentList.display();
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                    }
                } while (studentChoice != 4);
                break;
            }
            case 2: {
                int courseChoice;
                do {
                    cout << "1. Add Course" << endl;
                    cout << "2. Drop Course" << endl;
                    cout << "3. Display All Courses" << endl;
                    cout << "4. Back" << endl;
                    cout << "Enter your choice: ";
                    cin >> courseChoice;

                    switch (courseChoice) {
                        case 1:
                            courseBST.addCourse(courseHashTable); // Pass the hash table here
                            break;
                        case 2:
                            courseBST.dropCourse();
                            break;
                        case 3:
                            courseBST.displayCourses();
                            break;
                        case 4:
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                    }
                } while (courseChoice != 4);
                break;
            }
            case 3: {
                int enrollmentChoice;
                do {
                    cout << "1. Add Enrollment" << endl;
                    cout << "2. View Enrollment History" << endl;
                    cout << "3. Back" << endl;
                    cout << "Enter your choice: ";
                    cin >> enrollmentChoice;

                    switch (enrollmentChoice) {
                        case 1:
                            enrollmentHistory.add();
                            break;
                        case 2:
                            enrollmentHistory.view();
                            break;
                        case 3:
                            break;
                        default:
                            cout << "Invalid choice!" << endl;
                    }
                } while (enrollmentChoice != 3);
                break;
            }
            case 4: {
                int courseID, studentID;
                cout << "Enter Course ID: ";
                cin >> courseID;
                cout << "Enter Student ID: ";
                cin >> studentID;

                // Simulate prerequisites (e.g., course 101 requires 100)
                prerequisiteStack.push(100); // Example prerequisite
                prerequisiteStack.push(101); // Example prerequisite

                // Check prerequisites
                if (prerequisiteStack.isEmpty()) {
                    cout << "Student is eligible to register for the course." << endl;
                } else {
                    cout << "Student is not eligible. Remaining prerequisites:" << endl;
                    prerequisiteStack.displayRemaining();
                }
                break;
            }
            case 5: {
                int waitlistChoice;
                do {
                    cout << "1. Add Student to Waitlist" << endl;
                    cout << "2. Dequeue Student from Waitlist" << endl;
                    cout << "3. Display Waitlist" << endl;
                    cout << "4. Back" << endl;
                    cout << "Enter your choice: ";
                    cin >> waitlistChoice;

                    switch (waitlistChoice) {
                        case 1: {
                            int studentID;
                            cout << "Enter Student ID to add to waitlist: ";
                            cin >> studentID;
                            waitlistQueue.enqueue(studentID);
                            cout << "Student added to waitlist." << endl;
                            break;
                        }
                        case 2: {
                            if (!waitlistQueue.isEmpty()) {
                                cout << "Dequeuing student ID: " << waitlistQueue.getFront() << endl;
                                waitlistQueue.dequeue();
                            } else {
                                cout << "Waitlist is empty!" << endl;
                            }
                            break;
                        }
                        case 3: {
                            waitlistQueue.displayWaitlist();
                            break;
                        }
                        case 4: {
                            break;
                        }
                        default: {
                            cout << "Invalid choice!" << endl;
                        }
                    }
                } while (waitlistChoice != 4);
                break;
            }
            case 6: {
                int searchSortChoice;
                cout << "1. Search Student by ID" << endl;
                cout << "2. Search Course by ID" << endl;
                cout << "3. Sort Students by ID" << endl;
                cout << "4. Sort Courses by ID" << endl;
                cout << "Enter your choice: ";
                cin >> searchSortChoice;

                switch (searchSortChoice) {
                    case 1: {
                        // Search Student by ID
                        int studentID;
                        cout << "Enter Student ID: ";
                        cin >> studentID;
                        Student* student = studentList.searchStudent(studentID);
                        if (student != nullptr) {
                            cout << "Student found: " << student->name << endl;
                        } else {
                            cout << "Student not found!" << endl;
                        }
                        break;
                    }
                    case 2: {
                        // Search Course by ID
                        int courseID;
                        cout << "Enter Course ID: ";
                        cin >> courseID;
                        Course* course = courseBST.searchCourse(courseID);
                        if (course != nullptr) {
                            cout << "Course found: " << course->CourseName << endl;
                        } else {
                            cout << "Course not found!" << endl;
                        }
                        break;
                    }
                    case 3: {
                        // Sort Students by ID
                        if (studentList.head == nullptr) {
                            cout << "No students to sort!" << endl;
                            break;
                        }

                        // Convert the linked list to an array for sorting
                        int count = 0;
                        Student* temp = studentList.head;
                        while (temp != nullptr) {
                            count++;
                            temp = temp->next;
                        }

                        Student** studentsArray = new Student*[count];
                        temp = studentList.head;
                        for (int i = 0; i < count; i++) {
                            studentsArray[i] = temp;
                            temp = temp->next;
                        }

                        // Sort the array by student ID (ascending order)
                        for (int i = 0; i < count - 1; i++) {
                            for (int j = 0; j < count - i - 1; j++) {
                                if (studentsArray[j]->ID > studentsArray[j + 1]->ID) {
                                    swap(studentsArray[j], studentsArray[j + 1]);
                                }
                            }
                        }

                        // Display sorted students
                        cout << "Students sorted by ID (ascending order):" << endl;
                        for (int i = 0; i < count; i++) {
                            cout << "ID: " << studentsArray[i]->ID << ", Name: " << studentsArray[i]->name << endl;
                        }

                        delete[] studentsArray;
                        break;
                    }
                    case 4: {
                        // Sort Courses by ID
                        if (courseBST.root == nullptr) {
                            cout << "No courses to sort!" << endl;
                            break;
                        }

                        // Perform in-order traversal to get courses in sorted order
                        cout << "Courses sorted by ID (ascending order):" << endl;
                        courseBST.displayCourses(); // In-order traversal already displays sorted courses
                        break;
                    }
                    default: {
                        cout << "Invalid choice!" << endl;
                    }
                }
                break;
            }
            case 7: {
                int courseID;
                cout << "Enter Course ID to search: ";
                cin >> courseID;
                Course* course = courseHashTable.search(courseID);
                if (course != nullptr) {
                    cout << "Course found: " << course->CourseName << endl;
                } else {
                    cout << "Course not found!" << endl;
                }
                break;
            }
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 8);

    return 0;
}