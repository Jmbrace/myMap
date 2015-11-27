#ifndef _MAP_H_
#define _MAP_H_

template <typename HashObj, typename Object>
class Map
{
   public:
     Map();
    ~Map();
     void insert(const HashObj &key, const Object &definition);
     const Object& lookup(const HashObj key) const;
     bool isEmpty();
     void makeEmpty();
   private:
   	class Pair
   	{
       public:
       HashObj key;
       Object def;
   	   Pair(const HashObj &key, const Object &def);
   	   Pair();
      ~Pair();
   	};
   	Pair *hashArray;
   	int size;
   	int tableSize;
   	int *cellStatus;
   	int probe(int i) const;
  	int hash(const HashObj &key) const;

};

#include <functional>

template <typename HashObj, typename Object>
Map<HashObj,Object>::Map()
{
    hashArray = new Pair[11];
    cellStatus = new int[11];
    tableSize = 11;
    size = 0;
    makeEmpty();
}

template <typename HashObj, typename Object>
Map<HashObj, Object>::~Map()
{
   delete[] hashArray;
   delete[] cellStatus;
}

template <typename HashObj, typename Object>
void Map<HashObj, Object>::insert(const HashObj &key, const Object &def)
{
    int index = hash(key);
    int i = 1;
    while(cellStatus[index]!=0)
    {
       index = index + probe(i);
       index = index % tableSize;
       i++;
    }

    Pair pair(key, def);
    hashArray[index] = pair;
    cellStatus[index] = 1;
    size++;


}

template <typename HashObj, typename Object>
Map<HashObj, Object>::Pair::Pair(const HashObj &key, const Object &def)
{
   this->key = key;
   this->def = def;
}

template <typename HashObj, typename Object>
void Map<HashObj, Object>::makeEmpty()
{
   for(int i = 0; i < tableSize; i ++)
      cellStatus[i] = 0;
}

template <typename HashObj, typename Object>
Map<HashObj, Object>::Pair::Pair()
{

}

template <typename HashObj, typename Object>
Map<HashObj, Object>::Pair::~Pair()
{

}

template <typename HashObj, typename Object>
int Map<HashObj, Object>::probe(int i) const
{
   return i*i;
}

template <typename HashObj, typename Object>
int Map<HashObj, Object>::hash(const HashObj &key) const
{   int index = std::hash<HashObj>()(key) % tableSize;
	if (index < 0)
	   index = index + tableSize;
    return index;
}

template <typename HashObj, typename Object>
const Object& Map<HashObj, Object>::lookup(const HashObj key) const
{
   int index = hash(key);
   int i = 1;
   bool found = false;
    while(cellStatus[index]!=0)
    {
       if(cellStatus[index] == 1 && hashArray[index].key.compare(key)==0)
       {
       	found = true;
       	break;
       }
       index = index + probe(i);
       index = index % tableSize;
       i++;
    }
    if(found)
    	return hashArray[index].def;
    return NULL;
}
#endif