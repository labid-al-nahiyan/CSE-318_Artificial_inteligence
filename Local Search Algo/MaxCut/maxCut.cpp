#include<bits/stdc++.h>

using namespace std;

vector<vector<pair<int,int>>> graph;
vector<long long> S, S_;

long long maxCut = LONG_LONG_MIN;

//for output table....................
vector<long long> semi_greedy_output;
vector<long long> greedy_output;
vector<long long> random_output;
vector<long long> local_search_output;
long long iteratonLocal = 0;
//....................................


void SEMI_GREEDY_MAXCUT(double alpha)
{


    if(alpha==-1)
    {
        alpha = ((double) rand() / (RAND_MAX));   // -1 reserve for random semi greedy alpha
    }

    maxCut = LONG_LONG_MIN;

    int w_min = INT_MAX,w_max = INT_MIN;
    long long max_cut = 0;
    vector<pair<long long, pair<long long ,long long >>>edge;

    for(int i = 1;i< graph.size();i++){
        for(pair<int,int> j:graph[i]){
            w_max = max(w_max,j.second);
            w_min = min(w_min,j.second);
            edge.push_back({j.second,{j.first,i}});
        }
    }
   // cout<<w_min<<" "<<w_max<<'\n';
    double mu = w_min + (alpha)*(w_max-w_min);

    sort(edge.begin(),edge.end());

    int index_start;

    long long mx = LONG_LONG_MIN;
    for(int i=0;i<edge.size();i++){
        long long weight = edge[i].first;
        mx = max(mx,weight);
        if(weight >= floor(mu)){

            index_start = i;
            break;

        }
    }

    int random_index = rand()%((edge.size()-1)-index_start +1) + index_start;

    vector<long long>X,Y;
   // std::cout<<edge.size()<<" "<<alpha<<" "<<mu<<" "<<mx<<" "<<index_start<<" "<<random_index<<"\n";
    X.push_back(edge[random_index].second.first);
    Y.push_back(edge[random_index].second.second);
    max_cut += edge[random_index].first;

    vector<int>V_selected(graph.size()+1,0);
    V_selected[X[0]] = 1;
    V_selected[Y[0]] = 2;

    while(X.size()+Y.size() < graph.size()-1){

        vector<long long> sigma_x(graph.size()+1,0),sigma_y(graph.size()+1,0);
        long long weight_min = LONG_LONG_MAX;
        long long weight_max = LONG_LONG_MIN;


        for(int i = 1 ; i < graph.size() ; i++){

            if( V_selected[i] == 0){

                long long sum = 0;
                for(int j = 0; j < X.size() ; j++){
                    for(int k = 0; k< graph[i].size(); k++){
                        if(X[j] == graph[i][k].first){
                            sum += graph[i][k].second;
                            break;
                        }
                    }
                }
                sigma_y[i] = sum;
                sum  = 0;

                for(int j = 0; j < Y.size() ; j++){
                    for(int k = 0; k< graph[i].size(); k++){
                        if(Y[j] == graph[i][k].first){
                            sum += graph[i][k].second;
                            break;
                        }
                    }
                }
                sigma_x[i] = sum;

                weight_max = max(weight_max, sigma_x[i]);
                weight_min = min(weight_min, sigma_x[i]);
            
                weight_max = max(weight_max, sigma_y[i]);
                weight_min = min(weight_min, sigma_y[i]);

            }

        }

        

        double mu = weight_min + alpha*(weight_max-weight_min);

        vector<pair<int,pair<long long , long long>>> RCLv; // { vertix, {sigma_x, sigma_y}}

        for(int i = 1; i < graph.size() ;i++)
        {
            if(V_selected[i] == 0 && max(sigma_x[i],sigma_y[i]) >= mu)
            {
                RCLv.push_back({i,{sigma_x[i],sigma_y[i]}});
            }
        }

        int random_idx;
        if(RCLv.size()!=0)random_idx= rand()%RCLv.size();
        else random_idx = 1;

        int new_node = RCLv[random_idx].first;

        if( RCLv[random_idx].second.first >= RCLv[random_idx].second.second )
        {
            X.push_back(new_node);
            max_cut += RCLv[random_idx].second.first;
            V_selected[new_node] = 1; 
        }
        else
        {
            Y.push_back(new_node);
            max_cut += RCLv[random_idx].second.second;
            V_selected[new_node] = 2; 
        }
        
        

    }

    maxCut = max_cut; 
    S.clear();
    S_.clear();
    S.resize(X.size()),S_.resize(Y.size());
    for(int i = 0; i<X.size() ; i++){
        S[i] = X[i];                    // COPY X to S
    }
    for(int i = 0; i<Y.size() ; i++){
        S_[i] = Y[i];                   // COPY Y to S_
    }


}
void GREEDY_MAXCUT()
{
    SEMI_GREEDY_MAXCUT(1);
}
void RANDOM_MAXCUT()
{
    //SEMI_GREEDY_MAXCUT(0);
    int n = graph.size();
    vector<int>set_split(n+1,0);
    S.resize(0),S_.resize(0);
    for(int i = 1; i<=n  ; i++){
        if(rand()%2==1){
            S.push_back(i);
            set_split[i] = 1;
        }                 
        else{
            S_.push_back(i);
            set_split[i] = 2;
        }
    }
    long long max_cut = 0;
    for(int i= 0;i<S.size();i++){
        for(auto j : graph[i]){
            int node = j.first;
            int weight = j.second;
            if(set_split[node] == 2){
                max_cut += weight;
            }
        }
    }
    maxCut = max_cut;
    
}
void LOCAL_SEARCH_MAXCUT()
{
    int change = 1;
    int iterCount = 0;

    vector<int>set_select(graph.size()+1,0);
    for(int i = 1; i< S.size() ; i++)
    {
        set_select[S[i]] = 1;
    }
    for(int i = 1; i< S_.size() ; i++)
    {
        set_select[S_[i]] = 2;
    }

     while(1)
    //for(int i = 1;i< 100;i++)
    {
        change = 0;
        iterCount++;
        for(int i = 1; i< graph.size() ; i++){

            long long sigma_x = 0, sigma_y = 0;
            for(auto j : graph[i]){
                
                long long weight = j.second, node = j.first;
                if(set_select[node]==1)
                {
                    sigma_x += weight;
                }
                else if(set_select[node]==2)
                {
                    sigma_y += weight;
                }
            }
            if(set_select[i] == 1 && sigma_x >= sigma_y){

                //remove from s to s_
                for(int j = 0 ; j < S.size() ; j++){
                    if( S[j] == i){
                        S.erase(S.begin()+j);
                        S_.push_back(i);
                        set_select[i]==2;
                        maxCut += sigma_x-sigma_y;
                        change = 1;
                        break;
                    }
                }
            }
            else if(set_select[i] == 2 && sigma_y >= sigma_x){
                //remove from s_ to s
                

                for(int j = 0 ; j < S_.size() ; j++){
                    if( S_[j] == i){
                        S_.erase(S_.begin()+j);
                        S.push_back(i);
                        set_select[i]==1;
                        maxCut += sigma_y-sigma_x;
                        change = 1;
                        break;
                    }
                }
            }
        }

        if(!change)break;
    }

    iteratonLocal+=iterCount;
}
long long GRASP(int maxIteration)
{
    long long maximum = LONG_LONG_MIN;

    for(int i = 1 ;i<= maxIteration; i ++){

        SEMI_GREEDY_MAXCUT(-1);
        //for output table
        semi_greedy_output.push_back(maxCut);
        //.................
        LOCAL_SEARCH_MAXCUT();
        //for output table
        local_search_output.push_back(maxCut);

        if(maximum < maxCut){
            maximum = maxCut;
        }
    }
    return maximum;
}
long long GREEDY_LOCAL(int maxIteration)
{
    long long maximum = LONG_LONG_MIN;

    for(int i = 1 ;i<= maxIteration; i ++){

        GREEDY_MAXCUT();
        //for output table
        greedy_output.push_back(maxCut);
        //.................
        LOCAL_SEARCH_MAXCUT();
        //for output table
        local_search_output.push_back(maxCut);

        if(maximum < maxCut){
            maximum = maxCut;
        }
    }
    return maximum;
}
long long Random_LOCAL(int maxIteration)
{
    long long maximum = LONG_LONG_MIN;

    for(int i = 1 ;i<= maxIteration; i ++){

        RANDOM_MAXCUT();
        //for output table
        random_output.push_back(maxCut);
        //.................
        LOCAL_SEARCH_MAXCUT();
        //for output table
        local_search_output.push_back(maxCut);

        if(maximum < maxCut){
            maximum = maxCut;
        }
    }
    return maximum;
}


