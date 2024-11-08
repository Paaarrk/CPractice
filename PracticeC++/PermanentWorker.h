#ifndef __PERMANENT_WORKER_H__
#define __PERMANENT_WORKER_H__
#include "Employ.h"
class PermanentWorker : public Employ
{
private:
	int _salary;
public:
	PermanentWorker();
	PermanentWorker(const char*, int);
	explicit PermanentWorker(const PermanentWorker&);
	~PermanentWorker();
	virtual int GetSalary() const;
	virtual void SalaryInfo() const;
};

#endif
