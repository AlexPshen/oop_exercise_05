#include <iterator>
#include <memory>
#include <array>
#include <iostream>
#include <string.h>
#include <algorithm>

#include "queue.h"
#include "triangle.h"
#include "vertex.h"

int main(){
    que<triangle<double>> q;
    for(;;){
        char com[40];
        std::cin >> com;
        if(strcmp(com, "push") == 0){
            vertex<double> p1, p2, p3;
            std::cin >> p1 >> p2 >> p3;
            triangle<double> r_tr = triangle<double>(p1, p2, p3);
            q.push(r_tr);
        } else if(strcmp(com, "print_top") == 0){
            std::cout << q.top().area() << "\n";
        } else if(strcmp(com, "pop") == 0){
            q.pop();
        } else if(strcmp(com, "exit") == 0){
            break;
        } else if(strcmp(com, "insert") == 0){
            int index;
            std::cin >> index;
            vertex<double> p1, p2, p3;
            std::cin >> p1 >> p2 >> p3;
            triangle<double> r_tr = triangle<double>(p1, p2, p3);
            auto it = q.begin();
            q.insert(index, r_tr);
        } else if(strcmp(com, "erase") == 0){
            int index;
            std::cin >> index;
            auto it = q.begin();
            while(index !=0 && it != q.end()){
                ++ it;
                -- index;
            }
            q.erase(it);
        } else if(strcmp(com, "print_all") == 0){
            std::for_each(q.begin(),q.end(),[](triangle<double> f){std::cout << f.area() << " "; });
            std::cout << '\n';
        } else if(strcmp(com, "less") == 0){
            double val;
            std::cin >> val;
            int res = std::count_if(q.begin(), q.end(), [val](triangle<double> fig) { return fig.area() < val; });
            std::cout << res << '\n';
        } else {
            std::cout << "Неверно написана команда" << "\n";
        }
    }
}


















        

