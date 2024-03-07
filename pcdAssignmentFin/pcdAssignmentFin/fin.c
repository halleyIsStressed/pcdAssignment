#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#pragma warning (disable:4996)
#define THRESHOLD_CREDIT_HOURS 21

// Function Declarations

// Structural Functions
void adminRegistration(void);
void adminScoreCheck(void);
void viewStudentScores(void);
void studentInterface(void);
int adminInterface(void);
void exitFunction(void);
void displayCustom(void);

// Calculation Functions
void studentIdValidation();
float gradePointConvertion(void);
float scoreCalculator(void);
void graduationEligibility(void);

// Variable Declarations
int textColor, lightDark;
char studentName[30], studentId[10], studentLoginName[30], studentLoginId[10];
char courseCode[7][8], gradeObtained[7][3];
double creditHours[7], gradePointObtained[7], qualityPointObtained[7], totalQualityPoint, totalCreditHours, cumulativeGPA, gpaSem[3];
const double gradePoint[9] = { 4.00, 3.75, 3.50, 3.00, 2.75, 2.50, 2.00, 0.00, -1.00 };
const char idFormat[4] = { 'K', 'P', 'K', 'L'};
int currentSemSession;

// User Lobby, branches out to Student mode and Admin mode
void main() {
	int userMode;

	system("cls");
	printf(" _____ _____ __    _____    __    _____ _____ _____ _____ _____ \n");
	printf("|  |  |     |  |  |   __|__|  |  |  _  |  _  |   __|  _  | __  |\n");
	printf("|    -|  |  |  |__|   __|  |  |  |   __|     |__   |     |    -|\n");
	printf("|__|__|_____|_____|_____|_____|  |__|  |__|__|_____|__|__|__|__|\n");
	printf("\n");
	printf("============================================\n"); // 44 '='s
	printf("Welcome to Kolej Pasar GPA//CGPA calculator!\n");
	printf("Please specify your position.\n");
	printf("Type \'1\' for Admin Mode or \'2\' for Student Mode.\n");
	printf("Type \'5\' to choose display mode. Type \'8\' to EXIT.\n");
	printf("============================================\n");
	rewind(stdin);
	scanf("%d", &userMode);
	printf("\n\n");

	if (userMode == 1) {
		adminInterface(); // Moves to Admin Stage 1, line 74
	}
	else if (userMode == 2) {
		studentInterface(); // Moves to Student Stage 1, line 209
	}
	else if (userMode == 5) {
		displayCustom();
	}
	else if (userMode == 8) {
		exitFunction();
	}
	else {
		printf("Invalid input! Try again.\n"); // <--- is displayed if input is neither student nor staff.
		getch();
		main();
	}

}

// Admin Stage 1
int adminInterface() {
	int enterOrView;
	system("cls");
	printf("============================================\n");
	printf("Welcome, Kolej Pasar Administrator!\n");
	printf("Please select Administration Mode:\n");
	printf("Type \'1\' to register student's scorecard or \'2\' to view student's scores.\n");
	printf("Type \'5\' to return to Main Menu.\n");
	printf("============================================\n");
	scanf("%d", &enterOrView);

	switch (enterOrView) {
	case 1:
		adminRegistration(); // Goes to line 104. Register student's score.
		break;
	case 2:
		adminScoreCheck(); // Goes to line 187. Checks student's score. (ONLY WORKS IF REGISTERED)
		break;
	case 5:
		main(); // Goes to Main Menu
	default:
		printf("Invalid input!\n");
	}

	return enterOrView;
}

