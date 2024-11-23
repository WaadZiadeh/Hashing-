//waad alaa ziadeh
//1220423
//dr.ahmad abo sianah
//5/24/2024


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int size= 149;

int load = 0;


struct Hashnode;
typedef struct Hashnode *Hash;
struct Hashnode {
char word[30] ;
int counter;
char op;

};


struct AVLnode;
typedef struct AVLnode *AVL_T;

struct AVLnode {
    char *Data;
    AVL_T Left;
    AVL_T Right;
    int Height;
    int frequency;
};

void printmenu();

/*1*/AVL_T loadFile(const char *filename, AVL_T root);
int getHeight(AVL_T t);
int MAX(int x, int y);
AVL_T singleRotateLeft(AVL_T x);
AVL_T singleRotateRight(AVL_T y);
AVL_T doubleRotateLeft(AVL_T K3);
AVL_T doubleRotateRight(AVL_T K3);
AVL_T insert(AVL_T t, char *key);
int getBalance(AVL_T t);

int isChar(char c);

/*2*/ void CreateAVL();

/*3*/AVL_T insertwordTOavl(AVL_T node);
AVL_T search(AVL_T root, char *key);

/*4*/AVL_T deletwordFROMavl(AVL_T node);
AVL_T find_min(AVL_T node);
AVL_T deleteNode(AVL_T root, char *key);

/*5*/void printInOrder(AVL_T root);

////////////////////////////////////////////////
/*6*/void creationHash (Hash *table , AVL_T tree);
void hasHTable (Hash* table , int size);
Hash AVLHASH (Hash *table, int size,AVL_T root);
void printHash(Hash*table, int size);
int HashAndCollision(Hash * table ,char *word ,  int size);


/*7*/ Hash *InsertHash (Hash* table , char *data, int size  );
void AddwordtoHash (Hash * table,int size  );
int searchHash(Hash *table, char *data, int size);
Hash * rehash (Hash *table , int size);

/*8*/void deletewordfromHash(Hash* table,int size);
Hash DeleteHash (Hash* table , char*word,int size);

/*9*/void searchandprint(Hash *table , char* word , int size );
void printsearch(Hash *table , int size);


/*10*/void printwordStatistics(Hash* table,int size);
void wordStatistics(Hash* table ,int size,int count);

int main() {
    int option;
    AVL_T AVLtree = NULL; // Initialize AVL tree
   Hash* hashTable[size];

    while (1) {
        printmenu();
        printf("Enter your option:\n");
        scanf("%d", &option);
        switch (option) {
            case 1:
                AVLtree = loadFile("input.txt", AVLtree);
                break;
            case 2:CreateAVL();
                break;
            case 3:AVLtree = insertwordTOavl(AVLtree);
                break;
            case 4:AVLtree = deletwordFROMavl(AVLtree);
                break;
            case 5:if(load==1){
                 printf("AVL tree Contents:\n");
                 printf("--------------------\n");
                 printInOrder(AVLtree);}
             else{
                printf("Load the File please\n");
             }
                break;
            case 6:
                if (load == 0) {
              printf("Load the file please\n");
               } else {
                hasHTable(hashTable,size);
                 creationHash(hashTable, AVLtree);
                 printf("Hash Table Contents:\n");
                 printf("--------------------\n");
                 printHash(hashTable,size);
                printf("creation DONE!\n");}
                 break;
            case 7:
                  if (load == 0) {
        printf("Load the file please\n");
    } else {
                AddwordtoHash ( hashTable,size );}
                break;
            case 8:  if (load == 0) {
        printf("Load the file please\n");
    } else {
                deletewordfromHash( hashTable,size );}

                break;
            case 9:   if (load == 0) {
        printf("Load the file please\n");
    } else {
                printsearch(hashTable, size);}
                break;
            case 10:  if (load == 0) {
        printf("Load the file please\n");
    } else {
                printwordStatistics(hashTable,size);}
                break;
            case 11:
                printf("Good Bye!\n");
                exit(0);
                break;
            default:
                printf("Not a valid option\n");
        }
    }
    return 0;
}

void printmenu() {
    printf("\nMenu of my application \n\n");
    printf("1. Load data from the file.\n");
    printf("2. Create the AVL tree.\n");
    printf("3. Insert a word to the AVL tree.\n");
    printf("4. Delete a word from the AVL tree.\n");
    printf("5. Print the words as sorted in the AVL tree.\n");
    printf("6. Create the Hash Table.\n");
    printf("7. Insert a word to the Hash table.\n");
    printf("8. Delete a word from the hash table.\n");
    printf("9. Search for a word in the hash table and print its frequency.\n");
    printf("10. Print words statistics.\n");
    printf("11. Exit the application.\n");
    printf("\n");
}

