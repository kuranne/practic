#include <iostream>
#include <string>

signed main() 
{
start:
    std::string first_name, last_name, age;

input:
    std::cin >> first_name >> last_name >> age;

process:
    if (first_name.length() > 5 && last_name.length() > 5)
        std::cout << first_name[0] << first_name[1] << last_name[last_name.length() -1] << age[age.length() - 1] << std::endl;
    else 
        std::cout << first_name[0] << age << last_name[last_name.length() - 1] << std::endl;

exit:
    return 0;
}