// Admin Stage 2, option '1'
void adminRegistration() {
	int viewOrExit;
	system("cls");
	printf("============================================\n");
	printf("Please enter student's details:\n");		// Basic Details of Student: Name and ID.
	printf("Please enter a student name               > ");
	rewind(stdin);
	scanf("%[^\n]s", &studentName);
	printf("Please enter a student ID (e.g.KPKL12345) > ");
	rewind(stdin);
	scanf("%s", &studentId);

	for (char* z = studentId; *z; *z = toupper(*z), z++)	// toUpper function. A loop is used due to variable data type being a string.
		;													// char* z is used to go through all elements of studentId and converts it to Upper Case.
	studentIdValidation(); // Checks for Incorrect Format. Line 409

	printf("============================================\n");
	printf("Please enter student's course details:\n");  // Scans for currentSemSession. Used in calculation.
	printf("Current semester session (1-3) > ");
	scanf("%d", &currentSemSession);
	if (currentSemSession > 3 || currentSemSession == 0) {
		printf("\nInvalid Input: Semester count not within range!\n");
		printf("Press any key to re-enter..\n");
		getch();
		adminRegistration();
	}
	printf("\n");
	system("cls");

	for (int x = 0, y = 1; x < currentSemSession * 2; x++, y++) {	// x is used to store input into the correct slot of array. y is used for semester session display.
		printf("============================================\n");	// Scans for courseCode, creditHours, gradeObtained.
		printf("              SEMESTER %d\n", y);					// courseCode will be displayed only, creditHours and GradeObtained will be used in calculation.
		printf("============================================\n");
		printf("%-31s %s", "1st Couse code (e.g.AAA1003)", "> ");	// Input data for First Course of Semester.
		rewind(stdin);
		scanf("%s", &courseCode[x]);
		for (char* z = courseCode[x]; *z; *z = toupper(*z), z++)	// toUpper function. A loop is used due to variable data type being a string.
			;														// char* z is used to go through all elements of courseCode[] and converts it to Upper Case.
		printf("%-31s %s", "1st credit hours (Max is 4)", "> ");
		scanf("%lf", &creditHours[x]);
		printf("%-31s %s", "1st grade obatained (e.g. B+)", "> ");
		rewind(stdin);
		scanf("%s", gradeObtained[x]);
		for (char* z = gradeObtained[x]; *z; *z = toupper(*z), z++)	// toUpper function. A loop is used due to variable data type being a string.
			;														// char* z is used to go through all elements of gradeObtained[] and converts it to Upper Case.
		printf("\n");
		x++;
		printf("%-31s %s", "2nd Couse code (e.g.AAA1003)", "> ");	// Input data for Second Course of Semester.
		rewind(stdin);
		scanf("%s", &courseCode[x]);
		for (char* z = courseCode[x]; *z; *z = toupper(*z), z++)	// toUpper function. A loop is used due to variable data type being a string.
			;														// char* z is used to go through all elements of courseCode[] and converts it to Upper Case.
		printf("%-31s %s", "2nd credit hours (Max is 4)", "> ");
		scanf("%lf", &creditHours[x]);
		printf("%-31s %s", "2nd grade obatained (e.g. B+)", "> ");
		rewind(stdin);
		scanf("%s", gradeObtained[x]);
		for (char* z = gradeObtained[x]; *z; *z = toupper(*z), z++)	// toUpper function. A loop is used due to variable data type being a string.
			;														// char* z is used to go through all elements of gradeObtained[] and converts it to Upper Case.
		printf("\n");

	}

	// Running Calculation Functions
	gradePointConvertion();		// Line 280. Converts Grade Letter into Grade Point usable in calculations. (e.g. B+ -> 3.50)
	scoreCalculator();			// Line 319. Verifies input and calculates for all variables displayed on Scorecard. (e.g. CGPA and GPA, totalQualityPoint, etc)
	printf("\n");
	printf("%s's score has been uploaded!\n", studentName);
	printf("To view student's scores, type \'1\'. To return to Main Menu, type \'2\'.\n");
	printf("Enter any other number to EXIT.\n");
	scanf("%d", &viewOrExit);
	if (viewOrExit == 1) { // Chose to display inputted data. Goes to line 247.
		viewStudentScores();
	}
	else if (viewOrExit == 2) {
		main(); // Returns to Main Menu.
	}
	else { // Closes Program.
		exitFunction();
	}
}

// Admin Stage 3, option '0'
void adminScoreCheck() {
	system("cls");
	printf("============================================\n");
	printf("Please enter student name > "); // Basic Details of student, inputted into studentLoginName and studentLoginID.
	rewind(stdin);
	scanf("%[^\n]s", &studentLoginName);
	printf("Please enter student Id   > ");
	scanf("%s", &studentLoginId);

	if (strcmp(studentLoginName, studentName) == 0) { // studentLoginName is compared with studentName. If similar, compare studentLoginID with studentID.
		if (strcmp(studentLoginId, studentId) == 0) {
			viewStudentScores();					  // Both are similar, display student score details inputted on admin registration.
		}
		else {
			printf("\nInvalid: Incorrect ID!\n");	  // StudentLoginId is not similar, rerun.
			printf("Press any key to re-enter..");
			getch();
			adminScoreCheck();
		}
	}
	else {
		printf("\nInvalid: Unregistered Student!\n"); // StudentLoginName is not similar, return to prevent permanent looping.
		printf("Press any key to return to Administrator Interface..");
		getch();
		adminInterface();
	}
}

