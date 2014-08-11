/* 
 * File:   ShaderUtils.cpp
 * Author: johannes
 * 
 * Created on 11. August 2014, 16:16
 */

#include "ShaderUtils.h"

std::string ShaderUtils::readFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while (!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLhandleARB ShaderUtils::createStandardShaderPairFromFiles(char* vertSource, char* fragSource) {
    GLuint program = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);


    // Read shaders
    std::string vertShaderStr = ShaderUtils::readFile(vertSource);
    std::string fragShaderStr = ShaderUtils::readFile(fragSource);
    const char *source = vertShaderStr.c_str();


    glShaderSource(vertexShader, 1, &source, NULL);
    glCompileShader(vertexShader);
    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
        //We don't need the shader anymore.
        glDeleteShader(vertexShader);

        //Use the infoLog as you see fit.

        //In this simple program, we'll just leave
        return 0;
    }
    std::cout << "Vertex shader loaded" << std::endl;
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    source = fragShaderStr.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    //Compile the fragment shader
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
        //We don't need the shader anymore.
        glDeleteShader(fragmentShader);

        return 0;
    }
    std::cout << "Fragment shader loaded" << std::endl;

    //Vertex and fragment shaders are successfully compiled.
    //Now time to link them together into a program.
    //Get a program object.


    //Attach our shaders to our program	
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    //Link our program
    glLinkProgram(program);

    //Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *) &isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
        //The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        std::cerr << &infoLog[0] << std::endl;
        //We don't need the program anymore.	
        glDeleteProgram(program);
        //Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return 0;
    }

    //Always detach shaders after a successful link.

    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    return program;
}
