#include <iostream>
using namespace std;
int binarysearch(int a[],int size,int key,int &compare){
    int first=0,last=size-1;
    compare=0;
    while(first<=last){
        int mid=(first+last)/2;
        compare++;
        if(a[mid]==key) return mid;
        compare++;
        if(a[first]==a[mid]){
            compare++;
            if(a[mid]==a[last]){
                first++;
                last--;
                continue;
            }
        }
        compare++;
        if(a[first]<=a[mid]){
            compare++;
            if(a[first]<=key){
                compare++;
                if(key<a[mid]) last=mid-1;
                else first=mid+1;
            }
            else first=mid+1;
        }
        else{
            compare++;
            if(a[mid]<key){
                compare++;
                if(key<=a[last]) first=mid+1;
                else last=mid-1;
            }
            else last=mid-1;
        }
    }
    return -1;
}
void result(int item,int res,int com){
    if(res==-1) cout<<"Element: "<<item<<" is not found\n";
    else cout<<"Element: "<<item<<" is found\n";
    cout<<"Index of the element: "<<res<<"\nNumber of comparisons: "<<com<<"\n\n";
}
int main(){
    //without duplication
    int arr[7]={5,6,7,1,2,3,4},comp,item=7;
    int res=binarysearch(arr,7,item,comp);
    result(item,res,comp);

    //with duplication
    int arr2[7]={1,6,7,1,2,3,1},comp2,item2=7;
    int res2=binarysearch(arr2,7,item2,comp2);
    result(item2,res2,comp2);

    /*best case o(1), worst case o(n)*/
}