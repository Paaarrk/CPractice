#include <iostream>

static int& vecr()
{
	int a = 4;
	return a;
}
static int* vecp()
{
	int a = 4;
	return &a;
}

void Ex0401()
{
	/*
		Reference & 
			1)	그냥 포인터이다.
			2)	보통 CallbyValue변수는 가상메모리주소 [값]을 가져오지만
				이 Reference의 경우 [값(주소)]에서 [[값(주소에 있는 값)]]을 가져온다.
			3)	언어의 규칙을 깨버리는 경우도 있다 (메모리 상에서는 가능해서)
	*/

	/*
		1. 포인터랑 같은 경우를 확인하기
			Release모드에서 컴파일러는 *vecp(); 부분을 vecr()로 변경한다
		* 이 경우 언어적으로 사라진 지역변수를 재참조 하게되므로 언어영역을 벗어난다.
		(하지만.경고는 나오지 않는다.)
		* 이런 것을 Dangling Pointer (댕글린포인터) 라고한다.
		* 지역변수에는 사용하면 안되겠다!!
	*/
	printf_s("포인터랑 같은 취급을 받는 Ref& \n");
	int x = vecr();
	int y = *vecp();
	printf_s("x: %d,y: %d\n\n", x, y);

	/*
		2. 자신의 주소를 스스로 알 수 없는 Ref
			&(&x)와 같은 식은 불가능하기 때문이다.
			그 결과 lea명령어는 사용하지 않는다.
	*/
	printf_s("자신의 주소를 알 수 없는 Ref\n");
	int a = 5;
	int* p = &a;
	int& r = a;
	printf_s("&p = %p, &r = %p, &a = %p \n", &p, &r, &a);
	printf_s("p = %p, r = %d, a = %d\n", p, r, a);
	printf_s("*p = %d\n\n", *p);
}

static void func(unsigned char* i)
{
	int a = *i;
}
static void func(char* i)
{
	int a = *i;
}
void Ex0402()
{
	/*
		OverLoading 오버로딩
		매개 변수 타입이 다르면 같은 함수 이름 사용이 가능하다.
		(const, &로는 불가능)
		const : 자료형이 아니다. 언어적으로 변경 불가하도록 하는 키워드일 뿐이므로
		& : 자료형이 아니다. 언어적인 것이라 컴파일러가 해석하는 방식을 바꿀 뿐이다.
		   -> 그냥 int와 같음, 읽는 방법이 다를 뿐이다.

			이것에 대해 조금 더 생각해보면
			int a = 1;
			int* p = &a ;
			a는 [a의주소] , &a는 a의 주소

			int& r = a;
			int* p = &r;
			r은 [[r의 주소]] = [a의 주소], &r은 [r의주소] = a의 주소

			그냥 읽기 시작하는 위치가 달라진 것일 뿐이다.

		unsigned : 자료형이 아니다. 확장할 때 signedflag를 사용하느냐 안하느냐의 차이
		 -> 하지만 오버로딩은 가능하다 (컴파일러가 알아서 필요 없는 분할이면 지움
		 -> 예시: int형 지역변수에 값을 담는데 (char*)과 (uchar*) 매개변수면 옮기는 방법이 다르기 때문에
			(movezx인지 movesx인지) 오버로딩을 해준다. 하지만 char 변수에 담으면 어떻게되든 같아서 함수 하나를 지움
		
		* 오버로딩에서 중요한 것은 매개변수 타입이 달라야 한다. (int, short, char 등등)
	*/
	int i = 10;
	func((unsigned char*) & i);
	func((char*)&i);
}