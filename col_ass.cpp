#include<iostream>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;

# define INF 0x3f3f3f3f
typedef pair<int, int> iPair;

struct Node{
  int build_time;
  int traverse_time;
  long id;
  Node* next;
};

Node* a[1000000];
int b[100000];

void hello(int a[]){
  //cout<<a[0]<<endl;
  a[0] = 6;
  //cout<<a[0]<<endl;
}

Node* newNode(int id, int build_time, int traverse_time){
  Node* newNode = new Node();
  newNode->id = id;
  newNode->build_time = build_time;
  newNode->traverse_time = traverse_time;
  newNode->next = NULL;
  return(newNode);
}

void add_junction(int b[], int p, int q){
  b[p] = q;
  a[p] = NULL;
}

void add_edge(int p, int q, int r, int s){
  Node* iter = a[p];
  if(iter == NULL){
    a[p] = newNode(q, r, s);
  }
  else{
    Node* before_iter = NULL;
    while(iter != NULL && iter->id < q){
      before_iter = iter;
      iter = iter->next;
    }
    Node* temp = newNode(q, r, s);
    if(before_iter == NULL){
      temp->next = iter;
      a[p] = temp;
    }
    else{
      before_iter->next = temp;
      temp->next = iter;
    }
  }
  iter = a[q];
  if(iter == NULL){
    a[q] = newNode(p, r, s);
  }
  else{
    Node* before_iter = NULL;
    while(iter != NULL && iter->id < p){
      before_iter = iter;
      iter = iter->next;
    }
    Node* temp = newNode(p, r, s);
    if(before_iter == NULL){
      temp->next = iter;
      a[q] = temp;
    }
    else{
      before_iter->next = temp;
      temp->next = iter;
    }
  }
}

void remove_edge(int p, int q){
  Node* iter = a[p];
  if(iter == NULL){
    //no edge connects to it
  }
  else{
    Node* before_iter = NULL;
    while(iter != NULL && iter->id != q){
      before_iter = iter;
      iter = iter->next;
    }
    if(before_iter == NULL){
      a[p] = iter->next;
      delete iter;
    }
    else{
      before_iter->next = iter->next;
      delete iter;
    }
  }
  iter = a[q];
  if(iter == NULL){
    //no edge connects to it
  }
  else{
    Node* before_iter = NULL;
    while(iter != NULL && iter->id != p){
      before_iter = iter;
      iter = iter->next;
    }
    if(before_iter == NULL){
      a[q] = iter->next;
      delete iter;
    }
    else{
      before_iter->next = iter->next;
      delete iter;
    }
  }
}

void print_graph(int b[], int size){
  for(int i=0; i<=size; i++){
    Node* iter = a[i];
    printf("%i %i--", i+1, b[i]);
    //cout<<i<<" "<<b[i]<<"-- ";
    while(iter != NULL){
      printf("%ld ", iter->id + 1);
      //cout<<iter->id<<"->";
      iter = iter->next;
    }
    printf("\n");
    //cout<<endl;
  }
}

int k[1000000];
int p[1000000];
bool checklist[1000000];