// Student Stage 1
void studentInterface() {
	system("cls");
	printf("============================================\n");
	printf("Welcome, Kolej Pasar Student!\n");
	printf("============================================\n");
	printf("Please enter your name       > ");
	rewind(stdin);
	scanf("%[^\n]s", &studentLoginName);
	printf("Please enter your student Id > ");
	rewind(stdin);
	scanf("%s", &studentLoginId);

	if (strcmp(studentLoginName, studentName) == 0) {
		if (strcmp(studentLoginId, studentId) == 0) {
			viewStudentScores();
		}
		else {
			printf("\nInvalid: Incorrect ID!\n");
			printf("Press any key to re-enter..\n");
			getch();
			studentInterface();
		}
	}
	else {
		printf("\nInvalid: Unregistered Student!\n");
		printf("Press any key to return to Main Menu..\n");
		getch();
		main();
	}
}

// Student Stage 2, Admin Stage 3 (option '0')
void viewStudentScores() { // Displays student Scorecard. 
	int mainPageOrExit;
	system("cls");
	printf("STUDENT NAME > %s\n", studentName);
	printf("STUDENT ID   > %s\n", studentId);
	printf("\n");
	printf("%11s\t%12s\t%14s\t%20s\t%15s\n", "COURSE CODE", "CREDIT HOURS", "GRADE OBTAINED", "SEMESTER SESSION", "GPA PER SEM");
	printf("%11s\t%12s\t%14s\t%20s\t%15s\n", "===========", "============", "==============", "================", "===========");
	for (int x = 0, y = 0; x < currentSemSession * 2; x++, y++) { // x ranges from 0-5, y ranges from 0-2. 
		printf("%9s\t%6.0lf\t%16s\t%13s%d\t%20.2lf\n", courseCode[x], creditHours[x], gradeObtained[x], "SEM", (y + 1), gpaSem[y]);
		x++;
		printf("%9s\t%6.0lf\t%16s\t%13s%d\t%20s\n", courseCode[x], creditHours[x], gradeObtained[x], "SEM", (y + 1), "");
		printf("\n");
	}

	printf("\n");
	printf("%30s %2s %-.2lf\n", "Total quality point", ":", totalQualityPoint);
	printf("%30s %2s %-.0lf\n", "Total credit hours", ":", totalCreditHours);
	printf("%30s %2s %-.2lf\n", "CGPA", ":", cumulativeGPA);
	graduationEligibility(); // Checks if student is eligible to graduate.

	printf("Type \'1\' for return to Main Menu. Type any other number to EXIT > ");
	scanf("%d", &mainPageOrExit);

	if (mainPageOrExit == 1) {
		main();
	}
	else {
		exitFunction();
	}
}

// Calculation stage 1, unseen to user.
float gradePointConvertion() {
	int x = 0;

	do {
		if (strcmp(gradeObtained[x], "A") == 0) {
			gradePointObtained[x] = gradePoint[0]; // 4.00
		}
		else if (strcmp(gradeObtained[x], "A-") == 0) {
			gradePointObtained[x] = gradePoint[1]; // 3.75
		}
		else if (strcmp(gradeObtained[x], "B+") == 0) {
			gradePointObtained[x] = gradePoint[2]; // 3.50
		}
		else if (strcmp(gradeObtained[x], "B") == 0) {
			gradePointObtained[x] = gradePoint[3]; // 3.00
		}
		else if (strcmp(gradeObtained[x], "B-") == 0) {
			gradePointObtained[x] = gradePoint[4]; // 2.75
		}
		else if (strcmp(gradeObtained[x], "C+") == 0) {
			gradePointObtained[x] = gradePoint[5]; // 2.50
		}
		else if (strcmp(gradeObtained[x], "C") == 0) {
			gradePointObtained[x] = gradePoint[6]; // 2.00
		}
		else if (strcmp(gradeObtained[x], "F") == 0) {
			gradePointObtained[x] = gradePoint[7]; // 0.00
		}
		else {
			printf("Invalid Input: Grade not within range!\n"); // Checking for Invalid Input
			printf("Press any key to re-enter..\n");
			getch();
			adminRegistration(); // Re-runs Registration
		}
		x++;
	} while (x < currentSemSession * 2);	// 1 Semester = 2 Programmes
}

