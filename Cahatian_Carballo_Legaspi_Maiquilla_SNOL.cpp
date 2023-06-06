/*
	Simple Number-Only Language (SNOL) Program
	
	Program Information: This is a simplied custom programming language that utilizes C++ as its interpreter.
	This custom programming language could perform certain programming languages concepts such as data type 
	identification, variable assignment, and arithmetic operations.
	
	Program creators: Cahatian, Carballo, Legaspi, Maiquilla
*/

// Standard Library that were used in the Program
#include <iostream> // provides input and output stream functionality
#include <regex> // allows for pattern matching and manipulation of strings based on specified patterns
#include <string> // provides support for working with strings
#include <unordered_map> // allows efficient storage and retrieval of key-value pairs
#include <stack> // provides the implementation of a stack data structure
#include <deque> // provides the implementation of a deque (double-ended queue) data structure
#include <sstream>
#include <cctype>
using namespace std;

// Function to PRINT the value associated with a given key in a map
void print_command(string key_val, unordered_map<string, string>& map, string& error_check) {
	// Check if the key exists in the map
	if (map.find(key_val) == map.end()) {
		// If the key is not found, set the error_check string with an error message
		error_check = "Error! [" + key_val + "] is not defined!\n";
	} else {
		// If the key is found, print the key-value pair
		cout << "SNOL> [" << key_val << "] = " << map[key_val] << endl;
	}
}


// Function to EVALUATE the type of a given NUMBER STRING
int evaluate_number(string num) {
	int type = 3; // Returns 3 if not integer or float
	// Check if the number matches the pattern for an integer
	if (regex_match(num, regex("[+-]?[0-9]+"))) {
		// If the number matches the integer pattern, set type to 1
		type = 1;
	} 
	// Check if the number matches the pattern for a float
	else if (regex_match(num, regex("[+-]?[0-9]*[.][0-9]+"))) {
		// If the number matches the float pattern, set type to 2
		type = 2;
	}
	// Return the determined type of the number
	return type;
}

// Function to handle the BEG command, which prompts the user to enter a value for a given key and stores it in a map
void beg_command(string key_val, unordered_map<string, string>& map, string& error_check) {
	string user_input;
	cout << "SNOL> Please enter value for [" << key_val << "]: " << endl;
	cout << "Input: ";
	
	// Read user input from the console
	getline(cin, user_input);
	
	// Check if the user input is not an integer, float, or any valid command
	if (evaluate_number(user_input) == 3) {
		// If the input does not match any valid command or numeric value, set an error message
		error_check = "Unknown command! Does not match any valid command of the language.\n";
  	}
  	// Check if an error occurred during evaluation
  	if (error_check != "0") {
    	// If an error message is set, return without modifying the map
    	return;
  	}

  	// Check if the key exists in the map
  	if (map.find(key_val) == map.end()) {
    	// If the key is not found, insert a new key-value pair in the map
    	map.insert(make_pair(key_val, user_input));
  	} else {
    	// If the key is found, update the existing value in the map
    	map[key_val] = user_input;
  	}
}

// Function to check the type of a given user input command
int command_check(string user_input) {
	if (user_input.substr(0, 3) == "BEG") {
		// Check if the command starts with "BEG"
    	return 1;
	}
	if (user_input.substr(0, 5) == "PRINT") {
    	// Check if the command starts with "PRINT"
    	return 2;
  	} else if (user_input.find("BEG") != std::string::npos || user_input.find("PRINT") != std::string::npos) {
    	// Check if the command contains "BEG" or "PRINT" anywhere in the string
    	return 0;
 	} else {
    	// If none of the conditions above match, the command is unknown
    	return 3;
  	}
}

// Function to evaluate an ARITHMETIC OPERATIONS between two integers
int evaluate_int(char op, int first, int sec) {
	if (op == '+') return (sec + first); // Addition operation
	else if (op == '-') return (sec - first); // Subtraction operation
	else if (op == '*') return (sec * first); // Multiplication operation
	else if (op == '/') return (sec / first); // Division operation
	else if (op == '%') return (sec % first); // Modulo operation
	else return 0; // Invalid operation
}

