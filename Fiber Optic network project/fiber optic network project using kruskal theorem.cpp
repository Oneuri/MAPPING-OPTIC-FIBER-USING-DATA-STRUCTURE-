#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<string>
#include<conio.h>
#include<windows.h>
#include<mysql.h>
#include<sstream>


using namespace std;


class node{
    int id;
    string name;
    int users;
    friend class graph;
    friend class edge;
public:
    node(int id,string name,int users){
        this->id = id;
        this->name = name;
        this->users = users;
    }
    void createnode();
    };

class edge{

    node* begin,*end;
    int weight;
    friend class graph;
public:
    edge(node *start,node *end,int weight){
        this->begin = start;
        this->end = end;
        this->weight = weight;
    }

};
class disjoint{
    int *parent,*rnk;
    int n;
    friend class graph;
public:
    disjoint(int n){
        this->n = n;
        parent = new int[n+1];
        rnk = new int[n+1];

        for(int i=0;i<=n;i++){
            rnk[i] = 0;
            parent[i] = i;
        }
    }
    int find1(int u){
        if(u!=parent[u])
            parent[u] = find1(parent[u]);
        return parent[u];

    }
    void merge(int x,int y){
        x = find1(x);
        y = find1(y);
        if(rnk[x]>rnk[y])
            parent[y] = x;
        else
            parent[x] = y;
        if(rnk[x]==rnk[y])
            parent[x] = y;
            rnk[y]++;
    }
};
class graph{
public:
    int id;
    edge* earray[100];
    int ecount = 0;
    node* array[100];
    int count = 0;
    pair <int, pair<int, int> > p[100];
     pair<int,pair<int,int> > q[100];
     int ccount = 0;

public:
    void kruskal();
    node* getnode(int id);
    void displaynodes();
    void displayedges();
    void createGraph();
    void createPair();
    void diaplaySeq();
    void sorte();
    void createdat();
    void createdated();

};

void node::createnode(){
    cout<<"Enter name:"<<endl;
    cin>>name;
    cout<<"Enter id"<<endl;
    cin>>id;
    cout<<"Enter no. of users"<<endl;
    cin>>users;
    node* newnode = new node(id,name,users);

}

node* graph::getnode(int id){
    int i;
    for(i=0;i<count;i++){
        if(array[i]->id==id){
        return array[i];
        }
    }
}

void graph::displaynodes(){
    int it;
    for(it=0;it<count;it++){
        cout<<"Node "<<it+1<<endl;
        cout<<"Name: "<<array[it]->name<<endl;
        cout<<"ID: "<<array[it]->id<<endl;
        cout<<"Users: "<<array[it]->users<<endl;
    }
}

