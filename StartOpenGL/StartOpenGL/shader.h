#pragma once

#ifndef SHADER
#define SHADER

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
	unsigned int ID;

public: Shader(const char* vertexPath, const char* fragmentPath);
	  void use();
	  void setBool(const std::string& name, bool value) const;
	  void setInt(const std::string& name, int value) const;
	  void setFloat(const std::string& name, float value) const;

private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif