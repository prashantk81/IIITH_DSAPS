#include<iostream>
using namespace std;

//****************Checking greater string**************
bool greater_str(string str1, string str2){
    int n1 = str1.size();
    int n2 = str2.size();
    if(n1<n2){
        return true;
    }
    else if(n1>n2){
        return false;
    }
    else{
        for (int i = 0; i < n1; i++){
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
        }
        return true;    
    }
}
//***************************Addition*********************
string Addition(string str1, string str2){
    string add="";
    int carry=0;
    int i=str1.size()-1;
    int j=str2.size()-1;
    while(i>=0 && j>=0){
        int temp=(str1[i]-'0')+(str2[j]-'0')+carry;
        if(temp<10){
            add=to_string(temp)+add;
            carry=0;
        }
        else{
            add=to_string(temp%10)+add;
            carry=temp/10;
        }
        i--;
        j--;
    }
    while(i>=0){
        int temp=(str1[i]-'0')+carry;
        add=to_string(temp%10)+add;
        carry=temp/10;
        i--;
    }
    while(j>=0){
        int temp=(str2[j]-'0')+carry;
        add=to_string(temp%10)+add;
        carry=temp/10;
        j--;
    }
    if(carry!=0){
        add=to_string(carry)+add;
    }
    return add;

}
//***********************Subtraction*********************
string Subtraction(string str1, string str2){
    bool status=greater_str(str1,str2);
    if(status==0){
        string temp=str1;
        str1=str2;
        str2=temp;
    }
    string sub="";
    int n1=str1.size();
    int n2=str2.size();
    int borrow=0;
    if(n1<n2){
        for(int i=0;i<n2-n1;i++){
            str1="0"+str1;
        }
    }
    n1=str1.size();
    for(int i=n2-1;i>=0;i--){
        int temp=(str2[i]-'0')-(str1[i]-'0')-borrow;
        if(temp<0){
            temp+=10;
            borrow=1;
        }
        else{
            borrow=0;
        }
        sub=to_string(temp)+sub;
    }
    int x=0;
    while(x<n2){
        if(sub[x]=='0'){x++;}
        else{sub=sub.substr(x);break;}
    }
    int x2=0;
    while(x2<n2){
        if(str1[x2]=='0'){x2++;}
        else{str1=str1.substr(x2);break;}
    }
    return sub;
}
//***********Checking string equal or not**************
bool equal_string(string str1, string str2){
    int n1=str1.size();
    int n2=str2.size();
    if(n1!=n2){
        return false;
    }
    else{
        for(int i=0;i<n1;i++){
            if(str1[i]!=str2[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}
//**********************G C D ***********************
string G_C_D(string str1, string str2){
    if(str1.size()==1  && (str1[0]=='1')){
        return "1";
    }
    if((str2.size()==1) && str2[0]=='1'){
        return "1";
    }
    if(str1=="0" && str2=="0"){
        return "0";
    }
    if(str1=="0"){
        return str2;
    }
    if(str2=="0"){
        return str1;
    }
    if(equal_string(str1,str2)==1){
        return str1;
    }
    string res=Subtraction(str1,str2);
    bool status=greater_str(str1,str2);
        if(status==0){
            string final_res=G_C_D(res,str2);
            return final_res;
        }
        else{
            string final_res=G_C_D(res,str1);
            return final_res;
        }   
}
//***********************Multiplication**********************
string Multipliction(string str1, string str2){
    int n1=str1.size();
    int n2=str2.size();
    string mul(n1+n2, '0');
    for(int i=n1-1; i>=0;i--){
        for(int j=n2-1;j>=0;j--){
            int temp=(str1[i]-'0') * (str2[j]- '0') + (mul[i+j+1]-'0');
            mul[i+j+1]=temp%10+'0';
            mul[i+j]+=temp/10;
        }
    }

    int x=0;
    while(x<n1+n2){
        if(mul[x]=='0'){x++;}
        else{return mul.substr(x);}
    }
    return "0";

}
//****************** Calculating Exponential**********************
string Exponential(string str1, string str2){
    if(str1.size()==1 && str1[0]=='0'){return "0";}
    if(str1.size()==1 && str1[0]=='1'){return "1";}
        int temp=stoi(str2);
        if(temp==0){
            return "1";
        }
        string div=to_string(temp/2);
        string my_result=Exponential(str1,div);
        string multi=Multipliction(my_result,my_result);
        if(temp&1){
            string odd=Multipliction(multi,str1);
            return odd;
        }
        else{
             return multi;
        }
}
//******************Calculating Factorial************************* 
string Factorial(string str){
    if(str=="0"){
        return "1";
    }
    int n=stoi(str);
    int temp2=n-1;
    string res=to_string(n);
    for(int i=n-1;i>0;i--){
        string str2=to_string(i);
        res=Multipliction(res,str2);
    }
    return res;
}
//*****************Evaluating Arithmetic Expression ****************
string Arithmetic(string str){
    int count=0;
    for(int i=0;i<str.size();i++){
        if(str[i]=='+' || str[i]=='x' || str[i]=='-'){
            count++;
        }
    }
    str=str+"$";
    int n=2*count+1;
    string arr[n];
    int j=0;
    string temp="";
    for(int i=0;i<str.size();i++){
        if(str[i]!='+' && str[i]!='x' && str[i]!='-' && str[i]!='$'){
            temp=temp+str[i];
        }
        else{
            arr[j++]=temp;
            if(i!=str.size()-1){
                arr[j++]=str[i];
            }
            temp="";
        }
    }
    string result=arr[0];
    for(int i=1;i<n-1;i=i+2){
        if(arr[i]=="x"){
            arr[i+1]=Multipliction(arr[i-1],arr[i+1]);
            arr[i-1]="0";
            if(i!=1){
                arr[i]=arr[i-2];
            }  
            else{
                arr[i]="+";
            }
        }
    }
    result=arr[0];
    for(int i=1;i<n;i+=2){
        if(arr[i]=="+"){
            result=Addition(result,arr[i+1]);
        }
        else{
            result=Subtraction(result,arr[i+1]);
        }
    }

    return result;
}
//*******************Main Function******************
int main(){

    //1 for Arithmetic operation
    //2 for Exponentiation
    //3 for GCD
    //4 for Factorial

    cout<<"choice :-"<<endl;
    int n;
    cin>>n;
    if(n==1){
        string str1;
        cin>>str1;
        string res_exp=Arithmetic(str1);
        cout<<res_exp<<endl;
    }
    else if(n==2){
        string str1, str2;
        cin>>str1>>str2;
        string res_exp=Exponential(str1,str2);
        cout<<res_exp<<endl;
    }
    else if(n==3){
        string str1, str2;
        cin>>str1>>str2;
        string res_gcd=G_C_D(str1,str2);
        cout<<res_gcd<<endl;
       
    }
    else if(n==4){
        string str1;
        cin>>str1;
        string fact_res=Factorial(str1);
        cout<<fact_res<<endl;
    }
    else{
        cout<<"try again!!"<<endl;
    }
}


