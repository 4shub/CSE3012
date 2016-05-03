#include "HTable.h"
#include <iostream>


HTable::HTable(int size) : dt(new data[size]), max_size(size), numel(0){
    // init the table
    for(size_t i = 0; i < max_size; i++){
        emptyBlock(i);
    }
}

// empties a table
int HTable::emptyBlock(int i){
    dt[i].key = -1; // sets a bunch of empty slots with no value
    dt[i].value = "N/A";
}


HTable::HTable() : HTable(23){
    // fixed constructor
}

// hashing function (k mod n);
int HTable::hash(int &k){
    return k % max_size;
}

// secondary hashing fucntion (k+1 mod n)
int HTable::rehash(int &k){
    return (k+1) % max_size;
}

int HTable::add(data &content){
    // return if table is full
    if(numel == max_size){
        return -1;
    }
    
    // find a new unused index
    int index;
    for(index = hash(content.key); dt[index].key != -1; index = rehash(index)); // will hash until
    
    // insert
    dt[index] = content;
    numel++;
    return 0;

}


int HTable::remove(data &content){
    // if the table is empty
    if(!numel){
        return -1;
    }
    
    // find the data
    int index, i;
    
    // will search until unable to be found
    for(index = hash(content.key), i = 0; (dt[index].key != content.key) && (i < max_size); index = rehash(index), i++);
    
    if(i != max_size){
        emptyBlock(index);
        numel--;
        return 0;
    }
    return -1; // failed
}

// prints out the htable

void HTable::output(){
    for(int i = 0; i < max_size; i++){
        cout << i << " -> " << dt[i].key << "\t" << dt[i].value << endl;
    }
    cout << "There are " << numel << " data in the table" << endl;
}


