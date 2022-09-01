#include<iostream>
using namespace std;

template<typename T>class Deque{
    private:
        T *deque_arr;
        int fro,rear,size,capacity;

    public:

        void deque(){
            deque_arr=new T[0];
            fro=-1;
            rear=-1;
            size=0;
            capacity=0;
        }

        void deque(int n, T x){
            deque_arr=new T[n];
            for(int i=0;i<n;i++){
                deque_arr[i]=x;
            }
            fro=0;
            rear=n-1;
            size=n;
            capacity=n;
        }

        void push_back(T x){
            if((rear+1)%capacity==fro){
                T local_array[capacity];
                int k=0;
                if(fro>rear){
                    for(int i=fro;i<capacity;i++){
                        local_array[k++]=deque_arr[i];
                    }
                }    
                for(int i=0;i<=rear;i++){
                    local_array[k++]=deque_arr[i];
                }
                delete [] deque_arr;
                deque_arr=new T[2*capacity];
                for(int i=0;i<size;i++){
                   deque_arr[i]=local_array[i];     
                }
                fro=0;
                rear=size-1;
                capacity=2*size;
            }
            if(fro==-1 && rear==-1){
                fro=0;
                rear=0;
                deque_arr[rear]=x;
            }
            else{
                rear=(rear+1)%capacity;
                deque_arr[rear]=x;  
            }
            size=size+1; 
            
        }

        void pop_back(){
            if(fro==-1 && rear==-1){
                // cout<<"underflow"<<endl;
                // Do nothing
                return ;
            }
            else{  
                if(fro==rear){
                    fro=-1;
                    rear=-1;
                }
                else{
                    rear=(rear-1+capacity)%capacity;
                }
                size=size-1;
            }
        }

        void push_front(T x){
            if((fro+capacity-1)%capacity==rear){
                T local_array[capacity];
                int k=0;
                if(fro>rear){
                    for(int i=fro;i<capacity;i++){
                        local_array[k++]=deque_arr[i];
                    }
                }    
                for(int i=0;i<=rear;i++){
                    local_array[k++]=deque_arr[i];
                }
                delete [] deque_arr;
                deque_arr=new T[2*capacity];
                for(int i=0;i<size;i++){
                   deque_arr[i]=local_array[i];     
                }
                fro=0;
                rear=size-1;
                capacity=2*size;
            }
            if(fro==-1 && rear==-1){
                fro=0;
                rear=0;
                deque_arr[fro]=x;
            }
            else{
                fro=(fro+capacity-1)%capacity;
                deque_arr[fro]=x;  
            }
            size=size+1; 
        }

        void pop_front(){
            if(fro==-1 && rear==-1){
                // cout<<"underflow"<<endl;
                // Do nothing
                return ;
            }
            else{  
                if(fro==rear){
                    fro=-1;
                    rear=-1;
                }
                else{
                    fro=(fro+1)%capacity;
                }
                size=size-1;
            }
        }

        T front(){
            static T pr;
            if(fro==-1 && rear==-1){
                return pr;
                }
            // }
            return (deque_arr[fro]);
        }

        T back(){
            static T pr;
            if(fro==-1 && rear==-1){
                return pr;
            }
            return (deque_arr[rear]);
        }

        bool empty(){
            if(size==0){
                return true;
            }
            return false;
        }

        int size_(){
            return size;
        }

        void resize(int x,T d){
            T local_array[capacity];
            int k=0;
            if(fro>rear){
                for(int i=fro;i<capacity;i++){
                    local_array[k++]=deque_arr[i];
                    }
                }    
            for(int i=0;i<=rear;i++){
                local_array[k++]=deque_arr[i];
            }
            delete [] deque_arr;
            deque_arr=new T[x];
            if(x<size){
                for(int i=0;i<x;i++){
                    deque_arr[i]=local_array[i];     
                }
            }
            else{
                int tem=0;
                for(int i=0;i<size;i++){
                    deque_arr[tem++]=local_array[i];     
                }
                for(int i=tem;i<x;i++){
                    deque_arr[i]=d;
                }
            }
            fro=0;
            rear=x-1;
            size=x;
            capacity=x;
        }

        void clear(){
            delete [] deque_arr;
            deque_arr=new T[0];
            fro=-1;
            rear=-1;
            size=0;
            capacity=0; 
        }

        T  operator [](int n){
            static T pr;
            if((n<0) || n>=size){
                return pr;
            }
            return deque_arr[(fro+n)%capacity];
        }

        void print(){
            if(size==0){
                cout<<"Empty deque"<<endl;
                return ;
            }
            cout<<"Current deque is:- "<<endl;
             if(fro>rear){
                    for(int i=fro;i<capacity;i++){
                        cout<<deque_arr[i]<<" ";
                    }
                }    
                for(int i=0;i<=rear;i++){
                    cout<<deque_arr[i]<<" ";
                }
            cout<<endl;
        }
};

//************************Main Function*********************

int main(){
    Deque<int> dq;
    int x=1,temp;
    int value;

    // 0 - QUIT
    // 1 - deque()
    // 2 - deque(n, x)
    // 3 - push_back(x)
    // 4 - pop_back()
    // 5 - push_front(x)
    // 6 - pop_front()
    // 7 - front()
    // 8 - back()
    // 9 - D[n]
    // 10 - empty() 
    // 11 - size()
    // 12 - resize(n, x)
    // 13 - clear()
    // 14 - print()

    while(x){
        cout << "-------------------------\n";
        cout<<"Enter Choice:-"<<endl;
        cin>>temp;
        switch (temp)
        {
        case 0:
            x=0;
            break;
        case 1:
            dq.deque();
            break;

        case 2:
            int n;
            cin>>n>>value;
            dq.deque(n,value);
            break;

        case 3:
            cin>>value;
            dq.push_back(value);
            break;

        case 4:
            dq.pop_back();
            break;

        case 5:
            cin>>value;
            dq.push_front(value); 
            break;

        case 6:
            dq.pop_front();
            break;

        case 7:
            cout<<dq.front()<<endl;
            break;

        case 8:
            cout<<dq.back()<<endl;
            break;

        case 9:
            int index;
            cin>>index;
            cout<<dq[index]<<endl;
            break;

        case 10:
            if(dq.empty()){
                cout<<"true"<<endl;
            }
            else{
                cout<<"false"<<endl;
            }    
            break;

        case 11:
            cout<<dq.size_()<<endl;
            break;

        case 12:
            int new_size;
            cin>>new_size>>value;
            dq.resize(new_size,value);
            break;

        case 13:
            dq.clear();    
            break;

        case 14:
            dq.print();
            break;

        default:
            cout<<"Enter Correct choice !!\n";
            break;
        }
    }
}