// Function to evaluate a POSTFIX EXPRESSION containing integers
string eval_post_int(string num) {
	stringstream stream;
	stack <int> operands; // Stores the numbers for evaluation
	string results; // Stores the results
	int i;
	int first;
	int sec;
	int value;

  	for (i = 0; i < num.length(); i++) {
	  	if (num[i] == ' ') {
      		continue;
    } else if (isdigit(num[i])) {
		value = 0;
		
		while (isdigit(num[i])) {
        	value = value * 10 + (int)(num[i] - '0');
        	i++;
      	}
      i--;
      operands.push(value); // Pushes the integer value onto the operands stack
    } else if (num[i] == '~') { // Determines if negative number
      	operands.top() = operands.top() * -1; // Negates the top element of the operands stack
    } else {
    	first = operands.top(); // Retrieves the first operand from the stack
    	operands.pop(); // Removes the first operand from the stack
    	sec = operands.top(); // Retrieves the second operand from the stack
    	operands.pop(); // Removes the second operand from the stack
		value = evaluate_int(num[i], first, sec); // Evaluates the arithmetic operation using the operator and operands
		operands.push(value); // Pushes the result back onto the operands stack
    }
  }
  
  // Convert to string and returns it
  value = operands.top(); // Retrieves the final result from the operands stack
  operands.pop(); // Removes the final result from the stack
  stream << value; // Converts the result to a string
  results = stream.str(); // Stores the result as a string

  return results; // Returns the final result as a string
}

// Function to evaluate an ARITHMETIC OPERATIONS between two DOUBLE-PRECISION FLOATING-NUMBER numbers
double evaluate_double(char op, double first, double sec) {
	switch (op) {
        case '+':
            return sec + first; // Addition operation
            break;
        case '-':
            return sec - first; // Subtraction operation
            break;
        case '*':
            return sec * first; // Multiplication operation
            break;
        case '/':
            return sec / first; // Division operation
            break;
        default:
            return 0.0; // Invalid operation
            break;
    }
}

// Function to evaluate a POSTFIX EXPRESSION containing FLOATING-POINT numbers
string eval_post_float(string num) {
	ostringstream stream;
	stream.precision(10);
	stack <double> operands; // Stores the numbers for evaluation
	string results; // Stores the results
	int i;
	int j;
	int hold;
	int len;
	double first;
	double sec;
	double value;
	
	for (i = 0; i < num.length(); i++) {
    	if (num[i] == ' ') {
      		continue;
    	} else if (isdigit(num[i])) { // If character is a number
      		value = 0.0;
      		j = i;
      		len = 0;
      		while (isdigit(num[j]) || num[j] == '.') {
        		len++;
        		j++;
      		}
      	j = 0;
      	while (isdigit(num[i]) || num[i] == '.') {
        	if (num[i] == '.')
          		hold = len - j - 1;
        	else
          		value = value * 10 + (num[i] - '0');
        	i++;
        j++;
		}
		i--;
		while (hold != 0) {
			value /= 10;
	        hold--;
	    }
			operands.push(value); // Pushes the floating-point value onto the operands stack
		} else if (num[i] == '~') { // Determines if negative number
			operands.top() = operands.top() * -1; // Negates the top element of the operands stack
    	} else {
			// If the user entered MODULO, then this will execute
			if (num[i] == '%') {
        		return "ERROR"; // Returns an error message if the operator is '%'
      		}
      		first = operands.top(); // Retrieves the first operand from the stack
      		operands.pop(); // Removes the first operand from the stack
      		sec = operands.top(); // Retrieves the second operand from the stack
      		operands.pop(); // Removes the second operand from the stack
      		value = evaluate_double(num[i], first, sec); // Evaluates the arithmetic operation using the operator and operands
      		operands.push(value); // Pushes the result back onto the operands stack
    	}
	}	

  // Convert to string and returns it
  value = operands.top(); // Retrieves the final result from the operands stack
  operands.pop(); // Removes the final result from the stack
  stream << value; // Converts the result to a string
  results = stream.str(); // Stores the result as a string

  return results; // Returns the final result as a string
}

