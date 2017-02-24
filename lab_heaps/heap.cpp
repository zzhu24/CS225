/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the left child.
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the right child.
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    /// @todo Update to return the index of the parent.
    return currentIdx / 2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    /// @todo Update to return whether the given node has a child
    return currentIdx * 2 < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
	if(hasAChild(currentIdx) == true){
		if(higherPriority(_elems[currentIdx * 2] , _elems[currentIdx * 2 +1])){
			return currentIdx * 2;}
		else{
			return currentIdx * 2 + 1;}}
	return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
	if(hasAChild(currentIdx) == false){
		return;}
	else{
		size_t maxChild = maxPriorityChild(currentIdx);
		if(higherPriority(_elems[ currentIdx] , _elems[maxChild]) == false){
			std::swap(_elems[ currentIdx] , _elems[maxChild]);
			heapifyDown(maxChild);}}    
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
	_elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    /// @todo Construct a heap using the buildHeap algorithm
	_elems.push_back(T());
//T() is regarded as empty and from the default constructor
	for(size_t i = 0; i < elems.size(); i++){
		_elems.push_back(elems[i]);}
	for(size_t i = (_elems.size() -1) / 2; i > 0; i --){
		heapifyDown(i);}
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    /// @todo Remove, and return, the element with highest priority
	if(_elems.size() == 1){
		return T();}
	else{
		T highest = * (_elems.begin() + 1);
		_elems[1] = _elems[_elems.size()-1];
		_elems.pop_back();
		heapifyDown(1);
		return highest;}
	
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    /// @todo Return, but do not remove, the element with highest priority
	if(_elems.size() == 1){
		return T();}
	else{
		T highest = * (_elems.begin() + 1);
		return highest;}
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    /// @todo Add elem to the heap
	_elems.push_back(elem);
	heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    /// @todo Determine if the heap is empty
    return (_elems.size() == 1);
}
