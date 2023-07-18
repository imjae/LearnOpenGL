#pragma once

#include<glad/glad.h>

#include<string>
#include <fstream>
#include <sstream>
#include <iostream>

class MyShader
{
public:
    // program ID
    unsigned int ID;

    // 생성자는 shader를 읽고 생성합니다.
    MyShader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // shader를 활성화하고 사용합니다.
    void use();
    // Uniform 유틸리티 함수들
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setUniform3f(const std::string& name, float value1, float value2, float value3) const;
    void setUniform4f(const std::string& name, float value1, float value2, float value3, float value4) const;
};