void printMST(int c, int src){
  priority_queue< iPair, vector<iPair>, greater<iPair> >pq;
  if(c == 0){
    cout<<"-1"<<endl;
    return;
  }
  for(long i=0; i<1000000; i++){
    k[i] = INF;
    p[i] = -1;
    checklist[i] = false;
  }
  int weight_of_mst = 0;
  int count = 0;
  if(b[src] != -1){
    //cout<<"hello"<<endl;
    pq.push(make_pair(0, src));
    k[src] = 0;
  }
  int fact_checker = 0;
  priority_queue<iPair, vector<iPair>, greater<iPair> >ex;
  while(!pq.empty()){
    count = count + 1;
    if(count <= c){
      weight_of_mst = weight_of_mst + pq.top().first;
    }
    int v = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    //cout<<checklist[u]<<endl;
    if(checklist[u] == false){
      if(u != src){
        if(p[u] < u){
          //cout<<p[u]<<"---------"<<u<<endl;
          ex.push(make_pair(p[u], u));
        }
        else{
          //cout<<u<<"---------"<<p[u]<<endl;
          ex.push(make_pair(u, p[u]));
        }
      }
      checklist[u] = true;
      fact_checker = fact_checker + 1;
    }
    checklist[u] = true;
    Node* temp = a[u];
    while(temp != NULL){
      if(checklist[temp->id] == false && k[temp->id] > temp->build_time){
        //cout<<"Yes"<<endl;
        k[temp->id] = temp->build_time;
        pq.push(make_pair(k[temp->id], temp->id));
        p[temp->id] = u;
      }
      temp = temp->next;
    }
  }
  if(fact_checker != c){
    //cout<<fact_checker<<" "<<c<<endl;
    cout<<"-1"<<endl;
    return;
  }
  /*
  for(int i=0; i<c; i++){
    if(p[i] == -1 && i != src){
      cout<<"-1"<<endl;
      return;
    }
  }
  */
  /*
  for(int i=0; i<c; i++){
    if(i != src){
      //cout<<"-----"<<endl;
      //cout<<p[i]<<" "<<i<<endl;
      //ex.push(make_pair(p[i], i));
      if(p[i] < i){
        ex.push(make_pair(p[i], i));
      }
      else{
        ex.push(make_pair(i, p[i]));
      }
    }
  }
  */
  //cout<<ex.size()<<"---------------------"<<c<<endl;
  priority_queue<iPair, vector<iPair>, greater<iPair> >temp;
  if(weight_of_mst == 0){
    cout<<"-1"<<endl;
    return;
  }
  printf("%i %i ", c-1, weight_of_mst);
  for(int i=0; i<c; i++){
    if(i != src){
      int first = ex.top().first;
      int second = ex.top().second;
      ex.pop();
      temp.push(make_pair(second, first));
      while(first == ex.top().first && !ex.empty()){
        //cout<<"First Loop"<<endl;
        cout<<"(---"<<ex.size()<<"-----======"<<temp.size()<<"---)"<<endl;
        cout<<"Yes "<<i<<" "<<ex.top().first<<" "<<first<<endl;
        int temp_first = ex.top().first;
        int temp_second = ex.top().second;
        ex.pop();
        temp.push(make_pair(temp_second, temp_first));
        i++;
      }
      while(!temp.empty()){
        //cout<<"finishing"<<endl;
        printf("%i %i ", temp.top().second+1, temp.top().first+1);
        //cout<<"Second one "<<temp.top().second<<" "<<temp.top().first<<endl;
        //cout<<temp.top().second<<" "<<temp.top().first<<endl;
        temp.pop();
      }
      //cout<<"Ex.size() = "<<ex.size()<<" "<<ex.empty()<<endl;
      if(ex.empty()){
        break;
      }
      //cout<<endl;
      //cout<<"--"<<i<<"--"<<endl;
    }
  }
  cout<<endl;
}

int dist[1000000];

int wait_time(int u){
  if(b[u] == 0){
    return 0;
  }
  if(dist[u] < b[u]){
    return(b[u] - dist[u]);
  }
  else if(dist[u]%b[u] == 0){
    return(0);
  }
  else{
    return((int(dist[u]/b[u]) + 1)*b[u] - dist[u]);
  }
}
int storing_parent[1000000];

int printing_path(int j, int count, int extra_parameter){
  count = count + 1;
  if(storing_parent[j] == -2){
    cout<<-1;
    return 1;
  }
  if(storing_parent[j] == -1){
    printf("%i %i %i ",extra_parameter, count, j+1);
    //cout<<"0 ";
    return 0;
  }
  int qwerty = printing_path(storing_parent[j], count, extra_parameter);
  if(qwerty == 0){
    printf("%i ", j+1);
  }
  else{
    return 1;
  }
  return 0;
  //cout<<j<<" ";
}

