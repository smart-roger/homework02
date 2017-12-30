#define BOOST_TEST_MODULE	test_split
#include <iostream>
#include "split.h"

#include <boost/test/unit_test.hpp>
//#include <boost/test/unit_test_parameters.hpp>

BOOST_AUTO_TEST_SUITE(test_split)

// ("",  '.') -> [""]
BOOST_AUTO_TEST_CASE(test_split_case_1){	
	auto v = split("",  '.');
	BOOST_TEST_MESSAGE("v[0]: "<<v.at(0));	
	BOOST_CHECK( (1==v.size()) && (""==v.at(0)));
}

// ("11", '.') -> ["11"]
BOOST_AUTO_TEST_CASE(test_split_case_2){
	auto v = split("11",  '.');	
	BOOST_TEST_MESSAGE("v[0]: "<<v.at(0));
	BOOST_CHECK( (1==v.size()) && ("11"==v.at(0)));
}

// ("..", '.') -> ["", "", ""]
BOOST_AUTO_TEST_CASE(test_split_case_3){
	auto v = split("..",  '.');
	BOOST_CHECK( (3==v.size()) && (""==v.at(0))
								&& (""==v.at(1))
								&& (""==v.at(2)));
}

// ("11.", '.') -> ["11", ""]
BOOST_AUTO_TEST_CASE(test_split_case_4){
	auto v = split("11.",  '.');
	BOOST_CHECK( (2==v.size()) && ("11"==v.at(0)) && (""==v.at(1)));
}

// (".11", '.') -> ["", "11"]
BOOST_AUTO_TEST_CASE(test_split_case_5){
	auto v = split(".11",  '.');
	BOOST_CHECK( (2==v.size()) && (""==v.at(0)) && ("11"==v.at(1)));
}

// ("11.22", '.') -> ["11", "22"]
BOOST_AUTO_TEST_CASE(test_split_case_6){
	auto v = split("11.22",  '.');
	BOOST_CHECK( (2==v.size()) && ("11"==v.at(0)) && ("22"==v.at(1)));
}

}