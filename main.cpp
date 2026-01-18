#include <iostream>
#include <string.h>

#include <glad/glad.h>

using namespace std;

int main(int argc, char* argv[], char* envp[])
{
	cout << "Program Name: " << argv[0] << endl;
	cout << "Arguments:" << endl;
	for (int i = 1; i < argc; ++i) {
		cout << "  argv[" << i << "]: " << argv[i] << endl;
	}
	cout << "Environment Variables:" << endl;
	for (char** env = envp; *env != nullptr; ++env) {
		cout << "  " << *env << endl;
	}

	cout << "OpenGL Version: " << GLVersion.major << "." << GLVersion.minor << endl;
	return 0;
}