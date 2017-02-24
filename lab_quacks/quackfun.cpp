/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T QuackFun::sum(stack<T> & s)
{if(s.empty() == true){
	return 0;}
else{
	T temp = s.top();
	s.pop();
	T newTemp = temp + sum(s);
	s.push(temp);
	return newTemp;}
    // Your code here
// stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void QuackFun::scramble(queue<T> & q)
{
        stack<T> s;
    int sub = 1;
    int left=q.size();
    bool revise=false;
    bool end=true;
    while (end){
        if (revise) {
                for (int i=0;i<sub;i++){
                    T temp = q.front();
                    q.pop();
                    s.push(temp);
                    }
                for (int j=0;j<sub;j++){
                    T temp = s.top();
                    s.pop();
                    q.push(temp);
                    }
	left-=sub;
        if (left<0||left==0){end=false;}
        else if (sub+1>left){sub=left; revise=!revise;}
        else {sub++;revise=!revise;}
        }// end if
        else {
                for (int i=0;i<sub;i++){
                    T temp = q.front();
                    q.pop();
                    q.push(temp);}
	left-=sub;
        if (left<0||left==0){end=false;}
        else if (sub+1>left){sub=left; revise=!revise;}
        else {sub++;revise=!revise;}
                    
        }// end else
        
       
    }
    // optional: queue<T> q2;

    // Your code here
}

/**
 * @return true if the parameter stack and queue contain only elements of exactly
 *  the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in your return statement,
 *      and you may only declare TWO local variables of parametrized type T to use however you wish.
 *   No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be sure to comment your code VERY well.
 */
template <typename T>
bool QuackFun::verifySame(stack<T> & s, queue<T> & q)
{bool retval = true;
//we set base case of return value as true
if(s.empty()){
	return retval;}
//if the stack is empty we can straightly return the cas cas
T top = s.top();
//set top as the first of s
s.pop();
//delete last of s
retval = verifySame(s,q);
//call the recursive function and test until the base case is met
T front = q.front();
// let the front to be the front element of q
if(top != front){
retval = false;}
//compare the front of the queue to the bottom of the stack
q.push(front);
//push first element to the back
q.pop();
//pop the queue
s.push(top);
//push the top element of the stack to the back
return retval;
//return the value of required return type
}

