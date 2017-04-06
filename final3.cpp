#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
using namespace std;

#define V 9
long budget;
int nights;
int nights1,nights2;
int trainfare1;
int cab[3];

int hotelprice1,hotelprice2;
char dest[20];
class admin
{
    private:
		char apass[20];
	public:
	void getdata()
	{

		cout<<endl<<"enter the adminstrators password"<<endl;

		cin>>apass;
	}
	void checkpass();
	void inputpass();

};
struct trains
{
    char src[20];
    char dst[20];
    char name[20];
    long fare;
   // packages *p[];
}t[50];

struct hotels
    {
    char name[20];
    long price;
    }h[10];

int hcount;
int pcount=9;
int tcount=2;
struct packages
    {
    char destination[20];
    }p[9];

static char* jaipur[]=
{
  "Fortune","Radisson","Country-Inn","chokidhani","rajmandir","amerfort","hawamahal","citypalace","zoo"
};
static char* himachal[]=
{
 "Fortune","Radisson","Country-Inn","nainital","shimla","kullu","manali","mcleodganj","rohtang"
};
static char* goa[]=
{
 "Fortune","Radisson","Country-Inn","casinoroyale","chaporabeach","ramnathi","colvabeach","durgatemple","margaon"
};

static char* kerala[]=
{
 "Fortune","Radisson","Country-Inn","thekkady","munnar","kannur","cheraibeach","vembannad","hillpalace","anamudi"
};
static char* delhi[]=
{
 "Fortune","Radisson","Country-Inn","akshardham","delhi-haat","cannaught-place","red-fort","lotus-temple","doll-museum","qutub-minar"
};
static char* udaipur[]=
{
 "Fortune","Radisson","Country-Inn","city-palace","lake-pichola","kumbalgharh","sajjangarh","fatehsagar","nathdwara","shilpgram"
};
static char* mumbai[]=
{
 "Fortune","Radisson","Country-Inn","chaupati","marine-drive","essel-world","gateway-of-india","hanging-gardens","elephant-caves","victoria-terminus"
};
static char* ladakh[]=
{
 "Fortune","Radisson","Country-Inn","zanskar-ranges","pangong","moriri","khardungla","nubra-valley","spitic-gumpa","magnetic-hills"
};
static char* mount_abu[]=
{
 "Fortune","Radisson","Country-Inn","nakki-lake","dilwara-temples","guru-shikhar","sunset-point","guru-shikhar","peace-park","adhar-temple"
};
static char* city[]=
{
  "delhi","udaipur","mount_abu","jaipur","ladakh","goa","mumbai","kerala","himachal"
};
void total_budget()
{
    int total;
    cout<<"\nYour total budget of the tour is";
    total=cab[0]+(hotelprice1*nights)+(trainfare1*2);
    cout<<"\t"<<total;
}
void total_budget1()
{
    int total;
    cout<<"\nYour total budget of the tour is";
    total=cab[1]+(hotelprice1*nights1)+(trainfare1*2)+cab[2]+(hotelprice2*nights2);
    cout<<"\t"<<total;
}

void input_hotel()
{
    int i;
    int cnt;
    FILE *fr,*fp;
    cout<<"Enter number of hotels you want to add";
    cin>>cnt;
    fr=fopen("fil.txt","r+");
    fscanf(fr,"%d",&hcount);
    hcount+=cnt;
    fseek(fr,0,SEEK_SET);
    fprintf(fr,"%d",hcount);
    fclose(fr);

    fp=fopen("fil.txt", "a");

    for(i=1;i<=cnt;i++)
    {
    printf("Enter Name and Price of hotel %d",i);
   scanf("%s %d", h[i].name,&h[i].price);
   fprintf(fp,"%s %d",h[i].name,h[i].price);
    }
   fclose(fp);
}

int output_hotel(long budget,int nights)
{
    FILE *q;
     int i,j;
     int z=0;
    q=fopen("fil.txt","r+");

    long diff=budget/5; //apply formula here
    fscanf(q,"%d",&hcount);
    for(i=1;i<=hcount;i++)
    {
        fscanf(q,"%s %ld",h[i].name,&h[i].price);
        if(h[i].price<=diff)
        printf("\n\n\nPress %d for Hotel Name: %s  Price: %ld\n",i,h[i].name,h[i].price);
    };
    cin>>j;
        system("cls");
    printf("You selected %s ",h[j].name);
    hotelprice1=h[j].price;
    fclose(q);
    return j;
}