int main()
{
    srand(time(0));

    int n,e;
    ofstream ofs;
    ofs.open("result.csv",ios::out | ios::app);

    
    for(int  i = 25;i<=54;i++){ 

        
        string myText, sss = "../g";
        string num = to_string(i);
        string no = ".rud";
        sss = sss+num+no;
        std::cout<<sss<<'\n';

        ifstream MyReadFile(sss);

        getline (MyReadFile, myText);

        vector<string>tokens;
        stringstream ss(myText);
        string word;
        while (ss >> word) {
            tokens.push_back(word);
        }
        n = stoi(tokens[0]);
        e = stoi(tokens[1]);

        tokens.clear();
        

        graph.resize(n+1);
        for(int i=0;i<e;i++){
            int v,u,w;

            if(!(getline (MyReadFile, myText))){
                std::cout<<"File Read Error\n";
            }
            stringstream ss(myText);
            while (ss >> word) {
                tokens.push_back(word);
            }
            v = stoi(tokens[0]);
            u = stoi(tokens[1]);
            w = stoi(tokens[2]);
            tokens.clear();

            graph[v].push_back({u,w});
            graph[u].push_back({v,w});        
        }  
        MyReadFile.close();


        long long maximum ;
        // GRASP(15);   
        //GREEDY_LOCAL(15);
        Random_LOCAL(15);


        //for output table..................

        long long randomSum = 0;
        for(auto i:random_output)randomSum+=i;
        long long randomMax = randomSum / random_output.size();
        random_output.clear();

        long long greedySum = 0;
        for(auto i:greedy_output)greedySum+=i;
        long long greedyMax = greedySum / greedy_output.size();
        greedy_output.clear();

        long long semiGreedySum = 0;
        for(auto i:semi_greedy_output)semiGreedySum+=i;
        long long semiGreedyMax = semiGreedySum / semi_greedy_output.size();
        semi_greedy_output.clear();

        long long localSum = 0;                                         
        for(auto i:local_search_output)localSum += i;
        long long localMax = localSum / local_search_output.size();      
        long long meanLocalIteration = iteratonLocal / local_search_output.size();
        local_search_output.clear();

        iteratonLocal = 0;
        graph.clear();
        S.clear(),S_.clear();

        std::cout<<n<< " "<< e << " "<< randomSum << " "<< greedyMax<< " "<< semiGreedyMax << " "<< meanLocalIteration<<" " <<localMax<<" "<<20<< " "<< maximum<<"\n";
        ofs<<i<<","<<n<<","<<e<<","<<randomSum<<","<<greedyMax<<","<<semiGreedyMax<<","<<meanLocalIteration<<","<<localMax<<","<<20<<","<<maximum<<'\n';
    }

}