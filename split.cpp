#include "split.h"

std::vector<std::string> split(const std::string & str, char d)
{
    //	Вектор для хранения результата
	std::vector<std::string> r;
	
	//	Инициализируем переменные и ищем первое вхождение разделителя
    std::string::size_type start = 0;
    auto stop = str.find_first_of(d);
	
	//	Пока разделитель есть
    while(stop != std::string::npos)
    {
		//	Вырезаем кусок от начала или прошло разделителя и заносим в результат
        r.push_back(str.substr(start, stop - start));

		//	Переходим к следующему
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
	//	Добавляем часть после последнего разделителя (или целиком, если разделителя не было)
    r.push_back(str.substr(start));
	//	Делаем перемещение (пробую изежать копирования)
    return std::move(r);
}