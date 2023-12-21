#include <bits/stdc++.h>
using namespace std;

#define fast            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)

const int inf=1e9;
const int Reads_set_size = 4;    //A-T-G-C
int thresold = 0;     //thresold error

vector<pair<int,pair<int,int>>> Edges;      ///{weight,{node1,node2}}

vector<vector<int>> dp_matrix;
vector<int> st,en;

vector<char> rev_map = {'A','T','G','C'};

// trie node
struct TrieNode
{
    struct TrieNode *children[Reads_set_size];
    vector<int> EndOfWord;      //Vector storing all the indices of strings which ends over here (Taking vector because some duplicate words might be present)
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
    for (int i = 0; i < Reads_set_size; i++)
        pNode->children[i] = NULL;

    pNode->EndOfWord.clear();

    return pNode;
}

//Function to insert a string in trie.
void insert_in_trie(struct TrieNode *root,const string &key,int index_of_str)
{
    struct TrieNode *pNode = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - '0';

        if (!pNode->children[index])
            pNode->children[index] = getNode();
 
        pNode = pNode->children[index];
    }

    pNode->EndOfWord.push_back(index_of_str);
}

bool search_in_trie(struct TrieNode *root, string key)
{
    struct TrieNode *pNode = root;
 
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - '0';
        if (!pNode->children[index])
            return false;
 
        pNode = pNode->children[index];
    }

    return true;
}

void make_edges_for_same_read(struct TrieNode *root)
{
    struct TrieNode *pNode = root;

    for(int i=0;i<pNode->EndOfWord.size();i++)
    {
        for(int j=i+1;j<pNode->EndOfWord.size();j++)
        {
            Edges.push_back({0,{i+1,j+1}});
            // cerr << "edge : " << i+1 << " " << j+1 << "\n";
        }
    }
    
    for (int index = 0; index < Reads_set_size; index++)
    {
        if (!pNode->children[index])
            continue;
        
        make_edges_for_same_read(pNode->children[index]);
    }
    return;
}

int current_read;

void make_edges_lexi_lower(struct TrieNode *root, string &key,int pos,bool str_path)
{
    struct TrieNode *pNode = root;

    // if(current_read==1)
    // {
    //     cerr << "pos : " << pos << " st[pos] : " << st[pos] << " en[pos] : " << en[pos] << "\n";
    //     for(int ii=0;ii<dp_matrix.size();ii++)
    //     {
    //         for(int jj=0;jj<dp_matrix[ii].size();jj++)
    //         if(dp_matrix[ii][jj]==inf)
    //             cerr << setw(5) << "-" << ' ';
    //         else
    //             cerr << setw(5) << dp_matrix[ii][jj] << ' ';
    //         cerr << "\n";
    //     }
    //     cerr << "\n";        
    // }
    
    if(st[pos]<=key.size() && key.size()<=en[pos] && dp_matrix[pos][key.size()]<=thresold)
    {
        for(int read_ended_here : pNode->EndOfWord)
        {
            Edges.push_back({dp_matrix[pos][key.size()],{read_ended_here+1,current_read+1}});       //making it 1 based.
            // cerr << "edge : " << read_ended_here+1 << " " << current_read+1 << "\n";

            // for(int ii=0;ii<dp_matrix.size();ii++)
            // {
            //     for(int jj=0;jj<dp_matrix[ii].size();jj++)
            //     if(dp_matrix[ii][jj]==inf)
            //         cerr << setw(5) << "-" << ' ';
            //     else
            //         cerr << setw(5) << dp_matrix[ii][jj] << ' ';
            //     cerr << "\n";
            // }
            // cerr << "\n";
        }
    }

    int upto = Reads_set_size-1;
    if(str_path) upto=key[pos]-'0' - (pos+1==key.size());

    for (int index = 0; index <= upto; index++)
    {
        if (!pNode->children[index])
            continue;
        
        // cerr << rev_map[index] << '\n';

        dp_matrix[pos+1][st[pos]]=dp_matrix[pos][st[pos]]+1;

        for(int ii=st[pos]+1;ii<en[pos]+1;ii++)
            dp_matrix[pos+1][ii]=min({dp_matrix[pos][ii]+1,dp_matrix[pos+1][ii-1]+1,dp_matrix[pos][ii-1]+(index!=(key[ii-1]-'0'))});      //levenstein distance
        
        if(en[pos]!=(int)dp_matrix[pos].size()-1)
            dp_matrix[pos+1][en[pos]+1]=min({dp_matrix[pos+1][en[pos]]+1,dp_matrix[pos][en[pos]+1-1]+(index!=(key[en[pos]+1-1]-'0'))});

        int stt=min((int)dp_matrix[pos].size(),en[pos]+2);
        bool possible_path=0;
        
        for(int ii=st[pos];ii<min((int)dp_matrix[pos].size(),en[pos]+2);ii++)
        {
            // if(current_read==1)
            // {
            //     cerr << "ii : " << ii << " dp_matrix[pos+1][ii] : " << dp_matrix[pos+1][ii] << "\n";
            // }

            if(dp_matrix[pos+1][ii]<=thresold)
            {
                stt=ii;
                possible_path=1;
                break;
            }
            dp_matrix[pos+1][ii]=inf;
        }

        // if(current_read==1)
        // {
        //     cerr << "stt : " << stt << "\n";
        // }

        if(!possible_path)
            continue;

        st[pos+1]=stt;

        for(int ii=min((int)dp_matrix[pos].size(),en[pos]+2)-1;ii>=st[pos];ii--)
        {
            if(dp_matrix[pos+1][ii]<=thresold)
            {
                en[pos+1]=ii;
                break;
            }
            dp_matrix[pos+1][ii]=inf;
        }

        // for(int ii=0;ii<7;ii++)
        // {
        //     for(int jj=0;jj<7;jj++)
        //         cerr << dp_matrix[ii][jj] << ' ';
        //     cerr << "\n";
        // }
        // cerr << "\n";


        make_edges_lexi_lower(pNode->children[index],key,pos+1,str_path&(index==upto));
    }

    return;
}


