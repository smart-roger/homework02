#include <iostream>
#include <algorithm>

#include "ip.h"
#include "split.h"

constexpr static const int EXPECTED_VECTOR_SIZE = 1000;

int main(int argc, char const *argv[])
{
    try
    {	//	Набор адресов, который будем обрабатывать
        vecIp ip_pool;
		//	Немного ускорим - уменьшим число перераспределений памяти
		ip_pool.reserve(EXPECTED_VECTOR_SIZE);

		//	Считываем набор адресов из ввода
        for(std::string line; std::getline(std::cin, line);){
			//Разбираем считанную строку
			auto v = split(line,'\t');
			//	Выделяем адрес и преобразуем его в кортеж
            ip_pool.emplace_back( parseIp( 
									split(v.at(0), '.')));
		}

        //reverse lexicographically sort
        std::sort (ip_pool.begin(), ip_pool.end(), std::greater<tupleIp> ());
        print_pool(ip_pool);

		//Фильтруем по значению первого байта
		auto ip = filter(ip_pool, 1);		
		print_pool(ip);
		
		//	Фильтруем по значению первого и второго байта
		ip = filter(ip_pool,46,70);
		print_pool(ip);
		
		//	Можно отфильтровать по трём байтам
		//ip = filter(ip_pool,46,161,60);
		//print_pool(ip);
		
		//По четырём байтам нет смысла фильтровать. Только если подразумевается наличие дубликатов

		//	Фильтруем по совпадению любого байта
		ip = filter_any(ip_pool, 46);
        print_pool(ip);
		
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
