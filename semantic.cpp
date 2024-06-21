#include "semantic.hpp"

// input

std::unique_ptr<ContextEntry> SemanticInput::parse(Stream *i){ // fetch and validate input
	bool isValid = true;
	std::string name = ContextData::get<std::string>(i, isValid);
	if(!isValid) return nullptr;
	return std::make_unique<ContextEntry>(name);
}

std::string SemanticInput::to_string(){
	return "Name";
}

// format

SemanticFormat::SemanticFormat(std::unique_ptr<SemanticInput> in_field) : field(std::move(in_field)) {}

bool SemanticFormat::parse(Stream *i, Context *c){
	i->set_memento();
	std::unique_ptr<ContextEntry> entry = field->parse(i);
	if(entry == nullptr){
		i->get_memento();
		return false;
	}
	c->add(std::move(entry));
	return true;
}

std::string SemanticFormat::to_string(){
	return "Format { " + field->to_string() + " }";
}

// variable

SemanticVariable::SemanticVariable(std::unique_ptr<SemanticFormat> in_format) : format(std::move(in_format)) {}

bool SemanticVariable::parse(Stream *i, Context *c){
	if(format->parse(i, c)) return true;
	return false;
}

std::string SemanticVariable::to_string(){
	return "Variable { " + format->to_string() + " }";
}

// loop

SemanticLoop::SemanticLoop(std::unique_ptr<Semantic> in_repeat) : repeat(std::move(in_repeat)) {}

bool SemanticLoop::parse(Stream *i, Context *c){
	while(repeat->parse(i, c));
	return true;
}

void SemanticLoop::build(Context *c){
	repeat->build(c);
}

std::string SemanticLoop::to_string(){
	return "Loop { " + repeat->to_string() + " }";
}