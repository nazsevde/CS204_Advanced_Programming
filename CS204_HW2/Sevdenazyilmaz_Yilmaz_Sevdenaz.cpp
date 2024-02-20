#include <iostream>
#include <string>
#include "feedback.h"

struct node {
	int digit;
	node* next;
};

//string get_the_feedback(string guess, int game_id);
bool checkguess(string guess);
void printlist(node* head);
void insert(node*& head, int digit);
void deletenode(node*& head, int digit);
void deletelist(node*& head);
void duplicatedelete(node*& head);
void sortlist(node*& head);
bool finddigit(node* head, int digit);
int numberofelements(node* head);
char oracle(node* head);

int main() {
	node* Possibles[3], * Impossibles[3];
	bool isterminated = 0;
	int game_id;
	string guess, feedback, secretnumber;
	cout << "Please enter a game ID.\n";
	cin >> game_id;

	for (int i = 0; i < 3; i++) {
		Possibles[i] = 0;
		Impossibles[i] = 0;
	}

	while (!isterminated) {	//Main loop
		cout << "Enter your guess.\n";
		cin >> guess;
		while (checkguess(guess) == false) {	// Checking the guess if it is valid
			cout << "Invalid guess. Enter your guess.\n";
			cin >> guess;
		}

		feedback = get_the_feedback(guess, game_id);
		for (int i = 0; i < 3; i++) {
			if (feedback[i] == 'R') {	// If the feedback is R, the digit is added to the Impossibles list of the all slots
				for (int j = 0; j < 3; j++) {
					insert(Impossibles[j], guess[i] - 48);
				}
			}
			else if (feedback[i] == 'Y') {	// If the feedback is Y, the digit is added to the Possibles list of the remaining slots but not the slot that the digit is in
				deletenode(Possibles[i], guess[i] - 48);
				insert(Impossibles[i], guess[i] - 48);

				if (!finddigit(Impossibles[((i + 1) % 3)], guess[i] - 48)) {
					insert(Possibles[((i + 1) % 3)], guess[i] - 48);
				}

				if (!finddigit(Impossibles[((i + 2) % 3)], guess[i] - 48)) {
					insert(Possibles[((i + 2) % 3)], guess[i] - 48);
				}
			}
			else if (feedback[i] == 'G') {	// If the feedback is G, the digit is added to the Impossibles list of the remaining slots but not the slot that the digit is in
				insert(Possibles[i], guess[i] - 48);
				insert(Impossibles[((i + 1) % 3)], guess[i] - 48);
				insert(Impossibles[((i + 2) % 3)], (guess[i] - 48));
				deletenode(Possibles[((i + 1) % 3)], guess[i] - 48);
				deletenode(Possibles[((i + 2) % 3)], (guess[i] - 48));
				for (int j = 0; j < 10; j++) {	// Adding the all remaining digits to the Impossibles list of the slot
					insert(Impossibles[i], j);
				}
				deletenode(Impossibles[i], guess[i] - 48);
			}
			for (int i = 0; i < 3; i++) {
				duplicatedelete(Possibles[i]);
				duplicatedelete(Impossibles[i]);
				sortlist(Possibles[i]);
				sortlist(Impossibles[i]);
			}
		}
		cout << "Linked lists:\n";
		for (int i = 0; i < 3; i++) { // Printing the linked lists
			cout << "Slot: " << i + 1 << endl;
			cout << "Impossibles: ";
			printlist(Impossibles[i]);
			cout << "Possibles: ";
			printlist(Possibles[i]);
			cout << endl;
		}
		if (numberofelements(Impossibles[0]) == 9 && numberofelements(Impossibles[1]) == 9 && numberofelements(Impossibles[2]) == 9) {
			isterminated = 1;	// Estimating the secret number
			for (int i = 0; i < 3; i++) {
				secretnumber += oracle(Impossibles[i]);
			}
		}
	}
	cout << "The secret number is: " << secretnumber << "\nCongrats! Now, deleting the lists...\n";

	for (int i = 0; i < 3; i++) { // Deleting the linked lists
		deletelist(Possibles[i]);
		deletelist(Impossibles[i]);
	}
	return 0;
}

bool checkguess(string guess){ // Checking the guess if it is valid
	if (guess.length() != 3) {
		return false;
	}
	for (int i = 0; i < 3; i++) {
		if (guess[i] < 48 || guess[i] > 57) {
			return false;
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j < 3; j++) {
			if (guess[i] == guess[j]) {
				return false;
			}
		}
	}
	return true;
}

void printlist(node* head){	// Printing the linked lists
	node* temp = head;
	while (temp != 0) {
		cout << temp->digit << " ";
		temp = temp->next;
	}
	cout << endl;
}

void insert(node*& head, int digit){	// Inserting a node to the linked list
	node* ptr = new node;
	ptr->digit = digit;
	ptr->next = head;
	head = ptr;
}

void deletenode(node*& head, int digit){	// Deleting a node from the linked list
	if (finddigit(head,digit)) {
		node* temp = head;
		if (temp->digit == digit) {
			head = head->next;
			delete temp;
		}
		else {
			while (temp->next != 0) {
				if (temp->next->digit == digit) {
					node* temp2 = temp->next;
					temp->next = temp->next->next;
					delete temp2;
					break;
				}
				temp = temp->next;
			}
		}
	}
}

void deletelist(node*& head){	// Deleting the linked lists
	node* temp = head;
	while (temp != 0) {
		node* temp2 = temp;
		temp = temp->next;
		delete temp2;
	}
}

void duplicatedelete(node*& head){	// Deleting the duplicate digits in the linked lists
	node *temp = head, *temp2;
	while (temp != 0) {
		temp2 = temp;
		while (temp2->next != 0) {
			if (temp2->next->digit == temp->digit) {
				node* temp3 = temp2->next;
				temp2->next = temp2->next->next;
				delete temp3;
			}
			else {
				temp2 = temp2->next;
			}
		}
		temp = temp->next;
	}
}

void sortlist(node*& head){	// Sorting the linked lists
	node* temp = head;
	while (temp != 0) {
		node* temp2 = temp->next;
		while (temp2 != 0) {
			if (temp->digit > temp2->digit) {
				int temp3 = temp->digit;
				temp->digit = temp2->digit;
				temp2->digit = temp3;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
}

bool finddigit(node* head, int digit){	// Checking if a digit is in the linked list
	if (head != NULL) {
		node* temp = head;
		while (temp != 0) {
			if (temp->digit == digit) {
				return true;
			}
			temp = temp->next;
		}
	}
	return false;
}

int numberofelements(node* head) {	// Counting the number of elements in the linked list
	int count = 0;
	node* temp = head;
	while (temp != 0) {
		count++;
		temp = temp->next;
	}
	return count;
}

char oracle(node* head) {	// Finding the secret digit
	for (int i = 0; i < 10; i++)
		if (!finddigit(head, i))
			return i + 48;
}