// NAME: MOHAMMAD ARQAM
// STUDENT NUMBER: 7942667
// COURSE: COMP 2160, SECTION: AO1
// INSTRUCTOR: Saulo Q. dos Santos
// ASSIGNMENT: assignment #4
// 
// REMARKS: This program stimulates the garbage collection behaviour of gc languages.  
// 
//
//-----------------------------------------
#include "ObjectManager.h"
#include <stdio.h> 

typedef enum BOOL{False,True}Bool;


int testInsertion(const int size,Bool expected,int id)
{
    id=insertObject(size);
    if((id && expected) || (!id && !expected))
    {
        printf("\nInsertion works fine\n");
    }else
    {
        printf("Insertion doesn't work fine\n");;
    }
    return id;
}
char * testRetrieval(int id, Bool expected)
{
    char *ptr= (char*)retrieveObject(id);
    if((ptr==NULL && !expected)||(ptr!=NULL && expected))
    {
        printf("\nRetrieval works fine.\n");
    }else
    {
        printf("Retrieval does not work fine.\n");
    }
    return ptr;
}

int main(int argc, char *argv[])
{
    //Testing destroy pool
    initPool();
    int ref1= 0;
    ref1=testInsertion(100,True,ref1);
    int ref2=0;
    ref2=testInsertion(200,True,ref2);
    int ref3=0;
    ref3=testInsertion(1000,True,ref3);
    dumpPool();
    destroyPool(); //Pool should not print in the next dumpPool()
    
    printf("\n");

    initPool();

    int id1=0;
    id1=testInsertion(10000000,False,id1); //testing first item inserted that is out of space(should give error)
    id1=testInsertion(100,True,id1); //replacing first item
    
    int id2=0;
    id2=testInsertion(10000000,False,id2); //testing "non-first" out of spcae item (Should give error)
    id2=testInsertion(5000,True,id2); //replacing the second item

    //testing add & drop refrence functions
    for(int i=0;i<2;i++)
    {
    addReference(id2);  //added 2 more to the reference count (refrence count is 3 now)
    }
    for(int i=0;i<3;i++)
    {
    dropReference(id2); //dropped 3 refrences from the count, refrence count should be 0. Item should be deleted
    }

    //testing retrieve
    int id3=0;
    id3=testInsertion(100,True,id3);
    char *ptr=testRetrieval(id3,True);

    for (int i = 0; i < 100; i++) //testing if space has actually been allocated
    {
    ptr[i]=i;
    printf("%d",(int)ptr[i]); 
    }
    printf("\n");
   
    //testing compact
    int id4=0;
    id4=testInsertion(519087,True,id4); //Max outs the buffer
    int id5=0;
    id5=testInsertion(3000,True,id5); //Going over the limit, should defragment and insert into second buffer
   
    dumpPool();
    printf("\n");
}