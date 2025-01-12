#include <iostream>
#include <string>

using namespace std;

enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday};

class Schedule
{
public:
	Schedule();
	Schedule(int slots);
	Schedule(const Schedule & s);
	const Schedule& operator = (const Schedule& rhs);
	Schedule operator + (const Days& rhs);
	Schedule operator + (const int& rhs);
	Schedule operator + (const Schedule& rhs);
	Schedule operator * (const Schedule& rhs);
	string* operator [] (const Days& rhs) const;
	int get_time_slots() const;
	string** get_data() const;
	~Schedule();
private:
	int time_slots;
	string** data;
};

bool operator < (const Schedule& lhs, const Schedule& rhs);
ostream& operator << (ostream& lhs, const Schedule& rhs);
ostream& operator << (ostream& lhs, const Days& rhs);
