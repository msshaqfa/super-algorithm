  /////////////////////////////////////////////////////
 ///               Mahmoud S. Shaqfa               ///
/////////////////////////////////////////////////////

#ifndef MODIFIEDPSFHS_MYTYPES_H
#define MODIFIEDPSFHS_MYTYPES_H

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <memory>

  /////////////////////////////////////////////////////
 ///         Handy Types Definition                ///
/////////////////////////////////////////////////////

typedef unsigned int UInt;
typedef double Real;
typedef std::string Str;
typedef std::vector<Real> RealVec;
typedef std::vector<std::vector<Real>> RealMat;
typedef std::vector<std::vector<UInt>> UIntMat;
typedef std::vector<UInt> UIntVec;

template <class T>
class Mvector{

public:
    const UInt size;
    std::vector<T> storage;

public:
    Mvector(const UInt& size = 0):size(size){resize(size);}

    Mvector(std::vector<T>& initialize):size(initialize.size()){
        for(T& s: initialize){storage.push_back(s);}
    }

    ~Mvector(){}

    UInt& maxIdx(){
        static UInt idx = 0;
        UInt j =0;
        T current = std::numeric_limits<T>::lowest();
        for (T& i : storage){
            j++;
            if(i > current){
                current = i;
                idx = j;}}
        return idx;
    }

    UInt& minIdx(){
        static UInt idx = 0;
        T current = std::numeric_limits<T>::max();
        for (T& i: storage){
            if(i < current){
                current = i;
                idx = i;}}
        return idx;
    }

    T& maxVal(){
        static T current = std::numeric_limits<T>::lowest();
        for (T& i: storage){
            if(i > current)
                current = i;}
        return current;
    }

    T& minVal(){
        static T current = std::numeric_limits<T>::max();
        for (T& i: storage){
            if(i < current){
                current = i;}}
        return current;
    }

    T& sum(){
        static T current = 0;
        for (T& i: storage){
            current+=i;}
        return current;
    }

    UInt& sum(const T& val){
        static UInt idx_sum = 0;
        for (T& i: storage){
            if (val == i){
            idx_sum+=1;}}
        return idx_sum;
    }

    T& Val(const UInt& i){return storage[i];} //setter and getter

    void fill_Vals(const std::vector<T>& fillingVector){ //vector setter
        for(UInt i =0; i<fillingVector.size(); ++i){storage[i] = fillingVector[i];}
    }

    void print(){
        std::cout <<"[";
        for (T& s: storage){
            std::cout<<" "<< s;}
        std::cout<<" ]"<<std::endl;
    }

private:
    void resize(const UInt& size){storage.resize(size);};
};

template <class M>
class Mmatrix{

public:
    const UInt cols;
    const UInt rows;
    std::vector<std::vector<M>> storage;

public:
    Mmatrix(const UInt& rows = 0, const UInt& cols = 0): rows(rows), cols(cols){resize(rows, cols);}

    Mmatrix(std::vector<std::vector<M>>& initialize)
    : cols((UInt)initialize[0].size()), rows((UInt)initialize.size()){
        for(std::vector<M>& s: initialize){storage.push_back(s);}
    }

    ~Mmatrix(){}

    std::vector<UInt>& maxIdx(){
        static M current = std::numeric_limits<M>::lowest();
        static std::vector<UInt> idx{0,0};
        for(UInt i=0; i<rows;++i){
            for(UInt j=0; j<cols; ++j){
                if(current < storage[i][j]){
                    current = storage[i][j];
                    idx[0] = i; idx[1] = j;}}}
        return idx;
    }

    std::vector<UInt>& minIdx(){
        static M current = std::numeric_limits<M>::max();
        static std::vector<UInt> idx{0,0};
        for(UInt i=0; i<rows;++i){
            for(UInt j=0; j<cols; ++j){
                if(current > storage[i][j]){
                    current = storage[i][j];
                    idx[0] = i; idx[1] = j;}}}
        return idx;
    }

    M& maxVal(){
        static M current = std::numeric_limits<M>::lowest();
        for(UInt i=0; i<rows;++i){
            for(UInt j=0; j<cols; ++j){
                if(current < storage[i][j])
                    current = storage[i][j];}}
        return current;
    }

    M& minVal(){
        static M current = std::numeric_limits<M>::max();
        for(UInt i=0; i<rows;++i){
            for(UInt j=0; j<cols; ++j){
                if(current > storage[i][j])
                    current = storage[i][j];}}
        return current;
    }

    M& sum(){
        static M current = 0;
        for(UInt i=0; i<rows;++i){for(UInt j=0; j<cols; ++j){current+=storage[i][j];}}
        return current;
    }

    UInt& sum(const M& val){
        static UInt current = 0;
        for(UInt i=0; i<rows;++i){
            for(UInt j=0; j<cols; ++j){
                if(val == storage[i][j]){
                    current++;}}}
        return current;
    }

    M& Val(const UInt& row, const UInt& col){return storage[row][col];} // setter and getter

    void replace_row(Mvector<M>& newVector, const UInt& idx){
        for (UInt i = 0; i < cols; ++i){storage[idx][i] = newVector.Val(i);}
    }

    void replace_row(std::vector<M>& newVector, const UInt& idx){
        for (UInt i = 0; i<newVector.size(); ++i){
            storage[idx][i] = newVector[i];
        }
    }

    void print(){
        for(UInt i=0; i<rows;++i){
            std::cout<<"[";
            for(UInt j=0; j<cols; ++j){std::cout<<" "<<storage[i][j];}
            std::cout<<"]"<<std::endl;}
    }

private:
    void resize(const UInt& rows, const UInt& cols){
        for(UInt i=0;i<rows;++i){storage.push_back(std::vector<M>(cols));}
    }

};

#endif //MODIFIEDPSFHS_MYTYPES_H