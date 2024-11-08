#ifndef __EMPLOY_HANDLER_H__
#define __EMPLOY_HANDLER_H__
#include "Employ.h"

class EmployHandler
{
private:
	Employ** _empList;
	int _empNum;
	int _capacity;
	EmployHandler(Employ&);
	void IncCap();
public:
	EmployHandler();
	void AddEmploy(Employ*);
	void ShowAllSalaryInfo() const;
	void ShowTotalSalary() const;
	~EmployHandler();
};

#endif
