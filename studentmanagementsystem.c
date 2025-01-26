#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LEN 100
#define MAX_BRANCH_LEN 20
#define MAX_DIVISION_LEN 10
#define MAX_DAYS_IN_MONTH 30
#define MAX_HOLIDAYS 10
#define USER_ID "admin"   // Hardcoded User ID
#define PASSWORD "1234"   // Hardcoded Password

// Student structure
typedef struct {
    char name[MAX_NAME_LEN];
    int roll_no;
    char branch[MAX_BRANCH_LEN];
    int year;
    char division[MAX_DIVISION_LEN];
    int attendance[MAX_DAYS_IN_MONTH];  // Attendance for each day of the month (30 days)
    float fees_paid;
    float total_fees;
} Student;

Student students[MAX_STUDENTS];
int total_students = 0;
int holidays[MAX_HOLIDAYS]; // Array to store holidays
int total_holidays = 0;

// Function to convert string to lowercase
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Function to authenticate the user with User ID and Password
int authenticateUser () {
    char user_id[MAX_NAME_LEN], password[MAX_NAME_LEN];
    
    printf("Enter User ID: ");
    scanf("%s", user_id);
    
    printf("Enter Password: ");
    scanf("%s", password);
    
    if (strcmp(user_id, USER_ID) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("\nAuthentication successful! Welcome to the Student Management System.\n");
        return 1;
    } else {
        printf("\nInvalid User ID or Password. Access Denied.\n");
        return 0;
    }
}

// Function to display instructions
void displayInstructions() {
    printf("\n--- Instructions ---\n");
    printf("1. You must log in with a valid User ID and Password before using the system.\n");
    printf("2. After successful login, you will be able to add students, mark attendance, manage fees, etc.\n");
    printf("3. Choose options from the menu to perform operations on student data.\n");
    printf("4. After performing an operation, the system will show relevant information.\n");
    printf("5. To exit the program, select option '8'.\n");
    printf("\n--- End of Instructions ---\n");
}

// Function to add a student to the system
void addStudent() {
    if (total_students >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }

    Student new_student;
    
    printf("Enter Student Name: ");
    getchar(); // To consume the newline character
    fgets(new_student.name, MAX_NAME_LEN, stdin);
    new_student.name[strcspn(new_student.name, "\n")] = 0; // Remove newline

    printf("Enter Roll Number: ");
    scanf("%d", &new_student.roll_no);

    printf("Enter Branch: ");
    getchar(); // To consume the newline character
    fgets(new_student.branch, MAX_BRANCH_LEN, stdin);
    new_student.branch[strcspn(new_student.branch, "\n")] = 0; // Remove newline
    toLowerCase(new_student.branch); // Convert to lowercase

    printf("Enter Year: ");
    scanf("%d", &new_student.year);

    printf("Enter Division: ");
    getchar(); // To consume the newline character
    fgets(new_student.division, MAX_DIVISION_LEN, stdin);
    new_student.division[strcspn(new_student.division, "\n")] = 0; // Remove newline
    toLowerCase(new_student.division); // Convert to lowercase

    printf("Enter Total Fees: ");
    scanf("%f", &new_student.total_fees);

    new_student.fees_paid = 0; // Initial fees paid is 0
    memset(new_student.attendance, 0, sizeof(new_student.attendance)); // Initialize all attendance to 0

    students[total_students++] = new_student;

    printf("Student added successfully!\n");
}

// Function to add official holidays
void addHoliday() {
    if (total_holidays >= MAX_HOLIDAYS) {
        printf("Holiday limit reached!\n");
        return;
    }

    int holiday;
    printf("Enter the day of the holiday (1-30): ");
    scanf("%d", &holiday);

    if (holiday >= 1 && holiday <= 30) {
        holidays[total_holidays++] = holiday;
        printf("Holiday added successfully!\n");
    } else {
        printf("Invalid day. Please enter a day between 1 and 30.\n");
    }
}

// Function to check if a day is a holiday
int isHoliday(int day) {
    for (int i = 0; i < total_holidays; i++) {
        if (holidays[i] == day) {
            return 1; // It's a holiday
        }
    }
    return 0; // Not a holiday
}

