#include "ip.h"
tupleIp parseIp(std::vector<std::string>&& vsIp){
		
	//	�������� ������ �������� �������
	if (NUM_IP_PARTS!=vsIp.size()){		
		throw std::logic_error("IP address should consist of "+std::to_string(NUM_IP_PARTS)+" parts");
	};
	
	//	�������� ������ ����� ��� �������������� ����� � �����
	std::array<unsigned char, NUM_IP_PARTS> ip_parts;
	for (unsigned char index=0; index < NUM_IP_PARTS; ++index){
		if(vsIp.at(index).empty()) 
			throw std::logic_error("Empty byte string received!");
		//	��������, ��� �������� ���������� �������� ������
		auto val = stoi(vsIp.at(index));
		if( (255<val) or (0 > val))
			throw std::logic_error("byte should have value 0...255 " + std::to_string(val) + "received");
		ip_parts[index] = static_cast<unsigned char> (val);
	}
	
	//	����������� ������ � ������
	return std::make_tuple(ip_parts[0], ip_parts[1],ip_parts[2],ip_parts[3]);
}

void print_ip (const tupleIp& ip){
	std::cout << std::to_string(std::get<0>(ip)) << "." 
							<< std::to_string(std::get<1>(ip)) << "." 
							<< std::to_string(std::get<2>(ip)) << "." 
							<< std::to_string(std::get<3>(ip))
				<< std::endl;
};

void print_pool (const std::vector<tupleIp>& poll_out){
            for(auto ip : poll_out)
                print_ip(ip);
        };

