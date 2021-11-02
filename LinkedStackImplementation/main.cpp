#include <iostream>
#include <stack>
#include <cctype>
#include <stdexcept>
#include <cstring>

using namespace std;
#define N 4
#define M 5

int prec(char c);
string infixToPostfix(string s);
bool areBalnced(string expression);
bool arePair(char open , char close);

// maze of n*m matrix
int n = N, m = M;

// Coordinates of food
int fx, fy;
bool visited[N][M];

float postFixEvaluate(string exp);
bool isReachable(int maze[N][M]);

template<class dataType>
class linkedStack{
public:
    linkedStack();
    ~linkedStack();
    void pop(const dataType&);
    void pop();
    void push(const dataType&);
    bool stackIsEmpty();
    void advance();
    void print();
    void toFirst();
    void toEnd();
    dataType topStack();

private:
    struct node{
    dataType data;
    node *next;
    };

    typedef node *NodePointer;
    NodePointer top , cursor ,prev;

};
template<class dataType>
linkedStack<dataType>::linkedStack(){
    top = NULL;
    cursor = NULL;

}
template<class dataType>
linkedStack<dataType>::~linkedStack(){
    top = NULL;
    cursor = NULL;
}
template<class dataType>
void linkedStack<dataType>::push(const dataType&d){
    NodePointer pNew;
    pNew = new node;
    pNew->data = d;
    pNew->next = top;
    top = pNew;
}
template<class dataType>
dataType linkedStack<dataType>::topStack(){
    toFirst();
   return cursor->data;
}
template<class dataType>
void linkedStack<dataType>::pop(const dataType&d){
    NodePointer q;
    q = top;
    top = top->next;
    delete q;
}
template<class dataType>
void linkedStack<dataType>::pop(){
    NodePointer q;
    q = top;
    top = top->next;
    delete q;
}
template<class dataType>
bool linkedStack<dataType>::stackIsEmpty(){
    return (top == NULL);
}
template<class dataType>
void linkedStack<dataType>::advance(){
    if(!stackIsEmpty())
        cursor = cursor->next;
    else
        cout<<"the stack is empty"<<endl;
}
template<class dataType>
void linkedStack<dataType>::toFirst(){
    if(!stackIsEmpty())
        cursor = top;
    else
        cout<<"stack is empty"<<endl;

}
template<class dataType>
void linkedStack<dataType>::toEnd(){

    while(!stackIsEmpty()&& cursor!=NULL){
        advance();
}
}
template<class dataType>
void linkedStack<dataType>::print(){
    toFirst();
    while(!stackIsEmpty()&& cursor!=NULL){
        cout<<"\n"<<cursor->data<<endl;
        advance();
    }
}

int main()
{
    string str;
    linkedStack<string> s;
    s.push("shehab");
    s.push("osama");
    s.push("fathi");
    s.push("abdelazez");

    s.print();

    s.pop(str);
    cout<<"the first print is : "<<endl;

    s.print();
    s.topStack();

    cout<<"enter the expression"<<endl;

    cin>>str;
    string chickStr = (areBalnced(str))?"Balanced":"Not Balanced";
    cout<<"the expression is : "<<chickStr<<endl;

	cout << "the evaluation of the expression with post fix is : "<<postFixEvaluate(infixToPostfix(str))<<endl;



	 // Initially setting the visited
    // array to true (unvisited)
    memset(visited, true, sizeof(visited));

    // Maze matrix
    int maze[N][M] = {
        { 1, 0, 1, 1, 0 },
        { 1, 1, 1, 0, 1 },
        { 0, 0, 0, 1, 1 },
        { 1, 1, 1, 1, 1 }
    };

    // Food coordinates
    fx = 2;
    fy = 3;

    if (isReachable(maze)) {
        cout << "Path Found!" << '\n';
    }
    else
        cout << "No Path Found!" << '\n';


    return 0;
}

bool arePair(char open , char close){
    if(open == '(' && close == ')')return true;
        else if(open == '[' && close == ']')return true;
        else if(open == '{' && close == '}')return true;

    return false;
}
bool areBalnced(string expression){
 linkedStack<char> stack;
    for(int i=0; i < expression.length();i++){
        if(expression[i] == '('||expression[i] == '['||expression[i] == '{'){
            stack.push(expression[i]);
           }else if (expression[i] == ')'||expression[i] == ']'||expression[i] == '}')
           {
               if(stack.stackIsEmpty() || !arePair(stack.topStack() , expression[i]))
                return false;

               stack.pop();
           }
           }
           return (stack.stackIsEmpty());
    }

