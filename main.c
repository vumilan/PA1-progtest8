#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TEmployee {
  struct TEmployee         * m_Next;
  struct TEmployee         * m_Bak;
  char                     * m_Name;
} TEMPLOYEE;

#endif /* __PROGTEST__ */

TEMPLOYEE        * newEmployee  ( const char      * name,
                                  TEMPLOYEE       * m_Next ) {
  TEMPLOYEE * l;
  char * new_name;

  new_name = (char*) malloc ( sizeof ( char ) );
  strcpy(new_name, name);
  l = (TEMPLOYEE*) malloc ( sizeof ( *l ) );
  l -> m_Next = m_Next;
  l -> m_Bak = NULL;
  l -> m_Name = new_name;
  return l;
}
TEMPLOYEE        * cloneList    ( TEMPLOYEE       * src ) {
  if (src == NULL) return NULL;

  TEMPLOYEE *copy_list,*temp,*temp2;
    temp = src;
    //Step 1
    while(temp!=NULL)
    {
         TEMPLOYEE* newnode = newEmployee(temp->m_Name, NULL);
         temp2 = temp->m_Next;
         temp->m_Next = newnode;
         newnode->m_Next = temp2;
         temp = temp->m_Next->m_Next;
    }

    temp = src;

    //Step 2
    while ( temp != NULL && temp->m_Next != NULL )
    {
      if ( temp->m_Bak == NULL )
        temp->m_Next->m_Bak = NULL;
      else
        temp->m_Next->m_Bak = temp->m_Bak->m_Next;
      temp = temp->m_Next->m_Next;
    }

    //Step 3
    temp = src;
    copy_list = temp->m_Next;
    while(temp != NULL)
    {
        temp2 = temp->m_Next;
        if(temp->m_Next != NULL)
            temp->m_Next = temp->m_Next->m_Next;
        if(temp2->m_Next != NULL)
            temp2->m_Next = temp2->m_Next->m_Next;
        temp = temp->m_Next;
    }
    return copy_list;
}



void               freeList     ( TEMPLOYEE       * src )
{
  TEMPLOYEE * tmp;

  while ( src )
  {
    tmp = src;
    src = src->m_Next;
    free(tmp);
  }
}

#ifndef __PROGTEST__
int                main         ( int               argc,
                                  char            * argv [] ) {
  TEMPLOYEE * a, *b;
  char tmp[100];

  assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
  a = NULL;
  a = newEmployee ( "Peter", a );
  a = newEmployee ( "John", a );
  a = newEmployee ( "Joe", a );
  a = newEmployee ( "Maria", a );
  b = cloneList ( a );
  printf("%s\n", b -> m_Next -> m_Name);
  a -> m_Bak = a -> m_Next;
  a -> m_Next -> m_Next -> m_Bak = a -> m_Next -> m_Next -> m_Next;
  a -> m_Next -> m_Next -> m_Next -> m_Bak = a -> m_Next;
  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Bak == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  b = cloneList ( a );
  strncpy ( tmp, "Moe", sizeof ( tmp ) );
  a = newEmployee ( tmp, a );
  strncpy ( tmp, "Victoria", sizeof ( tmp ) );
  a = newEmployee ( tmp, a );
  strncpy ( tmp, "Peter", sizeof ( tmp ) );
  a = newEmployee ( tmp, a );
  if (b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next)
    printf("%s\n", b -> m_Next -> m_Next -> m_Name);
  b -> m_Next -> m_Next -> m_Next -> m_Bak = b -> m_Next -> m_Next;
  assert ( a
           && ! strcmp ( a -> m_Name, "Peter" )
           && a -> m_Bak == NULL );

  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Victoria" )
           && a -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "Moe" )
           && a -> m_Next -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
           && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == NULL );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Bak == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Bak == NULL );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( a );
  b -> m_Next -> m_Bak = b -> m_Next;
  a = cloneList ( b );
  assert ( a
           && ! strcmp ( a -> m_Name, "Maria" )
           && a -> m_Bak == a -> m_Next );
  assert ( a -> m_Next
           && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
           && a -> m_Next -> m_Bak == a -> m_Next );
  assert ( a -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
           && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next
           && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next );
  assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  assert ( b
           && ! strcmp ( b -> m_Name, "Maria" )
           && b -> m_Bak == b -> m_Next );
  assert ( b -> m_Next
           && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
           && b -> m_Next -> m_Bak == b -> m_Next );
  assert ( b -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
           && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next
           && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
           && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
  assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
  freeList ( b );
  freeList ( a );
  return 0;
}
#endif /* __PROGTEST__ */
