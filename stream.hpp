#ifndef HEADER_STREAM
#define HEADER_STREAM

#include <stdio.h> // file stream reading
#include <array> // file stream buffer

struct Stream{ // data input stream
	virtual std::string get_string() = 0;
	virtual void set_memento() = 0;
	virtual void get_memento() = 0;
	virtual bool is_finished() = 0;
};

struct FileStream : Stream{ // basic file string reader
	
	// file
	FILE *file;
	bool is_opened;
	long saved_position;
	
	// buffer
	static constexpr int bufferSize = 256;
	std::array<char,bufferSize> buffer;
	int bufferIndex;
	
	// file
	bool file_end();
	bool fill_buffer();
	bool step_buffer();
	bool is_spacing(char c);
	FileStream(const char *fileName);
	~FileStream();
	
	std::string get_string();
	void set_memento();
	void get_memento();
	bool is_finished();
};

#endif