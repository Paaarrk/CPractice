#ifndef __EMPLOY_H__
#define __EMPLOY_H__

class Employ
{
protected:
	char* _name;
public:
	Employ();
	Employ(const char* name);
	virtual ~Employ();
	virtual int GetSalary() const = 0;
	virtual void SalaryInfo() const = 0;
};

#endif