int printMST(int parent[], int n, int graph[V][V],char* a[],int y)
{
   int totalkms=0;
   int cabfare;
   int j=20;
   int k=y;
   int z=0;

   cout<<endl<<"Your city tour: "<<endl<<"fare of cab for each km is Rs.20"<<endl;
//   printf("Edge   Weight\n");
   for(int count=0;count<V-3;count++)
   {
   for (int i = 0; i < V; i++)
   {
        if(parent[i]==k)
      {
    printf("%s - %s    %d km\n", a[parent[i]],a[i], graph[i][parent[i]]);
      k=i;
      totalkms+= graph[i][parent[i]];
   }
   }
   }
   cab[z++]=(totalkms*j);
   cout<<endl<<"Total kms travelled\t\t"<<totalkms;
   cout<<endl<<"Total cab fare is\t\t"<<totalkms*j;


}

void primMST(int graph[V][V],char *a[],int x)
{
     int parent[V];
     int key[V];
     bool mstSet[V];
     int v,u;
     int y=x-1;

    for (int i = 0; i < V; i++)
   {
       key[i] = INT_MAX;
       parent[i]=INT_MAX;
       if(i<3)
       {
           if(i!=y)
            mstSet[i]=true;
           else mstSet[i]=false;
       }
       else
       mstSet[i] = false;

    }
/*    for(int i=0;i<3;i++)
    {
        key[i]=INT_MAX;
        if(i==y)
            mstSet[i]=false;
        else
            mstSet[i]=true;
    }*/
        u=y;
      key[y] = 0;
     parent[y] = -1;
     for (int count = 0; count < V-3; count++)
     {
    int min=INT_MAX;
	mstSet[u] = true;
	for (v = 0; v < V; v++)
	  {
        if (graph[u][v] && mstSet[v] == false && graph[u][v] < min)
        {
        min=graph[u][v];
        }
	  }
	  for(v=0;v<V;v++)
      {
          if(min==graph[u][v] && mstSet[v]==false)
          {
        parent[v]  = u;
        key[v] = graph[u][v];
        u=v;
        break;
      }
      }
     }
     printMST(parent, V, graph,a,y);
}

void primMST(int graph[V][V],char *a[],int x,int cities[9],int cnt)
{
     int parent[V];
     int key[V];
     bool mstSet[V];
     int v,u,j;
     int y=x-1;
     int flag;
    for (int i = 0; i < V; i++)
   {
       key[i] = INT_MAX;
        parent[i]=INT_MAX;
       if(i<3)
       {
           if(i!=y)
            mstSet[i]=true;
           else mstSet[i]=false;
       }
       else
       {
        for(j=0;j<cnt;j++)
        {
        if(i==cities[j])
        {
       flag=1;
       break;
        }
       else flag=0;
        }
        if(flag==1)
            mstSet[i]=false;
        else mstSet[i]=true;
       }

   }
   cout<<endl;

        u=y;
      key[y] = 0;
     parent[y] = -1;
     for (int count = 0; count < V-3; count++)
     {
    int min=INT_MAX;
	mstSet[u] = true;
	for (v = 0; v < V; v++)
	  {
        if (graph[u][v] && mstSet[v] == false && graph[u][v] < min)
        {
        min=graph[u][v];
        }
	  }
	  for(v=0;v<V;v++)
      {
          if(min==graph[u][v] && mstSet[v]==false)
          {
        parent[v]  = u;
        key[v] = graph[u][v];
        u=v;
        break;
      }
      }
     }
     printMST(parent, V, graph,a,y);
}

int minDistance(int dist[], bool sptSet[])
{

    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}


void printPath(int parent[], int j,char *a[])
{

    if (parent[j]==-1)
        return;

    printPath(parent, parent[j],a);

    printf("->%s ", a[j]);
}

int printMaxActivities(char *a[],int (&storecity)[9])
{
    int i, j,k=0;
   int s[] =  {1, 3, 4, 5, 8, 5, 9, 10, 1};
   int f[] =  {2, 4, 6, 7, 9, 9, 10, 11, 4};
   int n = sizeof(s)/sizeof(s[0]);
 //  cout<<endl<<"Following places of visit are selected";
    i = 4;
  //  cout<<endl<<i<<"\t"<<a[i];
    storecity[k++]=i;
    // Consider rest of the activities
    for (j = 1; j < n; j++)
    {

      if (s[j] >= f[i])
      {
    // cout<<endl<<j<<"\t"<<a[j];
        storecity[k++]=j;
	  i = j;
      }
    }
    return k;
}

