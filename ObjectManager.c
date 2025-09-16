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
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "ObjectManager.h"

typedef enum BOOL {False,True} Bool;

static Bool compact();
static struct INDEX *createIndex(const int size);
static void checkState();

unsigned char *b1;
unsigned char *b2;
unsigned char *B;
Ref freeptr;
unsigned int numIndex;
unsigned int total;

typedef struct INDEX
{
    Ref id;
    Ref start;
    Ref size;
    unsigned int count;
    struct INDEX *next;

}Index;


Index *top;
Index *last;

void initPool()
{
    assert(b1==NULL);
    assert(b2==NULL);
    assert(top==NULL);
    assert(last==NULL);
    b1=(unsigned char *)malloc(sizeof(unsigned char)*MEMORY_SIZE);
    b2=(unsigned char *)malloc(sizeof(unsigned char)*MEMORY_SIZE);
    assert(b1!=NULL);
    assert(b2!=NULL);
    freeptr=0;
    B=b1;
    top=NULL;
    checkState();
    numIndex=0;
    total=0;
    last=top;
    assert(top==NULL);
    assert(last==NULL);
    assert(freeptr==0);
    assert(B!=NULL);
}
static Index *createIndex(const int size)
{
    Index *node=(Index *) malloc(sizeof(Index));
    assert(node!=NULL);
    if(node!= NULL)
    {
    numIndex++;
    node->count=1;
    node->id=numIndex;
    node->size= size;
    node->next=NULL;
    }
    return node;
}
Ref insertObject( const int size )
{
    Bool noSpace=False;
    assert(size>=0);
    assert((b1 != NULL) && (b2!=NULL));
    Ref result=NULL_REF;
    int newTotal=total;
    Bool availSpace=True;

    if(freeptr+size>=MEMORY_SIZE && size>0)
    {
         noSpace=True;
         availSpace=compact(); 
    }
    if(freeptr +size<MEMORY_SIZE && size>0)
    {
        noSpace=False;
        Index *node= createIndex(size);
        if(top==NULL)
        {
            assert(node!=NULL);
            assert(top==NULL);
            assert(last==NULL);
            assert(total==0);
            node->start=freeptr;
            top=node;
            last=node;
            result= node->id;
            freeptr+=size;
            total++;
            assert(freeptr>0);
            assert(top!=NULL);
            assert(last!=NULL);
            assert(node->size>0);  
        }else   
        {  
            assert(node!=NULL);
            assert(last!=NULL);
            assert(last->next==NULL);
            assert(top!=NULL);
            assert(freeptr>0);
            assert(total>0);
            node->start=freeptr;
            last->next=node;
            last=node;
            result= node->id;
            freeptr+=size;
            total++;
            assert(last!=NULL);
            assert(last->next==NULL);
            assert(newTotal+1==total);
            newTotal++;
            newTotal--; //To avoid unused var error             
        }     
    }
        if(!availSpace || noSpace)
        {
            printf("\nError. Object not inserted.\n");
        }
    checkState();    
    return result;
}
void *retrieveObject( const Ref ref )
{
    void *result=NULL;
    assert((ref>0) && (ref<=numIndex));
    assert(top!=NULL);
    assert(last!=NULL);
    Index *curr=top;
    if((ref>0) && (ref<=numIndex))
    {
    while(curr!=NULL)
    {
        if(curr->id==ref)
        {
            result=&B[curr->start];
            assert(result!=NULL);
            break;
        }
        curr=curr->next;
    }
    if(result==NULL)
    {
        printf("Invalid reference %lu",ref);
    }
    }else
    {
        printf("Invalid reference number.\n");
    }  

    checkState();
    return result;
}
void addReference( const Ref ref )
{
    printf("4\n");
    assert((ref>0) && (ref<=numIndex));
    assert(B!=NULL);
    assert(top!=NULL);
    assert(last!=NULL);
    Index *curr=top;
    assert(curr!=NULL);
    if((ref>0) && (ref<=numIndex))
    {
    while(curr!=NULL)
    {
        if(curr->id==ref)
        {
            int newCount=curr->count;
            curr->count++;
            assert(curr->count==newCount+1);
            newCount++;
            newCount--; //To avoid unused var error  
            break;
        }
        curr=curr->next;
    }
    }else
    {
        printf("Error, invalid ref number");
    }
    checkState();
}
void dropReference( const Ref ref )
{
    if((ref>0) && (ref<=numIndex))
    {
    assert((ref>0) && (ref<=numIndex));
    assert(B!=NULL);
    assert(top!=NULL);
    assert(last!=NULL);
    int newTotal=total;
    Index *curr=top;
    Index *prev=NULL;
    while(curr!=NULL)
    {     
        if(curr->id==ref)
        {
            assert(curr->count>0);
            curr->count--;
            if(curr->count==0)
            {
                if(curr==top && curr==last)
                {
                    top=NULL;
                    last=NULL;
                    free(curr);
                    curr=NULL;
                }else if(curr==top)
                {
                    top=curr->next;
                    free(curr);
                    curr=NULL;    
                }else if(curr==last)
                {
                    assert(prev!=NULL);
                    prev->next=NULL;
                    last=prev;
                    free(curr);
                    curr=NULL;
                } else
                {
                    prev->next=curr->next;
                    free(curr);        
                    curr=NULL;     
                }
                total--;
                assert(total==newTotal-1);
                newTotal++;
                newTotal--; //To avoid unused var error  
            }
            break;         
        }
        prev=curr;
        curr=curr->next;
    }
    checkState();
    }else
    {
        printf("\nInvalid reference!\n");
    }
}
void destroyPool()
{
    assert(b1!=NULL);
    assert(b2!=NULL);
    
    Index *curr=top;
    Index *prev=NULL;

    while(curr!=NULL)
    {
        prev=curr;
        curr=curr->next;
        free(prev);
    }

    freeptr=0;
    free(b1);
    b1=NULL;
    free(b2);
    b2=NULL;
    B=NULL;
    top=NULL;
    last=NULL;
    numIndex=0;
    assert(b1==NULL);
    assert(b2==NULL);
    assert(B==NULL);
    assert(top==NULL);
    assert(last==NULL);
    checkState();   
}
void dumpPool()
{
    assert(B!=NULL);
    Index *curr=top;
    printf("\nTotal available Space: %d\n",MEMORY_SIZE);
    printf("\n"); 
    printf("Total Objects: %d\n",total);  
    printf("\n"); 
    printf("Storage used: %lu\n",freeptr);
    printf("\n");
    printf("Storage left: %lu\n", MEMORY_SIZE-freeptr); 
   
    while(curr!=NULL)
    {
        printf("\n Reference id: %lu\n Starting Address: %lu\n Block Size: %lu\n",curr->id,curr->start,curr->size);
        curr=curr->next;
    }
    checkState();
}
static Bool compact()
{
    Bool allocated=True;
    assert(B!=NULL);
    assert(b1!=NULL);
    assert(b2!=NULL);
    if(B==b1)
    {
        Ref freeptrNew=0;
        Index *curr=top;

        while(curr!=NULL)
        {     
          if(curr->size+freeptrNew<MEMORY_SIZE)
          {  
          assert(curr->size+freeptrNew<MEMORY_SIZE);  
          memcpy(&b2[freeptrNew],&b1[curr->start],curr->size);
          curr->start=freeptrNew;
          freeptrNew+=curr->size;
          }else
          {  
            allocated=False;
            break;
          }
          curr=curr->next;
        } 
        if(allocated && top!=NULL &&curr==NULL)
        {
        B=b2;
        freeptr=freeptrNew;
        }else
        {
            allocated=False;
        }
        
    }else if(B==b2)
    { 
        Ref freeptrNew=0;
        Index *curr=top;   
        while(curr!=NULL)
        {
        if(curr->size+freeptrNew<MEMORY_SIZE)
        {  
          assert(curr->size+freeptrNew<MEMORY_SIZE);   
          memcpy(&b1[freeptrNew],&b2[curr->start],curr->size);
          curr->start=freeptrNew;
          freeptrNew+=curr->size;
        } else
        {
            allocated=False;
            break;
        }  
        curr=curr->next;
        }   
        if(allocated && top!=NULL &&curr==NULL)
        {
        B=b1;
        freeptr=freeptrNew;
        }else
        {
            allocated=False;
        }  
    }
    assert(B!=NULL);
    checkState();
    return allocated;
}
static void checkState()
{
    if(B!=NULL)
    {
        if(top!= NULL)
        {
            Index *curr=top;
            Ref num=0;
            while(curr!=NULL)
            {
                num++;
                assert(curr->id>0);
                assert(curr->size>0);
                assert(curr->start>=0);
                assert(curr->count>0);
                curr=curr->next;
            }
            assert(num==total);     
        }
    }
}
