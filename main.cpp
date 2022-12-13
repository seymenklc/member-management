#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

// variables
const int tableSize = 10;

struct member
{
   string birthDate;
   string name;
   string surname;
   member *next;
};

int Hash(string key)
{
   int hash = 0;
   // Calculate the hash value
   for (int i = 0; i < key.length(); i++)
      hash += (int)key[i]; // add the ASCII value of the character to the hash value

   return hash % tableSize;
}

int totalMembers(member *hashTable[])
{
   int count = 0;
   // member count
   for (int i = 0; i < tableSize; i++)
   {
      member *ptr = hashTable[i];
      // it is not the end of the list and the member is not empty
      while (ptr != NULL && ptr->name != "")
      {
         count++;
         ptr = ptr->next;
      }
   }
   return count;
}

void addMember(string name, string surname, string birthDate, member *hashTable[])
{
   int index = Hash(name);

   // If the index is empty, add the member
   if (hashTable[index]->name == "")
   {
      hashTable[index]->name = name;
      hashTable[index]->surname = surname;
      hashTable[index]->birthDate = birthDate;
   }
   // If the index is not empty
   else
   {
      // Create a new pointer to the index
      member *ptr = hashTable[index];
      // init the new member
      member *mem = new member;
      mem->name = name;
      mem->surname = surname;
      mem->birthDate = birthDate;
      mem->next = NULL;
      // find the end of the list
      while (ptr->next != NULL)
         ptr = ptr->next;

      ptr->next = mem; // add the new member to the end of the list
   }
}

int numberOfMembersInIndex(int index, member *hashTable[])
{
   int count = 0;
   // If the index is empty
   if (hashTable[index]->name == "")
   {
      return count;
   }
   else
   {
      count++;
      member *ptr = hashTable[index]; // beginning of the list
      // find the end of the list as long as the next member is not empty
      while (ptr->next != NULL)
      {
         count++; // increment the member count
         ptr = ptr->next;
      }
   }
   return count;
}

void listMembersInIndex(int index, member *hashTable[])
{
   member *ptr = hashTable[index];
   // If the index is empty
   if (ptr->name == "")
   {
      cout << "index: " << index << " is empty" << endl;
      cout << "---------------------" << endl;
   }
   else
   {
      cout << "index " << index << " contains these members: " << endl;
      cout << "********************" << endl;
      // until the end of the list
      while (ptr != NULL)
      {
         cout << ptr->name << " " << ptr->surname << endl;
         ptr = ptr->next; // move to the next member
      }
      cout << "---------------------" << endl;
   }
}

void findMember(string name, member *hashTable[])
{
   int index = Hash(name);
   bool isFound = false;
   string surname; // the name to be found

   member *ptr = hashTable[index];
   // If it is not the end of the list
   while (ptr != NULL)
   {
      if (ptr->name == name) // if the surname is found
      {
         isFound = true;
         surname = ptr->surname; // get the name
      }
      ptr = ptr->next; // move to the next member
   }
   // If the member is found
   if (isFound == true)
   {
      cout << "---------------------" << endl;
      cout << "Found member: " << name << " " << surname << endl;
      cout << "---------------------" << endl;
   }
   else
   {
      if (surname == "exit")
         return;
      cout << "---------------------" << endl;
      cout << "The member with name " << name << " was not found" << endl;
      cout << "---------------------" << endl;
   }
}

void removeMember(string name, member *hashTable[])
{
   int index = Hash(name);
   member *delPtr;      // pointer to be deleted
   member *prevMember1; // pointer to the previous member
   member *prevMember2;

   // If the index is empty
   if (hashTable[index]->name == "" && hashTable[index]->surname == "")
   {
      cout << "---------------------" << endl;
      cout << name << " was not found in the hash table" << endl;
      cout << "---------------------" << endl;
   }
   // list contains only one member and it is the member to be deleted
   else if (hashTable[index]->name == name && hashTable[index]->next == NULL)
   {
      hashTable[index]->name = "";
      hashTable[index]->surname = "";
      hashTable[index]->birthDate = "";
      cout << name << " was removed from the hash table" << endl;
   }
   // key is match but there other members on the index
   else if (hashTable[index]->name == name)
   {
      delPtr = hashTable[index];
      hashTable[index] = hashTable[index]->next; // move the next member to the index
      delete delPtr;                             // delete the member
      cout << name << " was removed from the hash table" << endl;
   }
   // there are members but the first member is not the member to be deleted
   else
   {
      prevMember1 = hashTable[index]->next; // second member
      prevMember2 = hashTable[index];       // first member
      // while it is not the end of the list and the member is not found
      while (prevMember1 != NULL && prevMember1->name != name)
      {
         prevMember2 = prevMember1;
         prevMember1 = prevMember1->next; // move to the next member
      }
      // if the member is found
      if (prevMember1 != NULL)
      {
         delPtr = prevMember1;
         prevMember1 = prevMember1->next; // move to the next member
         prevMember2->next = prevMember1; // link the previous member to the next member

         delete delPtr; // delete the member
         cout << name << " was removed from the hash table" << endl;
      }
      else
      {
         cout << "---------------------" << endl;
         cout << name << " was not found in the hash table" << endl;
         cout << "---------------------" << endl;
      }
   }
}

