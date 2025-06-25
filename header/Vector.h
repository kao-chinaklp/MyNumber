#ifndef VECTOR_H_
#define VECTOR_H_

#include <cassert>

typedef unsigned int ui;

template<class T>
void inline swap(T& a, T& b)noexcept{
    T c=a;
    a=b;
    b=c;
}

template<class T>
class Vector{
    public:
        typedef T value_type;
        typedef value_type* iterator;
        struct reverseIterator{
            reverseIterator()=default;
            reverseIterator(const Vector<T>::iterator& it):rIt(it){}
            reverseIterator(const reverseIterator& it):rIt(it.rIt){}
            reverseIterator(reverseIterator&& it)noexcept:rIt(it.rIt){it.rIt=nullptr;}
            reverseIterator& operator=(const Vector<T>::iterator& it){rIt=it;return *this;}
            reverseIterator& operator=(const reverseIterator& it){rIt=it.rIt;return *this;}
            reverseIterator& operator=(reverseIterator&& it)noexcept{rIt=it.rIt,it.rIt=nullptr;return *this;}
            reverseIterator& operator++(){--rIt;return *this;}
            reverseIterator operator++(int){auto tmp=*this;--rIt;return tmp;}
            reverseIterator& operator--(){++rIt;return *this;}
            reverseIterator operator--(int){auto tmp=*this;++rIt;return tmp;}
            reverseIterator operator+(const long long num){return rIt-num;}
            reverseIterator operator-(const long long num){return rIt+num;}
            reverseIterator& operator+=(const long long num){rIt-=num;return *this;}
            reverseIterator& operator-=(const long long num){rIt+=num;return *this;}
            bool operator==(const reverseIterator& it)const{return rIt==it.rIt;}
            bool operator!=(const reverseIterator& it)const{return rIt!=it.rIt;}
            T& operator*(){return *rIt;}

            Vector<T>::iterator rIt;
        };

        Vector():Vector(1){IsInit=true;};
        explicit Vector(ui size, T val=0);
        explicit Vector(int size, T val=0);
        Vector(iterator _start, iterator _end);
        Vector(const Vector<T>& x);
        Vector(Vector<T>&& x)noexcept;
        ~Vector();

        Vector<T>& operator=(const Vector<T>& x);
        Vector<T>& operator=(Vector<T>&& x)noexcept;
        T& operator[](ui pos);
        const T& operator[](ui pos)const;

        [[nodiscard]] ui Size()const;
        [[nodiscard]] bool Empty();
        [[nodiscard]] bool Empty()const;
        void Clear();
        const iterator& EOS()const;
        const iterator& cbegin()const;
        const iterator& cend()const;
        const iterator& begin()const;
        const iterator& end()const;
        const reverseIterator& crbegin()const;
        const reverseIterator& crend()const;
        iterator& begin();
        iterator& end();
        reverseIterator& rbegin();
        reverseIterator& rend();
        T& Front();
        T& Back();

        void Assign(ui size, const T& val);
        void Assign(iterator _start, iterator _end);
        void PushBack(const T& val);
        void PopBack();
        iterator Insert(ui pos, const T& val);
        iterator Insert(iterator p, const T& val);
        iterator Erase(iterator p);
        iterator Erase(ui pos, ui size=1);

        void ShrinkToFit();
        void Reserse(ui size);
        void Resize(ui size, const T& val=T());

    protected:
        [[nodiscard]] ui Capacity()const;

    private:
        bool IsInit;
        iterator Start;
        iterator Finish;
        iterator EndOfStorage;
        reverseIterator Rstart;
        reverseIterator Rfinish;
};

template<typename iterator>
void Reverse(iterator first, iterator last){
    while((first!=last)&&(first!=--last)){
        swap(*first, *last);
        ++first;
    }
}

template<class T>
Vector<T>::Vector(ui size, const T val){
    IsInit=false;
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
    IsInit=false;
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
    IsInit=false;
    while(_start!=_end){
        PushBack(*_start);
        ++_start;
    }
    Rstart=Finish-1;
    Rfinish=Start-1;
}

