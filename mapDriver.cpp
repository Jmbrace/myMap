#include <iostream>
#include "Map.h"
#include <string>

int main(int numOfArgs, char **args)
{
   Map<std::string, int> map;
      map.insert("ab", 3);
      map.insert("abc", 4);
      map.insert("abd", 5);
      map.insert("abde", 6);
      map.insert("abdef", 7);

      std::cout << map.lookup("abc") << std::endl;
   return 0;
}