void updateMember(string name, member *hashTable[])
{
   int index = Hash(name);
   string surname;
   string birthDate;
   bool isFound = false;

   member *ptr = hashTable[index];
   // If it is not the end of the list
   while (ptr != NULL)
   {
      if (ptr->name == name) // if the surname is found
      {
         isFound = true;
         surname = ptr->surname; // get the surname to display
      }
      ptr = ptr->next; // move to the next member
   }
   // If the member is found
   if (isFound == true)
   {
      cout << "---------------------" << endl;
      cout << "Found member: " << name << " " << surname << endl;
      cout << "---------------------" << endl;
      // get new values for the member
      cout << "Enter the new surname: ";
      cin >> surname;
      cout << "Enter the new birth date: ";
      cin >> birthDate;

      hashTable[index]->surname = surname; // set new values for the member
      hashTable[index]->birthDate = birthDate;

      cout << "---------------------" << endl;
      cout << "Member updated: "
           << hashTable[index]->name << " "
           << hashTable[index]->surname << "-"
           << hashTable[index]->birthDate << endl;
      cout << "---------------------" << endl;
   }
   else
   {
      if (surname == "exit")
         return;
      cout << "---------------------" << endl;
      cout << "The member with name " << name << " was not found" << endl;
      cout << "---------------------" << endl;
   }
}

void printTable(member *hashTable[])
{
   for (int i = 0; i < tableSize; i++)
   {
      member *ptr = hashTable[i];
      // it is not the end of the list and the member is not empty
      while (ptr != NULL && ptr->name != "")
      {
         cout << "---------------------" << endl;
         cout << "index = " << i << endl;
         cout << "*********************" << endl;
         cout << "name: " << ptr->name << endl;
         cout << "surname: " << ptr->surname << endl;
         cout << "birth date: " << ptr->birthDate << endl;
         cout << "---------------------" << endl;
         ptr = ptr->next;
      }
   }
   int count = totalMembers(hashTable);
   cout << "Total number of members: " << count << endl;
}

void initTable(member *hashTable[])
{
   // Initialize the hash table
   for (int i = 0; i < tableSize; i++)
   {
      hashTable[i] = new member;
      hashTable[i]->name = "";
      hashTable[i]->surname = "";
      hashTable[i]->birthDate = "";
      hashTable[i]->next = NULL;
   }
}

void resetTable(member *hashTable[])
{
   int count = totalMembers(hashTable);
   cout << "Current total count of members: " << count << endl;
   cout << "Deleting table..." << endl;

   initTable(hashTable); // reset

   cout << "Table deleted" << endl;
   count = totalMembers(hashTable);
   cout << "New total count of members: " << count << endl;
}

int main(int argc, char *argv[])
{
   string inputStr = "";

   // initialize the hash table
   member *hashTable[tableSize];
   initTable(hashTable);

   // ADD MEMBERS TO THE HASH TABLE
   addMember("adem", "yilmaz", "2001", hashTable);
   addMember("seymen", "kilic", "2002", hashTable);
   addMember("aykut", "denk", "2002", hashTable);
   addMember("elif", "ozan", "2003", hashTable);
   addMember("meral", "yan", "2001", hashTable);
   addMember("melek", "bakar", "2006", hashTable);
   addMember("helin", "berkay", "2007", hashTable);
   addMember("ramazan", "bekar", "2008", hashTable);
   addMember("mehmet", "yilmaz", "2009", hashTable);

   /* LIST ALL MEMBERS WITH INDEXES */
   // printTable(hashTable);

   /* LIST ALL MEMBERS IN AN INDEX */
   for (int i = 0; i < tableSize; i++)
      listMembersInIndex(i, hashTable);

   /* REMOVE A MEMBER */
   // while (inputStr != "exit")
   // {
   //    cout << "Enter a name to search for: ";
   //    cin >> inputStr;
   //    findMember(inputStr, hashTable);
   // }

   /* REMOVE A MEMBER */
   // while (inputStr != "exit")
   // {
   //    cout << "Enter a name to remove from the table: ";
   //    cin >> inputStr;
   //    removeMember(inputStr, hashTable);
   // }

   /* UPDATE A MEMBER */
   // while (inputStr != "exit")
   // {
   //    cout << "Enter a name to update: ";
   //    cin >> inputStr;
   //    updateMember(inputStr, hashTable);
   // }

   /* RESET THE TABLE */
   // resetTable(hashTable);

   return 0;
}