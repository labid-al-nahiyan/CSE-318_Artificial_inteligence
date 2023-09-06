#include<bits/stdc++.h>

using namespace std;

//entropy count > 1

// --class values

// unacc, acc, good, vgood

// --attributes
// buying:   vhigh, high, med, low....0
// maint:    vhigh, high, med, low....1
// doors:    2, 3, 4, 5more...........2
// persons:  2, 4, more...............3
// lug_boot: small, med, big..........4
// safety:   low, med, high...........5
int attribute_value[6] = {4,4,4,3,3,3};

vector<vector<int>>givenData;
vector<vector<int>>trainingData;
vector<vector<int>>testData;

struct Node
{
    map<int,Node*> child;
    bool isLeaf;
    int value;
    int attribute;
};
void input()
{
    std::ifstream ifs;

    ifs.open ("car.data", std::ifstream::in);

    string str;

    while (getline(ifs,str)) {        
        stringstream ss(str);
        vector<string>v;
        vector<int>a;

        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            v.push_back(substr);
        }
        for(int i = 0 ; i < v.size() ; i++){
            if(i==0 || i==1){
                if(v[i]=="vhigh")a.push_back(1);
                if(v[i]=="high")a.push_back(2);
                if(v[i]=="med")a.push_back(3);
                if(v[i]=="low")a.push_back(4);
            }
            else if(i==2){
                if(v[i]=="2")a.push_back(1);
                if(v[i]=="3")a.push_back(2);
                if(v[i]=="4")a.push_back(3);
                if(v[i]=="5more")a.push_back(4);
            }
            else if(i==3){
                if(v[i]=="2")a.push_back(1);
                if(v[i]=="4")a.push_back(2);
                if(v[i]=="more")a.push_back(3);
            }
            else if(i==4){
                if(v[i]=="small")a.push_back(1);
                if(v[i]=="med")a.push_back(2);
                if(v[i]=="big")a.push_back(3);
            }
            else if(i==5){
                if(v[i]=="low")a.push_back(1);
                if(v[i]=="med")a.push_back(2);
                if(v[i]=="high")a.push_back(3);
            }
            else if(i==6){
                if(v[i]=="unacc")a.push_back(1);
                if(v[i]=="acc")a.push_back(2);
                if(v[i]=="good")a.push_back(3);
                if(v[i]=="vgood")a.push_back(4);
            }
        }
      
        givenData.push_back(a);
    }
    ifs.close();

}
void divideInput(int suffle)
{
    if(suffle){
        std::random_device rd;
        std::mt19937 rng(rd());
        std::shuffle(std::begin(givenData), std::end(givenData), rng);
    }

    int bound = floor(0.8*givenData.size());
    for(int i=0;i<bound;i++){
        trainingData.push_back(givenData[i]);
    }
    for(int i = bound;i<givenData.size();i++){
        testData.push_back(givenData[i]);
    }

}
double entropy(vector<vector<int>>example){
    vector<int> classCount(4,0);

    for(int i  = 0; i < example.size() ; i++){
        classCount[example[i][6]-1]++;   
    }
    
    int total = example.size();
    double entropy = 0;
    
    for(int i = 0; i< classCount.size() ; i++ ){
       if(classCount[i]!=0) entropy += (1.0*classCount[i]/total)*log2(1.0*total/classCount[i]);
    }
   // cout<<"Entropy : "<<entropy<<'\n';
    return entropy;
}
double Remainder(vector<vector<int>>example , int attNo)
{
    int x = attribute_value[attNo];
    int table[x+1][5];
    for(int i = 0;i<=x;i++){
        for(int j=0;j<=4;j++){
            table[i][j] = 0;
        }
    }

    for(int i = 0 ; i < example.size() ; i++){
        table[example[i][attNo]][example[i][6]]++;
    }

    double remainder = 0.0;
    int total = example.size();
    for(int i = 1 ; i<= x ; i++) {
        int n = table[i][4]+table[i][1]+table[i][2]+table[i][3];
        double weight = (1.0*n/total);  
        double entropy = 0.0;
        for(int j = 1; j <= 4 ; j++ ){
            if(table[i][j]!=0){
                entropy += (1.0*table[i][j]/n)*log2((1.0*n)/table[i][j]);
            }
        }
        remainder+= weight*entropy;
    }
   // cout<<"Remainder : " <<remainder<<'\n';
    return remainder;
}

int plurality_value(vector<vector<int>> example)
{
    int table[4] = {0};
    int value;
    int mx = 0;

    for(int i = 0 ; i < example.size() ; i++){
        table[example[i][6]]++;
        if(table[example[i][6]]>mx){
            mx = table[example[i][6]];
            value = example[i][6];
        }
    }
    return value;
}

void DecisionTreeBuild(vector<vector<int>>example, vector<int>attribute , vector<vector<int>>parentExample , struct Node* parent)
{   

    if(example.size()==0){
        //Plurality_value(parent_example)
        int value = plurality_value(parentExample);
        parent->isLeaf = true;
        parent->value = value;
        return;
    }
    double entpy = entropy(example);
    if(entpy == 0){  
        int table[5] = {0};
        int value = example[0][6];
        
        parent->isLeaf = true;
        parent->value = value; 
        
        return ;
    }
    int att = 0;
    for(int i = 0;i< attribute.size() ; i++){
        if(attribute[i]==1){
            att = 1;
            break;
        }
    }
    if(att == 0){
        //plurality_value(example)
        int value = plurality_value(example);
        parent->isLeaf = true;
        parent->value = value;
        return;
    }

    double maxGain = -1;
    int root = -1;

    for(int i = 0;i< attribute.size() ; i++){
        if(attribute[i]==1){
            double remainder = Remainder(example,i);
            double gain = entpy-remainder;

            if(gain > maxGain){
                maxGain = gain ;
                root = i;
            }
        
        }   
    }
    attribute[root] = 0;
    parent->attribute = root+1;
    for(int i = 0; i < attribute_value[root] ; i++){
        Node *node = new Node;
        parent->child[i+1] = node;
        node->isLeaf = false;
        vector<vector<int>>node_example;
        for(int j = 0; j < example.size() ; j++){
           if( example[j][root] == i+1){
                node_example.push_back(example[j]);
                
           }
        }  
 
        DecisionTreeBuild(node_example, attribute, example , node);
    }
 
    return;
}


void DecisionTreeApply(vector<vector<int>>test , Node *parent)
{
    int match = 0;
    for(int i = 0; i < test.size() ; i++){
        Node *node = parent;
        int clas = test[i][6],ans = -1;
        while(node->isLeaf!=true){
            int att = (node->attribute)-1;
            int value = test[i][att];
            node = node->child[value];
        }   
        ans = node->value;
        if(clas==ans)match++;
        
    }
    cout<<(1.0*match)*100/test.size()<<'\n';
    
}


int main()
{
    input();
    divideInput(1);

    Node *root = new Node;
    vector<int>attribute(6,1);

    DecisionTreeBuild(trainingData,attribute,trainingData,root);
    DecisionTreeApply(testData,root);

}