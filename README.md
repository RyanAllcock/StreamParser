# Stream Parser
Allows complex data streams to be defined using data structures, then executed to manipulate those data streams.

## Description
Implementation of a parser using the GOF "Interpreter" behavioural design pattern. Using this pattern, a semantic tree is utilised by an interpreter, to build a data storage context, then execute on a stream using that context, to manipulate that data stream. Currently, this includes taking a file stream, building a file structure using the semantic tree, and extracting the file's data into a context.

## Instructions
- Execution: run "reader.exe" to extract the default file "testStrIntLoop.txt", or run "reader.exe *fileName*" to run execution on the specified relative path *fileName*
- Compilation: see Makefile

## Motivation
File structures are often complicated, containing inconsistent and incompatible idiosyncrasies which cause trouble during data extraction. Using an abstract framework which can enclose these potential structures, I hope to build a generic data stream manipulation tool useful for porting complicated data into programs in an easier and more developer-friendly way.

## Features
- File reader: extract entries for names, and variables with a name and typed value

## Future Goals
- Wavefront files: implement a sufficient codebase to support a semantic tree which allows the extraction of .obj and .mtl files into a model context
- Exporting: export a given context through a semantic tree, into an outgoing data stream (e.g. a file)
- Structure Definition: allow the definition of a data stream's structure, from which to generate a corresponding semantic tree for both incoming and outgoing data streams of that structure