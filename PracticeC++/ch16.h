#ifndef __CH16_H__
#define __CH16_H__

/*
C++ 의 형변환
*/

void Ch16_00();

/*
dynamic_cast<T>(obj)
 : 실행 전 검사를 하기 때문에 실행까지 시간이 걸린다.
 : B : A 관계일 때 A에  가상함수가 있다면, A -> B로 캐스팅 가능
 : B -> A 로 캐스팅 가능
 : 변환 불가시 NULL반환(포인터), 참조자에게는 bad_cast예외 발생
static_cast<T>(obj)
 : 검사과정이 짧다(실행 속도가 빠르다). 책임을 져야한다.
 : B : A 관계일 때, A -> B , B -> A 전부 캐스팅 가능, 책임은 사용자의 몫
const_cast<T>(obj)
 : const 속성을 삭제한다.
 : volatile 의 성향을 삭제한다
reinterpret_cast<T>(obj)
 : 모든 유형의 형변환을 허용한다.
 : 인트값을 1바이트 단위로 읽거나 하는 등 유용하게 사용 할 수도 있다.
 */

#endif
