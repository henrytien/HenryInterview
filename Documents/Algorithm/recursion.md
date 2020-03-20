```cpp
#include<iostream>
using namespace std;
class Solution{
public:
    int get_sheep_num(int year){
        int num = 1;
        for(int i = 1; i <= year; i++){
            if(i == 2){
                num += get_sheep_num(year-2);
            }
            if(i == 4){
                num += get_sheep_num(year-4);
            }
            
            if(i == 5){
                num -= 1;
            }
        }
        return num;
    }
};


int main(){
    Solution s;
    cout << s.get_sheep_num(20)<< endl;
    return 0;
}
```