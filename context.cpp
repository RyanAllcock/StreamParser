#include "context.hpp"

// entry

std::string ContextEntry::to_string(){
	return name;
}

// context

void Context::add(std::shared_ptr<ContextEntry> entry){
	data.push_back(std::move(entry));
}

std::string Context::to_string(){
	std::string output;
	for(int i = 0; i < data.size(); i++) output += data[i]->to_string() + "\n";
	return output;
}