// Function to check the DATA TYPE of a STRING RESULT
int check_data_type(string result) {
	int j = 0; // Initialize j to 0 for integer data type
	
	for (int i = 0; i < result.length(); i++) {
		if (result[i] == '.') { // If the character is a dot (.), indicating a decimal point
      		j = 1; // Set j to 1 to indicate a floating-point number
      		break; // Exit the loop since the decimal point is found
    	}
  	}
  	return j; // Return the value of j, indicating the data type of the result (0 for integer, 1 for floating-point)
}

// Function to determine the OPERATOR HIERARCHY for POSTFIX EXPRESSION EVALUATION
//int op_hierarchy(char op) {
//	if (op == '%' return 5; // If the operator is '%', return 5 (highest priority)
//	else if (op == '*') return 4; // If the operator is '*', return 4
//	else if (op == '/') return 3; // If the operator is '/', return 3
//	else if (op == '-') return 2; // If the operator is '-', return 2
//	else if (op == '+') return 1; // If the operator is '+', return 1
//	else return -1; // If the operator is not recognized, return -1 (lowest priority)
//}

int op_hierarchy(char op) {
	if ((op == '%')||(op == '*')||(op == '/')) return 2; // If the operator is '%', return 2 (highest priority)
	else if ((op == '-')||(op == '+')) return 1; // If the operator is '-', return 1
	else return -1; // If the operator is not recognized, return -1 (lowest priority)
}

// Function to EVALUATE the expressions
string evaluate(string num) {
	stack<char> op_stack; // Stack to store operators
	string result; // Stores the final result
	int i;
	
  	num.erase(remove(num.begin(), num.end(), ' '), num.end()); // Removes whitespace from the input expression
	  
	for (i = 0; i < num.length(); i++) {
    	if (num[i] != '-') {
      		continue;
    	}
    	// Checks if the '-' character indicates a negative number
    	if (i == 0 || num[i - 1] == '(' || (op_hierarchy(num[i - 1]) != -1)) {
      		num[i] = '~'; // Replaces '-' with '~' to represent negative numbers
    	}
  	}

  	for (i = 0; i < num.length(); i++) {
    	if (isdigit(num[i]) || num[i] == '.') { // If the character is a digit or decimal point
      		// Add it to the result string
      		if (result.length() > 0 && !isdigit(result[result.length() - 1])) {
        		if (!isspace(result[result.length() - 1]) && !(result[result.length() - 1] == '.')) {
          			result += " "; // Add a space before adding the digit or decimal point
        		}
      		}
      	result += num[i];
    } else if (num[i] == '(') { // If the character is an opening parenthesis
		op_stack.push('('); // Push it to the operator stack
    } else if (isspace(num[num[i]])) { // If the character is a space
		continue; // Skip it
    } else if (num[i] == ')') { // If the character is a closing parenthesis
		// Pop operators from the stack and add them to the result until an opening parenthesis is encountered
		while (!op_stack.empty() && op_stack.top() != '(') {
        	if (result.length() > 0 && !isspace(result[result.length() - 1])) {
          		result += " "; // Add a space before adding the operator
        	}
        char placeholder = op_stack.top();
        op_stack.pop();
        result += placeholder;
      	}
      	op_stack.pop(); // Remove the opening parenthesis from the stack
    } else { // If the character is an operator
		if (num[i] == num[i + 1] || op_hierarchy(num[i + 1]) != -1) {
        	return "OPERATOR ERROR"; // Return an error if there are consecutive operators or an invalid operator
      	}
      	if (result.length() > 0 && !isspace(result[result.length() - 1])) {
        	result += " "; // Add a space before adding the operator
      	}
      	// Pop operators from the stack and add them to the result based on their hierarchy
      	while (!op_stack.empty() && op_hierarchy(num[i]) < op_hierarchy(op_stack.top())) {
        	char placeholder = op_stack.top();
        	op_stack.pop();
        	if (result.length() > 0 && !isspace(result[result.length() - 1])) {
          		result += " "; // Add a space before adding the operator
        	}
        result += placeholder;
      	}
		op_stack.push(num[i]); // Push the current operator to the stack
    	}
	}
	
	// Add any remaining operators from the stack to the result
	while (!op_stack.empty()) {
    	char placeholder = op_stack.top();
    	op_stack.pop();
    	if (result.length() > 0 && !isspace(result[result.length() - 1])) {
      		result += " "; // Add a space before adding the operator
    	}
    result += placeholder;
  	}

  	// Perform the main calculation by evaluating the postfix expression
  	int type;
  	type = check_data_type(result); // Check if the result contains a decimal point
  	if (type == 1) {
    	result = eval_post_float(result); // Evaluate the postfix expression with floating-point arithmetic
  	} else {
    	result = eval_post_int(result); // Evaluate the postfix expression with integer arithmetic
  	}
  	return result; // Return the final result
}