void graph::createdat(){
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn=mysql_init(0);
    conn=mysql_real_connect(conn,"192.168.0.106","admin","admin","trial",0,NULL,0);
    if(conn)
    {
        cout<<"Connected"<<endl;
    }
    else
        cout<<"Not connected"<<endl;
    int qstate=mysql_query(conn,"select * from test");
    if(!qstate)
        {
            res=mysql_store_result(conn);
            while(row=mysql_fetch_row(res))
            {
                int id=0;
                int users = 0;
                stringstream geek(row[0]);
                geek>>id;
                stringstream geek1(row[2]);
                geek1>>users;
                string name = row[1];

                node * newnode = new node(id,name,users);
                array[count] = newnode;
                count++;

                //cout<<row[0]<<row[1]<<row[2]<<endl;
            }
        }
    else
        cout<<"Failed"<<endl;
        displaynodes();



}
void graph::createdated()
{
    MYSQL* conn1;
    MYSQL_ROW row1;
    MYSQL_RES* res1;
    conn1=mysql_init(0);
    conn1=mysql_real_connect(conn1,"192.168.0.106","admin","admin","trial",0,NULL,0);
    if(conn1)
    {
        cout<<"Connected"<<endl;
    }
    else
        cout<<"Not connected"<<endl;

    int qstate1=mysql_query(conn1,"select * from edges");
    if(!qstate1)
        {
            res1=mysql_store_result(conn1);
            while(row1=mysql_fetch_row(res1))
            {
                int start=0;
                int stop = 0;
                int weight = 0;
                stringstream geek2(row1[0]);
                geek2>>start;
                stringstream geek3(row1[1]);
                geek3>>stop;
                stringstream geek4(row1[2]);
                geek4>>weight;



                edge * newedge = new edge(getnode(start),getnode(stop),weight);
                earray[ecount] = newedge;
                ecount++;
                displayedges();

                //cout<<row[0]<<row[1]<<row[2]<<endl;
            }
        }
    else
        cout<<"Failed"<<endl;

}
void graph::createPair(){
    int i,j;
    for(i=0;i<ecount;i++){
        p[i] = make_pair(earray[i]->weight,make_pair(earray[i]->begin->id,earray[i]->end->id));
    }
    sort(p,p+ecount);



}
void graph::displayedges(){
    int it;
    for(it=0;it<ecount;it++){
        cout<<"Edge "<<it+1<<endl;
        cout<<"Start: "<<earray[it]->begin->name<<endl;
        cout<<"stop: "<<earray[it]->end->name<<endl;
        cout<<"Weight: "<<earray[it]->weight<<endl;
    }
}
void graph::sorte(){
    int i;
    pair<int,pair<int,int> > temp;
    for(i=0;i<ccount;i++){
        for(int j=0;j<ecount;j++){
            if(q[i].second.first<q[j].second.first){
                temp = q[i];
                q[i] = q[j];
                q[j] = temp;
            }
        }
    }
    cout<<"SORTED PATHS"<<endl;
    for(i=0;i<ccount;i++){
        cout<<getnode(q[i].second.first)->name<<" - "<<getnode(q[i].second.second)->name<<endl;
    }
}


void graph::createGraph(){
    int start,stop,weight,id,users;
    string name;
    int it,nodes,edges;
    cout<<"Enter no of area cabinets"<<endl;
    cin>>nodes;
    for(it=0;it<nodes;it++){
        cout<<"LOCATION "<<it+1<<endl;
        cout<<"Enter location name:"<<endl;
        cin>>name;
        cout<<"Enter network id"<<endl;
        cin>>id;
        cout<<"Enter no. of users"<<endl;
        cin>>users;
         node *newnode = new node(id,name,users);
        array[count]=newnode;
        count++;
    }


    cout<<"Enter no of edges"<<endl;
    cin>>edges;
    for(it=0;it<edges;it++){
        cout<<"From.............."<<endl;
        cin>>start;
        cout<<"To................."<<endl;
        cin>>stop;
        cout<<"Enter Distance in km"<<endl;
        cin>>weight;
        edge *newedge = new edge(getnode(start),getnode(stop),weight);
        earray[ecount] = newedge;

        ecount++;
    }
    displaynodes();
    displayedges();
}

void graph::kruskal(){
    int mst_wt = 0;
    disjoint ds(count);
    for(int it=0;it<ecount;it++){
        int u = p[it].second.first;
        int v = p[it].second.second;

        int set_u = ds.find1(u);
        int set_v = ds.find1(v);

        if(set_u != set_v){
            cout<<getnode(u)->name<<" - "<<getnode(v)->name<<endl;
            mst_wt += p[it].first;
            ds.merge(set_u,set_v);
            q[ccount]=p[it];
            ccount++;


        }


    }
    cout<<"Cost = "<<mst_wt<<endl;

}

main(){
    graph g1;
    g1.createdat();
    g1.createdated();
    cout<<"************************************************************************************************************************"<<endl;
    cout<<"                                                 MIN COST FIBRE CABLE MAP                                               "<<endl;
    cout<<"************************************************************************************************************************"<<endl;


    g1.createGraph();
    g1.createPair();
    g1.kruskal();
    g1.sorte();
}
