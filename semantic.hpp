#ifndef HEADER_SEMANTIC
#define HEADER_SEMANTIC

#include "stream.hpp" // data access // WIP do through context?
#include "context.hpp" // data storage

#include <memory> // polymorphism
#include <vector> // ordering

struct SemanticInput{ // named data input
	virtual std::unique_ptr<ContextEntry> parse(Stream *i); // fetch and validate input
	virtual std::string to_string();
};

template <typename T>
struct SemanticField : SemanticInput{ // named single-value data input
	std::unique_ptr<ContextEntry> parse(Stream *i){
		bool isValid = true;
		std::string name = ContextData::get<std::string>(i, isValid);
		if(!isValid) return nullptr;
		T attribute = ContextData::get<T>(i, isValid);
		if(!isValid) return nullptr;
		return std::make_unique<ContextAttribute<T>>(name, attribute);
	}
	std::string to_string(){
		return "Field";
	}
};

struct SemanticFormat{ // data field input format
	std::unique_ptr<SemanticInput> field; // input type
	SemanticFormat(std::unique_ptr<SemanticInput> in_field);
	bool parse(Stream *i, Context *c); // stream data extraction
	void build(){}
	std::string to_string();
};

struct Semantic{ // base semantic structure
	virtual bool parse(Stream *i, Context *c) = 0; // return parsing success or rejection
	virtual void build(Context *c) = 0; // define local context tree ready for accepting data
	virtual std::string to_string() = 0;
};

struct SemanticVariable : Semantic{
	std::unique_ptr<SemanticFormat> format;
	SemanticVariable(std::unique_ptr<SemanticFormat> in_format);
	bool parse(Stream *i, Context *c); // parse first valid format
	void build(Context *c){}
	std::string to_string();
};

struct SemanticLoop : Semantic{ // flow
	std::unique_ptr<Semantic> repeat;
	SemanticLoop(std::unique_ptr<Semantic> in_repeat);
	bool parse(Stream *i, Context *c);
	void build(Context *c);
	std::string to_string();
};

#endif