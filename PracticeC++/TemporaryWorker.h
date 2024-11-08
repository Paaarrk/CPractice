#ifndef __TEMPORARYWORKER_H__
#define __TEMPORARYWORKER_H__
#include "Employ.h"

class TemporaryWorker:public Employ
{
private:
	int _workTime;
	int _payPerHour;
public:
	TemporaryWorker(const char*, int, int);
	~TemporaryWorker();
	TemporaryWorker* AddWorkTime(int);
	virtual int GetSalary() const;
	virtual void SalaryInfo() const;
	
};

#endif