void func(char dest[],int (&storecity)[9],int graph[9][9],int x)
{
    int cnt;
        if(strcmp(dest,"jaipur")==0)
        {
        cnt=printMaxActivities(jaipur,storecity);
        primMST(graph,jaipur,x,storecity,cnt);
        }
        else if(strcmp(dest,"himachal")==0)
        {
        cnt=printMaxActivities(himachal,storecity);
        primMST(graph,himachal,x,storecity,cnt);
        }
        else if(strcmp(dest,"goa")==0)
        {
        cnt=printMaxActivities(goa,storecity);
        primMST(graph,goa,x,storecity,cnt);
        }
        else if(strcmp(dest,"kerala")==0)
        {
        cnt=printMaxActivities(kerala,storecity);
        primMST(graph,kerala,x,storecity,cnt);
        }
        else if(strcmp(dest,"delhi")==0)
        {
        cnt=printMaxActivities(delhi,storecity);
        primMST(graph,delhi,x,storecity,cnt);
        }
        else if(strcmp(dest,"mumbai")==0)
        {
        cnt=printMaxActivities(mumbai,storecity);
        primMST(graph,mumbai,x,storecity,cnt);
        }
        else if(strcmp(dest,"udaipur")==0)
        {
        cnt=printMaxActivities(udaipur,storecity);
        primMST(graph,udaipur,x,storecity,cnt);
        }
        else if(strcmp(dest,"ladakh")==0)
        {
        cnt=printMaxActivities(ladakh,storecity);
        primMST(graph,ladakh,x,storecity,cnt);
        }
        else if(strcmp(dest,"mount_abu")==0)
        {
        cnt=printMaxActivities(mount_abu,storecity);
        primMST(graph,mount_abu,x,storecity,cnt);
        }
}
int function1(long bugdet,int nights)
{
    //float nights1;
   // int result;
   int budget1=bugdet/2;
    nights1=nights/2;
    nights2=nights-nights1;
    cout<<endl<<nights2;
   int result=output_hotel(budget1,nights1);
   hotelprice2=h[result].price;
   return result;
}

void next_city_travel(char dest[],int x)
{
    int k,cnt,i,j,graph[V][V],res;
    FILE *fp;
    char ch,c,cname[20];
    cout<<endl<<"do u wish to travel any of these cities in between? y/n";
    cin>>ch;
    fflush(stdin);
    int storecity[9]={0};
    if(ch=='y')
    {
        cout<<"\nEnter your choice: ";
        cin>>k;

        res=function1(budget,nights);

        printf("\nYour new tour: \n");
        strcpy(cname,dest);
        strcat(cname,".txt");

        fp=fopen(cname,"r");
        if(!fp)
        printf("unable to read file");

        for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        fscanf(fp,"%d%c",&graph[i][j],&c);

        func(dest,storecity,graph,x);
        fclose(fp);
        for(int s=0;s<9;s++)
            storecity[i]=0;
        if(k==0)
        {
            fp=fopen("delhi.txt","r");
            if(!fp)
            printf("unable to read file");

            for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            fscanf(fp,"%d%c",&graph[i][j],&c);

            cnt=printMaxActivities(delhi,storecity);
            primMST(graph,delhi,res,storecity,cnt);
        }
        else if(k==1)
        {
            fp=fopen("udaipur.txt","r");
            if(!fp)
            printf("unable to read file");

            for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            fscanf(fp,"%d%c",&graph[i][j],&c);

            cnt=printMaxActivities(udaipur,storecity);
            primMST(graph,udaipur,res,storecity,cnt);
        }
        else if(k==2)
        {
            fp=fopen("mount_abu.txt","r");
            if(!fp)
            printf("unable to read file");

            for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            fscanf(fp,"%d%c",&graph[i][j],&c);

            cnt=printMaxActivities(mount_abu,storecity);
            primMST(graph,mount_abu,res,storecity,cnt);
        }
        else if(k==3)
        {
            fp=fopen("jaipur.txt","r");
            if(!fp)
            printf("unable to read file");

            for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            fscanf(fp,"%d%c",&graph[i][j],&c);

            cnt=printMaxActivities(jaipur,storecity);
            primMST(graph,jaipur,res,storecity,cnt);
        }
        else if(k==4)
        {
            fp=fopen("ladakh.txt","r");
            if(!fp)
            printf("unable to read file");

            for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            fscanf(fp,"%d%c",&graph[i][j],&c);

            cnt=printMaxActivities(ladakh,storecity);
            primMST(graph,ladakh,res,storecity,cnt);
        }
        else if(k==5)
        {
            fp=fopen("goa.txt","r");
            if(!fp)
            printf("unable to read file");

            for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            fscanf(fp,"%d%c",&graph[i][j],&c);

            cnt=printMaxActivities(goa,storecity);
            primMST(graph,goa,res,storecity,cnt);
        }
        else if(k==6)
        {
            fp=fopen("mumbai.txt","r");
            if(!fp)
            printf("unable to read file");

            for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            fscanf(fp,"%d%c",&graph[i][j],&c);

            cnt=printMaxActivities(mumbai,storecity);
            primMST(graph,mumbai,res,storecity,cnt);
        }
        else if(k==7)
        {
            fp=fopen("kerala.txt","r");
            if(!fp)
            printf("unable to read file");

            for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            fscanf(fp,"%d%c",&graph[i][j],&c);

            cnt=printMaxActivities(kerala,storecity);
            primMST(graph,kerala,res,storecity,cnt);
        }
        else
        {
            fp=fopen("himachal.txt","r");
            if(!fp)
            printf("unable to read file");

            for(i=0;i<9;i++)
            for(j=0;j<9;j++)
            fscanf(fp,"%d%c",&graph[i][j],&c);

            cnt=printMaxActivities(himachal,storecity);
            primMST(graph,himachal,res,storecity,cnt);
        }
        total_budget1();

    }
    else
    {
       total_budget();
    }


}



