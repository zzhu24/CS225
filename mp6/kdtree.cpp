/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
if (first[curDim]>second[curDim]) return false;
else if (first[curDim]<second[curDim]) return true;
else return (first < second);
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
int tar_curr = finddistance(target,currentBest);
int tar_po = finddistance(target,potential);
if (tar_curr<tar_po) return false;
else if (tar_curr>tar_po) return true;
else return (potential<currentBest);
}

template<int Dim>
int KDTree<Dim>::finddistance(const Point<Dim> & target, const Point<Dim> & otherpoint) const
{
int distance=0;
for (int i=0;i<Dim;i++) distance += (target[i]-otherpoint[i])*(target[i]-otherpoint[i]);
    return distance;
}

template<int Dim>
void KDTree<Dim>::swap(int start, int end){
    auto temp = points[start];
    points[start] = points[end];
    points[end] = temp;
}


template<int Dim>
int KDTree<Dim>::partition(int left, int right, int dimension, int median)
{
    auto pivot=points[median];
    swap(median, right);
    int temp=left;
    int end = right - 1;
    while(1){
        if(smallerDimVal(points[temp],pivot,dimension)){
            temp++;
        }else{
            swap(temp , end);
            end--;
        }
        if(temp>end){
            swap(temp,right);
            break;
        }
    }
    return temp;//pivot index
}
template<int Dim>
void KDTree<Dim>::select(int k, int left, int right, int dimension)
{
    while(left!=right)
    {
        int pivot=partition(left, right, dimension, k);
        if(pivot==k)
            break;
        else if(k<pivot)
            right=pivot-1;
        else
            left=pivot+1;
    }
}

template<int Dim>
void KDTree<Dim>::buildtree(int left, int right, int dimension)
{
    if(left==right)
        return;
    int median = (left+right)/2;
    select(median, left, right, dimension);
    if(left<median)
        buildtree(left, median-1, (dimension+1)%Dim);
    if(right>median)
        buildtree(median+1, right, (dimension+1)%Dim);
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
    points=newPoints;
    if(points.size()!=0)
        buildtree(0, newPoints.size()-1, 0);
}


template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> ret=findNearestNeighbor(0, query, 0, points.size()-1, points[(points.size()-1)/2]);
    return ret;
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(int dimension, const Point<Dim> & query, int left, int right, const Point<Dim> & currentBest) const
{
    Point<Dim> ret=currentBest;
int dtest=1;
    if(left>=right)
    {   dtest++;
        if(shouldReplace(query, currentBest, points[left]) && dtest>1)
        {

            return points[left];
        }
        else return ret;
    }
int addnice=left + right;
    	int median = addnice/2;
   
    if(smallerDimVal(points[median], query, dimension))
    {
        ret=findNearestNeighbor((dimension+1)%Dim, query, median+1, right, currentBest);
    }
    if(!smallerDimVal(points[median], query, dimension))
    {
        ret=findNearestNeighbor((dimension+1)%Dim, query, left, median-1, currentBest);
    }
    if(shouldReplace(query, ret, points[median]))
        ret=points[median];
    Point<Dim> a=points[median];
    if((a[dimension] - query[dimension])*(a[dimension] - query[dimension]) <= finddistance(query, ret))
    {
        if(!smallerDimVal(points[median], query, dimension))
            ret=findNearestNeighbor((dimension+1)%Dim, query, median+1, right, ret);
        if(smallerDimVal(points[median], query, dimension))
            ret=findNearestNeighbor((dimension+1)%Dim, query, left, median-1, ret);
    }
    return ret;
    
}

