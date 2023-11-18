#ifndef VECTOR_H_
#define VECTOR_H_
#define ui unsigned int

#include <assert.h>

template<class T>
void inline swap(T& a,T& b){
    T c=a;
    a=b;
    c=b;
}

template<class T>
class Vector{
    public:
        typedef T value_type;
        typedef value_type* iterator;
        struct reverseIterator{
            reverseIterator()=default;
            reverseIterator(const Vector<T>::iterator& it):rIt(it){}
            reverseIterator(const reverseIterator &it):rIt(it){}
            reverseIterator operator++(){return --rIt;}
            reverseIterator operator++(int){return rIt--;}
            reverseIterator operator--(){return ++rIt;}
            reverseIterator operator--(int){return rIt++;}
            reverseIterator operator+(const long long num){return rIt-num;}
            reverseIterator operator-(const long long num){return rIt+num;}
            reverseIterator operator+=(const long long num){return rIt-=num;}
            reverseIterator operator-=(const long long num){return rIt+=num;}
            bool operator==(const reverseIterator& it)const{return rIt==it.rIt;}
            bool operator!=(const reverseIterator& it)const{return rIt!=it.rIt;}
            T& operator*(const reverseIterator&);

            Vector<T>::iterator rIt;
        };

        Vector();
        Vector(ui size, const T val=0);
        Vector(int size, const T val=0);
        Vector(const iterator _start, const iterator _end);
        Vector(const Vector<T>& x);
        ~Vector();

        T& operator[](ui pos);
        const T& operator[](ui pos)const;

        ui Size()const;
        bool Empty();
        bool Empty()const;
        void Clear();
        const iterator& Begin()const;
        const iterator& End()const;
        const iterator& EOS()const;
        const iterator& begin()const;
        const iterator& end()const;
        const reverseIterator& Rbegin()const;
        const reverseIterator& Rend()const;
        iterator& Begin();
        iterator& End();
        iterator& begin();
        iterator& end();
        reverseIterator& Rbegin();
        reverseIterator& Rend();
        T& Front();
        T& Back();

        void Assign(const ui size, const T& val);
        void Assign(iterator _start, iterator _end);
        void PushBack(const T& val);
        void PopBack();
        iterator Insert(const ui pos, const T& val);
        iterator Insert(iterator p, const T& val);
        iterator Erase(iterator p);
        iterator Erase(const ui pos, const ui size=1);

        void ShrinkToFit();
        void Reserse(ui size);
        void Resize(ui size, const T& val=T());

    protected:
        ui Capacity()const;

    private:
        iterator Start;
        iterator Finish;
        iterator EndOfStorage;
        reverseIterator Rstart;
        reverseIterator Rfinish;
};

template<class T>
Vector<T>::Vector(){
    Rstart=Rfinish=Start=Finish=EndOfStorage=nullptr;
}

template<class T>
Vector<T>::Vector(ui size, const T val){
    Start=new T[size];
    Finish=Start+size;
    Rstart=Finish-1;
    Rfinish=Start-1;
    EndOfStorage=Start+size;
    for(int i=0;i<size;i++)
        Start[i]=val;
}

template<class T>
Vector<T>::Vector(int size, const T val){
    Start=new T[size];
    Finish=Start+size;
    Rstart=Finish-1;
    Rfinish=Start-1;
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
    Rstart=End()-1;
    Rfinish=Begin()-1;
}

template<class T>
Vector<T>::Vector(const Vector<T>& x){
    Start=new T[x.Capacity()];
    for(int i=0,len=x.Size();i<len;i++)
        Start[i]=x[i];
    Finish=Start+x.Size();
    Rstart=Finish-1;
    Rfinish=Start-1;
    EndOfStorage=Start+x.Capacity();
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
const typename Vector<T>::iterator& Vector<T>::Begin()const{
    return Start;
}

template<class T>
const typename Vector<T>::iterator& Vector<T>::End()const{
    return Finish;
}

template<class T>
const typename Vector<T>::iterator& Vector<T>::EOS()const{
    return EndOfStorage;
}

template<class T>
const typename Vector<T>::iterator& Vector<T>::begin()const{
    return Start;
}

template<class T>
const typename Vector<T>::iterator& Vector<T>::end()const{
    return Finish;
}

template<class T>
const typename Vector<T>::reverseIterator& Vector<T>::Rbegin()const{
    return Rstart;
}

template<class T>
const typename Vector<T>::reverseIterator& Vector<T>::Rend()const{
    return Rfinish;
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
typename Vector<T>::iterator& Vector<T>::begin(){
    return Start;
}

template<class T>
typename Vector<T>::iterator& Vector<T>::end(){
    return Finish;
}

template<class T>
typename Vector<T>::reverseIterator& Vector<T>::Rbegin(){
    return Rstart;
}

template<class T>
typename Vector<T>::reverseIterator& Vector<T>::Rend(){
    return Rfinish;
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
void Vector<T>::Assign(const ui size, const T& val){
    for(int i=0;i<size;i++)    
        *(Start+i)=val;
}

template<class T>
void Vector<T>::Assign(Vector<T>::iterator _start, Vector<T>::iterator _end){
    ui new_size=_end-_start;
    if(new_size>this->Size())
        this->Resize(new_size);
    for(ui i=0;i<new_size;i++)
        *(Start+i)=*(_start+i);
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
typename Vector<T>::iterator Vector<T>::Insert(const ui pos, const T& val){
	return this->Insert(Start+pos, val);
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
typename Vector<T>::iterator Vector<T>::Erase(const ui pos, const ui size){
    assert(pos+size<=this->Size());
    for(ui p=pos+size, len=this->Size();p<len;p++)
        Start[p-size]=Start[p];
    this->ShrinkToFit();
    return Start+pos;
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
ui Vector<T>::Capacity()const{
    return EndOfStorage-Start;
}

template<class T>
T& operator*(const typename Vector<T>::reverseIterator& rIt){
    return *rIt.rIt;
}

#endif