AVL_T loadFile(const char *filename, AVL_T root) {
    /*1. Load data from the file. */
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return root;
    }
    char word[100];
    while (fscanf(file, "%99s", word) != EOF) {
        int len = strlen(word);
        for (int i = 0; i < len; i++) {
            if (isChar(word[i])) {
                word[i] = tolower(word[i]);
            } else {
                word[i] = '\0';
                break;
            }
        }
        if (strlen(word) > 0) {
            root = insert(root, word); // Insert the word into AVL tree
        }
    }
    fclose(file);
    printf("The load DONE!\n");

    load++;
    return root;
}
/////////////////////////////////
int isChar(char c) {
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    else
        return 0;
}
int getHeight(AVL_T t) {
    if (t == NULL)
        return -1;
    else
        return t->Height;
}
int MAX (int x, int y){
    if(x>y)
        return x;
    else
        return y;
}

AVL_T singleRotateLeft(AVL_T x) {
    AVL_T y = x->Right;
    x->Right = y->Left;
    y->Left = x;

    x->Height = 1 + MAX(getHeight(x->Left), getHeight(x->Right));
    y->Height = 1 + MAX(getHeight(x), getHeight(y->Right));

    return y;
}

AVL_T singleRotateRight(AVL_T y) {
    AVL_T x = y->Left;
    y->Left = x->Right;
    x->Right = y;

    y->Height = 1 + MAX(getHeight(y->Right), getHeight(y->Left));
    x->Height = 1 + MAX(getHeight(y), getHeight(x->Left));

    return x;
}

AVL_T doubleRotateLeft(AVL_T K3) {
    K3->Left = singleRotateLeft(K3->Left);
    return singleRotateRight(K3);
}

