#ifndef __SALES_WORKER_H__
#define __SALES_WORKER_H__
#include "PermanentWorker.h"

class SalesWorker : public PermanentWorker
{
private:
	int _salesResult;
	double _bonusRatio;
public:
	SalesWorker(const char*, int, int, double);
	~SalesWorker();
	SalesWorker* AddSalesResult(int);
	virtual int GetSalary() const;
	virtual void SalaryInfo() const;
};


#endif