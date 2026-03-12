//Name: Joseph Ferguson
//Program Description: This program calculates the user's recommended calorie and protein intake, has them put in their caloric and protein intake for the day, and outputs a fitness report for the day 

#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>

using namespace std;

int main() {
	//This section declares all the variables this program will need
	int userActivityLevel, dietTypeSelection;
	double userWeight, userHeight, userBmr, userTDEE;
	double adjustedCalorieGoal, adjustedCalorieGoalMin, adjustedCalorieGoalMax;
	double activityCoefficient;
	double recommendedProteinIntake, recProteinMin, recProteinMax;
	int minCalories;
	char userSex;
	int userAge;
	string userDietType, userName;
	bool moreFoodEntries = true;
	int numFoodEntries = 1;
	int calorieAccumulator = 0;
	double proteinAccumulator = 0;

	cout << "Please enter your first name: ";
	cin >> userName;

	//This section outputs the main menu for the program
	cout << "Hi, " << userName << "! Welcome to my calorie and protein tracker!" << endl << endl;

	//This section gets some user information so we can calculate the user's Basal Metabolic Rate
	cout << "Enter your weight in pounds: ";
	cin >> userWeight;
	cout << "Enter your height in inches: ";
	cin >> userHeight;
	cout << "Enter your sex ('M' or 'F'): ";
	cin >> userSex;
	cout << "Enter your age: ";
	cin >> userAge;

	//The formula differs based on their gender
	if (userSex == 'M') {
		userBmr = (10 * (userWeight / 2.20462)) + (6.25 * (userHeight * 2.54)) - (5 * userAge) + 5; //Mifflin-St Jeor Equation for men to determine Basal Metabolic Rate 
		minCalories = 1500; //Min recommended calories for any male to have per day
	}
	else if (userSex == 'F') {
		userBmr = (10 * (userWeight / 2.20462)) + (6.25 * (userHeight * 2.54)) - (5 * userAge) - 161; //Mifflin-St Jeor Equation for women to determine Basal Metabolic Rate
		minCalories = 1200; //Min recommended calories for any female to have per day
	}
	else { //Else clause for if they enter invalid value for gender
		cout << "Please enter a valid value for your gender." << endl;
		exit(0);
	}

	//Menu for activity level which we need to calculate their Total Daily Energy Expenditure
	cout << endl << endl;
	cout << "Please select one of the options for your activity level: " << endl;
	cout << "1. Sedentary (little to no exercise)." << endl;
	cout << "2. Lightly active (light exercise 1-3 days a week)." << endl;
	cout << "3. Moderately active (moderate exercise 3-5 days a week)." << endl;
	cout << "4. Very active (hard exercise 6-7 days a week)." << endl;
	cin >> userActivityLevel;

	//This switch statement assigns activityCoefficient a value based on their activity level
	switch (userActivityLevel) {
	case 1:
		activityCoefficient = 1.2;
		break;
	case 2:
		activityCoefficient = 1.375;
		break;
	case 3:
		activityCoefficient = 1.55;
		break;
	case 4:
		activityCoefficient = 1.725;
		break;
	default: //Exits out of program if they didn't enter a valid activity level
		cout << "Please enter a valid activity level.";
		exit(0);
	}

	//Calculates user Total Daily Energy Expenditure
	userTDEE = userBmr * activityCoefficient;

	//Outputs a menu for whether they want to cut, maintain, or bulk
	cout << endl << endl;
	cout << "Please select one of the following options for your diet goal: " << endl;
	cout << "1. Hard cut." << endl;
	cout << "2. Light cut." << endl;
	cout << "3. Maintenance." << endl;
	cout << "4. Light bulk." << endl;
	cout << "5. Hard bulk." << endl;
	cin >> dietTypeSelection;

	//This switch statement gives them a calorie goal based off of which diet goal the user has
	switch (dietTypeSelection) {
	case 1:
		adjustedCalorieGoal = userTDEE * 0.75;
		userDietType = "hard cut";
		break;
	case 2:
		adjustedCalorieGoal = userTDEE * 0.85;
		userDietType = "light cut";
		break;
	case 3:
		adjustedCalorieGoal = userTDEE;
		userDietType = "maintenance";
		break;
	case 4:
		adjustedCalorieGoal = userTDEE * 1.1;
		userDietType = "light bulk";
		break;
	case 5:
		adjustedCalorieGoal = userTDEE * 1.2;
		userDietType = "hard bulk";
		break;
	default: //Exits out of the program if they didn't select a valid option
		cout << "Please select a valid diet goal.";
		exit(0);
	}

	//Calculates users recommended protein intake in grams
	recommendedProteinIntake = userWeight * 0.8;

	//Rounds the calorie minimum and maximum for cleaner output at the end
	adjustedCalorieGoalMin = round(adjustedCalorieGoal * 0.95);
	adjustedCalorieGoalMax = round(adjustedCalorieGoal * 1.05);

	//Calculates a lower bound and upper bound for protein intake
	recProteinMin = recommendedProteinIntake * 0.9;
	recProteinMax = recommendedProteinIntake * 1.1;

	//If the lower range of their calculated calorie goal is lower than the minimum calories recommended to them either based off gender or their BMR (which is the min calories they need even without movement), then it changes that lower range to be more safe
	if (adjustedCalorieGoalMin < minCalories) {
		adjustedCalorieGoalMin = round(minCalories);
		adjustedCalorieGoal = round(minCalories * 1.05);
		adjustedCalorieGoalMax = round(minCalories * 1.10);
	}
	if (adjustedCalorieGoal < userBmr) {
		adjustedCalorieGoalMin = round(userBmr);
		adjustedCalorieGoal = round(userBmr * 1.05);
		adjustedCalorieGoalMax = round(userBmr * 1.10);
	}


	//Prompts user to enter food they ate
	cout << endl << endl << endl << endl;
	cout << "Now please enter all the food you ate today: " << endl;


	//I know we haven't covered loops yet, but a while loop was the best way to let the user enter each food item that they had for the day
	//The loop keeps going until the user says that they don't have any more food to input
	//I didn't use any AI for writing this, I just looked up the syntax for while loops in C++
	while (moreFoodEntries == true) {
		//Variables that we'll only use inside the while loop
		int caloriesCurrentFood;
		double proteinCurrentFood;
		char moreFoodEntryAnswer;

		//Gets the calories and protein count of the current food item
		cout << "Please enter the calorie count for food item " << numFoodEntries << ": ";
		cin >> caloriesCurrentFood;
		cout << "Please enter the protein count (in grams) for food item " << numFoodEntries << ": ";
		cin >> proteinCurrentFood;

		//Adds the protein and calories of the current food item to the accumulators, and increases the number of food items by 1
		calorieAccumulator += caloriesCurrentFood;
		proteinAccumulator += proteinCurrentFood;
		numFoodEntries++;

		//Asks the user if they have more food to enter
		cout << "Do you have any more food to enter? (Y/N): ";
		cin >> moreFoodEntryAnswer;
		cout << endl << endl;

		//If the user has no more food to enter, the loop terminates. If they do have more food, the loop keeps going, and if they enter something invalid the program terminates
		if (moreFoodEntryAnswer == 'N' || moreFoodEntryAnswer == 'n') {
			moreFoodEntries = false;
		}
		else if (moreFoodEntryAnswer == 'Y' || moreFoodEntryAnswer == 'y') {
			//Does nothing
		}
		else {
			cout << "Please enter a valid answer";
			exit(0);
		}
	}

	//Final output of the program
	cout << setprecision(0) << fixed;
	cout << endl << endl << endl << endl;
	cout << "Fitness information for the day for " << userName << endl;
	cout << "------------------------------------------------------" << endl << endl;
	cout << left << setw(30) << "Weight: " << right << setw(20) << userWeight << " lbs" << endl;
	cout << left << setw(30) << "Height: " << right << setw(20) << userHeight << " in" << endl;
	cout << left << setw(30) << "Gender: " << right << setw(20) << userSex << endl;
	cout << left << setw(30) << "Age: " << right << setw(20) << userAge << endl;
	cout << left << setw(30) << "Diet Goal:" << right << setw(20) << userDietType << endl;
	cout << "------------------------------------------------------" << endl << endl;
	cout << left << setw(30) << "Ideal Caloric Intake: " << right << setw(20) << adjustedCalorieGoalMin << "-" << adjustedCalorieGoalMax << " cals" << endl;
	cout << left << setw(30) << "Ideal Protein Intake: " << right << setw(20) << recProteinMin << "-" << recProteinMax << " g" << endl;
	cout << left << setw(30) << "Actual Caloric Intake: " << right << setw(20) << calorieAccumulator << " cals" << endl;
	cout << left << setw(30) << "Actual Protein Intake: " << right << setw(20) << proteinAccumulator << " g" << endl;
	cout << "------------------------------------------------------" << endl << endl;

	//Outputs a message depending on if they hit their calorie goal or not
	if (calorieAccumulator < adjustedCalorieGoalMin) {
		cout << "You're a bit under your calorie goal today." << endl;
		cout << "Try adding a nutitious snack to meet your goal!" << endl;
	}
	else if (calorieAccumulator > adjustedCalorieGoalMax) {
		cout << "You're a bit over your calorie goal today." << endl;
		cout << "Remember, consistency matters more than perfection!" << endl;
	}
	else {
		cout << "You met your calorie target today!" << endl;
		cout << "Consistency like this is what helps you reach your goals!";
	}

	cout << endl;

	//Outputs a message depending on if they hit their protein goal or not
	if (proteinAccumulator < recProteinMin) {
		cout << "Looks like you didn't hit your protein goal today." << endl;
		cout << "Adding a protein-rich snack or meal can help you stay strong and hit your fitness goals!" << endl;
	}
	else if (proteinAccumulator > recProteinMax) {
		cout << "You went a bit over your protein goal today." << endl;
		cout << "No worries! Your body can handle extra protein, just try to balance it with other nutrients!" << endl;
	}
	else {
		cout << "Great job! You met your protein goal today!" << endl;
		cout << "Keep up the great work!" << endl;
	}

	cout << endl;
	cout << "Note: This is just a recommendation, not medical advice. Make sure to pay attention to your body and talk with your doctor!" << endl << endl << endl << endl;

	return 0;
}