// Calculation stage 2, unseen by user.
float scoreCalculator() {
	int w = 0, x = 0, y = 0, z = 1;
	do {
		if (creditHours[w] <= 0 || creditHours[w] > 4) {				// Checking for Invalid Input. w is used to go through all elements in the arrays.
			printf("Invalid Input: Credit Hour not within range!\n");	// Not in range, or not a number
			printf("Press any key to re-enter..\n");
			getch();
			adminRegistration(); // Re-runs Registration
		}
		else { // In case of non-invalid Input
			qualityPointObtained[w] = gradePointObtained[w] * creditHours[w];	// Formula for Quality Point Calculations
			totalQualityPoint += qualityPointObtained[w];						// Adds all elements of qualityPointObtained[] into totalQualityPoint
			totalCreditHours += creditHours[w];									// Adds all elements of creditHours[] into totalCreditHours
			cumulativeGPA = totalQualityPoint / totalCreditHours;				// Cumulative GPA Calculation
			w++;
		}
	} while (w < currentSemSession * 2);	// 1 Semester = 2 Programmes

	do { // GPA Calculations
		gpaSem[x] = (qualityPointObtained[y] + qualityPointObtained[z]) / (creditHours[y] + creditHours[z]);
		x++;		// x is used to go through all elements in gpaSem[].
		y += 2;		// y and z are used to go through all elements in qualityPointObtained[] and creditHours[]. 
		z += 2;		// the range of y is 0,2,4 while the range of z is 1,3,5. the first value of y is paired with the first value of z and so on.
	} while (x < currentSemSession);
}

// Calculation stage 3, unseen by user.
void graduationEligibility() {
	if (totalCreditHours >= THRESHOLD_CREDIT_HOURS && cumulativeGPA >= 2.00) { // Minimum threshold for graduation, checks to see if student is above threshold.
		printf("\nCongratulations, %s (%s) is eligible to graduate!\n\n", studentName, studentId);
	}
	else {
		printf("\nUnfortunately, %s (%s) is not eligible to graduate yet!\n(MUST fulfil 21 credit hours and 2.00 CGPA and above to graduate.)\n\n", studentName, studentId);
	}

}

// EXTRA FEATURE: Display Customization
void displayCustom()
{
	system("cls");
	printf("============================================\n");
	printf("Please select display mode:\n");
	printf("Type \'1\' to remain in dark mode. Type \'2\' for light mode > ");	// Picks Background Color.
	scanf("%d", &lightDark);

	if (lightDark == 1) {
		printf("Type \'1\' to use white text. Type \'2\' to use green text. Type \'3\' to use blue text. > "); // Picks Text Color.
		scanf("%d", &textColor);
		if (textColor == 1) {		// Dark Mode
			system("color 07");
		}
		else if (textColor == 2) {
			system("color 02");
		}
		else if (textColor == 3) {
			system("color 03");
		}
		else {
			printf("Invalid Input. Try again.");
			getch();
			main();
		}
	}
	else if (lightDark == 2) {		// Light Mode
		printf("Type \'1\' to use black text. Type \'2\' to use blue text. > ");
		scanf("%d", &textColor);
		if (textColor == 1) {
			system("color F0");
		}
		else if (textColor == 2) {
			system("color F1");
		}
		else {
			printf("Invalid Input. Try again.");
			getch();
			main();
		}
	}
	else {
		printf("Invalid Input. Try again.");
		getch();
		main();
	}

	main();

}

void studentIdValidation() {
	int x;

	for (x = 0; x <= 3; x++) {
		if (studentId[x] != idFormat[x]) {
			printf("Invalid Input: Incorrect ID format! Press any key to re-enter...");
			getch();
			adminRegistration();
		}
	}
}

// Closes Program 
void exitFunction() {
	system("cls");
	printf("============================================");
	printf("\nThank You for using Kolej Pasar GPA/CGPA calculator!\n");
	printf("============================================\n");
	exit(0);
}