// postFix and preFix Application
float MathOperation(float op1 , float op2 , char operat){

    if(operat == '+')return op1 +op2;
    else if(operat == '-')return op1 - op2;
    else if(operat == '/')return op1 / op2;
    else if(operat == '*')return op1 * op2;
    else return 0;
}

bool isDigit(char C){
    return (C >= '0' && C <= '9');

}

// The main function that returns value of a given postfix expression
float postFixEvaluate(string exp){
linkedStack<float> stk;
for(int i=0 ; i< exp.length();i++){
    if(isDigit(exp[i]))
        stk.push(exp[i]-'0'); /* note: there is a number for every character in aski code for example the number of character 2 is 50 i want to change this value form character to real number
         ... it is simple operation get the number of character and
        subtract it from the number of character 0 which is number 48 the 50 - 48 will be 2!!!!!!! awesome we get the real number from character*/
    else{ // operator

        float op2 = stk.topStack();
        stk.pop();
        float op1 = stk.topStack();
        stk.pop();

        float result =MathOperation(op1,op2,exp[i]);
        stk.push(result);

    }
}


return stk.topStack();
}



//Function to return precedence of operators
int prec(char c) {
    if(c == '^')
        return 3;
    else if(c == '/' || c=='*')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// The main function to convert infix expression
//to postfix expression
string infixToPostfix(string s) {

    stack<char> st; //For stack operations, we are using C++ built in stack
    string result;

    for(int i = 0; i < s.length(); i++) {
        char c = s[i];

        // If the scanned character is
        // an operand, add it to output string.
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            result += c;

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if(c == '(')
            st.push('(');

        // If the scanned character is an ‘)’,
        // pop and to output string from the stack
        // until an ‘(‘ is encountered.
        else if(c == ')') {
            while(st.top() != '(')
            {
                result += st.top();
                st.pop();
            }
            st.pop();
        }

        //If an operator is scanned
        else {
            while(!st.empty() && prec(s[i]) <= prec(st.top())) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop all the remaining elements from the stack
    while(!st.empty()) {
        result += st.top();
        st.pop();
    }

    cout<<"the result is : "<<result<<endl;
    return result;
}





class node {
public:
    int x, y;
    int dir;

    node(int i, int j)
    {
        x = i;
        y = j;

        // Initially direction
        // set to 0
        dir = 0;
    }
};



bool isReachable(int maze[N][M])
{
    // Initially starting at (0, 0).
    int i = 0, j = 0;

    stack<node> s;

    node temp(i, j);

    s.push(temp);

    while (!s.empty()) {

        // Pop the top node and move to the
        // left, right, top, down or retract
        // back according the value of node's
        // dir variable.
        temp = s.top();
        int d = temp.dir;
        i = temp.x, j = temp.y;

        // Increment the direction and
        // push the node in the stack again.
        temp.dir++;
        s.pop();
        s.push(temp);

        // If we reach the Food coordinates
        // return true
        if (i == fx and j == fy) {
            return true;
        }

        // Checking the Up direction.
        if (d == 0) {
            if (i - 1 >= 0 and maze[i - 1][j] and visited[i - 1][j]) {
                node temp1(i - 1, j);
                visited[i - 1][j] = false;
                s.push(temp1);


            }
        }

        // Checking the left direction
        else if (d == 1) {
            if (j - 1 >= 0 and maze[i][j - 1] and visited[i][j - 1]) {
                node temp1(i, j - 1);
                visited[i][j - 1] = false;
                s.push(temp1);


            }
        }

        // Checking the down direction
        else if (d == 2) {
            if (i + 1 < n and maze[i + 1][j] and visited[i + 1][j]) {
                node temp1(i + 1, j);
                visited[i + 1][j] = false;
                s.push(temp1);


            }
        }
        // Checking the right direction
        else if (d == 3) {
            if (j + 1 < m and maze[i][j + 1] and
                                    visited[i][j + 1]) {
                node temp1(i, j + 1);
                visited[i][j + 1] = false;
                s.push(temp1);


            }
        }

        // If none of the direction can take
        // the rat to the Food, retract back
        // to the path where the rat came from.
        else {
            visited[temp.x][temp.y] = true;
            s.pop();


        }
    }

    // If the stack is empty and
    // no path is found return false.
    return false;
}



