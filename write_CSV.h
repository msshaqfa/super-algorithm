//
// Created by shaqfa on 13/02/19.
//

#ifndef MODIFIEDPSFHS_WRITE_CSV_H
#define MODIFIEDPSFHS_WRITE_CSV_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "types.h"

//template <class T>
class csv_dump{
public:
    csv_dump(std::string&);
    ~csv_dump();

    template<typename T>
    void dump(T&);

    template<typename T>
    void dump(std::vector<T>&);
    void dump(RealVec&);
    void dump(UIntVec&);

    template<typename T>
    void dump(std::vector<std::vector<T>>&);
    void dump(RealMat&);
    void dump(UIntMat&);

private:
    std::string fname;
    std::ofstream new_file;

};
#endif //MODIFIEDPSFHS_WRITE_CSV_H
