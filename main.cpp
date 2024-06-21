#include "stream.hpp" // data streaming
#include "context.hpp" // data storage
#include "semantic.hpp" // data extraction

#include <stdio.h> // context displaying

// interpretation

struct Interpreter{
	std::unique_ptr<Semantic> semantics;
	std::unique_ptr<Context> interpret(Stream *stream){
		std::unique_ptr<Context> context = std::make_unique<Context>();
		semantics->build(context.get());
		semantics->parse(stream, context.get());
		return context;
	}
};

struct BasicInterpreter : Interpreter{ // interpreter
	BasicInterpreter(){
		std::unique_ptr<SemanticInput> intInput = std::make_unique<SemanticField<int>>(); // expect input data to be an int
		std::unique_ptr<SemanticFormat> intFormat = std::make_unique<SemanticFormat>(std::move(intInput)); // expect format with a name and int input data
		std::unique_ptr<SemanticVariable> intInstruction = std::make_unique<SemanticVariable>(std::move(intFormat)); // expect unknown-name attribute of type int
		semantics = std::make_unique<SemanticLoop>(std::move(intInstruction)); // expect unknown-name attributes of type int
	}
};

// main

int main(int argc, char *argv[]){
	
	// arguments
	std::string fileName = "testStrIntLoop.txt";
	if(argc > 1) fileName = argv[1];
	
	// stream
	FileStream stream(fileName.c_str());
	
	// interpreter
	BasicInterpreter interpreter;
	
	// output
	std::unique_ptr<Context> context = interpreter.interpret(&stream);
	
	// display
	printf("context output:\n%s", context->to_string().c_str());
	
	return 0;
}