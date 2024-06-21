#include "stream.hpp"

// file

bool FileStream::file_end(){
	return feof(file) || ferror(file);
}

bool FileStream::fill_buffer(){
	size_t read_amount = 0;
	do{
		if(file_end()) return false;
		read_amount = fread(buffer.data(), sizeof(char), bufferSize, file);
	} while(read_amount == 0);
	buffer[read_amount] = '\0';
	bufferIndex = 0;
	return true;
}

bool FileStream::step_buffer(){
	++bufferIndex;
	while(bufferIndex >= bufferSize || buffer[bufferIndex] == '\0'){
		if(!fill_buffer()) return false;
	}
	return true;
}

bool FileStream::is_spacing(char c){
	return c == '\n' || c == ' ';
}

FileStream::FileStream(const char *fileName) : saved_position{0} {
	file = fopen(fileName, "r");
	is_opened = file != NULL && fill_buffer();
}

FileStream::~FileStream(){
	fclose(file);
}

std::string FileStream::get_string(){
	std::string output;
	if(is_finished()) return output;
	
	// pass spacing
	while(is_spacing(buffer[bufferIndex])){
		if(!step_buffer()) return output;
	}
	
	// store string
	do{
		output += buffer[bufferIndex];
		if(!step_buffer()) return output;
	}
	while(!is_spacing(buffer[bufferIndex]));
	return output;
}

void FileStream::set_memento(){
	saved_position = ftell(file);
}

void FileStream::get_memento(){
	fseek(file, saved_position, SEEK_SET);
}

bool FileStream::is_finished(){
	return !is_opened || (buffer[bufferIndex] == '\0' && file_end());
}