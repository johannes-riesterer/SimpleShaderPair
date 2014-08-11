/* 
 * File:   ShaderUtils.h
 * Author: johannes
 *
 * Created on 11. August 2014, 16:16
 */

#ifndef SHADERUTILS_H
#define	SHADERUTILS_H
#include <GL/glew.h>

#include <GL/glut.h>
#include <vector>
#include <stdio.h>
#include <GL/glext.h>
#include <iostream>
#include <string>
#include <fstream>
namespace ShaderUtils {

    GLhandleARB createStandardShaderPairFromFiles(char*, char*);
    std::string readFile(const char*);


};


#endif	/* SHADERUTILS_H */

