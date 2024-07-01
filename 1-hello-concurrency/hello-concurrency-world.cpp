#include <iostream>
#include <thread>

using namespace std;

void hello(){
    cout << "Hello concurrent world!" << std::endl;
}

int main(){
    thread thread1(hello);
    thread1.join();
}