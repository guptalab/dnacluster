#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> edit_distance(string str1,string str2)
{
    vector<vector<int>> dp(str1.size()+1,vector<int>(str2.size()+1));

    for(int i=0;i<=str1.size();i++)
        dp[i][0]=i;

    for(int i=0;i<=str2.size();i++)
        dp[0][i]=i;

    for(int i=0;i<str1.size();i++)
    {
        for(int j=0;j<str2.size();j++)
        {
            dp[i+1][j+1]=min({dp[i][j+1]+1,dp[i+1][j]+1,dp[i][j]+(str1[i]!=str2[j])});
        }
    }

    return dp;
}

signed main()
{
    // string str1;
    // string str2;
    // fast;

    // string output_path = path_to_store + "Graph_generated" + ".txt";

    // string input_path = "Reads_example.txt";
    string input_path = "D:\\daiict\\DNA_clusturing_New_Algorithm\\datasets\\ERR1816980\\ERR1816980_converted.txt";
    string output_path = "D:\\daiict\\DNA_clusturing_New_Algorithm\\datasets\\ERR1816980\\edges.csv";

	#ifndef ONLINE_JUDGE
        freopen(input_path.c_str(), "r", stdin);
        freopen(output_path.c_str(), "w", stdout);
        freopen("error.txt", "w", stderr);
    #endif

	int n,not_used;
	vector<string> strs;
	string nnew;

    cin>>n;
	int which_min=0,anss=1e9;
	for(int i=0;i<n;i++)
	{
		nnew.clear();
		cin>>not_used>>not_used>>nnew;
		strs.push_back(nnew);
	}

	for(int i=1;i<n;i++)
	{
    	vector<vector<int>> mat=edit_distance(strs[0],strs[i]);
        // cout << mat[mat.size()-1][mat[0].size()-1] << "\n";
		if(anss>mat[mat.size()-1][mat[0].size()-1])
		{
			anss=mat[mat.size()-1][mat[0].size()-1];
			which_min=i;
		}
	}

	cout << anss << ' ' << which_min << "\n";

    // for(int i=0;i<mat.size();i++)
    // {
    //     for(int j=0;j<mat[i].size();j++)
    //         cout << setw(5) <<  mat[i][j];
    //     cout << '\n';
    // }

    return 0;
}















// // C++ implementation of search and insert
// // operations on Trie
// #include <bits/stdc++.h>
// using namespace std;

// const int ALPHABET_SIZE = 26;

// // trie node
// struct TrieNode
// {
// 	struct TrieNode *children[ALPHABET_SIZE];

// 	// isEndOfWord is true if the node represents
// 	// end of a word
// 	bool isEndOfWord;
// };

// // Returns new trie node (initialized to NULLs)
// struct TrieNode *getNode(void)
// {
// 	struct TrieNode *pNode = new TrieNode;

// 	pNode->isEndOfWord = false;

// 	for (int i = 0; i < ALPHABET_SIZE; i++)
// 		pNode->children[i] = NULL;

// 	return pNode;
// }

// // If not present, inserts key into trie
// // If the key is prefix of trie node, just
// // marks leaf node
// void insert(struct TrieNode *root, string key)
// {
// 	struct TrieNode *pCrawl = root;

// 	for (int i = 0; i < key.length(); i++)
// 	{
// 		int index = key[i] - 'a';
// 		if (!pCrawl->children[index])
// 			pCrawl->children[index] = getNode();

// 		pCrawl = pCrawl->children[index];
// 	}

// 	// mark last node as leaf
// 	pCrawl->isEndOfWord = true;
// }

// // Returns true if key presents in trie, else
// // false
// bool search(struct TrieNode *root, string key)
// {
// 	struct TrieNode *pCrawl = root;

// 	for (int i = 0; i < key.length(); i++)
// 	{
// 		int index = key[i] - 'a';
// 		if (!pCrawl->children[index])
// 			return false;

// 		pCrawl = pCrawl->children[index];
// 	}

// 	return (pCrawl->isEndOfWord);
// }

// // Driver
// int main()
// {
// 	// Input keys (use only 'a' through 'z'
// 	// and lower case)
// 	string keys[] = {"the", "a", "there",
// 					"answer", "any", "by",
// 					"bye", "their" };
// 	int n = sizeof(keys)/sizeof(keys[0]);

// 	struct TrieNode *root = getNode();

// 	// Construct trie
// 	for (int i = 0; i < n; i++)
// 		insert(root, keys[i]);

// 	// Search for different keys
// 	char output[][32] = {"Not present in trie", "Present in trie"};

// 	// Search for different keys
// 	cout<<"the"<<" --- "<<output[search(root, "the")]<<endl;
// 	cout<<"these"<<" --- "<<output[search(root, "these")]<<endl;
// 	cout<<"their"<<" --- "<<output[search(root, "their")]<<endl;
// 	cout<<"thaw"<<" --- "<<output[search(root, "thaw")]<<endl;
// 	return 0;
// }