// Next step is to implement pocuet search inside this (you can use some poucet search code(clover etc.)).

int main(int argc, char* argv[])
{
    fast;

    // string output_path = path_to_store + "Graph_generated" + ".txt";

    // string input_path = "Reads_example.txt";
    string input_path = "D:\\daiict\\DNA_clusturing_New_Algorithm\\datasets\\ERR1816980\\ERR1816980_converted.txt";
    // string output_path = "D:\\daiict\\DNA_clusturing_New_Algorithm\\datasets\\ERR1816980\\edges.csv";
    string output_path = "D:\\daiict\\DNA_clusturing_New_Algorithm\\datasets\\ERR1816980\\edges_generated\\thresold_" + string(argv[1]) + ".csv";

    string Time_tkane_path = "D:\\daiict\\DNA_clusturing_New_Algorithm\\datasets\\ERR1816980\\edges_generated\\Time_taken.txt";

    #ifndef ONLINE_JUDGE
        freopen(input_path.c_str(), "r", stdin);
        freopen(output_path.c_str(), "w", stdout);
        freopen("error.txt", "w", stderr);

        ofstream time_output(Time_tkane_path, std::ios::app);
    #endif

    thresold = stoi(argv[1]);
    auto begin = std::chrono::high_resolution_clock::now();

    int n;

    cin>>n;

    // vector<string> Reads(n);

    TrieNode *Rs = getNode();   //Root of the Trie.
    vector<string> inputReads;
    string str_new;
    map<char,char> mapper = {{'A','0'},{'T','1'},{'G','2'},{'C','3'}};      //Mapping [A,T,G,C] with [0-3]

    ///Taking input strings - converting it into [0-3] format, also storing it into trie.
    int max_str_len=0;
    int nodeid,grp;

    for(int i=0;i<n;i++)
    {   
        str_new.clear();
        cin>>nodeid >> grp>>str_new;
        max_str_len=max(max_str_len,(int)str_new.size());

        for(char &ch : str_new)
            ch = mapper[ch];

        inputReads.push_back(str_new);
        // cerr << str_new << "\n";

        insert_in_trie(Rs,inputReads[i],i);
    }
    cerr << "input taken\n";

    make_edges_for_same_read(Rs);       ///making edges for the same reads 
    cerr << "same reads connected\n";

    ///From here Poucet Search !!!

    dp_matrix.resize(max_str_len+1,vector<int>(max_str_len+1,inf));
    for(int i=0;i<dp_matrix.size();i++) dp_matrix[i][0]=i;
    for(int i=0;i<dp_matrix[0].size();i++) dp_matrix[0][i]=i;
    st.resize(max_str_len+1);
    en.resize(max_str_len+1);
    st[0]=0;
    en[0]=thresold;

    cerr << "initialization complete\n";

    for(int i=0;i<n;i++)
    {
        current_read=i;
        // cerr << i+1 << " \n";
        make_edges_lexi_lower(Rs,inputReads[i],0,1);          ///making edges for lexicographically lower edges.
    }
    cerr << "complete, now printing\n";

    // cout << "weight node1 node2\n";
    cout << "weight,node1,node2\n";     //for csv file

    for(auto edge : Edges)
    {
        // cout << setw(3) << edge.first << setw(3) << edge.second.first << setw(3) << edge.second.second << "\n";
        cout << edge.first << "," << edge.second.first << "," << edge.second.second << "\n";     //for csv file
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    
    cerr << "Time measured: " << (elapsed.count() * 1e-9) << " seconds.\n";
    time_output << setw(10) << thresold << setw(10) << (elapsed.count() * 1e-9) << setw(10) << Edges.size() << "\n";

    return 0;
}