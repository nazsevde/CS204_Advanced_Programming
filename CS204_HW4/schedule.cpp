#include "schedule.h"

Schedule::Schedule() {
	time_slots = 0;
	data = new string*[7];
	for (int i = 0; i < 7; i++) {
		data[i] = NULL;
	}
}

Schedule::Schedule(int slots){
	this->time_slots= slots;
	data = new string*[7];
	for (int i = 0; i < 7; i++) {
		data[i] = new string[slots];
		for (int j = 0; j < slots; j++) {
			this->data[i][j] = "free";
		}
	}
}

Schedule::Schedule(const Schedule& s){
	time_slots = s.time_slots;
	data = new string*[7];
	for (int i = 0; i < 7; i++) {
		data[i] = new string[time_slots];
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < time_slots; j++) {
			data[i][j] = s.data[i][j];
		}
	}
}

const Schedule& Schedule::operator = (const Schedule& rhs) {
	if (this != &rhs) {
		for (int i = 0; i < 7; i++) {
			delete[] data[i];
		}
		delete[] data;
		time_slots = rhs.time_slots;
		data = new string*[7];
		for (int i = 0; i < 7; i++) {
			data[i] = new string[time_slots];
		}
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < time_slots; j++) {
				data[i][j] = rhs.data[i][j];
			}
		}
	}
	return *this;
}

Schedule Schedule::operator + (const Days& rhs) {
	Schedule temp = *this;

	for (int i = 0; i < time_slots; i++){
		temp.data[rhs][i] = "busy";
	}

	return temp;
}

Schedule Schedule::operator + (const int& rhs) {
	Schedule temp = *this;
	
	for (int i = 0; i < 7; i++) {
		temp.data[i][rhs] = "busy";
	}
	return temp;
}

Schedule Schedule::operator + (const Schedule& rhs) {
	Schedule temp(time_slots);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < time_slots; j++) {
			if (data[i][j] == "free" && rhs.data[i][j] == "free") {
				temp.data[i][j] = "free";
			}
			else {
				temp.data[i][j] = "busy";
			}
		}
	}
	return temp;
}

Schedule Schedule::operator * (const Schedule& rhs){
	Schedule temp(rhs.time_slots);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < time_slots; j++) {
			if (data[i][j] == "busy" && rhs.data[i][j] == "busy") {
				temp.data[i][j] = "busy";
			}
			else {
				temp.data[i][j] = "free";
			}
		}
	}
	return temp;
}

string* Schedule::operator [] (const Days& rhs) const {
	return data[rhs];
}

int Schedule::get_time_slots() const {
	return time_slots;
}

string** Schedule::get_data() const {
	return data;
}

bool operator < (const Schedule& lhs, const Schedule& rhs){
	int lhs_count = 0;
	int rhs_count = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < lhs.get_time_slots(); j++) {
			if (lhs.get_data()[i][j] == "busy") {
				lhs_count++;
			}
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < rhs.get_time_slots(); j++) {
			if (rhs.get_data()[i][j] == "busy") {
				rhs_count++;
			}
		}
	}
	if (lhs_count < rhs_count) {
		return true;
	}
	else {
		return false;
	}
}

ostream& operator << (ostream& lhs, const Schedule& rhs) {
	string ** temp = rhs.get_data();
	for (int i = 0; i < 7; i++) {

		if (Days(i) == Monday) {
			lhs << "Mo: ";
		}
		else if (Days(i) == Tuesday) {
			lhs << "Tu: ";
		}
		else if (Days(i) == Wednesday) {
			lhs << "We: ";
		}
		else if (Days(i) == Thursday) {
			lhs << "Th: ";
		}
		else if (Days(i) == Friday) {
			lhs << "Fr: ";
		}
		else if (Days(i) == Saturday) {
			lhs << "Sa: ";
		}
		else if (Days(i) == Sunday) {
			lhs << "Su: ";
		}

		//lhs << Days(i);
		for (int j = 0; j < rhs.get_time_slots(); j++) {
			lhs << rhs.get_data()[i][j] << " ";
		}
		lhs << endl;
	}
	return lhs;
}



ostream& operator << (ostream& lhs, const Days& rhs){
	
	if (rhs == Monday) {
		lhs << "Monday";
	}
	else if (rhs == Tuesday) {
		lhs << "Tuesday";
	}
	else if (rhs == Wednesday) {
		lhs << "Wednesday";
	}
	else if (rhs == Thursday) {
		lhs << "Thursday";
	}
	else if (rhs == Friday) {
		lhs << "Friday";
	}
	else if (rhs == Saturday) {
		lhs << "Saturday";
	}
	else if (rhs == Sunday) {
		lhs << "Sunday";
	}
	return lhs;
}

Schedule::~Schedule(){
	for (int i = 0; i < 7; i++) {
		delete[] data[i];
	}
	delete[] data;
}