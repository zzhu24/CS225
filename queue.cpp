/**
 * @file queue.cpp
 * Implementation of the Queue class.
 *
 * @author CS 225 course staff
 * @date Fall 2009
 */

/**
 * Adds the parameter object to the back of the Queue.
 *
 * @param newItem object to be added to the Queue.
 */
template<class T>
void Queue<T>::enqueue(T const & newItem){
inStack.push(newItem);}
    /**
     * @todo Your code here!
     */


/**
 * Removes the object at the front of the Queue, and returns it to the
 * caller.
 *
 * @return The item that used to be at the front of the Queue.
 */
template<class T>
T Queue<T>::dequeue() {
if(outStack.isEmpty() == true){
	while(inStack.isEmpty() != true){
		outStack.push(inStack.pop());}
	return outStack.pop();}
else {
	return outStack.pop();}}
//there are generally two stack list, one is the inner stack list and another is the outer stack list. We try to finish the process within the outer stack list, if ir is empty, we just pop all element in the inner stack to the outter stack and finish the process still wihtin the outer stack
    /**
     * @todo Your code here! You will need to replace the following line.
     */


/**
 * Adds an element to the ordering structure.
 *
 * @see OrderingStructure::add()
 */
template <class T>
void Queue<T>::add( const T & theItem ) {
enqueue(theItem);}
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to add the element to the Queue.
     */


/**
 * Removes an element from the ordering structure.
 *
 * @see OrderingStructure::remove()
 */
template <class T>
T Queue<T>::remove() {
return dequeue();}
    /**
     * @todo Your code here! Hint: this function should call a Queue
     *  function to remove an element from the Queue and return it. You will
     *  need to replace the following line.
     */


/**
 * Finds the object at the front of the Queue, and returns it to the
 * caller. Unlike pop(), this operation does not alter the queue.
 *
 * @return The item at the front of the queue.
 */
template<class T>
T Queue<T>::peek() {
if(outStack.isEmpty() == false){
	return outStack.peek();}
else {
	while(inStack.isEmpty() == false){
		outStack.push(inStack.pop());}
	return outStack.peek();}}
    /**
     * @todo Your code here! You will need to replace the following line.
     */


/**
 * Determines if the Queue is empty.
 *
 * @return bool which is true if the Queue is empty, false otherwise.
 */
template<class T>
bool Queue<T>::isEmpty() const{
if((inStack.isEmpty() == true ) && (outStack.isEmpty() == true)){
	return true;}
else {
	return false;}}
    /**
     * @todo Your code here! You will need to replace the following line.
     */

