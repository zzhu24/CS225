/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{clear();
    /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{ListNode *Temp;

if((head == NULL) || (tail == NULL))
{return;}
else
{while(head!=tail)
{Temp=head;
head=head->next;
delete Temp;}
delete head;
head=NULL;
tail=NULL;
Temp=NULL;
length = 0;}
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{if(head==NULL)
{ListNode *newHead = new ListNode(ndata);
head=newHead;
length=1;
tail=newHead;
newHead->next=NULL;
newHead->prev=NULL;}

else
{ListNode *newHead = new ListNode(ndata);
newHead->next = head;
head->prev = newHead;
head = newHead;
newHead->prev =NULL;
length++;}
    /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{if(tail==NULL)
{ListNode *newTail = new ListNode(ndata);
head=newTail;
length=1;
tail=newTail;
newTail->next=NULL;
newTail->prev=NULL;}

else{
ListNode *newTail = new ListNode(ndata);
tail->next = newTail;
newTail->prev = tail;
newTail->next = NULL;
tail = newTail;
length++;}
    /// @todo Graded in MP3.1
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
} 

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{if(startPoint==NULL||endPoint==NULL)
return;

if(startPoint==endPoint)
return;                                                                                                                

ListNode * begin = startPoint -> prev;
ListNode * stop = endPoint ->next;
ListNode * first = startPoint;
ListNode * second = startPoint;
	while(first !=stop){
		second = second->next;
		first->next = first->prev;
		first->prev = second;
		first = second;}
	ListNode *temp = startPoint;
	startPoint = endPoint;
	endPoint = temp;
	endPoint->next = stop;
	startPoint ->prev = begin;
	endPoint->next = stop;
	if(begin != NULL)
		{begin -> next = startPoint;}
	else if(begin == NULL)
		{head = startPoint;}
	if(stop != NULL)
		{stop->prev = endPoint;}
	else if(stop == NULL)
		{tail = endPoint;}
	begin = NULL;
	stop = NULL;
	first = NULL;
	second = NULL;
    /// @todo Graded in MP3.1
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{if(n<length){
ListNode * first = head;
ListNode * second = head;
for(int i=0;i<length/n;i++){
for(int j =0; j<n-1;j++){
second=second->next;}
reverse(first,second);
first =second->next;
second=first;}
reverse(first,tail);
first = NULL;
second = NULL;}
else{
reverse(head,tail);
return;}
    /// @todo Graded in MP3.1
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{if(head==NULL)
return;
ListNode *temp =head;
while(temp->next->next!=NULL){
ListNode *newTemp = temp->next;
temp->next=temp->next->next;
temp->next->prev=temp;
newTemp->prev=tail;
newTemp->next=NULL;
tail->next=newTemp;
tail=newTemp;
temp=temp->next;}
    /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{if(splitPoint<=0 || splitPoint >=length)
return start;

else {
ListNode * temp = start;
for(int i = 0 ; i < splitPoint ; i ++){
start = start ->next;}
temp = start -> prev;
temp -> next = NULL;
start -> prev = NULL;
return start;
temp = NULL;}
    /// @todo Graded in MP3.2
// change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second){
ListNode * temp;
if (second -> data < first -> data){
	temp = second;
	second = first;
	first = temp;
	temp = first;}
else {
	temp = first;}
ListNode * one = first;
ListNode * two = second;
while(two != NULL){
	while (one -> data < two-> data){
		if (one -> next != NULL){
			one = one -> next;}
		else{
			one -> next = two;
			two -> prev = one;
			return first;}}
		ListNode * help = two -> next;
		ListNode * curr = one ->prev;
		two -> next = one ;
		one -> prev = two;
		two -> prev = curr;
		if(curr!=NULL) {
			curr->next = two;}
		else{
			first = two;}
			two = help;}
return first;
    /// @todo Graded in MP3.2
   // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{ListNode * temp = start;
	if(chainLength==1||chainLength==0)
		return temp;
	else if((chainLength>1) && (start!=NULL)){
		temp = split(start,chainLength/2);
		start = mergesort(start, chainLength/2);
		temp = mergesort(temp, chainLength-chainLength/2);
		start=merge(start,temp);
		return start;}
	else
		return NULL;}
    /// @todo Graded in MP3.2
    // change me!

