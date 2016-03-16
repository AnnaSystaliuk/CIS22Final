//
//  main.cpp
//  QD
//
//  Created by A on 3/15/16.
//  Copyright © 2016 E. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

const int TABLE_SIZE = 128;


class HashEntry {
private:
    string name;
    int id;
public:
    bool isEmpty = true;

    HashEntry()
    {
        
    }
    
    HashEntry(string key, int value) {
        this->name = key;
        this->id = value;
        isEmpty = false;
    }
    
    string getName() {
        return name;
    }
    
    int getID() {
        return id;
    }
};

class HashTable {
private:
    vector<HashEntry> *table;
    int m = TABLE_SIZE;
    int totalProbes;
    int numInserts;
    void tallyProbes(int p);
public:
    HashTable() {
        table = new vector<HashEntry>(TABLE_SIZE);
        
    }
    
    void search(int id) {
        int probe;
        int i = 0 ;
        probe = (hash(id) + i*i) % m;
        
        for(int j = 0; i< table->size() ; j++)
        {
          
            if ((*table)[probe].isEmpty)
                return;
            
            else if (id == (*table)[probe].getID())
            {
                cout <<  endl << " [ index : " << probe << " | " <<  (*table)[probe].getName() << " , " <<  (*table)[probe].getID() << " ] " << endl;            }
            
            ++i;
            probe = (hash(id) + i*i) % m;
        }
      
    }
    
    void print()
    {
        auto i = table->size();
        for( int x = 0; x < i ; x++)
        {
            if(!(*table)[x].isEmpty)
                cout <<  endl << " [ index : " << x << " | " <<  (*table)[x].getName() << " , " <<  (*table)[x].getID() << " ] " << endl;
        }
    }
    
    
    int hash(int k) {
        return k % m;
    }
    
    float probeRate() {
        return (float)totalProbes / (float)numInserts;
    }
    
    void put(string name, int id) {
        int i = 0, pre_inserts = numInserts;
        int probe, LIMIT = m/2;
        
        do{
            probe = (hash(id) + i*i) % m;
            if((*table)[probe].isEmpty){
                (*table)[probe] = HashEntry(name,id);
                numInserts++;
                break;
            }else{
                totalProbes++;
                 cout<<" for " << name << "  i = "<< ++i <<" , index = "<<probe<<endl;
            }
//            i++;
        }while(!(*table)[probe].isEmpty && i != m && i < LIMIT);
        if(pre_inserts == numInserts){
             cout<<"Fail on Insertion(Maximum number of probes["<<LIMIT<<"] exceeded)."<<endl;
        }
        
    }
    
    void remove(int id)
    {
        int probe;
        int i = 0 ;
        probe = (hash(id) + i*i) % m;
        
        for(int j = 0; i< table->size() ; j++)
        {
            
            if ((*table)[probe].isEmpty)
                return;
            
            else if (id == (*table)[probe].getID())
            {
                
                (*table).erase((*table).begin() + probe);
            }
            
            ++i;
            probe = (hash(id) + i*i) % m;
        }
    }
    
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (!(*table)[i].isEmpty)
                  table->pop_back();
        delete table;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    HashTable a;
    
    a.put("Anna Systaliuk", 1);
    a.put("Eddy Lee", 2);
    a.put("Isac Newton", 3);
    a.put("Tesla", 4);
    a.put("Albert Einstie", 3);
    a.put("Tony Star", 3);
    a.put("Robert Hooke", 3);

    a.search(3);
    
    cout << " ___________________" << endl;
    a.remove(3);

    a.search(3);

    
    return 0;
}
