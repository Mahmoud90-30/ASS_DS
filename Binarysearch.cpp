#include <iostream>
using namespace std;
int comp=0;
bool countcomp(bool condition){
    comp++;
    return condition;
}
int binarysearch(int a[],int size,int key){
    int first=0,last=size-1;
    while(first<=last){
        int mid=(first+last)/2;
        if(countcomp(a[mid]==key)) return mid;
        if(countcomp(a[first]==a[mid]) && countcomp(a[mid]==a[last])){
            first++;
            last--;
        }
        else if(countcomp(a[first]<=a[mid])){
            if(countcomp(a[first]<=key) && countcomp(key<a[mid])) last=mid-1;
            else first=mid+1;
        }
        else{
            if(countcomp(a[mid]<key) && countcomp(key<=a[last])) first=mid+1;
            else last=mid-1;
        }
    }
    return -1;
}
void result(int item,int res){
    if(res==-1) cout<<"Element: "<<item<<" is not found\n";
    else cout<<"Element: "<<item<<" is found\n";
    cout<<"Index of the element: "<<res<<"\nNumber of comparisons: "<<comp<<"\n\n";
}
int main(){
    //without duplication
    cout<<"===== Without Duplication =====\n";
    int arr[7]={5,6,7,1,2,3,4},item=7;
    int res=binarysearch(arr,7,item);
    result(item,res);

    //with duplication
    cout<<"===== With Duplication =====\n";
    comp = 0;
    int arr2[9]={3,3,3,1,3,3,3,3,3},item2=1;
    int res2=binarysearch(arr2,9,item2);
    result(item2,res2);

    /*best case o(1), worst case o(n)*/
}
