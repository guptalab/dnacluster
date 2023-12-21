#include <iostream>
// #include <stdio.h>

using namespace std;

const int inf=1e9;
const int Reads_set_size = 4;    //A-T-G-C
int thresold = 0;     //thresold error

int dp_matrix[200][200];
int st[200],en[200];


// trie node
struct TrieNode
{
    struct TrieNode *children[Reads_set_size];
    int EndOfWord=-1;      //Vector storing all the indices of strings which ends over here (Taking vector because some duplicate words might be present)
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
    for (int i = 0; i < Reads_set_size; i++)
        pNode->children[i] = NULL;

    pNode->EndOfWord=-1;

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

    pNode->EndOfWord=index_of_str;
}

int current_read;

void make_edges_lexi_lower(struct TrieNode *root, string &key,int pos,bool str_path)
{
    struct TrieNode *pNode = root;

    if(st[pos]<=key.size() && key.size()<=en[pos] && dp_matrix[pos][key.size()]<=thresold)
    {
        if(pNode->EndOfWord!=-1)
        {
            // cout << dp_matrix[pos][key.size()] << ' ' << pNode->EndOfWord+1 << ' ' << current_read+1 << "\n";       //making it 1 based.
        }
    }

    int upto = Reads_set_size-1;
    if(str_path) upto=key[pos]-'0' - (pos+1==key.size());

    for (int index = 0; index <= upto; index++)
    {
        if (!pNode->children[index])
            continue;

        dp_matrix[pos+1][st[pos]]=dp_matrix[pos][st[pos]]+1;
    
        for(int ii=st[pos]+1;ii<en[pos]+1;ii++)
            dp_matrix[pos+1][ii]=min(min(dp_matrix[pos][ii]+1,dp_matrix[pos+1][ii-1]+1),dp_matrix[pos][ii-1]+(index!=(key[ii-1]-'0')));      //levenstein distance
        
        if(en[pos]!=200-1)
            dp_matrix[pos+1][en[pos]+1]=min(dp_matrix[pos+1][en[pos]]+1,dp_matrix[pos][en[pos]+1-1]+(index!=(key[en[pos]+1-1]-'0')));

        int stt=min(200,en[pos]+2);
        bool possible_path=0;
        
        for(int ii=st[pos];ii<min(200,en[pos]+2);ii++)
        {
            if(dp_matrix[pos+1][ii]<=thresold)
            {
                stt=ii;
                possible_path=1;
                break;
            }
            dp_matrix[pos+1][ii]=inf;
        }

        if(!possible_path)
            continue;

        st[pos+1]=stt;

        for(int ii=min(200,en[pos]+2)-1;ii>=st[pos];ii--)
        {
            if(dp_matrix[pos+1][ii]<=thresold)
            {
                en[pos+1]=ii;
                break;
            }
            dp_matrix[pos+1][ii]=inf;
        }

        make_edges_lexi_lower(pNode->children[index],key,pos+1,str_path&(index==upto));
    }

    return;
}

int main(int argc, char *argv[])
{
    // if (argc != 3) {
    //     fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
    //     return 1;
    // }

    // FILE *input_file = fopen(argv[1], "r");
    // if (!input_file) {
    //     fprintf(stderr, "Error opening input file: %s\n", argv[1]);
    //     return 1;
    // }

    // FILE *output_file = fopen(argv[2], "w");
    // if (!output_file) {
    //     fprintf(stderr, "Error opening output file: %s\n", argv[2]);
    //     fclose(input_file);
    //     return 1;
    // }


    int start_=70;
    int end_=70;

    int n;

    TrieNode *Rs = getNode();
    
    string inputReads[72000];   ///assuming max 72000 reads
    string str_new;
    int max_str_len=0;
    int nodeid,grp;

    cin>>n;
    for(int i=0;i<n;i++)
    {   
        str_new.clear();
        cin>>nodeid >> grp>>str_new;
        max_str_len=max(max_str_len,(int)str_new.size());

        for(char &ch : str_new)
        {
            // ch = mapper[ch];
            if(ch=='A')
                ch='0';
            else if(ch=='T')
                ch='1';
            else if(ch=='G')
                ch='2';
            else if(ch=='C')
                ch='3';
        }
        inputReads[i]=str_new;

        insert_in_trie(Rs,inputReads[i],i);
    }
    cerr << "input taken\n";

    for(int thrr=start_;thrr<=end_;thrr++)
    {
    thresold = thrr;

    for(int i=0;i<max_str_len+1;i++)
        for(int j=0;j<max_str_len+1;j++)
            dp_matrix[i][j]=inf;
    
    for(int i=0;i<200;i++) dp_matrix[i][0]=i;
    for(int i=0;i<200;i++) dp_matrix[0][i]=i;

    st[0]=0;
    en[0]=thresold;

    cerr << "initialization complete\n";
    cout << "weight,node1,node2\n";     //for csv file

    for(int i=0;i<n;i++)
    {
        current_read=i;
        cerr << i+1 << "\n\n";
        make_edges_lexi_lower(Rs,inputReads[i],0,1);          ///making edges for lexicographically lower edges.
    }
    cerr << "complete, now printing\n";           
    }

    // fclose(input_file);
    // fclose(output_file);

    return 0;
}