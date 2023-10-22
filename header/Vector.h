#ifndef VECTOR_H_
#define VECTOR_H_
#define ui unsigned int

#include <assert.h>
#include <cstdio>
#include <algorithm>

template<class T>
class Vector{
    public:
        typedef T value_type;
        typedef value_type* iterator;

        Vector();
        Vector(ui size, const T val=0);
        Vector(int size, const T val=0);
        Vector(const iterator _start, const iterator _end);
        Vector(const Vector<T>& x);
        ~Vector();

        Vector<T> operator=(Vector<T>& x);
        const Vector<T> operator=(const Vector<T>& x);
        T& operator[](ui pos);
        const T& operator[](ui pos)const;

        ui Size()const;
        bool Empty();
        bool Empty()const;
        void Clear();
        iterator& Begin();
        iterator& End();
        iterator& EOS();
        iterator& begin();
        iterator& end();
        T& Front();
        T& Back();

        void PushBack(const T& val);
        void PopBack();
        iterator Insert(iterator p, const T& val);
        iterator Erase(iterator p);

        void ShrinkToFit();
        void Reserse(ui size);
        void Resize(ui size, const T& val=T());

    protected:
        void Swap(Vector<T>& x);
        ui Capacity()const;

    private:
        iterator Start;
        iterator Finish;
        iterator EndOfStorage;
};

template<class T>
Vector<T>::Vector(){
    Start=Finish=EndOfStorage=nullptr;
}

template<class T>
Vector<T>::Vector(ui size, const T val){
    Start=new T[size];
    Finish=Start+size;
    EndOfStorage=Start+size;
    for(int i=0;i<size;i++)
        Start[i]=val;
}

template<class T>
Vector<T>::Vector(int size, const T val){
    Start=new T[size];
    Finish=Start+size;
    EndOfStorage=Start+size;
    for(int i=0;i<size;i++)
        Start[i]=val;
}

template<class T>
Vector<T>::Vector(const iterator _start, const iterator _end){
    while(_start!=_end){
        PushBack(*_start);
        ++_start;
    }
}

template<class T>
Vector<T>::Vector(const Vector<T>& x){
    Start=new T[x.Capacity()];
    for(int i=0,len=x.Size();i<len;i++)
        Start[i]=x[i];
    Finish=Start+x.Size();
    EndOfStorage=Start+x.Capacity();
}

template<class T>
Vector<T> Vector<T>::operator=(Vector<T>& x){
    Swap(x);
    return *this;
}

template<class T>
const Vector<T> Vector<T>::operator=(const Vector<T>& x){
    T* tmp=new T[x.Capacity()];
    for(int i=0,len=x.Size();i<len;i++)
        tmp[i]=x[i];
    if(Start!=nullptr)delete []Start;
    Start=tmp;
    Finish=Start+x.Size();
    EndOfStorage=Start+x.Capacity();
    return *this;
    
}

template<class T>
T& Vector<T>::operator[](ui pos){
    assert(pos<Size());
    return Start[pos];
}

template<class T>
const T& Vector<T>::operator[](ui pos)const{
    assert(pos<Size());
    return Start[pos];
}

template<class T>
Vector<T>::~Vector(){
    delete []Start;
    Start=Finish=EndOfStorage=nullptr;
}

template<class T>
ui Vector<T>::Size()const{
    return Finish-Start;
}

template<class T>
bool Vector<T>::Empty(){
    return Finish==Start;
}

template<class T>
bool Vector<T>::Empty()const{
    return Finish==Start;
}

template<class T>
void Vector<T>::Clear(){
    Finish=Start;
}

template<class T>
typename Vector<T>::iterator& Vector<T>::Begin(){
    return Start;
}

template<class T>
typename Vector<T>::iterator& Vector<T>::End(){
    return Finish;
}

template<class T>
typename Vector<T>::iterator& Vector<T>::EOS(){
    return EndOfStorage;
}

template<class T>
typename Vector<T>::iterator& Vector<T>::begin(){
    return Start;
}

template<class T>
typename Vector<T>::iterator& Vector<T>::end(){
    return Finish;
}

template<class T>
T& Vector<T>::Front(){
    assert(Start);
    return *Start;
}

template<class T>
T& Vector<T>::Back(){
    assert(Finish-1);
    return *(Finish-1);
}

template<class T>
void Vector<T>::PushBack(const T& val){
    Insert(End(), val);
}

template<class T>
void Vector<T>::PopBack(){
    assert(Size());
    Erase(End()-1);
}

template<class T>
typename Vector<T>::iterator Vector<T>::Insert(typename Vector<T>::iterator p, const T& val){
    assert(p>=Start);
    assert(p<=Finish);
    if(Finish==EndOfStorage){
        ui len=Size();
        ui pos=p-Start;
        if(len==0)len=2;
        Reserse(len*2);
        p=Start+pos;
    }
    iterator end=Finish-1;
    while(end>=p){
        *(end+1)=*end;
        --end;
    }
    *p=val;
    ++Finish;
    return p+1;
}

template<class T>
typename Vector<T>::iterator Vector<T>::Erase(typename Vector<T>::iterator p){
    assert(p>=Start);
    assert(p<Finish);
    iterator pos=p;
    while(pos<Finish){
        *pos=*(pos+1);
        ++pos;
    }
    --Finish;
    return p;
}

template<class T>
void Vector<T>::ShrinkToFit(){
    if(Finish==EndOfStorage)return;
    Reserse(Size());
}

template<class T>
void Vector<T>::Reserse(ui size){
    if(size>Capacity()){
        ui oldSize=Size();
        T* tmp=new T[size];
        if(Start!=nullptr){
            for(int i=0;i<oldSize;i++)
                tmp[i]=Start[i];
            delete []Start;
        }
        Start=tmp;
        Finish=Start+oldSize;
        EndOfStorage=Start+size;
    }
}

template<class T>
void Vector<T>::Resize(ui size, const T& val){
    if(size<Size())Finish=Start+size;
    else {
        if(size<=Capacity()){
            while(Finish!=EndOfStorage){
                *Finish=val;
                ++Finish;
            }
        }
        else {
            ui oldSize=Size();
            T* tmp=new T[size];
            for(ui i=0, len=Size();i<len;i++)
                tmp[i]=Start[i];
            delete []Start;
            Start=tmp;
            Finish=Start+oldSize;
            EndOfStorage=Start+size;
            while(Finish!=EndOfStorage){
                *Finish=val;
                ++Finish;
            }
        }
    }
}

template<class T>
void Vector<T>::Swap(Vector<T>& x){
    std::swap(Start, x.Begin());
    std::swap(Finish, x.End());
    std::swap(EndOfStorage, x.EOS());
}

template<class T>
ui Vector<T>::Capacity()const{
    return EndOfStorage-Start;
}

#endif