// Function that CHECKS for OPERATORS
bool operator_check(char op) {
	if (op == '+' || op == '-' || op == '*' || op == '/' || op == '%') { // Checks if the character is a valid operator
    	return true; // Returns true if the character is an operator
  	} else {
		return false; // Returns false if the character is not an operator
  	}
}

// Function that CHECKS if VARIABLE is VALID
bool variable_check(string user_input) {
	if (regex_match(user_input, regex("[a-zA-Z][a-zA-Z0-9]*")) && user_input != "BEG" && user_input != "PRINT") { // Checks if the user_input is a valid variable name
    	return true; // Returns true if user_input is a valid variable name
  	}
  	return false; // Returns false if user_input is not a valid variable name
}

// Function that CHECKS if VARIABLE already EXISTS. If it does, then OVERWRITE.
string check_duplicate_var(int &var_type, string &operand, unordered_map<string, string> map, string &error_check) {
	if (variable_check(operand)) { // Checks if operand is a valid variable name
		if (map.find(operand) == map.end()) { // Checks if the variable is not defined in the map
      		return "false"; // Returns "false" to indicate that the variable is not a duplicate
    	}	
    operand = map[operand]; // Retrieves the value of the variable from the map
    var_type = evaluate_number(operand); // Evaluates the type of the variable (integer, float, or other)
    return "true"; // Returns "true" to indicate that the variable is a duplicate
  	} else {
    	error_check = "Error! [" + operand + "] is not defined!\n"; // Sets the error message indicating that the variable is not defined
    	return "Invalid"; // Returns "Invalid" to indicate that the variable is invalid
  	}
}

