#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <stdexcept>

#include "types.h"


#include <iostream>
//	����� ������ � ������.
constexpr unsigned NUM_IP_PARTS(4);
//	����������� ������ ����� � ����������� � ������ �������
tupleIp parseIp(std::vector<std::string>&& vsIp);

//	������� ������ ���������� �� ������
void print_pool (const vecIp& poll_out);

//	������� ���� �������� �� ������
void print_ip (const tupleIp& ip);

//	���������� ������ ������� �� ������ �������� �����
template <typename T>
vecIp filter_any(const vecIp& input, const T&& byte){
	//	�������� ����������
	vecIp filterResult;
	//	���������� ������� ������
	std::copy_if(input.begin(), input.end(),
				back_inserter(filterResult), 
				//	������ ������ ��, � ������� ���� ������ ����
				[byte](const tupleIp& test_value){
					return (std::get<0>(test_value) == byte ||
							std::get<1>(test_value) == byte ||
							std::get<2>(test_value) == byte ||
							std::get<3>(test_value) == byte );
				});
	return filterResult;
}

//	��������� ��� �������� variadic template
//	N - ����� �������������� ����� 
template<int N=0, typename T>
std::vector<tupleIp> filter (vecIp& input, const T&& final_byte){
	//	��������, ��� �� �������� �� ������� �������
	static_assert (N>=0 && N<NUM_IP_PARTS, "Wrong byye number (N) in filter!");
	//	�������� ����������
	vecIp filterResult;	
	//	������� � ��������� ���������� ��������
	std::copy_if(input.begin(), input.end(),
				back_inserter(filterResult), 
				//	��������� ���������� �����. ����� �������� � ������� ������ �� ��������� �������
				[final_byte](const tupleIp& test_value){
					return (std::get<N>(test_value) == final_byte);
				}
	);
	//	���������� ���������
	return filterResult;
}
//	�������� ��� ��� ���������� �� ������
//	N - ����� �������������� ����� 
//	Args - ���������� ����� (�� ���� ������������ ���� ��� ���������. ���� � double ����� ���� ������ %( )

template<int N=0, typename T, typename... Args>
std::vector<tupleIp> filter (const vecIp& input, const T&& curr_byte, Args... other){	
	//	��������, ��� �� �������� �� ������� �������
	static_assert (N>=0 && N<NUM_IP_PARTS, "Wrong byte number (N) in filter!");
	//������ ��� �����������
	vecIp correct;
	//	�������� ���������� � ��������� (���������� �������� �� ������)
	std::copy_if(input.begin(), input.end(),
				back_inserter(correct),
				//	��������� ���������� �����. ����� �������� � ������� ������ �� ��������� �������				
				[curr_byte](const tupleIp& test_value){
					return (std::get<N>(test_value) == curr_byte);
				}
	);
	//	������� ������ �� ��������� ��������������� ������ � ���������� ���������
	return filter<N+1>(correct, std::forward<Args>(other)...);	
}