void minimum_path(int src, int location, int c){
  priority_queue< iPair, vector<iPair>, greater<iPair> >pq;
  for(int i=0; i<1000000; i++){
    dist[i] = INF;
    storing_parent[i] = -2;
  }
  storing_parent[src] = -1;
  pq.push(make_pair(0, src));
  dist[src] = 0;
  while(!pq.empty()){
    int u = pq.top().second;
    pq.pop();
    Node* temp = a[u];
    while(temp != NULL){
      if(u == src){
        if(dist[temp->id] > dist[u] + temp->traverse_time){
          //cout<<"Yes"<<endl;
          storing_parent[temp->id] = u;
          dist[temp->id] = dist[u] + temp->traverse_time;
          pq.push(make_pair(dist[temp->id], temp->id));
        }
      }
      else{
        if(dist[temp->id] > dist[u] + temp->traverse_time + wait_time(u)){
          //cout<<"Yes"<<endl;
          storing_parent[temp->id] = u;
          dist[temp->id] = dist[u] + temp->traverse_time + wait_time(u);
          pq.push(make_pair(dist[temp->id], temp->id));
        }
      }
      temp = temp->next;
    }
  }
  /*
  for(int i=0; i<c; i++){
    cout<<i<<" "<<dist[i]<<endl;
  }
  cout<<"----------"<<endl;
  for(int i=0; i<c; i++){
    cout<<i<<"->  ";
    printing_path(i);
    cout<<endl;
  }
  */
  printing_path(location, 0, dist[location]);
  cout<<endl;
}

int main(){
  /*
  long store = pow(10, 6);
  long c = pow(10, 9);
  int d[c][10];
  int b[c];
  int e = sizeof(d)/sizeof(d[0]);
  int f = sizeof(b)/sizeof(b[0]);
  cout<<e<<" "<<f<<endl;
  int a[2];
  a[0] = 4;
  a[1] = 7;
  hello(a);
  cout<<a[0]<<endl;
*/
  //cout<<"1"<<endl;
  //cout<<"2"<<endl;
  int src = -1;
  for(int i=0; i<1000000; i++){
    a[i] = NULL;
    b[i] = -1;
  }
  int c = -1;
  int v, e, p, q, r, s;
  cin>>v>>e;
  for(int i=0; i<v; i++){
    cin>>p>>q;
    c++;
    add_junction(b, p-1, q);
    if(c == 0){
      src = p-1;
    }
  }
  for(int i=0; i<e; i++){
    cin>>p>>q>>r>>s;
    add_edge(p-1, q-1, r, s);
  }
  //print_graph(b, c);
  //cout<<"Demolish road between?"<<endl;
  //cin>>p>>q;
  //remove_edge(p-1, q-1);
  //print_graph(b, c);
  //printMST(c+1);
  //minimum_path(0, c+1);
  int n;
  cin>>n;
  int option;
  for(int i=0; i<n; i++){
    cin>>option;
    //cout<<"---"<<option<<endl;
    switch(option){
      case 1:{
        int c1, c2;
        cin>>c1>>c2;
        c++;
        if(src == -1){
          src = c1-1;
        }
        add_junction(b, c1-1, c2);
        break;
      }
      case 2:{
        int c1, c2, c3, c4;
        cin>>c1>>c2>>c3>>c4;
        add_edge(c1-1, c2-1, c3, c4);
        break;
      }
      case 3:{
        int c1, c2;
        cin>>c1>>c2;
        remove_edge(c1-1, c2-1);
        break;
      }
      case 4:{
        //cout<<"got to 4"<<endl;
        printMST(c+1,src);
        break;
      }
      case 5:{
        int c1, c2;
        cin>>c1>>c2;
        minimum_path(c1-1, c2-1, c+1);
        break;
      }
      default:{
        cout<<"Option is wrong"<<endl;
      }
    }
  }
}