template<class T>
Vector<T>::Vector(const Vector<T>& x){
    IsInit=false;
    Start=new T[x.Capacity()];
    for(int i=0, len=x.Size();i<len;i++)
        Start[i]=x[i];
    Finish=Start+x.Size();
    Rstart=Finish-1;
    Rfinish=Start-1;
    EndOfStorage=Start+x.Capacity();
}

template<class T>
Vector<T>::Vector(Vector<T>&& x)noexcept{
    IsInit=false;
    this->Start=x.Start;x.Start=nullptr;
    this->Finish=x.Finish;x.Finish=nullptr;
    this->EndOfStorage=x.EndOfStorage;x.EndOfStorage=nullptr;
    this->Rstart=x.Rstart;x.Rstart=nullptr;
    this->Rfinish=x.Rfinish;x.Rfinish=nullptr;
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& x){
    IsInit=false;
    Start=new T[x.Capacity()];
    for(int i=0, len=x.Size();i<len;i++)
        Start[i]=x[i];
    Finish=Start+x.Size();
    Rstart=Finish-1;
    Rfinish=Start-1;
    EndOfStorage=Start+x.Capacity();
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& x)noexcept{
    IsInit=false;
    this->Start=x.Start;x.Start=nullptr;
    this->Finish=x.Finish;x.Finish=nullptr;
    this->EndOfStorage=x.EndOfStorage;x.EndOfStorage=nullptr;
    this->Rstart=x.Rstart;x.Rstart=nullptr;
    this->Rfinish=x.Rfinish;x.Rfinish=nullptr;
    return *this;
}

template <class T>
T &Vector<T>::operator[](ui pos){
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
    if(Start!=nullptr)delete []Start;
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
    Rfinish=Rstart;
}

template<class T>
const typename Vector<T>::iterator& Vector<T>::EOS()const{
    return EndOfStorage;
}

template<class T>
const typename Vector<T>::iterator& Vector<T>::cbegin()const{
    return Start;
}

template<class T>
const typename Vector<T>::iterator& Vector<T>::cend()const{
    return Finish;
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
const typename Vector<T>::reverseIterator& Vector<T>::crbegin()const{
    return Rstart;
}

template<class T>
const typename Vector<T>::reverseIterator& Vector<T>::crend()const{
    return Rfinish;
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
typename Vector<T>::reverseIterator& Vector<T>::rbegin(){
    return Rstart;
}

template<class T>
typename Vector<T>::reverseIterator& Vector<T>::rend(){
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
    if(IsInit){
        IsInit=false;
        Clear();
    }
    Insert(end(), val);
}

template<class T>
void Vector<T>::PopBack(){
    assert(Size());
    Erase(end()-1);
}

template<class T>
typename Vector<T>::iterator Vector<T>::Insert(const ui pos, const T& val){
	return this->Insert(Start+pos, val);
}

template<class T>
typename Vector<T>::iterator Vector<T>::Insert(iterator p, const T& val){
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
    Rstart=Finish-1;

    return p+1;
}

template<class T>
typename Vector<T>::iterator Vector<T>::Erase(iterator p){
    assert(p>=Start);
    assert(p<Finish);

    iterator pos=p;
    while(pos<Finish){
        *pos=*(pos+1);
        ++pos;
    }
    --Finish;
    Rstart=Finish-1;

    return p;
}

template<class T>
typename Vector<T>::iterator Vector<T>::Erase(const ui pos, const ui size){
    assert(pos+size<=this->Size());

    for(ui p=pos+size, len=this->Size();p<len;p++)
        Start[p-size]=Start[p];
    this->Finish-=size;
    this->Rstart=this->Finish-1;
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
        Rstart=Finish-1;
        Rfinish=Start-1;
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
    Rstart=Finish-1;
    Rfinish=Start-1;
    IsInit=false;
}

template<class T>
ui Vector<T>::Capacity()const{
    return EndOfStorage-Start;
}

#endif