// Function for PARSING that CHECKS whether BOTH NUMBERS have the same DATA TYPE
bool parse(unordered_map<string, string> map, int &var_type, string num, deque<string> &equation, string &error_check) {
	if (num == "") { // If there is no number specified
    	error_check = "Unknown command! Does not match any valid command of the language.\n";
    	return false;
  	} else if (var_type == 0) { // Checks for expressions
	  	var_type = evaluate_number(num); // Evaluates the type of the expression
    		if (var_type == 3) { // If the expression is a variable
      			if (check_duplicate_var(var_type, num, map, error_check) == "true") { // Checks if the variable is a duplicate
        			var_type = evaluate_number(num); // Re-evaluates the type of the variable
        			if (num[0] == '-') {
          				equation.push_back("( " + num + " )"); // Adds the variable to the equation with parentheses if it's negative
        			} else {
          				equation.push_back(num); // Adds the variable to the equation
        			}			
        		return true;
      			} else if (check_duplicate_var(var_type, num, map, error_check) == "false") { // If the variable is not defined
        			error_check = "Error! [" + num + "] is not defined!\n";
        			return false;
      			}		
    		}
    		equation.push_back(num); // Adds the expression to the equation
    		return true;
  	} else if (evaluate_number(num) == 3) { // Checks for variable names
    	int temp = var_type;
    		if (check_duplicate_var(var_type, num, map, error_check) == "true") { // Checks if the variable is a duplicate
      			if (temp == evaluate_number(num)) { // Checks if the operands have the same type
        			if (num[0] == '-') {
          				equation.push_back("( " + num + " )"); // Adds the variable to the equation with parentheses if it's negative
        			} else {
						equation.push_back(num); // Adds the variable to the equation
					}
        		return true;
      			} else {
        			error_check = "Error! Operands must be of the same type in an arithmetic operation!\n";
        			return false;
				}
    		} else if (check_duplicate_var(var_type, num, map, error_check) == "false") { // If the variable is not defined
				error_check = "Error! [" + num + "] is not defined!\n";
				return false;
    		}
	} else if (var_type == evaluate_number(num)) { // Checks for numbers
    	equation.push_back(num); // Adds the number to the equation
    	return true;
  	} else {
    	error_check = "Error! Operands must be of the same type in an arithmetic operation!\n";
    	return false;
  }
  // Add a default return statement
  return false;
}

// Function that CHECKS for ASSIGNMENTS
bool assignment_check(string assign_input, string &user_input, string &expr) {
	if ((assign_input.find("=") != std::string::npos)) { // Checks if the assignment input contains an equal sign
    // Extracts the assignment
	int position_equal = assign_input.find('=');
    user_input = assign_input.substr(0, position_equal); // Stores the left-hand side of the assignment
    expr = assign_input.substr(position_equal + 1, assign_input.length() - user_input.length()); // Stores the right-hand side of the assignment
    // Removes the spaces
    user_input = regex_replace(user_input, regex("^ +| +$|( ) +"), "$1"); // Removes leading, trailing, and extra spaces in the left-hand side
    expr = regex_replace(expr, regex("^ +| +$|( ) +"), "$1"); // Removes leading, trailing, and extra spaces in the right-hand side
    return true;
	} else {
    return false;
  	}
}

