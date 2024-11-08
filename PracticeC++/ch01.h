#ifndef _CH01_H__
#define _CH01_H__

void Ch01_00();
void Ch01_01();
void Ch01_02();
void Ch01_03();
void Ch01_04();
void Ch01_05();
void Ch01_06();

int BoxVolume(int l = 1);
int BoxVolume(int, int);
int BoxVolume(int, int, int);

namespace BestCom {
	void SimpleFunc(void);
	void PrettyFunc(void);
	namespace BestCom_2 {
		void MainFunc(void);
	}
}
namespace ProgCom {
	void SimpleFunc(void);
	void PrettyFunc(void);
}

#endif