// Function to mark attendance for a single student
void markAttendanceSingle() {
    int roll_no, year;
    char branch[MAX_BRANCH_LEN], division[MAX_DIVISION_LEN];
    int day;

    printf("Enter Year: ");
    scanf("%d", &year);

    printf("Enter Branch: ");
    getchar(); // To consume newline
    fgets(branch, MAX_BRANCH_LEN, stdin);
    branch[strcspn(branch, "\n")] = 0;
    toLowerCase(branch); // Convert to lowercase

    printf("Enter Division: ");
    fgets(division, MAX_DIVISION_LEN, stdin);
    division[strcspn(division, "\n")] = 0;
    toLowerCase(division); // Convert to lowercase

    printf("Enter Roll Number: ");
    scanf("%d", &roll_no);

    // Find the student
    int found = 0;
    for (int i = 0; i < total_students; i++) {
        if (students[i].roll_no == roll_no && students[i].year == year &&
            strcmp(students[i].branch, branch) == 0 && strcmp(students[i].division, division) == 0) {
            found = 1;
            printf("Enter the day (1-30) to mark attendance (1 for present, 0 for absent): ");
            scanf("%d", &day);
            if (day >= 1 && day <= MAX_DAYS_IN_MONTH) {
                if (isHoliday(day)) {
                    printf("Attendance cannot be marked on a holiday.\n");
                } else {
                    printf("Marking attendance for day %d...\n", day);
                    printf("Is the student present? (1 for present, 0 for absent): ");
                    scanf("%d", &students[i].attendance[day - 1]);
                }
            } else {
                printf("Invalid day.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Student not found!\n");
    }
}

// Function to mark attendance for multiple students in a class
void markAttendanceMultiple() {
    int year;
    char branch[MAX_BRANCH_LEN], division[MAX_DIVISION_LEN];
    int num_present, roll_no;

    printf("Enter Year: ");
    scanf("%d", &year);

    printf("Enter Branch: ");
    getchar(); // To consume newline
    fgets(branch, MAX_BRANCH_LEN, stdin);
    branch[strcspn(branch, "\n")] = 0;
    toLowerCase(branch); // Convert to lowercase

    printf("Enter Division: ");
    fgets(division, MAX_DIVISION_LEN, stdin);
    division[strcspn(division, "\n")] = 0;
    toLowerCase(division); // Convert to lowercase

    printf("Enter the number of present students: ");
    scanf("%d", &num_present);

    int present_rolls[num_present];
    printf("Enter roll numbers of present students: ");
    for (int i = 0; i < num_present; i++) {
        scanf("%d", &present_rolls[i]);
    }

    // Find and mark attendance
    for (int i = 0; i < total_students; i++) {
        if (students[i].year == year && strcmp(students[i].branch, branch) == 0 &&
            strcmp(students[i].division, division) == 0) {
            int is_present = 0;
            for (int j = 0; j < num_present; j++) {
                if (students[i].roll_no == present_rolls[j]) {
                    is_present = 1;
                    break;
                }
            }
            // Mark attendance
            if (!isHoliday(1)) { // For simplicity, assume marking attendance for day 1
                students[i].attendance[0] = is_present ? 1 : 0;
            } else {
                printf("Attendance cannot be marked on a holiday.\n");
            }
        }
    }
    printf("Attendance marked!\n");
}

// Function to view defaulter students
void viewDefaulterStudents() {
    printf("Defaulter Students (Attendance < 75%%):\n");

    for (int i = 0; i < total_students; i++) {
        int total_days = MAX_DAYS_IN_MONTH; // Assuming the month has 30 days
        int present_days = 0;
        
        for (int j = 0; j < total_days; j++) {
            if (students[i].attendance[j] == 1 && !isHoliday(j + 1)) { // Check if not a holiday
                present_days++;
            }
        }

        float attendance_percentage = (float)present_days / (total_days - total_holidays) * 100; // Adjust for holidays
        if (attendance_percentage < 75) {
            printf("Name: %s, Roll No: %d, Attendance: %.2f%%\n", students[i].name, students[i].roll_no, attendance_percentage);
        }
    }
}

// Function to view fees status of a student
void viewFeesStatus() {
    int roll_no;
    printf("Enter Roll Number: ");
    scanf("%d", &roll_no);

    for (int i = 0; i < total_students; i++) {
        if (students[i].roll_no == roll_no) {
            float remaining_fees = students[i].total_fees - students[i].fees_paid;
            printf("Name: %s\n", students[i].name);
            printf("Roll No: %d\n", students[i].roll_no);
            printf("Branch: %s\n", students[i].branch);
            printf("Year: %d\n", students[i].year);
            printf("Division: %s\n", students[i].division);
            printf("Total Fees: %.2f\n", students[i].total_fees);
            printf("Fees Paid: %.2f\n", students[i].fees_paid);
            printf("Remaining Fees: %.2f\n", remaining_fees);
            return;
        }
    }
    printf("Student not found!\n");
}

// Function to manage the fees (update fees paid)
void manageFees() {
    int roll_no;
    char branch[MAX_BRANCH_LEN], division[MAX_BRANCH_LEN];
    char mode_of_payment[MAX_NAME_LEN];

    printf("Enter Roll Number: ");
    scanf("%d", &roll_no);

    printf("Enter Branch: ");
    getchar(); // To consume newline
    fgets(branch, MAX_BRANCH_LEN, stdin);
    branch[strcspn(branch, "\n")] = 0; // Remove newline
    toLowerCase(branch); // Convert to lowercase

    printf("Enter Division: ");
    fgets(division, MAX_DIVISION_LEN, stdin);
    division[strcspn(division, "\n")] = 0; // Remove newline
    toLowerCase(division); // Convert to lowercase

    for (int i = 0; i < total_students; i++) {
        if (students[i].roll_no == roll_no && strcmp(students[i].branch, branch) == 0 &&
            strcmp(students[i].division, division) == 0) {
            printf("Enter Fees Paid: ");
            float fees_paid;
            scanf("%f", &fees_paid);

            printf("Enter Mode of Payment (e.g., Cash, Card, Online): ");
            getchar(); // To consume newline
            fgets(mode_of_payment, MAX_NAME_LEN, stdin);
            mode_of_payment[strcspn(mode_of_payment, "\n")] = 0; // Remove newline

            students[i].fees_paid += fees_paid; // Update fees paid
            printf("Fees updated successfully!");
            printf("\nMode of Payment: %s\n", mode_of_payment);
            return;
        }
    }
    printf("Student not found!\n");
}

// Function to view all students' data
void viewAllStudentsData() {
    for (int i = 0; i < total_students; i++) {
        printf("Name: %s\n", students[i].name);
        printf("Roll No: %d\n", students[i].roll_no);
        printf("Branch: %s\n", students[i].branch);
        printf("Year: %d\n", students[i].year);
        printf("Division: %s\n", students[i].division);

        // Calculate attendance percentage
        int total_days = MAX_DAYS_IN_MONTH; // Assuming 30 days in a month
        int present_days = 0;
        for (int j = 0; j < total_days; j++) {
            if (students[i].attendance[j] == 1 && !isHoliday(j + 1)) { // Check if not a holiday
                present_days++;
            }
        }
        float attendance_percentage = (float)present_days / (total_days - total_holidays) * 100; // Adjust for holidays

        printf("Attendance: %.2f%%\n", attendance_percentage);
        printf("Fees Paid: %.2f\n", students[i].fees_paid);
        printf("Total Fees: %.2f\n", students[i].total_fees);
        printf("Remaining Fees: %.2f\n\n", students[i].total_fees - students[i].fees_paid);
    }
}

// Function to exit the program
void exitProgram() {
    printf("Exiting the program...\n");
    exit(0);
}

// Main function to display menu and call appropriate functions
int main() {
    if (!authenticateUser ()) {
        return 0;  // Exit if authentication fails
    }

    // Display instructions after login
    displayInstructions();

    int choice;
    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Add Official Holiday\n");
        printf("3. Mark Attendance for Single Student\n");
        printf("4. Mark Attendance for Multiple Students\n");
        printf("5. View Defaulter Students\n");
        printf("6. View Fees Status\n");
        printf("7. Manage Fees\n");
        printf("8. View All Students Data\n");
        printf("9. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                addHoliday();
                break;
            case 3:
                markAttendanceSingle();
                break;
            case 4:
                markAttendanceMultiple();
                break;
            case 5:
                viewDefaulterStudents();
                break;
            case 6:
                viewFeesStatus();
                break;
            case 7:
                manageFees();
                break;
            case 8:
                viewAllStudentsData();
                break;
            case 9:
                exitProgram();
                break;
            default:
                printf("Invalid choice, try again.\n");
        }
    }

    return 0;
}


























