#include <iostream>

using namespace std;
template<class Type>
class stackt{
public:
    stackt(int element=128);
    //stackt(const stackt<Type>&);
    ~stackt();
    void push(const Type&);
    void pop(Type&);
    void stackTop(Type&)const;
    bool stackIsEmpty()const;
    bool stackIsFull()const;
    void print();
private:
    Type *stack;
    int top,maxSize;
};
template<class Type>
stackt<Type>::~stackt(){
    top=-1;
}
template<class Type>
stackt<Type>::stackt(int element){
    top = -1;
    maxSize = element;
    stack = new Type[maxSize];
}
template<class Type>
void stackt<Type>::push(const Type&t){
    if(!stackIsFull()){
       top++;
       stack[top] = t;
    }
    else
        cout<<"this stack is full on push"<<endl;
}

template<class Type>
void stackt<Type>::pop(Type&t){

    if(!stackIsEmpty()){
       t = stack[top];
       top--;
       cout<<"the "<<t<<" item is deleted"<<endl;
    }
    else
        cout<<"this stack is Empty on pop"<<endl;
}
template<class Type>
void stackt<Type>::stackTop(Type&t)const{

    if(!stackIsEmpty()){
       t = stack[top];
       cout<<t<<endl;
    }
    else
        cout<<"this stack is Empty on pop"<<endl;
}

template<class Type>
bool stackt<Type>::stackIsFull()const{
    return (top >= maxSize-1);
}
template<class Type>
bool stackt<Type>::stackIsEmpty()const{
    return (top < 0);
}

template<class Type>
void stackt<Type>::print(){

    if(!stackIsEmpty()){
      for(int i =top ; i >=0 ;i--){
        cout<< stack[i]<<endl;
      }
    }
    else
        cout<<"this stack is Empty"<<endl;
}
int main()
{
    int t;
    stackt<int> s(10);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(30);
    cout<<"the first print"<<endl;
    s.print();
    s.pop(t);
    s.pop(t);
     cout<<"the second print"<<endl;
    s.print();
    cout<<"new pushed items"<<endl;
    s.push(50);
    s.push(60);
    s.push(70);
     s.push(70);
    s.print();
    cout<<"the top item is "<<endl;
    s.stackTop(t);


    return 0;
}
