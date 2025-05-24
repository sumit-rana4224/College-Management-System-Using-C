# College Management System (CMS) User Documentation

## Overview
The College Management System (CMS) is a C-based console application designed to manage student and faculty data for a college. It provides functionalities for administrators to manage records, faculty to handle marks and attendance, and students to view their details, marks, and attendance. The system supports secure login, data persistence, and various administrative tasks.

## System Requirements
- Operating System: Windows (due to the use of `conio.h` for password input)
- Compiler: Any C compiler supporting standard libraries (e.g., GCC)
- Dependencies: Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, `conio.h`)

## Setup Instructions
1. Compile the Program:
   - Save the provided source code as `cms.c`.
   - Compile using a C compiler, e.g., `gcc cms.c -o cms.exe`.
   - Run the compiled executable: `./cms.exe` (Windows).

2. Initial Configuration:
   - On first run, the system initializes with a default admin password: `admin1234`.
   - Data is stored in text files (`admin.txt`, `students_data.txt`, `faculty_data.txt`, `allnotice.txt`, `ranklist.txt`).
   - Ensure the program has read/write permissions in the directory to create and modify these files.

3. File Structure:
   - `admin.txt`: Stores admin password, attendance count, and registration counters.
   - `students_data.txt`: Stores student records.
   - `faculty_data.txt`: Stores faculty records.
   - `allnotice.txt`: Stores admin notices.
   - `ranklist.txt`: Stores student rankings based on CGPA.

## User Roles
The CMS supports three user roles, each with specific functionalities:
1. Admin: Manages student and faculty records, changes passwords, and generates rank lists.
2. Faculty: Views personal details, uploads student marks, and records attendance.
3. Student: Views personal details, marks, and attendance percentage.

## Login Instructions
- Admin Login:
  - Select option `1` from the main menu.
  - Enter the admin password (default: `admin1234`).
- Faculty Login:
  - Select option `2` from the main menu.
  - Enter the faculty registration number and password (default password is the registration number).
- Student Login:
  - Select option `3` from the main menu.
  - Enter the student registration number and password (default password is the registration number).
- Exit: Select option `4` to save all data and exit the program.

Note: Passwords are masked with asterisks (`*`) during input for security.

## Admin Features
After successful admin login, the following options are available:

1. Add Faculty:
   - Enter faculty details (name, father’s name, state, district, CGPA, 12th percentage, salary).
   - A unique registration number is assigned automatically.
   - Default password is set to the registration number.

2. Add Student:
   - Enter student details (name, father’s name, state, district, CGPA, 12th percentage, 10th percentage, fees status).
   - A unique registration number and serial number are assigned.
   - Default password is set to the registration number.

3. Check Rankwise Students List:
   - Displays a sorted list of students based on CGPA (highest to lowest).
   - Saves the rank list to `ranklist.txt`.

4. See Faculty Details:
   - Displays a table of all faculty details, including name, registration number, father’s name, state, district, CGPA, 12th percentage, and salary.

5. See Student Details:
   - Displays a table of all student details, including serial number, name, registration number, father’s name, state, district, CGPA, 12th percentage, 10th percentage, fees status, and attendance.

6. Delete Faculty:
   - Enter the faculty registration number to remove their record.

7. Delete Student:
   - Enter the student registration number to remove their record.

8. Change Student Password:
   - Enter the student’s registration number and a new password.

9. Change Faculty Password:
   - Enter the faculty’s registration number and a new password.

10. Change Admin Password:
    - Enter a new password for the admin account.

11. Logout:
    - Returns to the main menu.

## Faculty Features
After successful faculty login, the following options are available:

1. See Personal Details:
   - Displays the faculty’s name, registration number, salary, 12th percentage, CGPA, father’s name, state, and district.

2. Upload Marks:
   - Enter a student’s registration number and their marks (out of 10).
   - If the student has no prior marks, the entered marks become their CGPA; otherwise, the CGPA is averaged with the new marks.
   - Enter `0` to exit the marks upload process.

3. Take Attendance:
   - For each student, enter `1` (present) or `0` (absent) to update their attendance.
   - Attendance is incremented for both present and absent inputs (this is a bug in the system; see Known Issues).

4. Logout:
   - Returns to the main menu.

## Student Features
After successful student login, the following options are available:

1. See Personal Details:
   - Displays the student’s name, registration number, serial number, CGPA, 12th percentage, 10th percentage, attendance, state, district, father’s name, and fees status.

2. See Marks:
   - Displays the student’s current CGPA.

3. See Attendance:
   - Displays the student’s attendance percentage, calculated as `(attendance count / total attendance sessions) * 100`.

4. Logout:
   - Returns to the main menu.

## Data Validation
- Names: Must be at least 3 characters long and contain only letters and spaces.
- CGPA: Must be between 0.0 and 10.0.
- Percentages (12th, 10th): Must be between 0.0 and 100.0.
- Salary: Must be at least 20,000.
- Fees Status: Enter `1` for paid or `0` for unpaid.

## Known Issues
1. Attendance Bug: In the `take_attendance` function, both `1` (present) and `0` (absent) increment the attendance count, leading to incorrect attendance percentages.
2. Password Input for Faculty: The `change_fac_pass` function uses `scanf` instead of `get_password`, so the password is not masked during input.
3. File Handling: The `feof` loop in `load_all_data` may read an extra invalid record, potentially causing issues.
4. Notice Feature: The `admin_notice` function is defined but not used in the admin menu.

## Troubleshooting
- Login Failure: Ensure the correct registration number and password are entered. Default passwords are the registration numbers.
- File Errors: Ensure the program has permission to read/write in the directory where data files are stored.
- Invalid Input: Follow the validation rules for names, CGPA, percentages, and salary to avoid errors.

## Best Practices
- Backup Data: Regularly back up the data files (`students_data.txt`, `faculty_data.txt`, `admin.txt`) to prevent data loss.
- Secure Passwords: Change the default admin password and encourage users to update their passwords.
- Exit Properly: Use the exit option (4) from the main menu to ensure all data is saved before closing the program.

## Contact
For support or bug reports, contact the system administrator or the development team.
1. System Developer - I 
   Sumit Rana
   Email- sumitrana4224@gmail.com
   Linkedin- [Sumit Rana](https://www.linkedin.com/in/sumit-rana-14069b326)

2. System Developer - II
   Diganta Kumar Dinda
   Email - itsurgugu98@gmail.com
   
---
This documentation provides a clear guide to using the College Management System. Follow the instructions for each role to manage college data efficiently.