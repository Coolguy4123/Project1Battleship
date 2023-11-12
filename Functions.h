/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   Functions.h
 * Author: Freeman Yiu
 *
 * Created on 11 November 2023, 11:22 pm
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <set>
using namespace std;
#ifdef __cplusplus
extern "C" {
#endif
    
void assign(Game&,int,char);
bool collidesVert(Game&,int,int,int);
bool collidesHorz(Game&,int,int,int);
bool pdetermineHit(Game&,int,int);
bool edetermineHit(Game&,int,int);
bool pdetermineError(Game&,int,int,set<char> const &);
bool edetermineError(Game&,int,int,set<char> const &);
bool pOOB(int,int);
int chartoInt(char);
char getletter(char*,int);

#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H */

