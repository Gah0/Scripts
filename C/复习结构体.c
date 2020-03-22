#include <stdio.h>
#include <string.h>
#define num 50

struct Books{
    int book_id;
    char title[num];
    char author[num];
    char subject[num];
};

void printBook(struct Books *book);


int main (){
    struct Books Book1;
    struct Books Book2;

    strcpy( Book1.title,"C learning");
    strcpy( Book1.author,"woshishacha");
    strcpy( Book1.subject,"tutoral");
    Book1.book_id = 1;

    strcpy( Book2.title,"Python learning");
    strcpy( Book2.author,"woshishacha");
    strcpy( Book2.subject,"tutoral");
    Book1.book_id = 2;
    
    printBook(&Book1);
    printBook(&Book2);
}

void printBook(struct Books *book){
    printf("Book title : %s\n", book->title);
    printf("Book author : %s\n", book->author);
    printf( "Book subject : %s\n", book->subject);
    printf( "Book book_id : %d\n", book->book_id);
}

//    pbit->b&=3;    /* 使用了复合的位运算符 "&="，相当于：pbit->b=pbit->b&3，位域 b 中原有值为 7，与 3 作按位与运算的结果为 3（111&011=011，十进制值为 3） */
//   pbit->c|=1;    /* 使用了复合位运算符"|="，相当于：pbit->c=pbit->c|1，其结果为 15 */