// Function that CONVERTS the arithmetic expression into a valid expression
string evaluate_math(string user_input, unordered_map <string, string> map, string &error_check) {
	stack <char> z;
	deque <string> equation; // Stores the converted expressions
	string placeholder;
	string num;
	bool neg_val = false;
	int len = user_input.length();
	int op = 0;
	int terms = 0;
	int var_type = 0;
	int i;
	
	user_input = regex_replace(user_input, regex("^ +| +$|( ) +"), "$1"); // Removes whitespaces
	
	for (i = 0; i < len; i++) {
		if ((error_check.find("Error!") != std::string::npos)) { // If an error is encountered
      		break;
    }
    
    // Checks for parentheses
    if (user_input[i] == '(' || user_input[i] == ')') { //  checks if the current character in the user_input string is either an opening parenthesis '(' or a closing parenthesis ')'
		// if the current character is an opening parenthesis '(', it adds an opening parenthesis to the equation vector and pushes the character onto the z stack.
		if (user_input[i] == '(') { 
			equation.push_back("(");
        	z.push(user_input[i]);
      	} else {
      		// If the current character is a closing parenthesis ')', it checks if the previous character (at index i - 1) in the user_input string is a space character.
		  	if (user_input[i - 1] == ' ') {
			  equation.push_back(")"); // adds a closing parenthesis to the equation vector
			  z.pop(); // pops the top element from the z stack
       	 	} else {
				if (num != "") { // Checks if there is a number before a closed parentheses
            		if (!parse(map, var_type, num, equation, error_check)) {
              			break;
            		} if (neg_val) { // Converts negative expression to a real number
						string neg_num = "( -" + equation.back() + " )";
						equation.pop_back();
						equation.push_back(neg_num);
						neg_val = false;
            		}
            		num = "";
            		terms++;
          		}
          	equation.push_back(")");
          	z.pop();
        	}
      	}
		continue;
    }

    // Checks for unary negatives
    if ((user_input[i] == '-' && i == 0)) { // checks if the current character in the user_input string is a minus sign '-' and if it is the first character in the string (at index 0)
		// If the condition is true, it means that the minus sign '-' is used as a negation operator, indicating a negative value.
		if (!isdigit(user_input[i + 1])) { // checks if the next character (at index i + 1) in the user_input string is not a digit.
        error_check = "Unknown command! Does not match any valid command of the language.\n";
      }
      else {
      	// If the next character is a digit, it means that the minus sign is indeed used as a negation operator
        neg_val = true; // sets the neg_val flag to true to indicate that a negative value is detected
      }
      continue; // continues to the next iteration of the loop.
    }

    // Checks for the format negatives in the expression
    if (user_input[i] == '-' && equation.size() != 0) { //  checks if the current character in the user_input string is a minus sign '-' and if the equation vector is not empty
		if (user_input[i - 1] == '(' || user_input[i - 2] == '(') { // checks if the character before the current character (at index i - 1) or two characters before the current character (at index i - 2) in the user_input string is an opening parenthesis '('
			if (!isdigit(user_input[i + 1])) { // checks if the next character (at index i + 1) in the user_input string is not a digit.
          		error_check = "Unknown command! Does not match any valid command of the language.\n";
        	}
        	// it means that the minus sign is indeed used as a negation operator
        	else neg_val = true;
        	// continues to the next iteration of the loop
        	continue;
      	}
    if (operator_check(user_input[i - 1])) {
    	//  the code checks if the next character (at index i + 1) in the user_input string is not a digit.
        if (!isdigit(user_input[i + 1])) { // invalid use of the minus sign as a command that doesn't match any valid command of the language.
          error_check = "Unknown command! Does not match any valid command of the language.\n";
        }
        else neg_val = true; //  the minus sign is indeed used as a negation operator
        continue; // continues to the next iteration of the loop
    }
    if (user_input[i-1]==' '&&operator_check(equation.back()[0])){
        if (!isdigit(user_input[i + 1])) { // checks if the next character (at index i + 1) in the user_input string is not a digit
          error_check = "Unknown command! Does not match any valid command of the language.\n"; // an invalid use of the minus sign as a command that doesn't match any valid command of the language.
        }
        else neg_val = true; // a negative value is detected
        continue; // continues to the next iteration of the loop
      }
    }

    // Checks for operators
    if (operator_check(user_input[i])) { // checks if the current character in the user_input string is an operator (using the operator_check function).
		if (i == 0) {
			// the operator is not used correctly because there are no operands before it
        	error_check = "Unknown command! Does not match any valid command of the language.\n";
        	break;
      	}
      	// checks if the character before the current character (at index i - 1) in the user_input string is neither a space character nor a closing parenthesis ')'.
      	if (!(user_input[i - 1] == ' ') && !(user_input[i - 1] == ')')) {
        	if (!parse(map, var_type, num, equation, error_check)) {
          		break;
        	}
        	// If neg_val is true, it means that a negative value was detected, so the code converts the expression to a real number by adding a negation symbol and parentheses.
        	if (neg_val) {
          		string neg_num = "( -" + equation.back() + " )";
          		equation.pop_back();
          		equation.push_back(neg_num);
          		neg_val = false;
        	}
        terms++;
      	}
      	if (equation.size() != 0) { // checks if the equation vector is not empty
        	if (operator_check(equation.back()[0]) && equation.back().length() == 1) { //  If it is not empty, it checks if the last element in the equation vector is an operator (using the operator_check function)
          		error_check = "Unknown command! Does not match any valid command of the language.\n";
          		break;
        	}
      	}
      	num = user_input[i]; // assigns the current character to the num string, indicating a new operand
      	equation.push_back(num); // adds the num string to the equation vector
      	op++; //  increments the op counter
      	num = ""; // resets the num string
      	if (terms != op) { // checks if the number of terms (operands) is equal to the number of operators 
        	error_check = "Unknown command! Does not match any valid command of the language.\n"; // the expression is not balanced
      	}
      	continue; //  continues to the next iteration of the loop
    }

    // Checks for spaces in between operands and operators
    if (user_input[i] == ' ') { // checks if the current character in the user_input string is a space character
		if (equation.size() != 0) {
			if (num != "") { //  checks if the num string is not empty
				if (!parse(map, var_type, num, equation, error_check)) { // calls the parse function with some arguments to process the number, store it in the equation vector, and perform other necessary operations
            		break; // If the parsing operation fails (returns false), the code breaks out of the loop
          		}
        	terms++;
        	continue;
        	}	
        if (!operator_check(equation.back()[0]) && (equation.back()[0] != ')' && equation.back()[0] != '(')) { // the num string is empty
			if (!parse(map, var_type, num, equation, error_check)) { // calls the parse function to process the number and checks if the next character after the number (at index 1 of the last element) is a digit
            	break;
          	}
        if (!operator_check(equation.back()[0]) && isdigit(equation.back()[1])) { // it means that there is a missing operator between the number and the next expression, leading to an error
            error_check = "Unknown command! Does not match any valid command of the language.\n";
        }
        terms++;
        }
      } else { //  the current character is not a space character
	  		if (!parse(map, var_type, num, equation, error_check)) { // assumes that it is a part of a number or an operator and calls the parse function to process the num string, store it in the equation vector, and perform other necessary operations
          	break; // If the parsing operation fails (returns false), the code breaks out of the loop.
		}
        terms++;
      }
      num = ""; //  resets the num string to an empty string
      continue; // continues to the next iteration of the loop
    }

    // If the operand or operator isn't in a parentheses
    if (!(user_input[i] == ')') && !(user_input[i] == '('))
		num += user_input[i];

    // Checks for the end of the expression
    if (i == len - 1) { // checks if the current index i is equal to the last index of the input string (len - 1)
		if (!parse(map, var_type, num, equation, error_check)) { // calls the parse function to process the number, store it in the equation vector, and perform other necessary operations
        	break; // If the parsing operation fails (returns false), the code breaks out of the loop
      	}
      	if (neg_val) { // a negative value was detected
        	string neg_num = "( -" + equation.back() + " )"; // creates a new string neg_num by adding a negation symbol and parentheses around the last element in the equation vector
        	equation.pop_back(); // removes the last element from the equation vector using pop_back()
        	equation.push_back(neg_num); // adds the neg_num string to the equation vector
        	neg_val = false; // sets the neg_val flag to false to indicate that the negative value has been processed
      	}
      	terms++; //  keep track of the number of terms (operands) in the equation
    }
}
	//  checks if the error_check string is not equal to "0"
  	if (error_check != "0") {
    	return error_check; // an error message has been assigned to error_check during the execution of the previous code
  	}
  	if (terms != 1) { // Checks for sufficient operators/operands
    	if (terms != op + 1) { // further checks if the number of terms is not equal to the number of operators (op) plus 1
      		error_check = "Unknown command! Does not match any valid command of the language. \n"; // the equation is not well-formed
    	}
  	}
  	if (error_check != "0") {
    	return error_check; // means that an error message has been assigned to error_check during the execution of the previous code
  	}

  	// Makes & returns the final result
  	int eq_len = equation.size(); // calculates the initial size of the equation vector and assigns it to the variable eq_len
  	for (i = 0; i < eq_len; i++) { // indicates that we want to process each element in the equation vector
    	string result = equation.front(); // retrieves the front (first) element from the equation vector and assigns it to the variable result
    	placeholder += result + " "; //  appends the result string and a space character to the placeholder string.
    	equation.pop_front(); // after processing the front element, this line removes it from the equation vector using the pop_front() function
  	}
  	string result = evaluate(placeholder);
  	return result;
}

