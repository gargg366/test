/* circular doubly link list using list_for_each_entry
 *
 * =========================================================
 * list_entry: for more reference go to
 * http://stackoverflow.com/questions/18554721/how-to-understand-size-t-type-0-member
 *
 * The sequence of operations can be illustrated in the following way:
 *
 *     1.                         0
 *     2.                ((TYPE *)0)
 *     3.              ( ((TYPE *)0)->MEMBER )
 *     4.             &( ((TYPE *)0)->MEMBER )
 *     5.  ( (size_t) &( ((TYPE *)0)->MEMBER )
 *
 *     1.Everything starts with number 0
 *     2. 0 is cast to a pointer to struct TYPE. IOW, we are making the compiler believe that there is such a struct at the beginning of the program's data segment (which is generally dangerous, but I'll mention later why not in this particular case).
 *     3. Then, member MEMBER within this struct is referenced.
 *     4. Its contents are not used, but its address taken (with &),
 *     5. And this address converted back to a numeric type size_t.
 *
 *     As the address for the "start" of the struct was specified as 0, the address of MEMBER (when converted to a number) is its offset within the struct.
 *     Everything involves just pointers to those positions (but not their contents) and numbers. All of them held in machine registers or the usual local stack.
 *
 *     The following expression:
 *     ( (size_t) &( ((TYPE *)3264)->MEMBER ) - 3264 )
 *
 *
 *     would also work. Added a parentheses set to make it more legible.
 *========================================================
 * list_for_each_entry (pos, head, member): iterate over list of given type
 *
 * pos: the type *to use as a loop cursor.
 *
 * head: the head for your list
 *
 * member: the name of the list_struct within the struct.
 * ======================================================
 *
 * http://dev.man-online.org/man9/list_for_each_entry_safe/
 *
 *=======================================================
 *
 * list_for_each_entry_safe (pos, n, head, member)
 * iterate over list of given type safe against removal of list entry
 *
 * pos: the type *to use as a loop cursor.
 *
 * n:  another type *to use as temporary storage
 *
 * head: the head of your list
 *
 * member: the name of the list_struct within the struct.
 *
 *========================================================
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define list_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type*)0)->member)))

#define list_for_each(pos, head) \
	for (pos = head->next; pos != head; pos = pos->next)

#define list_for_each_entry(pos, head, member) \
	for (pos = list_entry((head)->next, typeof(*pos), member); \
	     &pos->member != head; \
	     pos = list_entry(pos->member.next, typeof(*pos), member))


/* Basic type for the double-link list. */
struct list_head {
	struct list_head *prev, *next;
};

struct company {
	int value;
	char ch[40];
	struct list_head lp;
};

struct list_head *head = NULL;


void init_list_head ()
{
	if (head == NULL) {
		head = (struct list_head *)malloc (sizeof(struct list_head));
		head->next = head->prev = head;
        }
	
}

void list_add_tail (struct list_head *new, struct list_head *head)
{
        new->next = head;
        new->prev = head->prev;
	
	new->prev->next = new;
	new->next->prev = new;
}

void print_list ()
{
	struct company *iter = NULL;
	int i=1;
	
	list_for_each_entry (iter, head, lp)
	{
		printf ("%d payload is: \n",i);
		printf ("%d  and  %s\n", iter->value,iter->ch);
		i++;
	}
}

void add_payload ()
{
	struct company *cpny;
	
	cpny = (struct company*)malloc (1* sizeof(struct company));

	init_list_head (&cpny->lp);
	
	printf ("enter serial number for company\n");
	scanf ("%d", &cpny->value);

	printf ("enter name of company\n");
	scanf ("%s", cpny->ch);

	//cpny->value = 123;
	//strcpy(cpny->ch, "gaurav");

	//add this payload to doubly link list
	list_add_tail (&cpny->lp, head);			
}

int main ()
{
	init_list_head (head);

	add_payload ();
	add_payload ();
	add_payload ();	

	print_list (head);

	return 0;
}