void print(int parent[], int j,char *a[])
{

    int i,k;
 char ch;
    long budget1;
    if (parent[j]==-1)
        return;

    print(parent, parent[j],a);
     if(strcmp(a[j],dest)!=0)
     {
         printf("\n\nYou may also like to visit: \n");
        printf(" Press %d for %s \n",j,a[j]);
//function1();
    }
}

int printSolution(int dist[], int n, int parent[],char *a[],int sr)
{
    int src = sr;
    printf("\nSource city\t\t Distance\t\t Path\n");
    for (int i = 1; i < V; i++)
    {
        if(strcmp(a[i],dest)==0)
        {
          printf("\n%s->%s \t\t %d\t\t%s ", a[src], a[i], dist[i], a[src]);
          printPath(parent, i,a);

          print(parent,i,a);
        }


        //distance from source to every city with its path
        //printf("\n%s->%s \t\t %d\t\t%s ", a[src], a[i], dist[i], a[src]);
        //printPath(parent, i,a);
    }
}



void dijkstra(int graph[V][V], char *a[],int src,char dest[],int x)
{
    int dist[V];
     bool sptSet[V];

    int parent[V];

    for (int i = 0; i < V; i++)
    {
        parent[src]=-1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

      dist[src] = 0;

     for (int count = 0; count < V-1; count++)
    {

        int u = minDistance(dist, sptSet);


        sptSet[u] = true;


        for (int v = 0; v < V; v++)


            if (!sptSet[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    printSolution(dist, V, parent,a,src);
    next_city_travel(dest,x);

}




void admin::inputpass()
{
	fstream f("aaa.txt",ios::out);
	if(!f)
	{
		cout<<endl<<"unable to write to file";
		return;
	}
	this->getdata();
	f.write((char *)this,sizeof(*this));

}
void admin::checkpass()
{

	fstream fp("aaa.txt",ios::in);
	char pass[20];
	int f=0;
	int ch;
	if(!fp)
	{
		cout<<"unable to read the file and find the search data"<<endl;
		return;
	}
	cout<<"enter the password"<<endl;
	cin>>pass;
	while(fp.read((char *)this,sizeof(*this)))
	{
		if(strcmp(this->apass,pass)==0)
		{
			f=1;
			break;
		}
	}
	if(f==1)
	{

		cout<<"You have successfully logged in"<<endl;
		cout<<"press 1 to add hotels:"<<endl;
		//cout<<"enter 2 to read all data:"<<endl;
//cout<<"enter 3 to see suppliers in sorted order"<<endl;
		cin>>ch;
        //items r;
		switch(ch)
		{
		    case 1:input_hotel();;
            break;
            default:
            break;
		}
	}
	else
	cout<<"Incorrect Password"<<endl;
}

void output_train(char dest[],char source[])
{
    FILE *r;
     int i;

    r=fopen("tra.txt","r");
        for(i=0;i<tcount;i++)
    {
        fscanf(r,"%s %s %ld %s",&t[i].src,&t[i].dst,&t[i].fare,&t[i].name);
        if(strcmp(t[i].src,source)==0 && strcmp(t[i].dst,dest)==0)
        break;
    }
        printf("\n\nTrain Name: %s   Train Fare: %ld\n\n\n",t[i].name,t[i].fare);
        trainfare1=t[i].fare;

    fclose(r);
}
void customer(int graph1[V][V])
{
    FILE *fp;
    char ch,c,c1;

    char source[20];
    char fname[20];
    char cname[20];
   // long budget;
    //int nights;
    int graph[9][9];
    int i,flag,j,x,cnt;
    int storecity[9]={0};
    cout<<"Wish to travel? y/n";
    cin>>ch;
    if(ch=='y')
    {
next:fflush(stdin);
    cout<<"Enter destination \n";
    gets(dest);
    fflush(stdin);
    cout<<"Enter source \n";
    gets(source);
    fflush(stdin);
    cout<<"Enter budget \n";
    cin>>budget;
    cout<<"Enter number of nights\n";
    cin>>nights;

    fp=fopen("dest.txt","r");
    for(i=0;i<pcount;i++)
    {
        fscanf(fp,"%s",p[i].destination);
        if(strcmp(dest,p[i].destination)==0)
        {
        flag=1;
        x=output_hotel(budget,nights);
        break;
        }
        else flag=0;
    }
            if(flag==0)
            {
            printf("Enter a valid city name\n");
            goto next;
        }



    strcpy(fname,dest);
    strcpy(cname,dest);
    strcat(fname,".txt");

   fp=fopen(fname,"r");
     if(!fp)
     printf("unable to read file");

     for(i=0;i<9;i++)
     for(j=0;j<9;j++)
    {
        fscanf(fp,"%d%c",&graph[i][j],&c);
//        printf("%d ",graph[i][j]);
    }

    if(nights<=2)
    {
        func(dest,storecity,graph,x);

        cout<<endl;
     }



    else
    {

    if(strcmp(cname,"jaipur")==0)
     primMST(graph,jaipur,x);
    else if(strcmp(cname,"himachal")==0)
     primMST(graph,himachal,x);
     else if(strcmp(cname,"goa")==0)
     primMST(graph,goa,x);
     else if(strcmp(cname,"kerala")==0)
     primMST(graph,kerala,x);
     else if(strcmp(cname,"delhi")==0)
     primMST(graph,delhi,x);
     else if(strcmp(cname,"mumbai")==0)
     primMST(graph,mumbai,x);
     else if(strcmp(cname,"ladakh")==0)
     primMST(graph,ladakh,x);
     else if(strcmp(cname,"udaipur")==0)
     primMST(graph,udaipur,x);
     else if(strcmp(cname,"mount_abu")==0)
     primMST(graph,mount_abu,x);

    }
    fclose(fp);
    cout<<endl;
        output_train(dest,source);
    for(i=0;i<9;i++)
    {
    if(strcmp(city[i],source)==0)
    {
    dijkstra(graph1,city,i,dest,x);
    break;
    }

    }
    }
}

int main()
{
    FILE *fp;
    char ch;
    char dest[20];
    int i;
    int choice;
    int graph1[V][V] = {{0, 0, 6, 5, 12, 0, 10, 0, 16},
                       {0, 0, 3, 5, 15, 10, 9, 14, 12},
                       {6, 3, 0, 2, 10, 15, 13, 16, 9},
                       {5, 5, 2, 0, 12, 10, 8, 17, 11},
                       {12, 15, 10, 12, 0, 13, 10, 25, 14},
                       {0, 10, 15, 10, 13, 0, 3, 8, 15},
                       {10, 9, 13, 8, 10, 3, 0, 10, 17},
                       {0, 14, 16, 17, 25, 8, 10, 0, 30},
                       {16, 12, 9, 11, 14, 15, 17, 30, 0}
                      };
     admin obj;
		cout<<"press 1 for admin login:"<<endl;
        cout<<"press 2 for customer login:"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:
			obj.checkpass();
			break;
			case 2: customer(graph1);
                    break;
			case 11:
            obj.inputpass();
			break;

			default:
			cout<<"please enter a valid choice:"<<endl;
		}
   // cout<<"want to add hotels? y/n";
    //cin>>ch;
    //if(ch=='y')
    //input_hotel();


    return 0;
}
