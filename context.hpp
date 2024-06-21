#ifndef HEADER_CONTEXT
#define HEADER_CONTEXT

#include "stream.hpp" // data access

#include <memory> // polymorphism
#include <vector> // entry storage

struct ContextData{ // basic stream data extraction interface
	template <typename T>
	static T get(Stream *i, bool &success){ // perform semantic data request
		return T();
	}
};

template<> inline std::string ContextData::get<std::string>(Stream *i, bool &success){
	std::string input = i->get_string();
	success = !input.empty();
	return input;
}

template<> inline int ContextData::get<int>(Stream *i, bool &success){
	std::string input = ContextData::get<std::string>(i, success);
	if(!success) return 0;
	int number = 0;
	for(int i = 0; success & i < input.size(); i++){
		success = success && (input[i] >= '0' && input[i] <= '9');
		number = number * 10 + (input[i] - '0');
	}
	return number;
}

struct ContextEntry{ // named entry
	std::string name;
	ContextEntry(std::string in_name) : name{in_name} {}
	virtual std::string to_string();
};

template <typename T>
struct ContextAttribute : ContextEntry{ // named valued entry
	T data;
	ContextAttribute(std::string in_name, T in_data) : ContextEntry(in_name), data{in_data} {}
	std::string to_string(){
		return name + ": " + std::to_string(data);
	}
};

struct Context{ // data entry collection
	std::vector<std::shared_ptr<ContextEntry>> data;
	Context() = default;
	Context(std::vector<std::shared_ptr<ContextEntry>> in_data) : data{in_data} {}
	void add(std::shared_ptr<ContextEntry> entry);
	std::string to_string();
};

#endif