AVL_T doubleRotateRight(AVL_T K3) {
    K3->Right = singleRotateRight(K3->Right);
    return singleRotateLeft(K3);
}
/////////////////////////////
//function to insert node to avl
AVL_T insert(AVL_T t, char *key) {
    if (t == NULL) {
        t = malloc(sizeof(struct AVLnode));
        t->Data = strdup(key); // Allocate and copy the key string
        t->Height = 0;
        t->Left = t->Right = NULL;
        t->frequency = 1;
    } else if (strcmp(key, t->Data) < 0) {
        t->Left = insert(t->Left, key);
        if (getHeight(t->Left) - getHeight(t->Right) >= 2) {
            if (strcmp(key, t->Left->Data) < 0)
                t = singleRotateRight(t);
            else
                t = doubleRotateLeft(t);
        }
    } else if (strcmp(key, t->Data) > 0) {
        t->Right = insert(t->Right, key);
        if (getHeight(t->Right) - getHeight(t->Left) >= 2) {
            if (strcmp(key, t->Right->Data) > 0)
                t = singleRotateLeft(t);
            else
                t = doubleRotateRight(t);
        }
    } else {
        t->frequency++;
    }

    t->Height = 1 + MAX(getHeight(t->Right), getHeight(t->Left));

    return t;
}
///////////////////////////
//function to create avl
void CreateAVL() {
    /*2. Create the AVL tree.*/
    if (load == 1) {
        printf(" The AVL tree created automatically when option 1 is chosen !\n \n ");
    } else {
        printf(" chose option 1 , to create and load the data from file\n \n ");
    }
}
///////////////////////////////
//function to add word to avl
AVL_T insertwordTOavl(AVL_T node) {
    /*3. Insert a word to the AVL tree. */
        char word[100];
        printf("Enter the word to insert it: \n");
        scanf("%s", word);
        int alpha=0;

        // Convert to lowercase and check if the word is alphabetical
        for (int i = 0; i<strlen(word); i++) {
              if (isChar(word[i])) {
                    alpha=1;
                word[i] = tolower(word[i]);
            }
             else if((isChar(word[0])==0)) {
                alpha=0;
                         }
            else
           word[i]='\0';
        }

        if (alpha) {
            AVL_T newNode = search(node, word);
            if (newNode) {
                newNode->frequency++;
                printf("Word already exists\n");
            } else {
                node = insert(node, word);
                printf("insertion DONE\n");
            }
        } else {
            printf("The AVL tree only accepts alphabetical words\n");
        }

    return node;
}
//////////////////////
//Function to search in avl
AVL_T search(AVL_T root, char *key) {
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(key, root->Data) == 0) {
        return root;
    } else if (strcmp(key, root->Data) < 0) {
        return search(root->Left, key);
    } else {
        return search(root->Right, key);
    }
}
///////////////////////////////////
//function to delete word from avl
AVL_T deletwordFROMavl(AVL_T node) {
    /*4. Delete a word from the AVL tree. */
    if (load == 0) {
        printf("Load the file please\n");
    } else {
        char word[100];
        printf("Enter the word to delete it: \n");
        scanf("%s", word);

        AVL_T Dword = search(node, word);
        if (Dword) {
            if (Dword->frequency > 1) {
                Dword->frequency--;
                printf("The Frequency has been update SUCCESSFULLY !\n");
            } else {
                node = deleteNode(node, word);
                printf("Deletion DONE!\n");
            }
        } else {
            printf("The word not found to delete it\n");
        }
    }
    return node;
}
////////////////////////
//function to find min in avl
AVL_T find_min(AVL_T node) {
    if (node == NULL)
        return NULL;
    else if (node->Left == NULL)
        return node;
    else
        return find_min(node->Left);
}
int getBalance(AVL_T t) {
    if (t == NULL)
        return 0;
    return getHeight(t->Left) - getHeight(t->Right);
}
////////////////////
// Function to delete a node from the AVL tree
AVL_T deleteNode(AVL_T root, char *key) {
    AVL_T tmp_cell, child;

    if (root == NULL) {
        return root;
    }

    if (strcmp(key, root->Data) < 0) {
        root->Left = deleteNode(root->Left, key);
    } else if (strcmp(key, root->Data) > 0) {
        root->Right = deleteNode(root->Right, key);
    } else {
        // Node with only one child or no child
        if (root->Left == NULL || root->Right == NULL) {
            child = root->Left ? root->Left : root->Right;

            // No child case
            if (child == NULL) {
                child = root;
                root = NULL;
            } else {
                // One child case
                *root = *child; // Copy the contents of the non-empty child
            }

            free(child);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            tmp_cell = find_min(root->Right);
            root->Data = tmp_cell->Data;

            // Delete the inorder successor
            root->Right = deleteNode(root->Right, tmp_cell->Data);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // Update height of the current node
    root->Height = 1 + MAX(getHeight(root->Left), getHeight(root->Right));

    // Get the balance factor of this node to check whether this node became unbalanced
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->Left) >= 0)
        return singleRotateRight(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->Left) < 0) {
        root->Left = singleRotateLeft(root->Left);
        return singleRotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->Right) <= 0)
        return singleRotateLeft(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->Right) > 0) {
        root->Right = singleRotateRight(root->Right);
        return singleRotateLeft(root);
    }

    return root;
}
/////////////////////////
//function to print the AVL tree
void printInOrder(AVL_T root) {
    /*5. Print the words as sorted in the AVL tree.*/
    if (root != NULL) {
        printInOrder(root->Left);
        printf("word :%s\t", root->Data);
        printf(" Frequency :%d\n",root->frequency);
        printInOrder(root->Right);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//initialized hash table
void hasHTable(Hash* table, int size) {
    for (int i = 0; i < size; i++) {
        table[i] = (Hash)malloc(sizeof(struct Hashnode)); // Allocate memory for each Hashnode
        //make hash table empty
        strcpy(table[i]->word, "");
        table[i]->counter = 0;
        table[i]->op = 'e';
    }
}
//////////////////////////////////
//function to transfer data from avl to hash
void creationHash(Hash* table, AVL_T tree) {
    /*6. Create the Hash Table. */
    if (tree != NULL) {
            //fill the table data
        creationHash(table, tree->Left);
       AVLHASH(table, size, tree);
        creationHash(table, tree->Right);
    }
}
////////////////////////////////////////
// function like insert to insert data that in avl to hash table
Hash AVLHASH(Hash* table, int size, AVL_T root) {
    unsigned int index = HashAndCollision(table, root->Data, size);

    if (table[index]->op == 'e') {
        strcpy(table[index]->word, root->Data);
        table[index]->counter = root->frequency;
        table[index]->op = 'o';
    }

    return table[index];
}
///////////////////////////////////////
//hash function and collision to return final index
int HashAndCollision(Hash* table, char* word, int size) {
    int i = 0;
    int key = (word[0] + (27 * word[1]) + (729 * word[2]));//calculate the key
    int index = (key % size);//find index

    while (table[index]->op == 'o' && strcmp(table[index]->word, word) != 0) {// check if index empty or not
            //if the index not empty make collision
        index = (key + (int)pow(i, 2)) % size; // quadratic hashing(Probing) to solve collision problem
        i++;
    }
    return index; // return index
}

/////////////////////////////////////////////
//insert words to hash table
Hash* InsertHash(Hash* table, char* data, int size) {
    unsigned int index = HashAndCollision(table, data, size);//calculate index
    int found = searchHash(table, data, index);//check if word is find

    if (!found) {
            //if word not find
        strcpy(table[index]->word, data); //put the data in hash
        table[index]->counter = 1;//make frequency =1
        table[index]->op = 'o';//operation = o
    } else {
        table[index]->counter++; // if the word found increment the frequency
    }

   int item=0 ;
    for (int i = 0; i < size; i++) {
        if (table[i]->op == 'o') {
            item++;
        }
    }
 double loadFactor = (double)(item)/149;
double factor =0.7;
if(loadFactor>factor){
   table=rehash(table,size);
   }

printHash(table, size);//print hash
 printf("\n-items=%d\n",item);
 printf("\n-load factor=%f\n",loadFactor);

    return table;
}
////////////////////////////
//rahash function;
Hash * rehash (Hash *table , int size){

int newSIZE=307; //size*2
Hash  newTable[newSIZE];
hasHTable(newTable,newSIZE);
for (int i = 0; i <newSIZE; i++) {
        if (table[i]->op == 'o') {
            unsigned int newIndex = HashAndCollision(newTable, table[i]->word, newSIZE);
            strcpy(newTable[newIndex]->word, table[i]->word);
            newTable[newIndex]->counter = table[i]->counter;
            newTable[newIndex]->op = 'o';
        }
    }
 // Free the old table
    for (int i = 0; i <size; i++) {
        free(table[i]);
    }
    free(table);
// to update the size u need pointer
size= newSIZE;
printf("Rehash DONE!");
return newTable;
}
/////////////////////////
//function to search about word in hash and return 1 or 0
int searchHash(Hash* table, char* data, int index) {
    if (table[index]->op == 'o' && strcmp(table[index]->word, data) == 0) {
        return 1;
    }
    return 0;
}
////////////////////
// function that Receives word and add it to hash by call function inserthash
void AddwordtoHash(Hash* table, int size) {
    /*7.Insert a word to the Hash table. */
    char word[30];
    printf("Enter word to insert to the HASH TABLE:\n");
    scanf("%s", word);
    table = InsertHash(table, word, size);
    printf("DONE!\n");
}
///////////////////////////////
//function to search about word and delete it
Hash DeleteHash(Hash* table, char* word, int size) {
    int index = HashAndCollision(table, word, size);
    if (strcmp(table[index]->word, word) == 0 && table[index]->op == 'o') {
        table[index]->op = 'e';
        table[index]->counter = 0;
        strcpy(table[index]->word, "");
        printf("DONE!\n");
    } else {
        printf("Word not found!\n");
    }

    return table;
}
///////////////////////////////////
//function that receives a word to delete it
void deletewordfromHash(Hash* table, int size) {
    /*8. Delete a word from the hash table.*/
    char word[30];
    printf("Enter word to delete from Hash Table:\n");
    scanf("%s", word);
    table = DeleteHash(table, word, size);
    printHash(table,size);
}
/////////////////////////
// Function to print the word and frequency after searching for it
void printsearch(Hash *table, int size) {
    /*9. Search for a word in the hash table and print its frequency. */
    char data[30];
    printf("Enter the word to search in Hash Table:\n");
    scanf("%s", data);
    searchandprint(table, data, size);
}

// Function to search for a word and print its frequency
void searchandprint(Hash *table, char* word, int size) {
    int index = HashAndCollision(table, word, size);
    int found = searchHash(table, word, index);
    if (found) {
        printf("Word: %s\t Frequency: %d\n", word, table[index]->counter);
    } else {
        printf("The word not found!\n");
    }
}
////////////////////////////
//function to search about the word in hash depends on number
void wordStatistics(Hash* table, int size, int count) {
    int found = 0; // Flag to track if any word meets the criteria

    for (int i = 0; i < size; i++) {
        if (table[i]->counter > count) {
            printf("Word: %s\t Frequency: %d\n", table[i]->word, table[i]->counter);
            found = 1; // Set flag if a word is found
        }
    }

    if (!found) {
        printf("No word has a frequency greater than %d\n", count);
    }
}
//////////////////
//function receives number and found a word that have frequency bigger than the user number
void printwordStatistics(Hash* table, int size) {
    /*10. Print words statistics. */
    int key;
    int count=0 ;
    int max = 0;
    int maxindex=0;
    //number of words the frequency =1
     for (int i = 0; i < size; i++) {
        if (table[i]->counter == 1) {
        count ++;
        }
    }
    //max frequency
    max =table[0]->counter;
     for (int i = 0; i < size; i++) {
         if (table[i]->counter > max ) {
            max = table[i]->counter;
            maxindex=i;
        }
    }

    {printf("The word that have larger frequency is =%s\n",table[maxindex]->word);
    printf("The number of words that has frequency= 1 is = %d words \n",count);
    printf("\n Enter a number to find word has frequency bigger than it :\n");
    scanf("%d", &key);
    wordStatistics(table, size, key);}
}
/////////////////
//function to print hash table
void printHash(Hash* table, int size) {

    for (int i = 0; i < size; i++) {
        if (table[i]->op == 'o') {
            printf("Index = %d\t Word = %s\t Frequency = %d\n", i, table[i]->word, table[i]->counter);
        }
    }
}
