#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <stdexcept>

#include "types.h"


#include <iostream>
//	Число блоков в адресе.
constexpr unsigned NUM_IP_PARTS(4);
//	Преобразует вектор строк с айпишниками в кортеж адресов
tupleIp parseIp(std::vector<std::string>&& vsIp);

//	Выводит вектор айпишников на печать
void print_pool (const vecIp& poll_out);

//	Выводит один айпишник на печать
void print_ip (const tupleIp& ip);

//	Фильтрация набора адресов по ЛЮБОМУ значению байта
template <typename T>
vecIp filter_any(const vecIp& input, const T&& byte){
	//	Хранение результата
	vecIp filterResult;
	//	Перебираем входной вектор
	std::copy_if(input.begin(), input.end(),
				back_inserter(filterResult), 
				//	Заноим только те, у которых есть нужный байт
				[byte](const tupleIp& test_value){
					return (std::get<0>(test_value) == byte ||
							std::get<1>(test_value) == byte ||
							std::get<2>(test_value) == byte ||
							std::get<3>(test_value) == byte );
				});
	return filterResult;
}

//	Окончание для рекурсии variadic template
//	N - номер анализируемого байта 
template<int N=0>
std::vector<tupleIp> filter (vecIp& input){
	return input;
}
//	Основной код для фильтрации по байтам
//	N - номер анализируемого байта 
//	Args - переданные байты (не стал ограничивать типы для сравнения. Хотя с double может быть весело %( )

template<int N=0, typename T, typename... Args>
std::vector<tupleIp> filter (const vecIp& input, const T&& curr_byte, Args... other){	
	//	Проверим, что не выползли за пределы кортежа
	static_assert (N>=0 && N<NUM_IP_PARTS, "Wrong byte number (N) in filter!");
	//Вектор для результатов
	vecIp correct;
	//	Копируем подходящие в результат (переданный аргумент не портим)
	std::copy_if(input.begin(), input.end(),
				back_inserter(correct),
				//	Проверяем совпадение байта. номер элемента в кортеже берётся из параметра шаблона				
				[curr_byte](const tupleIp& test_value){
					return (std::get<N>(test_value) == curr_byte);
				}
	);
	//	Передаём дальше на обработку отфильтрованный вектор и оставшиеся аргументы
	return filter<N+1>(correct, std::forward<Args>(other)...);	
}

