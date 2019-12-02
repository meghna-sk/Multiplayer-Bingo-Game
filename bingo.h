#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;
class card
{
  public:
      int arr[5][5];
      int move(int );
      int checkwin();
      int cardcheck(int,int);
      void generate();
};
class player:public card
{
  public:
  void input();
  void display();
};
class computer:public card
{
  int q[5];
  public:
  computer();
  void display();
  int play();
};
int card::cardcheck(int i,int j)
{
    if(arr[i][j]<=0 || arr[i][j]>25)
      return 0;
    int k,l;
    for(k=0;k<=i;k++)
    { 
       for(l=0;l<5;l++)
        {
          if(k==i && l==j)
           return 1;
          if(arr[i][j]==arr[k][l])
           return 0;
        
        }
     
    }
 return 1;
}
void player::input()
{


    for(int i=0;i<5;i++)
    {
      for(int j=0;j<5;j++)
      {

        cin>>arr[i][j];
        if(!card::cardcheck(i,j))
          {
             cout<<"Invalid Entry: Enter Again !!!";
             j--;
          }
      }
    }
    
  cout<<"Twenty Five numbers have been entered. \n";
}
void player::display(){
  for(int i=0;i<5;i++)
  {
   for(int j=0;j<5;j++)
   {
    if(arr[i][j]!=0)
    cout<<setw(3)<<arr[i][j];
    else
    cout<<" X";
   }
   cout<<"\n";
  } 
}
void computer::display(){
  for(int i=0;i<5;i++)
  {
   for(int j=0;j<5;j++)
   {
    if(arr[i][j]!=0)
    cout<<" .";
    else
    cout<<" X";
   }
   cout<<"\n";
  } 
}
void card::generate()
{
  for(int i=0;i<5;i++)
  {
   for(int j=0;j<5;j++)
   {
    arr[i][j]=rand()%25 +1;
    if(!cardcheck(i,j))
      {
       j--;
      }
   }
  }
}
int computer::play()
{
 int i,j,temp;
 for(i=0;i<5;i++)
 {
    for(j=0;j<5;j++)
    {
        if(i<3)
        {
          if(arr[q[i]][j]!=0)
          {
            temp=arr[q[i]][j];
            arr[q[i]][j]=0;
            return temp;
          } 
        }
        else
        {
          if(arr[j][q[i]]!=0)
          {
            temp=arr[j][q[i]];
            arr[j][q[i]]=0;
            return temp; 
          }             
        }  
    }   
 }
}
computer::computer()
{
  srand(time(0));
  for(int i=0;i<5;i++)
  {
     q[i]=rand()%5;
     for(int j=0;j<i;j++)
      {
        if(q[i]==q[j])
        {
          i--;
          break;
         
        }
      }
  }                 
}
int card::move(int x)
{
 for(int i=0;i<5;i++)
  {
   for(int j=0;j<5;j++)
   {
        
        if(arr[i][j]==x)
        {
          arr[i][j]=0;
          
          return 1;       
        }  
   }
  } 
  return 0;
}
int card::checkwin()
{
 int c=0;
 int i,j;
 for(i=0;i<5;i++)
 {
   for(j=0;j<5;j++)
   { 
      if(arr[i][j]==0)
        continue;
      else
        break;
   }
  if(j==5)
    c++;
 }
  for(i=0;i<5;i++)
  {
    for(j=0;j<5;j++)
    {
     if(arr[j][i]==0)
     continue;
     else
     break;
    }
   
    if(j==5)
    c++;
  }
  if(c==5)
   return 1;
  else
   return 0; 
}