// This is the entry point of the program. It defines the main function.
int main(){
	// Declare several variables used in the program
	string user;
	string user_var;
	string expr;
	string key_val;
	string error_check;
	unordered_map <string, string> map;
	int eval;
	
	// Prints a message to the console, indicating that the SNOL environment is active and the user can start entering commands.
	cout << "The SNOL environment is now active, you may proceed with giving your commands.\n";
	 
	// Starts a loop that continues until the user enters "EXIT!" as the command, indicating the desire to exit the program
  	while (user != "EXIT!") {
	  cin.clear(); // clear any previous input errors 
	  error_check = "0"; // to indicate no error
	  cout << "\nCommand: ";
	  getline(cin, user); // prompt the user to enter a command and read the input from the console into the user variable
	  user = regex_replace(user, regex("^ +| +$|( ) +"), "$1"); // uses regular expressions to remove leading and trailing spaces from the user input
	  	if (assignment_check(user, user_var, expr)) { // checks if the user's command is an assignment statement
			if (variable_check(user_var)){ //  checks if the variable name (user_var) in the assignment statement is valid
        		expr = evaluate_math(expr, map, error_check); // Evaluates the mathematic expression "expr"
        	if (expr == "ERROR") { // indicates that the command is unknown
          		error_check = "Unknown command! Does not match any valid command of the language.\n";
        } if (error_check != "0") { // checks if there is an error message 
			cout << "SNOL> "<< error_check; // If so, it prints the error message to the console
			continue; // continues to the next iteration of the loop
        } else {
			// Insert variable-value pair in the "map" if the variable does not exist
			if (map.find(user_var) == map.end()) { 
				map.insert(make_pair(user_var, expr));
			} else { // Updates the variable-value pair in the "map" if the variable exists
				map[user_var] = expr;
			}
        }
    } else {
		// Handles the case where the user entered "PRINT" or "BEG" without specifying a variable
		if (user_var == "PRINT" || user_var == "BEG") {
          cout << "SNOL> Invalid word [" << user_var << "].\n"; // prints an error message indicating the invalid word 
        } continue; // continues to the next iteration of the loop
      }
      continue;
    }
	
	int command = command_check(user); // checks the user's command type
    if (user == "EXIT!") { // checks if the user wants to exit by entering "EXIT!"
		cout << "\n\nInterpreter is now terminated..." << endl;
		return 0;  // terminates the program
    } else if (command == 0) { // checks if the command type is 0, indicating an unknown command
		error_check = "Unknown command! Does not match any valid command of the language.\n";
		cout << "SNOL> " << error_check; // prints the error message to the console
    } else if (command == 1) { // handles the case where the command type is 1, indicating a "BEG" command
		key_val = user.substr(4, user.length());
		if (variable_check(key_val)) { // extracts the key value from the user input
			beg_command(key_val, map, error_check); // calls the beg_command function to perform the corresponding action
      	}
    } else if (command == 2) { // handles the case where the command type is 2, indicating a "PRINT" command
		key_val = user.substr(6, user.length()); // extracts the value string from the user input 
		eval = evaluate_number(key_val); // evaluates the type of value
		switch (eval) {
			case 1:
			case 2:
				cout << "SNOL> " << key_val;
				break;
			case 3:
				if (variable_check(key_val)) {
					print_command(key_val, map, error_check);
          		}
          		break;
      	}
		if (error_check != "0") { // More specified error
			cout << "SNOL> "<< error_check;
    	}
	} else if (command == 3) { // handles the case where the command type is 3, indicating an EXPRESSION to be EVALUATED
		expr = evaluate_math(user, map, error_check); // evaluate the expression
			if(expr == "ERROR") { // If command is unknown
				error_check = "Unknown command! Does not match any valid command of the language.\n";
      		} else if (error_check != "0") { // More specified error
			  	cout << "SNOL> "<< error_check;
      		}
   		}
  	}
}